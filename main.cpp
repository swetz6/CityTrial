//
// main.cpp
// Final Project - Kart Part Park
// 
// Created by Bryan Bell, Eric Johnson, Mustafa, Chirs Pauley
// Date Created: 1/25/13
//
// For CSC476 - Real Time 3D Rendering

#include <GL/glfw.h>

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "GLSL_helper.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr
#include "MStackHelp.h"

//-----------------------------------------------
// These are global state machines: 
// "physics_sim"-
//  Controls the movement and collisions of 
//   objects and as such each object will have a
//   pointer to an object of class type 
//   KPPPhysics::Actor which will control various
//   states of the object such as position
// "mesh_loader"-
//  This is a class I will make using my .obj 
//   loader code. It is passed, along with the
//   file name of the .obj file, to the 
//   KPPDrawnObject constructor.
// "shader"-
//  Shader object for the entire program. Pointer
//   is passed to "mesh_loader" and should not be
//   tampered with after that unless to change 
//   shader for all objects.
// "model_trans"-
//  This is the model-view translation matrix,
//   we might not need this given objects' 
//   independence from one another when drawn.
// NOTE: These objects should be the only of 
//  their type for the entire program. When 
//  initializing other objects please pass a 
//  pointer to these objects and do NOT create
//  duplicates.
//-----------------------------------------------
KPPPhysics *physics_sim;
KPPMeshLoader *mesh_loader;
KPPShader *shader;
RenderingHelper *model_trans;

vector<KPPObject *> moving_objects;
vector<KPPDrawnObject *> drawn_objects;
vector<KPPKartObject *> kart_objects;

int g_w_wdth, g_w_hgt;
double g_last_time;

void update(double deltaTime)
{
	for each (KKPKartObject kart in kart_objects) {
		kart->update();
	}
}

//-----------------------------------------------
// This function initializes geometry from a 
//  geometry file "geometry_loader", which has 
//  has the format:
//  (type) (.obj file) (type specific data) ...
//-----------------------------------------------
void initGeometry()
{
	ifstream in("geometry_loader", ios::in);
	if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }
	
	string line;
   while (getline(in, line)) {
		istringstream s(line);
		
		char type;
		type << s;
		
		string meshFile;
		meshFile << s;
		
		switch (type) {
			case: "d"
				KPPDrawnObject *object = new KPPDrawnObject(mesh_loader, physics_sim, meshFile.c_str());
				//Any initialization from type specific data in file
				drawn_objects.push_back(object);
				moving_objects.push_back(object);
				break;
			case: "k"
				KKPKartObject *object = new KPPKartObject(mesh_loader, physics_sim, meshFile.c_str());
				if (glfwGetJoystickParam(kart_objects.size(), GLFW_PRESENT) == GL_TRUE) {
					printf("Controller Connected for Player %d\n", kart_objects.size());
				}
				//Any initialization from type specific data in file
				kart_objects.push_back(object);
				drawn_objects.push_back(object);
				moving_objects.push_back(object);
				break;
			default:
				cerr << "ERROR: Inproper Type Declared in Geometry Loader File\n";
				exit(0);
		}
	}
}

void draw()
{
	for each (KKPDrawnObject object in drawn_objects) {
		object->draw(model_trans);
	}
}

void gameLoop(double deltaTime)
{
	update(deltaTime);
	draw();
}

void initialize()
{
	/* Start OpenGL Initialization */
   glClearColor (0.8f, 0.8f, 1.0f, 1.0f);
   // Black Background
   glClearDepth (1.0f);    // Depth Buffer Setup
   glDepthFunc (GL_LEQUAL);    // The Type Of Depth Testing
   glEnable (GL_DEPTH_TEST);// Enable Depth Testing
   /* texture specific settings */
   glEnable(GL_TEXTURE_2D);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   
   model_trans.useModelViewMatrix();
   model_trans.loadIdentity();
   /* End OpenGL Initialization */
   
   /* Start Shader Initialization 
   if (!InstallShader(textFileRead((char *)"tex_vert.glsl"), textFileRead((char *)"tex_frag.glsl"))) {
      printf("Error installing shader!\n");
      return;
   }
   /* End Shader Initialization */
   
   shader = new PhongShader();
   mesh_loader = new KPPMeshLoader(shader, model_trans);
   
   initGeometry();
}

void reshape(int width, int height)
{
	g_w_wdth = width;
	g_w_hgt = height;
}

int main(int argc, char** argv) 
{
	g_w_wdth = 640;
	g_w_hgt = 480;
	
   if (glfwInit() == GL_TRUE) {
    	glfwOpenWindow(w_wdth, w_hgt, 0, 0, 0, 0, 16, 0, GLFW_WINDOW);
    	glfwSetWindowSizeCallback( reshape );
    }
    	
   initialize();
   
   glfwSetTime(0.0);
    	
   while (glfwGetWindowParam(GLFW_OPENED)) {
   		double time = glfwGetTime();
	
    	gameLoop(time - g_last_time);
    	g_last_time = time;   	
   }
    
   glfwTerminate();
}
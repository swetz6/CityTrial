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

KPPPhysics *physics_sim;
RenderingHelper model_trans;

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
				drawn_objects.push_back(object);
				moving_objects.push_back(object);
				break;
			case: "k"
				KKPKartObject *object = new KPPKartObject(mesh_loader, physics_sim, meshFile.c_str());
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
		object->draw();
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
   
   /* Start Shader Initialization */
   if (!InstallShader(textFileRead((char *)"tex_vert.glsl"), textFileRead((char *)"tex_frag.glsl"))) {
      printf("Error installing shader!\n");
      return;
   }
   /* End Shader Initialization */
   
   initGeometry();
	
	if (glfwGetJoystickParam(GLFW_JOYSTICK_1, GLFW_PRESENT) == GL_TRUE) {
		printf("Number of Axes: %d\n", glfwGetJoystickParam(GLFW_JOYSTICK_1, GLFW_AXES));
		printf("Number of Buttons: %d\n", glfwGetJoystickParam(GLFW_JOYSTICK_1, GLFW_BUTTONS));
	}
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
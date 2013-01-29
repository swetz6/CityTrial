//
// KPPMeshManager.cpp
// Final Project - Kart Part Park
// 
// Created by Bryan Bell
// Date Created: 1/25/13
//
// The KPPMeshManager class is directly responsible
//  for managing meshes needed in runtime for 
//  drawing.
//
// For CSC476 - Real Time 3D Rendering

#include "ModelManager.h"

ModelManager::ModelManager()
{
   
}

ModelManager::~ModelManager()
{
   for (int i = 0; i < (int)storage.size(); i++) {
      delete[] storage[i].indexBuffer;
      delete[] storage[i].indexBufferLength;
   }
}

bool ModelManager::getObject(const char *fileName, GLuint *vertexBuffer, GLuint *textureBuffer,
                             GLuint *normalBuffer, GLuint **indexBuffer, int **indexBufferLength)
{
   if (storage.empty()) {
      loadObject("Hello!");
   }
   	
   *vertexBuffer = storage[0].vertexBuffer;
   *normalBuffer = storage[0].normalBuffer;
   *textureBuffer = storage[0].textureBuffer;
   
   int size = sizeof(storage[0].indexBuffer) / sizeof(GLuint*);
   *indexBuffer = new GLuint[size];
   *indexBufferLength = new int[size];
   
   for (int i = 0; i < size; i++) {
      (*indexBuffer)[i] = storage[0].indexBuffer[i];
      (*indexBufferLength)[i] = storage[0].indexBufferLength[i];
   }
#ifdef DEBUG_VBO   
   printf("VBO Transfered to Given Pointer Location: %d\n", (int)*vertexBuffer);
#endif
   return true;
}

void ModelManager::loadObject(const char *filename)
{
	storage.push_back(cubeMesh());
#ifdef DEBUG_VBO
   printf("VBO Transfered to Object Memory: %d\n", (int)storage[0].vertexBuffer);
#endif
}

bufferStore ModelManager::cubeMesh()
{
	bufferStore store;
	
   float vertecies[24] = {
		-1.0, -1.0, -1.0,
		-1.0, 1.0, -1.0,
		1.0, 1.0, -1.0,
		1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,
		-1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, -1.0, 1.0
   	};
   	
   float normals[24] = {
		-1.0, -1.0, -1.0,
		-1.0, 1.0, -1.0,
		1.0, 1.0, -1.0,
		1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,
		-1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, -1.0, 1.0
   	};
   	
   GLuint faces[36] = {
		1, 3, 0,
		1, 2, 3,
		5, 1, 0,
		5, 0, 4,
		6, 2, 3,
		6, 3, 7,
		5, 6, 7, 
		5, 7, 4,
		1, 2, 6,
		1, 6, 5,
		0, 3, 7,
		0, 7, 4
   	};
  
   //vec3 diff = vec3(1.0, 0.0, 0.0);
   //float spec = 0.3;
   
   GLuint vbo, ibo, nbo;

   int ibl = 36;
#ifdef DEBUG_VBO   
   printf("VBO Pre-Initialization: %d\n", (int)vbo);
#endif   
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);
   
   glGenBuffers(1, &ibo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
   
   glGenBuffers(1, &nbo);
   glBindBuffer(GL_ARRAY_BUFFER, nbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
#ifdef DEBUG_VBO   
   printf("VBO Post-Initialization: %d\n", (int)vbo);
#endif   
   store.vertexBuffer = vbo;
   store.normalBuffer = nbo;
   store.textureBuffer = 0;
   
   store.indexBuffer = new GLuint[1];
   store.indexBufferLength = new int[1];
   
   store.indexBuffer[0] = ibo;
   store.indexBufferLength[0] = ibl;
#ifdef DEBUG_VBO   
   printf("VBO Transfered to Local Variable \"store\": %d\n", (int)store.indexBufferLength[0]);
#endif   
   return store;
}
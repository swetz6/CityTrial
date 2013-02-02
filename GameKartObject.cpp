#include "GameKartObject.h"

#include <cmath>

#include <iostream>
using namespace std;

GameKartObject::GameKartObject(const char *fileName) : GamePhysicalObject("chassis") {
    
   for (int i = 0; i < 4; i++) {
      GameDrawableObject *tire = new GameDrawableObject("tire");
      wheels.push_back(tire);
   }
   
   /*glm::vec3 pos = position();
   wheels[0]->setPosition(vec3(pos.x - 12.0, pos.y-6, pos.z - 12.0));
   wheels[1]->setPosition(vec3(pos.x + 12.0, pos.y-6, pos.z - 12.0));
   wheels[2]->setPosition(vec3(pos.x + 12.0, pos.y-6, pos.z + 12.0));
   wheels[3]->setPosition(vec3(pos.x - 12.0, pos.y-6, pos.z + 12.0));*/
    
   usingController = false;
   setDirection(0);
   setSpeed(0);
   acceleration = 5;
   friction = 2.5;
   topSpeed = 5.0;
   turningRadius = 1.0;
    
   //object->setPosition(vec3(pos.x - 5.0,pos.y - 5.0,pos.z));
   
   /*&drawable_objects->push_back(wheel[1]);
   &drawable_objects->push_back(wheel[2]);
   &drawable_objects->push_back(wheel[3]);
   &drawable_objects->push_back(chassis);
   */

}

void GameKartObject::collide(GameObject *collide)
{
   //Need some way of telling if PhysicsActor came from upgrade
   
   if (!strcmp(collide->getName(), "upgrade" )) {
      GameDrawableObject *upgrade = new GameDrawableObject("wings");
      upgrade->setPosition(vec3(0.0, 0.0, 0.0));
      upgrades.push_back(upgrade);
   }
   
   //return true;
}

GameKartObject::~GameKartObject()
{
   cout << "Kart Object Deleted\n";
}

void GameKartObject::stop()
{
   // cout << "bunnie stop\n";
   //stage = STILL;
}

void GameKartObject::draw(PhongShader *meshShader, RenderingHelper modelViewMatrix)
{
   GameDrawableObject::draw(meshShader, modelViewMatrix);
   
   
   modelViewMatrix.pushMatrix();
   modelViewMatrix.translate(getPosition());
   modelViewMatrix.scale(0.5,0.5,0.5);
  
   
   //modelViewMatrix.pushMatrix();
   //meshShader->use();
   
   //modelViewMatrix.translate(position());
   //modelViewMatrix.scale(scl.x, scl.y, scl.z);
   modelViewMatrix.rotate(rot.x, vec3(1.0, 0.0, 0.0));
   modelViewMatrix.rotate(rot.y, vec3(0.0, 1.0, 0.0));
   modelViewMatrix.rotate(rot.z, vec3(0.0, 0.0, 1.0));
   //meshShader->setModelMatrix(modelViewMatrix.getMatrix());
   
   //glBindVertexArray(vertexArray);
   
   //GLuint h_aPos = meshShader->getPosLocation();
   
   /*safe_glEnableVertexAttribArray(h_aPos);
   glBindBuffer(GL_ARRAY_BUFFER, meshStorage.vertexBuffer);
   safe_glVertexAttribPointer(h_aPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
   for (int i = 0; i < meshStorage.numMeshes; i++) {
      //printf("We are drawing, right? %d\n", indexBufferLength[i]);
      
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshStorage.indexBuffer[i]);
      
      glDrawElements(GL_TRIANGLES, meshStorage.indexBufferLength[i], GL_UNSIGNED_SHORT, 0);
   }*/
   
   //safe_glDisableVertexAttribArray(h_aPos);
   
   //glBindVertexArray(0);
   //modelViewMatrix.popMatrix();
   
   modelViewMatrix.pushMatrix();
   modelViewMatrix.translate(glm::vec3(-2.0,-1.0,-2.0));
   //modelViewMatrix.rotate(-45.0,vec3(0.0,0.0,1.0));
   modelViewMatrix.scale(1.0,0.5,1.0);
   wheels[0]->draw(meshShader,modelViewMatrix);
   modelViewMatrix.popMatrix();
   modelViewMatrix.pushMatrix();
   modelViewMatrix.translate(glm::vec3(-2.0,-1.0,2.0));
   modelViewMatrix.scale(1.0,0.5,1.0);
   wheels[1]->draw(meshShader,modelViewMatrix);
   modelViewMatrix.popMatrix();
   modelViewMatrix.pushMatrix();
   modelViewMatrix.translate(glm::vec3(2.0,-1.0,-2.0));
   modelViewMatrix.scale(1.0,0.5,1.0);
   wheels[2]->draw(meshShader,modelViewMatrix);
   modelViewMatrix.popMatrix();
   modelViewMatrix.pushMatrix();
   modelViewMatrix.translate(glm::vec3(2.0,-1.0,2.0));
   modelViewMatrix.scale(1.0,0.5,1.0);
   wheels[3]->draw(meshShader,modelViewMatrix);
   modelViewMatrix.popMatrix();
   modelViewMatrix.popMatrix();
   
   //Draws Wheels and Upgrades More efficiently *****
   /*for (int i = 0; i < (int)wheels.size(); i++) {
      modelViewMatrix.pushMatrix();
      wheels[i]->draw(meshShader,modelViewMatrix);
      modelViewMatrix.popMatrix();
   }
   
   for (int i = 0; i < (int)upgrades.size(); i++) {
      modelViewMatrix.pushMatrix();
      upgrades[i]->draw(meshShader,modelViewMatrix);
      modelViewMatrix.popMatrix();
   }*/
}

void GameKartObject::update(float dt)
{
   glm::vec3 vel = getVelocity();
   glm::vec3 pos = getPosition();
   
   printf("\nbefore\n");
   printf(" position: %f,%f,%f\n", pos.x, pos.y, pos.z);
   printf(" velocity: %f,%f,%f\n", vel.x, vel.y, vel.z);
   printf(" direction: %f\n", getDirection());
   printf(" speed: %f\n", getSpeed());
   
    // Update Actor parameters based on current input from joystickState and buttonState
   //if(usingController == true){
   
   /*vec3 up = vec3(0.0, 1.0, 0.0);
   glm::vec3 oldDir = direction();
   vec3 move = normalize(cross(up, oldDir));
   move = vec3(move.x * turningRadius * dt, move.y * turningRadius * dt, move.z * turningRadius * dt);*/
   
   short speedDirectionInverse = (joystickState[3] < 0.0) ? -1 : 1;
   
   if (joystickState[0] < 0.0) {
      setDirection(getDirection()+speedDirectionInverse*turningRadius);
      //setDirection(glm::vec3(oldDir.x - move.x,oldDir.y,oldDir.z - move.z));
   } else if(joystickState[0] > 0.0) {
      setDirection(getDirection()-speedDirectionInverse*turningRadius);
      //setDirection(glm::vec3(oldDir.x + move.x,oldDir.y,oldDir.z + move.z));
   }
 
   setRotation(vec3(0, -getDirection(), 0 ));
   
   float oldSpeed = getSpeed();
   
   short speedBrakeMult = (oldSpeed < 0.0) ? 1 : 2;
   short speedAccelMult = (oldSpeed > 0.0) ? 1 : 2;
   
   if(joystickState[3] > 0.0) {      
      setSpeed(oldSpeed + (speedAccelMult * acceleration * dt));
   } else if(joystickState[3] < 0.0) {
      setSpeed(oldSpeed - (speedBrakeMult*acceleration * dt));
   } else {
      setSpeed(oldSpeed - (sign(oldSpeed) * friction * dt));
   }
   //}
   
   vel = getVelocity();
   pos = getPosition();

   
   printf("after\n");
   printf(" position: %f,%f,%f\n", pos.x, pos.y, pos.z);
   printf(" velocity: %f,%f,%f\n", vel.x, vel.y, vel.z);
   printf(" direction: %f\n", getDirection());
   printf(" speed: %f\n", getSpeed());
   
   GameObject::update(dt);
}

//
//  GameRamp.h
//  
//
//  Created by Bryan Bell on 1/30/13.
//
// NOTE: Do not rotate this object by anything but the y-axis,
//  it will not work properly if the object is not flat.

#ifndef ____GameRamp__
#define ____GameRamp__

#include <iostream>

#include "GameDrawableObject.h"

class GameRamp : public GameDrawableObject {
public:
   GameRamp(GamePhysics *physics);
   
   float getHeightAt(float x, float z);
};

#endif /* defined(____GameRamp__) */

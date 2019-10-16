#include <cmath>
#include <iostream>
#include "missle.h"

// init static variable
int Missle::_idCnt = 0;

/**
 * Set initial line position / length properties.
 */
void Missle::setMissleVector(float x, float y, float gx, float gy) {
  
  _startX = x;
  _startY = y;

  _posX = x;
  _posY = y;
 
  _goalX = gx;
  _goalY = gy;

  _dx = gx - _posX;
  _dy = gy - _posY;

  float length = sqrt((_dx * _dx) + (_dy * _dy));
  //std::cout << "length: " << stepsToGoal << "\n";

  percentPerStep = (float) speed / length;
  stepsToGoal = (float) length / speed;

  //std::cout << "Steps to goal: " << stepsToGoal << "\n";
}

/**
 * Return the current line position / length properties.
 */
void Missle::getMissleVector(float &startx, float &starty, float &posx, float &posy) {
  startx = _startX;
  starty = _startY;
  posx = _posX;
  posy = _posY;
}

/**
 * Adjust the position / shape of missle during one time tick interval
 */
void Missle::Update() {
  
  if (_state == MissleState::Done) {
    return;
  }

  if (_state == MissleState::Exploding) { 
    _explosionRadius += 0.4;
  } else if (_state == MissleState::Imploding) {
    _explosionRadius -= 0.6;
  }
  /*
  std::cout << "radius: " << _explosionRadius << "\n";
  std::cout << "state: " << _state << "\n";
  */
  // test for state transition
  if (_explosionRadius >= 20.0) {
  
    _state = MissleState::Imploding;
    return;
  
  } else if (_explosionRadius < 0.0) {
  
    _state = MissleState::Done;
    return;

  } else if (_state == MissleState::Falling) {
  
    stepNumber += 1;
    
    // made it to the goal
    if (stepNumber >= stepsToGoal) {

      _posX = _goalX;
      _posY = _goalY;
      _state = MissleState::Exploding;

    } else {
      _posX += percentPerStep * _dx;
      _posY += percentPerStep * _dy; 

    }
  }

 

}
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

  _percentPerStep = (float) _speed / length;
  _stepsToGoal = (float) length / _speed;

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

void Missle::getPosition(float &px, float &py) {
  px = _posX;
  py = _posY;
}

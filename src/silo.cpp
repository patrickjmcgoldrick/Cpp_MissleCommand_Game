#include "silo.h"
#include <iostream>

// constructor
Silo::Silo() {

}

void Silo::setPosition(float x, float y) {
  _posX = x;
  _posY = y;
}

void Silo::getDimensions(float &x, float &y, float &width, float &height) {
  x = _posX;
  y = _posY;
  width = _width;
  height = _hight;
}

void Silo::Update() {
  
}

#include "city.h"
#include <iostream>

// constructor
City::City() {

}

void City::setPosition(float x, float y) {
  _posX = x;
  _posY = y;
}

void City::getDimensions(float &x, float &y, float &width, float &height) {
  x = _posX;
  y = _posY;
  width = _width;
  height = _hight;
}

void City::Update() {
  
}

bool City::isActive() {
    return _active;
}
#include "missle.h"

// init static variable
int Missle::_idCnt = 0;

void Missle::getPosition(float &x, float &y) {
  x = _posX;
  y = _posY;
}
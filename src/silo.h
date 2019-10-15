#ifndef SILO_H
#define SILO_H

#include "SDL.h"

/**
 * Class to describe a missle silo.  Ground based defense with 'Patriot' type missles.
 */

class Silo {
  public:

    // constructor
  	Silo();
  
    // getters / setters
    void setPosition(float x, float y);
    void getDimensions(float &x, float &y, float &width, float &height);

  	void Update();
    bool isActive();

  private:
    float _posX = 0.0f;
    float _posY = 0.0f;
    float _width = 60.0f;
    float _hight = 20.0f;
    
    int _missleCount = 10;
    bool _active = true;

};

#endif

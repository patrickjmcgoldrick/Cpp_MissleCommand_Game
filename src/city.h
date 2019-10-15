#ifndef CITY_H
#define CITY_H

#include "SDL.h"

/**
 * Class to describe a missle silo.  Ground based defense with 'Patriot' type missles.
 */

class City {
  public:

  	City();
    
    void setPosition(float x, float y);
    void getDimensions(float &x, float &y, float &width, float &height);

  	void Update();
    
    bool isActive();

  private:
    float _posX = 0.0f;
    float _posY = 0.0f;
    float _width = 40.0f;
    float _hight = 10.0f;
    
    bool _active = true;

};

#endif
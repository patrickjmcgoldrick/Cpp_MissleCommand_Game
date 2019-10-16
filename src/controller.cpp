#include "controller.h"
#include <iostream>
#include <algorithm>
#include "SDL.h"


void Controller::HandleInput(bool &running, std::vector<std::shared_ptr<DefenseMissle>> &defenseMissles) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {

      switch(e.button.which) {
        case SDL_BUTTON_LEFT:
          std::cout << "Button LEFT - at: " << e.button.x << ", " << e.button.y << std::endl;
          break;
        case SDL_BUTTON_RIGHT:
          std::cout << "Button RIGHT - at: " << e.button.x << ", " << e.button.y << std::endl;
          break;
        default:
          std::cout << "Unknown Button - at: " << e.button.x << ", " << e.button.y << std::endl;
          float clickX = static_cast <float> (e.button.x);
          float clickY = static_cast <float> (e.button.y);
          

      } 

    }
  }
}



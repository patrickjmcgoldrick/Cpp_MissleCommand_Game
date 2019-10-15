#include "controller.h"
#include <iostream>
#include <algorithm>
#include "SDL.h"


void Controller::HandleInput(bool &running, std::vector<std::shared_ptr<Missle>> &offenseMissles) {
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
          
          bool selectedNewLifeguard = false;

/*
          // check Lifeguards for clicks
          std::for_each(lifeguards.begin(), lifeguards.end(), [&, clickX, clickY](std::shared_ptr<Lifeguard> &lifeguard) {
            if (DidClickInside(clickX, clickY, lifeguard)) {
              
              selectedNewLifeguard = true;
              std::cout << "Lifeguard selected #: " <<  lifeguard->id << "\n";

            }
          });
          
          if (!selectedNewLifeguard) {
            // set new goal for currently selected.
            std::cout << "get selected" << "\n";

            std::shared_ptr<Lifeguard> selected = SelectedLifeguard(lifeguards);
            std::cout << "Lifeguard #: " <<  selected->id << "\n";
            std::cout << "setting new goal: " << clickX << " , " << clickY << "\n";

            //SDL_Point newGoal = {clickX, clickY};
            if (selected == NULL) {
              std::cout << "NULL ref" << "\n";
            } else {
              std::cout << "good ref" << "\n";
              selected->SetGoal(clickX, clickY);
            }
            
            std::cout << "test new Goal: " << clickX << " , " << clickY << "\n";

            
          }
          break;
          */
      } 

    }
  }
}



#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <thread>
#include <vector>
#include "silo.h"
#include "missle.h"

class Controller {
 public:

  Controller(const std::size_t screen_width, const std::size_t screen_height) : screen_width(screen_width),
      screen_height(screen_height) {};

  void HandleInput(bool &running, std::vector<std::shared_ptr<Missle>> &defenseMissles);

 private:
  
  const std::size_t screen_width;
  const std::size_t screen_height;

};

#endif
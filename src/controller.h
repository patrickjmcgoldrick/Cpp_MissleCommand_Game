#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <thread>
#include <vector>
#include "silo.h"
#include "missle.h"

class Controller {
 public:

  Controller(const std::size_t block_width, const std::size_t block_height) : block_width(block_width),
      block_height(block_height) {};

  void HandleInput(bool &running, std::vector<std::shared_ptr<Missle>> &offenseMissles);

 private:
  
  const std::size_t block_width;
  const std::size_t block_height;

};

#endif
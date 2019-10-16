#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "city.h"
#include "silo.h"
#include "missle.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);



  int GetScore() const;
  int GetSize() const;


 private:

  void AddNewOffenseMissle();

  std::vector<std::shared_ptr<City>> cities; 
  std::vector<std::shared_ptr<Silo>> silos;  
 
  std::vector<std::shared_ptr<Missle>> offenseMissles;  
  std::vector<std::shared_ptr<Missle>> defenseMissles;  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_game_width;
  std::uniform_int_distribution<int> random_missle_count;

  int score{0};

  void Update();
};

#endif

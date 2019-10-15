#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <thread>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

#include "silo.h"
#include "city.h"
#include "missle.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::vector<std::shared_ptr<City>> &cities, 
              std::vector<std::shared_ptr<Silo>> &silos,
              std::vector<std::shared_ptr<Missle>> &offenseMissles,  
              std::vector<std::shared_ptr<Missle>> &defenseMissles);
              
  void UpdateWindowTitle(int score, int fps);

 private:
  void RenderCity(std::shared_ptr<City> &city);
  void RenderSilo(std::shared_ptr<Silo> &silo);
  void RenderOffenseMissle(std::shared_ptr<Missle> &offenseMissle);
  void RenderDefenseMissle(std::shared_ptr<Missle> &defenseMissle);

  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  std::size_t y_water_sand_divide;


};

#endif
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
#include "offense_missle.h"
#include "defense_missle.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::vector<std::shared_ptr<City>> &cities, 
              std::vector<std::shared_ptr<Silo>> &silos,
              std::vector<std::shared_ptr<OffenseMissle>> &offenseMissles,  
              std::vector<std::shared_ptr<DefenseMissle>> &defenseMissles);
              
  void UpdateWindowTitle(int score, int fps);

 private:
  void RenderCity(std::shared_ptr<City> &city);
  void RenderSilo(std::shared_ptr<Silo> &silo);
  void RenderOffenseMissle(std::shared_ptr<OffenseMissle> &offenseMissle);
  void RenderDefenseMissle(std::shared_ptr<DefenseMissle> &defenseMissle);

  void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
  
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  std::size_t y_water_sand_divide;


};

#endif
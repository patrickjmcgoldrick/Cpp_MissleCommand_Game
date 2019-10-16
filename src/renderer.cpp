#include "renderer.h"
#include <iostream>
#include <algorithm>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // where we draw the line between water and sand
  y_water_sand_divide = 2 * screen_height / 3;
  
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::vector<std::shared_ptr<City>> &cities, 
                      std::vector<std::shared_ptr<Silo>> &silos,  
                      std::vector<std::shared_ptr<OffenseMissle>> &offenseMissles,  
                      std::vector<std::shared_ptr<DefenseMissle>> &defenseMissles) {

  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  SDL_Rect background;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);


  // render Sand
  SDL_SetRenderDrawColor(sdl_renderer, 0xF0, 0xD9, 0x9A, 0xFF);
  background.x = 0;
  background.w = screen_width;
  background.y = screen_height - 10;
  background.h = screen_height;
  SDL_RenderFillRect(sdl_renderer, &background);
  
  // render Cities
  std::for_each(cities.begin(), cities.end(), [&](std::shared_ptr<City> &city) {
    RenderCity(city);
  });

  // render Silos
  std::for_each(silos.begin(), silos.end(), [&](std::shared_ptr<Silo> &silo) {
    RenderSilo(silo);
  });
  
  // render Offense Missles
  std::for_each(offenseMissles.begin(), offenseMissles.end(), [&](std::shared_ptr<OffenseMissle> &offense) {
    RenderOffenseMissle(offense);
  });

  // render Defensive Missles
  std::for_each(defenseMissles.begin(), defenseMissles.end(), [&](std::shared_ptr<DefenseMissle> &defense) {
    RenderDefenseMissle(defense);
  });

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderCity(std::shared_ptr<City> &city) {
  // render City
  float x, y, width, height;
  city->getDimensions(x, y, width, height);

  int intx = static_cast <int> (x);
  int inty = static_cast <int> (y);
  int intw = static_cast <int> (width);
  int inth = static_cast <int> (height);

  SDL_Rect block;
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x88, 0xFF); // blue
  block.x = intx;
  block.y = inty;
  block.w = intw;
  block.h = inth;
  SDL_RenderFillRect(sdl_renderer, &block);
  
}

void Renderer::RenderSilo(std::shared_ptr<Silo> &silo) {
  // render Silo
  float x, y, width, height;
  silo->getDimensions(x, y, width, height);

  int intx = static_cast <int> (x);
  int inty = static_cast <int> (y);
  int intw = static_cast <int> (width);
  int inth = static_cast <int> (height);

  SDL_Rect block;
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x88, 0x00, 0xFF); // green
  block.x = intx;
  block.y = inty;
  block.w = intw;
  block.h = inth;
  SDL_RenderFillRect(sdl_renderer, &block);
  
}

void Renderer::RenderOffenseMissle(std::shared_ptr<OffenseMissle> &offenseMissle) {

  if (offenseMissle->getState() != MissleState::Falling) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);  //red
  
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);  //white
  }

  float startx, starty, px, py;
  offenseMissle->getMissleVector(startx, starty, px, py);

  SDL_RenderDrawLine(sdl_renderer, startx, starty, px, py);
    

  if (offenseMissle->getState() == MissleState::Exploding 
     || offenseMissle->getState() == MissleState::Imploding) {
    // draw explosion / implosion

    float radius = offenseMissle->getExplosionRadius();

    // center explosion over hit point
    DrawCircle(sdl_renderer, px, py, radius);
    DrawCircle(sdl_renderer, px, py, (radius * 3.0 / 4.0));
    DrawCircle(sdl_renderer, px, py, (radius / 2.0));
    DrawCircle(sdl_renderer, px, py, (radius / 4));
  }
}

void Renderer::RenderDefenseMissle(std::shared_ptr<DefenseMissle> &defenseMissle) {

  // set line color
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);  //light blue
  
  float startx, starty, px, py;
  defenseMissle->getMissleVector(startx, starty, px, py);
 
  SDL_RenderDrawLine(sdl_renderer, startx, starty, px, py);
    

  if (defenseMissle->getState() == MissleState::Exploding 
    || defenseMissle->getState() == MissleState::Imploding) {
    // draw explosion / implosion

    float radius = defenseMissle->getExplosionRadius();

    // center explosion over hit point
    DrawCircle(sdl_renderer, px, py, radius);
    DrawCircle(sdl_renderer, px, py, (radius * 3.0 / 4.0));
    DrawCircle(sdl_renderer, px, py, (radius / 2.0));
    DrawCircle(sdl_renderer, px, py, (radius / 4));
  }
}

/**
 * Draw circle from: https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
 */
void Renderer::DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

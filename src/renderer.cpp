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

void Renderer::Render(std::vector<std::shared_ptr<City>> &cities, std::vector<std::shared_ptr<Silo>> &silos) {

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
  background.y = y_water_sand_divide;
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

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

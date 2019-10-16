#include "game.h"
#include <iostream>
#include <algorithm>
#include "SDL.h"

Game::Game(std::size_t game_width, std::size_t game_height)
    : engine(dev()),
      random_game_width(0, static_cast<int>(game_width)),
      random_missle_count (0, static_cast<int>(4)) {

  
  // create ground objects
  // init missle silos
  int nSilos = 3;
  for (size_t ni = 0; ni < nSilos; ni++)
  {
      silos.push_back(std::make_shared<Silo>());
  }

  // position silos
  silos.at(0)->setPosition(15, 620);  // left
  silos.at(1)->setPosition(290, 620); // center
  silos.at(2)->setPosition(565, 620); // right


  int nCities = 6;
  for (size_t ni = 0; ni < nCities; ni++)
  {
      cities.push_back(std::make_shared<City>());
  }

  // position cities
  cities.at(0)->setPosition(100, 620); // left
  cities.at(1)->setPosition(150, 620); // left
  cities.at(2)->setPosition(200, 620); // left
  cities.at(3)->setPosition(400, 620); // right
  cities.at(4)->setPosition(450, 620); // right
  cities.at(5)->setPosition(500, 620); // right

}

void Game::AddNewOffenseMissle() {

  // create offense missle
  float startx = (float)random_game_width(engine);  // random start
  float goalx = (float)random_game_width(engine);   // random target

  std::shared_ptr<OffenseMissle> missle = std::make_shared<OffenseMissle>();
  missle->setMissleVector(startx, 0.0f, goalx, 625.0f);
  offenseMissles.push_back(missle);

}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, defenseMissles);
    Update();
    renderer.Render(cities, silos, offenseMissles, defenseMissles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;

      int numNewMissles = random_missle_count(engine);
      for (int i=0; i<numNewMissles; i++) {
        AddNewOffenseMissle();
      }
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


void Game::Update() {

  // move offense missles
  std::for_each(offenseMissles.begin(), offenseMissles.end(), [](std::shared_ptr<OffenseMissle> &missle) {
    missle->Update();
  });


  
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return 0; }

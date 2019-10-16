#include "game.h"
#include <iostream>
#include <algorithm>
#include <stack>
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

  // move defense missles
  std::for_each(defenseMissles.begin(), defenseMissles.end(), [](std::shared_ptr<DefenseMissle> &missle) {
    missle->Update();
  });
  
  std::stack<int> doneMissles;
  std::stack<int> doneCities;
  std::stack<int> doneSilos;

  // compare done missles with terrain objects (silos and cities)
  for (int i=0; i< offenseMissles.size(); i++) {
    std::shared_ptr<OffenseMissle> missle = offenseMissles.at(i);
    if (missle->getState() == MissleState::Done) {
      // add to stack to be removed
      doneMissles.push(i);

      float mx, my;
      missle->getPosition(mx, my);

      // check if it hit a city
      for (int ci=0; ci< cities.size(); ci++) {
        std::shared_ptr<City> city = cities.at(ci);

        float cx, cy, cw, ch;
        city->getDimensions(cx, cy, cw, ch);

        if (mx >= cx && mx <= (cx + cw)) {
          // city was hit by this missle
          doneCities.push(ci);
        }
      }

      // check if it hit a silo
      for (int si=0; si < silos.size(); si++) {
        std::shared_ptr<Silo> silo = silos.at(si);

        float sx, sy, sw, sh;
        silo->getDimensions(sx, sy, sw, sh);

        if (mx >= sx && mx <= (sx + sw)) {
          // silo was hit by this missle
          doneSilos.push(si);
        }
      }
    }
  }

  // cleanup missles
  while (!doneMissles.empty()) {
    int index = doneMissles.top();
    offenseMissles.erase(offenseMissles.begin() + index);
    doneMissles.pop();
  }

  // clean cities
  while (!doneCities.empty()) {
    int index = doneCities.top();
    cities.erase(cities.begin() +  + index);
    doneCities.pop();
  }

  // clean silos
  while (!doneSilos.empty()) {
    int index = doneSilos.top();
    silos.erase(silos.begin() + index);
    doneSilos.pop();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return 0; }

#ifndef DEFENSE_MISSLE_H
#define DEFENSE_MISSLE_H

#include <thread>

#include "offense_missle.h"

class DefenseMissle : public Missle {
  public:

    // constructor
    DefenseMissle();

    void Update();

    bool blastRadiusContains(std::shared_ptr<OffenseMissle> &offMissle);
};

#endif
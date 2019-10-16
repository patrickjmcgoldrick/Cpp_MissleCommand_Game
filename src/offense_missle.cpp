#include "offense_missle.h"

/**
 * Adjust the position / shape of missle during one time tick interval
 */
void OffenseMissle::Update() {
  
  if (_state == MissleState::Done) {
    return;
  }

  if (_state == MissleState::Exploding) { 
    _explosionRadius += 0.4;
  } else if (_state == MissleState::Imploding) {
    _explosionRadius -= 0.6;
  }
  /*
  std::cout << "radius: " << _explosionRadius << "\n";
  std::cout << "state: " << _state << "\n";
  */
  // test for state transition
  if (_explosionRadius >= 20.0) {
  
    _state = MissleState::Imploding;
    return;
  
  } else if (_explosionRadius < 0.0) {
  
    _state = MissleState::Done;
    return;

  } else if (_state == MissleState::Falling) {
  
    stepNumber += 1;
    
    // made it to the goal
    if (stepNumber >= stepsToGoal) {

      _posX = _goalX;
      _posY = _goalY;
      _state = MissleState::Exploding;

    } else {
      _posX += percentPerStep * _dx;
      _posY += percentPerStep * _dy; 

    }
  }

}
#include <cmath>
#include "defense_missle.h"

// constructor
DefenseMissle::DefenseMissle() {
  _speed = 3.0f;
}

// changes to missle over one time tick.
void DefenseMissle::Update() {

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
  if (_explosionRadius >= 30.0) {
  
    _state = MissleState::Imploding;
    return;
  
  } else if (_explosionRadius < 0.0) {
  
    _state = MissleState::Done;
    return;

  } else if (_state == MissleState::Falling) {
  
    _stepNumber += 1;
    
    // made it to the goal
    if (_stepNumber >= _stepsToGoal) {

      _posX = _goalX;
      _posY = _goalY;
      _state = MissleState::Exploding;

    } else {
      _posX += _percentPerStep * _dx;
      _posY += _percentPerStep * _dy; 

    }
  }
}

// is the given offense missle in the blast radius of this denfense missle?
bool DefenseMissle::blastRadiusContains(std::shared_ptr<OffenseMissle> &offMissle) {

    float x, y;
    this->getPosition(x, y);

    float offPosX, offPosY;
    offMissle->getPosition(offPosX, offPosY);

    float offdx, offdy, offDistance;

    offdx = offPosX - x;
    offdy = offPosY - y;

    offDistance = sqrt((offdx * offdx) * (offdy * offdy));

    float explosionRadius = this->getExplosionRadius();

    return (offDistance < explosionRadius);

}
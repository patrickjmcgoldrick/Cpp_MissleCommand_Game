#ifndef MISSLE_H
#define MISSLE_H

enum MissleState { 
  Falling, 
  Exploding, 
  Imploding, 
  Done 
};

class Missle {

  public:
		
    Missle() {
      id = _idCnt++;
    }

    void setMissleVector(float x, float y, float gx, float gy);

    void getMissleVector(float &startx, float &starty, float &posx, float &posy);
    
    void getPosition(float &x, float&y);

    virtual void Update() = 0;  // it's important that the virtual function '= 0;'
                                // won't compile otherwise.  Compiler thing.

    float getExplosionRadius() {
      return _explosionRadius;
    }

    MissleState getState() {
      return _state;
    }

    int id;

  protected:
    
    MissleState _state = MissleState::Falling;

  	float _speed{1.0f};

    float _startX = 0.0f;
    float _startY = 0.0f;

    float _posX = 0.0f;
    float _posY = 0.0f;

    float _goalX = 0.0f;
    float _goalY = 0.0f;
    
    float _stepNumber = 0.0f;
    float _stepsToGoal = 0.0f;

    float _percentPerStep = 0.0f;

    float _dx = 0.0f;
    float _dy = 0.0f;

    float _explosionRadius = 0.0f;

  private:
          
    static int _idCnt; // global variable for counting object ids

};

#endif
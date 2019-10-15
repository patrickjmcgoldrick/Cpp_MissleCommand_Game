#ifndef MISSLE_H
#define MISSLE_H

class Missle {
  public:
		
    Missle() {
      id = _idCnt++;
    }

    Missle(float x, float y) : _posX(x), _posY(y) {
      id = _idCnt++;
    }

    void getPosition(float &x, float &y);
    

    bool selected = true;
    int id;

  protected:

  	float speed{0.03f};

    float _posX = 0.0f;
    float _posY = 0.0f;
    
    private:
      static int _idCnt; // global variable for counting object ids

};

#endif
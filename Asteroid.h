#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid{
  public:
    Asteroid();
    Asteroid(float,float,float);
    ~Asteroid();
    void setX(float);
    float getX();
    void setY(float);
    float getY();
    void setZ(float);
    float getZ();
    
  private:
    float x;
    float y;
    float z;
};

#endif

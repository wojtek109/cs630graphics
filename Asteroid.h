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


Asteroid::Asteroid()
{
  srand( time(NULL) );
  x = rand() % 20;
  srand( time(NULL) );
  y = rand() % 20;
  srand( time(NULL) );
  z = rand() % 20;

}

Asteroid::Asteroid(float inX,float inY, float inZ)
{
  x = inX;
  y = inY;
  z = inZ;
}

Asteroid::~Asteroid()
{

}

void Asteroid::setX(float inX)
{
  x = inX;
}

float Asteroid::getX()
{
  return x;
}

void Asteroid::setY(float inY)
{
  y = inY;
}

float Asteroid::getY()
{
  return y;
}

void Asteroid::setZ(float inZ)
{
  z = inZ;
}

float Asteroid::getZ()
{
  return z;
}

#endif

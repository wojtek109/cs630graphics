#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Asteroid.h"

using namespace std;

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

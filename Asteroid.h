
#ifndef ASTEROID_H
#define ASTEROID_H
/*
* Asteroid Class
* float x,y,z = coordinates
* float rotation = angle of current rotation
* float speed = speed of rock
* bool destroyed
* class includes getters and setters for x,y,z,rotation
* getter for speed and a reset() to regenerate all values
*/
class Asteroid{
  public:
    Asteroid(void);
    Asteroid(float xCoord, float yCoord, float zCoord);
    ~Asteroid(void);
    void setX(float xCoord);
    float getX(void);
    void setY(float yCoord);
    float getY(void);
    void setZ(float zCoord);
    float getZ(void);
    void setRotation(float newRotation);
    float getRotation(void);
    void reset(int mode);
    void updateZ(float change);
    float getSpeed();
    void updateRotation();
    int isDestroyed();
    void destroy();
  private:
    float x;
    float y;
    float z;
    float rotation;
    float speed;
    int destroyed;
};



Asteroid::Asteroid()
{
    x = (rand()%10)-5;
    y = (rand()%10)-5;
    z = -50.0f - rand()%50; 
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
 this->x = inX;
}

float Asteroid::getX(void)
{
  return x;
}

void Asteroid::setY(float inY)
{
  this->y = inY;
}

float Asteroid::getY(void)
{
  return y;
}

void Asteroid::setZ(float inZ)
{
  this->z = inZ;
}

float Asteroid::getZ(void)
{
  return z;
}

void Asteroid::setRotation(float newRotation)
{
     this->rotation = newRotation;
}

float Asteroid::getRotation(void)
{
    return rotation;                       
}

void Asteroid::reset(int mode){
     if(mode){
         this->x = 0.0f;
         this->y = 0.0f;
         this->z = -50.0f - rand()%50; 
         speed = 0.5;
         rotation = rand();
         destroyed = 0;
     }
     else{
         this->x = fabs((rand()%10))-5;
         this->y = fabs((rand()%10))-5;
         this->z = -50.0f - rand()%50; 
         speed = 0.5;
         rotation = rand();
         destroyed = 0;
      }
}

void Asteroid::updateRotation(){
     this->rotation += 1;
     if(this->rotation > 360)
                       this->rotation = 0;
                       }

void Asteroid::updateZ(float change){
      this->z += change;
}

float Asteroid::getSpeed(){
      return this->speed;
}

int Asteroid::isDestroyed(){
    return destroyed;
}

void Asteroid::destroy(){
     destroyed = 1;
     }
#endif

#ifndef STAR_H
#define STAR_H
#include <cmath>
#include <ctime>
#include <cstdlib>

/*
* Star class
* Based Asteroid off of this
* pretty self-explanitory
* x y z = coordinates
* size = draw-size
* setters & getters for x y z and size
* reset to regenerate 
*/
class star{
private:
      float x;
      float y;
      float z;
      float size;
public:
      star(void);
      ~star(void);
      void updatex(float upd);
      void updatey(float upd);
      void updatez(float upd);
      void setSize(float sNew);
      float getx(void);
      float gety(void);
      float getz(void);
      float getSize(void );
      void reset(void);
};
      
star::star(void){
     x = (rand()%10)-5;
     y = (rand()%10)-5;
     z = -50.0f - rand()%50; 
}

void star::updatex(float upd){
     x += upd;
}

void star::updatey(float upd){
     y += upd;
}

void star::updatez(float upd){
     z += upd;
}

float star::getx(void){
     return x;
}

float star::gety(void){
     return y;
}

float star::getz(void){
     return z;
}

void star::reset(){
     x = fabs((rand()%20))-10;
     y = fabs((rand()%20))-10;
     z = -20.0f - fabs((rand()%50)); 
     size = fabs((rand()%2))+1; 
}
void star::setSize(float sNew){
     this->size = sNew;
}
float star::getSize(void){
     return this->size;
}
star::~star(void){
}
#endif

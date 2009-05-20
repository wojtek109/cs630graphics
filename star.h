#ifndef STAR_H
#define STAR_H
#include <cmath>
#include <ctime>
#include <cstdlib>

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
            
      void operator=(star s);             
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
     x = (rand()%20)-10;
     y = (rand()%20)-10;
     z = -20.0f - (rand()%50); 
     size = fabs((rand()%2))+1; 

     }
void star::operator=(star s){
     this->x = s.getx();
     this->y = s.gety();
     this->z = s.getz();
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

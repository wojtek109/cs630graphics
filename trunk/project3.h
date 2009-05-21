#ifndef PROJECT3_H
#define PROJECT3_H
/****************************************************************************
*  Space Flight Shooter
*  Authors:
*          Alex Bonilla
*          Ramil Nobleza
*          Sunchol Yoo
*  Description: This demo will feature a controllable spaceship
*  which will fly through space through a path through asteroids
*  and other objects. Shooting (hopefully) will be implemented soon.
*
*
*
*  Edit: Shooting works. Flying works. have a nice backdrop of a spinning planet.
*
*
******************************************************************************/

//The ususal includes
#include <cstdlib>
#include <cmath>
#include <GL/glaux.h>
#include <GL/glut.h>
#include <cctype> //for bigText
#include <windows.h>
#include <sstream> //(for int->string conversion)

#include "star.h" //for a starfield
#include "Asteroid.h" //for asteroids

#include "Model_3DS.cpp"//to import figures
#include "GLTexture.cpp" //alternative texture mapper

/*
* Globals. I hate globals. But you have to use them I guess
*/
GLint main_menu; //glut menu variable
GLint mainWindow; //main window (obviously)
GLuint myTexture;  //the texture variable
GLUquadricObj *quadricObj = gluNewQuadric(); //quadric for object creation 
AUX_RGBImageRec *TextureImage[5];	//setup a  pointer to the texture
Model_3DS modelAPI; //3ds interface object

//a nice pi to eat... I mean use. better than typing 3.1415926535...
float pi=acos(-1);


/*
* Environment variables
*/

//draw the 3ds model?
bool draw3ds = true;

//rotation for the little asteroid in the instruction screen
float introRotation = 0;

//sound on?
bool sound = 1;   

//fullscreen on?
bool fullscreen=0;

//checking for intro screen/ quit screen
int instructions = 1;
int quitting = 0;
int quitStart = 1;

//number of stars on screen and an array to hold them
int fieldSize = 50;
star field[50];

//number of Asteroids on the screen and an array to hold them
int numRocks = 4;
Asteroid rocks[4];

//more variables. self-explanitory
int score = 0;
int pause = 0; // 1 = paused
int mode = 0; //1 = no random rock-gen

//are we shooting?
int shoot = 0;


/*
* Fighter-specific variables. 
* Position, Velocity and roll/pitch
*/
float f_x, f_y = 0;
float f_z = -1;
float f_vel_x = 0.0f;
float f_vel_y = 0.0f;
float f_roll, f_pitch = 0;
float speed = 1.0f;

/*
* Collision Detection stuff (dynamic bounding box generation)
*/
float cxmax;
float cymax;
float czmax;
float cxmin;
float cymin;
float czmin;

/*
* The following lines included to complement re-mapping of keys
*/
int up = 'W';
int down = 'S';
int left = 'A';
int right = 'D';
int fire = ' ';


/*
* Movement-specific variables
*/
int goingUp = 0;
int goingDown = 0;
int levelling = 0; // all of these are actually bools
int goingLeft = 0;
int goingRight = 0;
int noRoll = 0;

/*
* boundary conditions for angles
*/
float pitchMax = 30.0f;
float rollMax = 30.0f;

/*
* angular velocity
*/
float pitchSpeed = 1.9f;
float rollSpeed =1.9f;

/*
* angular velocity with no input
*/
float pitchLevel = 0.5f;
float rollLevel = 0.6f;

/*
* boundary conditionsfor movement
*/
float ymin = -10.0f;
float ymax = 7.0f;

float xmax = 6.0f;
float xmin = -6.0f;

/*
* Movement speeds
*/

float vel_x = 0.25f;
float vel_y = 0.25f;


//planet (in the distance)rotation and speed
float rotation = 0;
float rotationSpeed = 0.05f;

//scroll counter for the end
float endHeight = -10;

/*
* Function Declarations. In no particular order.
*/
void myDisplay(void);
void myReshape(int w, int h);
void myKeyboard(unsigned char key, int pointx, int pointy);
void myMenu(int id);
void checkFullscreen(void);
void bigText(char *s);
void myInit(void);
void myTime(int time);
void figureFighter(void);
void mainKeyUp(unsigned char key, int pointx, int pointy);
void drawFighter();
void updateStars();
void drawStars();
void drawRocks();
void drawShot();
void crosshair();
void updateRocks();
void checkSpace();
void updateIntro();
#endif

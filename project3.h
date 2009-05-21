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

#include "Model_3DS.cpp"
#include "GLTexture.cpp"

/*
* Globals. I hate globals. But you have to use them I guess
*/
GLint main_menu;
GLint mainWindow, helpWindow;
GLuint myTexture;  //the texture variable
GLUquadricObj *quadricObj = gluNewQuadric(); 
AUX_RGBImageRec *TextureImage[5];	//setup a  pointer to the texture
Model_3DS modelAPI;
bool draw3ds = true;
float introRotation = 0;

/*
* Environment variables
*/
float pi=acos(-1);

bool sound = 1;   //sound on?

//screen mode
bool fullscreen=0;

//checking for intro screen/ quit screen
int instructions = 1;
int quitting = 0;

//alpha effects for intro?
int introAlpha = -1;

//number of stars on screen and an array to hold them
int fieldSize = 50;
star field[50];

//number of Asteroids on the screen and an array to hold them
int numRocks = 4;
Asteroid rocks[4];

int score = 0;
int pause = 0;
int mode = 0;

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
* Collision Detection stuff
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

int shoot = 0;

/*
* Movement-specific variables
*/
int goingUp = 0;
int goingDown = 0;
int levelling = 0;
int goingLeft = 0;
int goingRight = 0;
int noRoll = 0;

float pitchMax = 30.0f;
float rollMax = 30.0f;

float pitchSpeed = 1.9f;
float rollSpeed =1.9f;

float pitchLevel = 0.5f;
float rollLevel = 0.6f;

float ymin = -10.0f;
float ymax = 7.0f;

float xmax = 6.0f;
float xmin = -6.0f;

float vel_x = 0.25f;
float vel_y = 0.25f;

//how far we want to view from
float cameraDistance = 30.0f;

float camerax = 0.0f;
float cameraz = 0.0f;

//planet (in the distance)rotation
float rotation = 0;
float rotationSpeed = 0.05f;

/*
* Function Declarations. In no particular order.
*/
void myDisplay(void);
void helpDisplay(void);
void myReshape(int w, int h);
void myKeyboard(unsigned char key, int pointx, int pointy);
void myMenu(int id);
void checkFullscreen(void);
void bigText(char *s);
void pinBackgroundTexture(void);
void myInit(void);
//void startScreen(void);
void pinIntro(void);
void myTime(int time);
void figureFighter(void);
void loadImages(void);
void mainKeyUp(unsigned char key, int pointx, int pointy);
void pinFloor();
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

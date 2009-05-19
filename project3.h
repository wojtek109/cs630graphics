#ifndef PROJECT3_H
#define PROJECT3_H
/****************************************************************************
*  Space Flight Demo
*  Authors:
*          Alex Bonilla
*          Ramil Nobleza
*          Sunchol Yoo
*  Description: This demo will feature a controllable spaceship
*  which will fly through space through a path through asteroids
*  and other objects. Shooting (hopefully) will be implemented soon.
*
******************************************************************************/

//The ususal includes
#include <cstdlib>
#include <cmath>
#include <GL/glaux.h>
#include <GL/glut.h>
#include <cctype> //for bigText
#include <windows.h>
#include "star.h"

#include "GLTexture.cpp"
#include "Model_3DS.cpp"

/*
* Globals. I hate globals. But you have to use them I guess
*/
GLint main_menu;
GLint mainWindow, helpWindow;
GLuint myTexture;  //the texture variable
GLUquadricObj *quadricObj = gluNewQuadric(); 
AUX_RGBImageRec *TextureImage[4];	//setup a  pointer to the texture
Model_3DS modelAPI;


/*
* Environment variables
*/

//screen mode
bool fullscreen=0;

//checking for intro screen
bool intro = 1;

//alpha effects for intro?
int introAlpha = 100;

//number of stars on screen
int fieldSize = 50;

//starfield array
star field[50];
/*
* Fighter-specific variables. 
* Position, Velocity and roll/pitch
*/
float f_x, f_y = 0;
float f_z = -1;
float f_vel_x, f_vel_y = 0.0 ;
float f_roll, f_pitch = 0;
float speed = 1.0f;


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

float pitchSpeed = 2.1f;
float rollSpeed =2.1f;

float pitchLevel = 0.5f;
float rollLevel = 0.6f;

float ymin = -10.0f;
float ymax = 3.0f;

float xmax = 3.0f;
float xmin = -3.0f;

float vel_x = 0.25f;
float vel_y = 0.25f;

//how far we want to view from
float cameraDistance = 30.0f;

float camerax = 0.0f;
float cameraz = 0.0f;

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
void startScreen(void);
void pinIntro(void);
void myTime(int time);
void figureFighter(void);
void loadImages(void);
void mainKeyUp(unsigned char key, int pointx, int pointy);
void pinFloor();
void drawFighter();
void updateStars();
void drawStars();
void drawShot();
void crosshair();
#endif

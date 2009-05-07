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
#include <GL/glaux.h>
#include <GL/glut.h>
#include <cctype> //for bigText
#include <windows.h>

/*
* Globals. I hate globals. But you have to use them I guess
*/
GLint main_menu;
GLint mainWindow, helpWindow;
GLuint myTexture;  //the texture variable
GLUquadricObj *quadricObj = gluNewQuadric(); 
AUX_RGBImageRec *TextureImage[3];	//setup a  pointer to the texture
	
/*
* Environment variables
*/
bool fullscreen=0;
bool intro = 1;
int introAlpha = 100;

/*
* Fighter-specific variables. 
* Position, Velocity and roll/pitch
*/
float f_x, f_y, f_z = 0;
float f_vel_x, f_vel_y, f_vel_z = 0.0 ;
float f_roll, f_pitch = 0;

/*
* The following lines included to complement re-mapping of keys
*/
int up = 'W';
int down = 'S';
int left = 'A';
int right = 'D';
int fire = ' ';

int shoot = 0;

int goingUp = 0;
int goingDown = 0;
int levelling = 0;
int goingLeft = 0;
int goingRight = 0;
int noRoll = 0;

float pitchMax = 30.0f;
float rollMax = 30.0f;

/*
* Declarations. In no particular order.
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

#endif

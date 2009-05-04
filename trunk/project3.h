#ifndef PROJECT3_H
#define PROJECT3_H

/*
* Globals. I hate globals. But you have to use them I guess
*/
GLint main_menu;
GLint mainWindow, helpWindow;
GLuint myTexture;  //the texture variable
GLUquadricObj *quadricObj = gluNewQuadric(); 
AUX_RGBImageRec *TextureImage[2];	//setup a  pointer to the texture
	
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
float f_roll, f_vert = 0;

/*
* The following lines included to complement re-mapping of keys
*/
int up = 'W';
int down = 'S';
int left = 'A';
int right = 'D';

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

#endif

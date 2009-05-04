#ifndef PROJECT3_H
#define PROJECT3_H

GLint main_menu;
GLint mainWindow, helpWindow;
GLuint myTexture;  //the texture variable
GLUquadricObj *quadricObj = gluNewQuadric(); 
AUX_RGBImageRec *TextureImage[2];	//setup a  pointer to the texture
	
bool fullscreen=0;
bool intro = 1;
int introAlpha = 100;
float f_x, f_y, f_z = 0;
float f_accel_x, f_accel_y, f_accel_z = 0;
float f_vel_x, f_vel_y, f_vel_z = 0.0 ;
float f_roll, f_vert = 0;

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


#endif

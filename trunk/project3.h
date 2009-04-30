#ifndef PROJECT3_H
#define PROJECT3_H

GLint main_menu;
GLint mainWindow, helpWindow;
GLuint myTexture;  //the texture variable
GLUquadricObj *quadricObj = gluNewQuadric(); 

bool fullscreen=0;
bool intro = 1;
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

#endif

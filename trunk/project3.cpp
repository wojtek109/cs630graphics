#include <cstdlib>
#include <stdlib.h>
#include <GL/glaux.h>
#include <GL/glut.h>
#include <cctype>
//#include <GLUT/glut.h> on Mac
#include "project3.h"
// checking if its working 

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //avoid flicker
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (50, 50);
   mainWindow = glutCreateWindow ("Project 3a"); //use string for title 
   glutDisplayFunc(myDisplay); 
   glutKeyboardFunc(myKeyboard);
   glutReshapeFunc(myReshape);

   main_menu=glutCreateMenu(myMenu);
   glutAddMenuEntry("Instructions",1);
   glutAddMenuEntry("Toggle Fullscreen",2);
   glutAddMenuEntry("Quit",3);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   
   // Help Menu Window
   glutInitWindowSize(240,350);
   glutInitWindowPosition(555,50);
   helpWindow = glutCreateWindow("Help Menu");
   glutDisplayFunc(helpDisplay);
   glutKeyboardFunc(myKeyboard);
   glutReshapeFunc(myReshape);
   glutHideWindow();
   glutSetWindow(mainWindow);

   myInit();
   glutMainLoop();
   return 0;
}
//////////////////////////////////////////////////////
/*Main Window Display*/
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	pinBackgroundTexture();
	
	glBegin(GL_TRIANGLES);
	
	//left top
	glColor3f(1,0,0);
	glVertex3f(-2.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	glVertex3f(0.0,0.0,-2.0);
  
  //right top
  glColor3f(0,1,0);
	glVertex3f(2.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	glVertex3f(0.0,0.0,-2.0);
	
	//underside
	glColor3f(0,0,1);
	glVertex3f(-2.0,0.0,0.0);
	glVertex3f(2.0,0.0,0.0);
	glVertex3f(0.0,0.0,-2.0);
	
	//back
	glColor3f(1,1,1);
	glVertex3f(-2.0,0.0,0.0);
	glVertex3f(2.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	
	glEnd();
    startScreen();
  glutSwapBuffers();
  glutPostRedisplay();
}

//////////////////////////////////////////////////////
/*Displays Second Window (Help Menu)*/
void helpDisplay(void)
{
  
  glClearColor(0.0, 0.0, 0.0, 0.0); //Set bkgrnd-color
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0, 1, 1); // Set lettercolor white
  
  glRasterPos2f(-2, 4.5);
  bigText("HELP MENU");
  
  glRasterPos2f(-4, 3);
  bigText("I  for Instructions");
  
  glRasterPos2f(-4, 0);
  bigText("F  to Fullscreen");
  
  glRasterPos2f(-4, -1.5);
  bigText("Q  to Quit");

  glutSwapBuffers();
  glutPostRedisplay();
  glutSetWindow(mainWindow);
  
}

////////////////////////////////////////////////////////////
void myInit (void) //set the background color, the lights, and the texture
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);  //black
	
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(quadricObj, GLU_TRUE);
	AUX_RGBImageRec *TextureImage[1];	//setup a pointer to the texture
	TextureImage[0] = auxDIBImageLoad("galaxy-512x512.bmp"); //load the image file
	//	NOTE: BE SURE BACKGROUND IMAGE IS LOCATED IN THE PROJECT DIRECTORY!
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //set the pixel storage mode
	glGenTextures(1, &myTexture); //generate one texture identified as myTexture
	glBindTexture(GL_TEXTURE_2D, myTexture); //tells which texture we will be working with.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 
		0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
}

/////////////////////////////////////////////////////////////////////
/*Sets range for resizing screen and resets camera view for
when user resizes the window*/
void myReshape (int w, int h)
{
   if (h==0) h=1; //Don't allow a total window ht of zero.
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   //designate a perspective view for best 3D effect
   glFrustum (-1.0, 1.0, -1.0, 1.0, 2, 40.0); 
   gluLookAt(0.0, 7.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glMatrixMode (GL_MODELVIEW);  
}

/////////////////////////////////////////////////////////////////////
/*This functions toggles fullscreen based on flag value*/
void checkFullscreen(void)
{
  glutSetWindow(mainWindow);
  if(!fullscreen)
  {
    glutFullScreen();
    fullscreen=1;
  }
  else
  {
    glutReshapeWindow(500,500);
    glutPositionWindow(50,50);
    fullscreen=0;
  }
}

////////////////////////////////////////////////////////////////////
/*This functions creates menu actions for when a menu
item is selected*/
void myMenu(int id)
{
	switch(id)
	{
	case 1:
		glutSetWindow(helpWindow);
		glutShowWindow();
		break;
	case 2: 
		checkFullscreen();
		break;
	case 3: 
		exit(0);
		break;
	default:
		break;
	} //end switch
}

////////////////////////////////////////////////////////////////////
void myKeyboard(unsigned char key, int pointx, int pointy)  // keyboard callback 
//OGL sends us the key character and where on the screen it was pressed.
{
  key = toupper(key);
	switch(key)
	{
	  case 'Q':
		  exit(0);
		  break;
    case 'I':
         glutSetWindow(helpWindow);
         glutShowWindow();
         break;
    case 'F':
         checkFullscreen();
         break;
         case 'C':
              glutSetWindow(helpWindow);
              glutHideWindow();
              break;
    default:
		  glutPostRedisplay();
	}
}

//////////////////////////////////////////////////////////////////////
void bigText(char *s){
	for (unsigned int i=0; i<strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
} 

////////////////////////////////////////////////////////////////////
void pinBackgroundTexture(void)
{
	//******************************************
	//  3.  Draw the texture and specify the x, y, z coordinates.
	//      The texture should be placed BEHIND the cube.
	//******************************************
	
	glEnable(GL_TEXTURE_2D); 

	glBegin(GL_QUADS);

		//Set the bottom left of the image
		glTexCoord2f(0.0f, 0.0f); //bottom left of the 2D viewport in the window
		glVertex3f(-20.0f, -70.0f, -12.0f); //bottom left back
		//glVertex3f(-19.0f, -19.0f, -35.0f); //bottom left back

		//Set the top left of the image
		glTexCoord2f(0.0f, 1.0f); //top left of the 2D viewport in the window
		glVertex3f(-10.0f, 10.0f, -12.0f); //top left back
		//glVertex3f(-19.0f, 19.0f, -35.0f); //top left back

		//Set the top right of the image
		glTexCoord2f(1.0f, 1.0f); //top right of the 2D viewport in the window
		glVertex3f( 10.0f, 10.0f, -12.0f); //top right back
		//glVertex3f( 19.0f, 19.0f, 35.0f);

		//Set the bottom right of the image
		glTexCoord2f(1.0f, 0.0f); //bottom right of the 2D viewport in the window
		glVertex3f( 20.0f, -70.0f, -12.0f); //bottom right back
		//glVertex3f( 19.0f, -19.0f, -35.0f); //bottom right back

		//Change the vertex locations where the texture is mapped and see the result
  
	glEnd();  // done with the texture map
	glDisable(GL_TEXTURE_2D); //We don't want to map onto the sphere 
  //////////////////////////////////////////////////////////////////////
}
void startScreen(){
     if(intro){
               
               }
}

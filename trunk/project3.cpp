//including the 
#include "project3.h"
//#include "Asteroid.cpp"

/* 
* Main loop.
* Big fat initialization!
*/

int main(int argc, char** argv)
{
    //we always call this
    glutInit(&argc, argv);
    
    //double-buffered, rgb color with depth-testing
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    
    //create a 800 x 600 pixel window
    glutInitWindowSize (800, 600);
    
    // and put it @ 50 x 50 from the top-left of the screen 
    glutInitWindowPosition (50, 50);
    
    //actually instansiate the window   
    mainWindow = glutCreateWindow ("SPACE!... the game");
    
    //define a display function for the window
    glutDisplayFunc(myDisplay); 
    
    //ignore key repeats (because it slows things down)
    glutIgnoreKeyRepeat(1);
    
    //define a keyboard handler
    glutKeyboardFunc(myKeyboard);
    
    //and a key-up handler (I found this myself. I'm proud ^^ )
    glutKeyboardUpFunc(mainKeyUp);
    
    //regulate re-shaping of the window
    glutReshapeFunc(myReshape);
    
    //menu creation (with a callback function for selection)   
    main_menu=glutCreateMenu(myMenu);
    //adding members to the menu
    glutAddMenuEntry("Instructions",1);
    glutAddMenuEntry("Toggle Fullscreen",2);
    glutAddMenuEntry("Quit",3);
    
    //load the fighter
    modelAPI.Load("fighter.3ds");
    
    //and attaching it to an event (right-mouse click)
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    //creating star array
    for(int i = 0; i < fieldSize; i++){
            field[i].reset();
    }
    for(int i = 0; i < numRocks; i++){
            rocks[i].reset();
    }
    
/*    // Help window starts here
    // smaller window (in 16:9 even)
    glutInitWindowSize(320,180);
    
    //put it to the right
    glutInitWindowPosition(600,50);
    
    //actually create it
    helpWindow = glutCreateWindow("Help Menu");
    
    //tell ogl what to display inside
    glutDisplayFunc(helpDisplay);
    
    //define a keyboard handler (maybe it should be different?)
    glutKeyboardFunc(myKeyboard);
    
    //and of course a- hey wait, that's the same reshape! is that safe?
    glutReshapeFunc(myReshape);
    
    //default view:hidden
    glutHideWindow();
*/    
    //show the main window as default
    glutSetWindow(mainWindow);
    
    //turn on 2-D textures (because we need them)
//    glEnable(GL_TEXTURE_2D);
    
    //some settings about coordinate style
   	gluQuadricTexture(quadricObj, GLU_TRUE);
    	
   	//load the images into memory
    TextureImage[0] = auxDIBImageLoad("space.bmp"); //load the image file
   	TextureImage[1] = auxDIBImageLoad("rock.bmp"); //load the image file
//    TextureImage[2] = auxDIBImageLoad("ship.bmp"); //load the image file
    TextureImage[3] = auxDIBImageLoad("planet.bmp");
    //pixel storage mode (drawing options)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /*
    * more texture things.
    * I'm not sure how all of these others work
    */
   	glGenTextures(1, &myTexture); //generate one texture identified as myTexture
   	glBindTexture(GL_TEXTURE_2D, myTexture); //tells which texture we will be working with.
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   	
   	

    	
            
    //texture options (all I know is GL_REPLACE draws over other stuff)		
   	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   	//call initial time function (for a delay!)
    glutTimerFunc(1000,myTime,1);

    //enable z-testing for draw-order
    glEnable(GL_DEPTH_TEST);

    //to enable alpha-blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);

    //set bg-color
	glClearColor(0,0,0,0);
  //  PlaySound("StarFox_Asteroid.mid",NULL,SND_ASYNC);
    //and process events   
    glutMainLoop();
       return 0;
}

/*
* key-up handler. I couldn't handle velocity changes very well without
* the very useful glutKeyUpFunc
*/
void mainKeyUp(unsigned char key, int pointx, int pointy){
     //check for which key is up, and reset its velocity
     key = toupper(key);
     if(key == up){
     f_vel_y = 0.0f;
//     f_pitch = 0.0f;
       goingUp = 0;
       goingDown = 0;
       levelling = 1;
     }
     else if(key == down){
     f_vel_y = 0.0f;
     goingDown = 0;
     goingUp = 0;
     levelling = 1;
//     f_pitch = 0.0f;
     }
     else if(key == left){
     f_vel_x = 0.0f;
  //   f_roll = 0.0f;
     goingLeft = 0;
     goingRight = 0;
     noRoll = 1;
     }
     else if(key == right){
     f_vel_x = 0.0f;
   //  f_roll = 0.0f;
     goingLeft = 0;
     goingRight = 0;
     noRoll = 1;
     
     }
     }

//////////////////////////////////////////////////////
/*Main Window Display*/
void myDisplay(void)
{ 
     
    /*testing 3rd person */
//	   glMatrixMode (GL_PROJECTION);
//   glLoadIdentity();
   
   //designate a perspective view for best 3D effect
//   glFrustum (-1.0, 1.0, -1.0, 1.0, 2, 1000.0); 
//   camerax = cameraDistance * cos((f_roll + 270.0f) * M_PI / 180) + f_x;
//   cameraz = cameraDistance * -sin((f_roll + 270.0f) * M_PI / 180) + f_z;

//   glTranslatef(f_x,f_y,f_z);
//	glRotatef(-f_roll,0,1,0);
//	glRotatef(-f_pitch,1,0,0);

//   gluLookAt(camerax, 0.0, 
   //cameraz
//   cameraz, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
   
/*       glRotatef(-f_pitch,1,0,0);
    glRotatef(-f_roll,0,1,0);
    glTranslatef(-f_x,-f_y,-f_z);
*/
   
   /*with this code*/
   if(instructions){
   glOrtho(-1,1,-1,1,1,-1);
   glLoadIdentity();                    
  	
      //clear black background
	glClearColor(0,0,0,0);
	
	glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
	//change draw color to white
	glColor3f(1.0, 1.0,1.0); 
	
	//set draw position
	glRasterPos2f(0, 2);
	bigText("'i' to display this message");
	
	//a little lower for the next message
	glRasterPos2f(0, 1);
	bigText("'c' to close this window");

	//and even lower for the last message
	glRasterPos2f(0,0);
	bigText("'q' to quit");

	//execute commands
	glutSwapBuffers();
	glutPostRedisplay();
	glEnable(GL_DEPTH_TEST);
    }
   else if(quitting){
        }
   else{
glFrustum (-1.0, 1.0, -1.0, 1.0, 2, 1000.0); 
   gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	//clear the buffers
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_MODELVIEW);  
	
    //and load the identity matrix
    glLoadIdentity();
    
    //bring in the background texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 
		0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data); 
	glTranslatef(300,-275,-500);
    glEnable(GL_TEXTURE_2D);
//    glColor3f(0,0,1);
    glRotatef(rotation,0,1,0);
    glRotatef(-90,1,0,0);
    gluSphere(quadricObj,200,200,200);
    glRotatef(90,1,0,0);
    glRotatef(-rotation,0,1,0);
    rotation += rotationSpeed;
    if(rotation>360)
                    rotation = 0;
    glDisable(GL_TEXTURE_2D);  
    glTranslatef(-300,275,500);
    //and map it
//    glEnable(GL_TEXTURE_2D);
//    gluSphere(quadricObj,1000.0, 20,20);
//    glDisable(GL_TEXTURE_2D);
    
    //time to draw stars
    updateStars();
    drawStars();
    	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 
		0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data); 

    updateRocks();
    drawRocks();
    
//	pinFloor();
//    pinBackgroundTexture();

	
	//figure out where the fighter/ship is going to be
    figureFighter();
    
    //move the draw points that way!
	glTranslatef(f_x,f_y,f_z);
	
	//and rotate too
	glRotatef(f_roll,0,1,0);
	glRotatef(f_pitch,1,0,0);
	
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 
//		0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data); 
    
    //draw the fighter
	drawFighter();
	
	//draw the shot
   	if(shoot){
    drawShot();
    shoot = 0;
    }
    
    //and the crosshair/aiming box    
    crosshair();

    //reset the movement
    glRotatef(-f_pitch,1,0,0);
    glRotatef(-f_roll,0,1,0);
    glTranslatef(-f_x,-f_y,-f_z);
	
	//change the current texture
/*    glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 
		0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data); */
    //and display the intro screen (if the intro is still about)
    //startScreen();
    drawScore();
    
    
    checkSpace();
    
    //deflicker and re-display
    glutSwapBuffers();
    glutPostRedisplay();
}
}

/*
* Fighter figure function
*/
void drawFighter(void){
//    glColor3f(1,1,1);
if(draw3ds){
    glRotatef(90,1,0,0);
    modelAPI.lit = false;
//    modelAPI.shownormals = true;
     modelAPI.Draw();
//     glDisable(GL_TEXTURE_2D);

           
     glRotatef(-90,1,0,0); 
//        glEnable(GL_TEXTURE_2D);
 
   	glGenTextures(1, &myTexture); //generate one texture identified as myTexture
   	glBindTexture(GL_TEXTURE_2D, myTexture); //tells which texture we will be working with.
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
else{
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
//	glDisable(GL_TEXTURE_2D);
    }
}

//////////////////////////////////////////////////////
/*Displays Second Window (Help Menu)*/
void helpDisplay(void)
{
  
  	//clear black background
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
		
	//change draw color to white
	glColor3f(1.0, 1.0,1.0); 
	
	//set draw position
	glRasterPos2f(0, 2);
	bigText("'i' to display this message");
	
	//a little lower for the next message
	glRasterPos2f(0, 1);
	bigText("'c' to close this window");

	//and even lower for the last message
	glRasterPos2f(0,0);
	bigText("'q' to quit");

	//execute commands
	glutSwapBuffers();
	glutPostRedisplay();

  
}

////////////////////////////////////////////////////////////


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
   glFrustum (-1.0, 1.0, -1.0, 1.0, 2, 1000.0); 
   gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
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
    glutReshapeWindow(800,600);
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
  
  //check for keypress (switch doesn't take non-statics)
  if(key == up){
         f_vel_y = vel_y;
         goingDown = 0;
         goingUp = 1;
         levelling = 0;
         //f_pitch = 10.0f;
         }
    else if(key==down){
         f_vel_y = -vel_y;
         goingUp = 0;
         goingDown = 1;
         levelling = 0;
         //f_pitch = -10.0f;
         }
    else if(key ==left){
         f_vel_x = -vel_x;
         goingRight = 0;
         goingLeft = 1;
         noRoll = 0;
         
//         f_roll = 10.0f;
         }
    else if(key==right){
         f_vel_x = vel_x;
//         f_roll = -10.0f;
           goingLeft = 0;
           goingRight = 1;
           noRoll = 0;
         }
         if(key == fire){
                    PlaySound(TEXT("15.wav"),NULL,SND_ASYNC);
                shoot = 1;
                }
  //check statics
	switch(key)
	{
    case 'Q':
		  exit(0);
		  break;
    case 'I':
         instructions = 1;
         break;
    case 'F':
         checkFullscreen();
         break;
    case 'C':
         instructions = 0;    
         break;
    case 'T':
         draw3ds = !(draw3ds);
         break;
    default:
            break;
    //redisplay the screen;
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
		glVertex3f(-50.0f, -100.0f, -40.0f); //bottom left back
		//glVertex3f(-19.0f, -19.0f, -35.0f); //bottom left back

		//Set the top left of the image
		glTexCoord2f(0.0f, 1.0f); //top left of the 2D viewport in the window
		glVertex3f(-50.0f, 0.0f, -40.0f); //top left back
		//glVertex3f(-19.0f, 19.0f, -35.0f); //top left back

		//Set the top right of the image
		glTexCoord2f(1.0f, 1.0f); //top right of the 2D viewport in the window
		glVertex3f( 50.0f, 0.0f, -40.0f); //top right back
		//glVertex3f( 19.0f, 19.0f, 35.0f);

		//Set the bottom right of the image
		glTexCoord2f(1.0f, 0.0f); //bottom right of the 2D viewport in the window
		glVertex3f( 50.0f, -100.0f, -40.0f); //bottom right back
		//glVertex3f( 19.0f, -19.0f, -35.0f); //bottom right back
        //floor, bottom right

		//Change the vertex locations where the texture is mapped and see the result
  
	glEnd();  // done with the texture map
	glDisable(GL_TEXTURE_2D); //We don't want to map onto the sphere 
  //////////////////////////////////////////////////////////////////////
}
void pinFloor(){
     glEnable(GL_TEXTURE_2D);
     glBegin(GL_QUADS);
             		glTexCoord2f(1,1);

        glVertex3f( 50.0f,-20.0f,-40.0f);

        		glTexCoord2f(0,1);

        glVertex3f(-50.0f, -20.0f,-40.0f);

        		glTexCoord2f(0,0);

        glVertex3f(-50.0f,-20.0f,0.0f);
        		glTexCoord2f(1,0);

        glVertex3f(50.0f,-20.0f,0.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
     }
/*void startScreen(){
     if(intro){
               introAlpha --;
               pinIntro();
               }
     if(introAlpha <= 0){
     intro = 0;                       
     }
                            
}
void pinIntro(){
	
	glEnable(GL_TEXTURE_2D); 

	glBegin(GL_QUADS);
		//Set the bottom left of the image
		glTexCoord2f(0.0f, 0.0f); //bottom left of the 2D viewport in the window
        //glVertex3f(-3.2f, 0.0f, 4.5f); //bottom left back
		glVertex3f(-3.7f, 0.0f, 4.5f); //bottom left back
		
        //glVertex3f(-19.0f, -19.0f, -35.0f); //bottom left back

		//Set the top left of the image
		glTexCoord2f(0.0f, 1.0f); //top left of the 2D viewport in the window
		//glVertex3f(-3.0f, 4.5f, 0.0f); //top left back
        glVertex3f(-3.7f, 4.5f, 0.0f); //top left back
		//glVertex3f(-19.0f, 19.0f, -35.0f); //top left back

		//Set the top right of the image
		glTexCoord2f(1.0f, 1.0f); //top right of the 2D viewport in the window
		glVertex3f( 4.0f, 4.5f, 0.0f); //top right back
		//glVertex3f( 19.0f, 19.0f, 35.0f);

		//Set the bottom right of the image
		glTexCoord2f(1.0f, 0.0f); //bottom right of the 2D viewport in the window
		glVertex3f( 3.2f, 0.0f, 4.5f); //bottom right back
		//glVertex3f( 19.0f, -19.0f, -35.0f); //bottom right back

		//Change the vertex locations where the texture is mapped and see the result
  
    // stop the rectangle!
	glEnd();  
	
	//turn off textures
	glDisable(GL_TEXTURE_2D); 
	
	//display it all
	glutSwapBuffers();
	glutPostRedisplay();
     }*/


//timer for good measure. 30 frames a second. Kind of heavy
void myTime(int time){
     	glutPostRedisplay();
	glutTimerFunc(1000/30,myTime,1);
     }
//find out where the fighter is
 void figureFighter(){
      //min,max x= -3, 3
      //min,max y = -3, 3
      if(goingUp){
                  if(f_pitch < pitchMax){
                                    f_pitch += pitchSpeed;
                                    }
                  else{
                                    goingUp = 0;
                                    //levelling = 1;
                                    }
                                    }             
      else if(goingDown){
                         if(f_pitch >-pitchMax){
                                    f_pitch -= pitchSpeed;
                                    }
                         else{
                                    goingDown = 0;
                                    //levelling = 1;
                                    }
                                    }
      if(levelling){
                    if(f_pitch > 0.0f){
                               f_pitch -=pitchLevel;
                    }
                    if(f_pitch < 0.0f){
                               f_pitch += pitchLevel;
                               }
                  //  if( -0.1f <= f_pitch <= 0.01f){
                  //             f_pitch = 0;
      }
                                              
            if(goingRight){
                  if(f_roll > -rollMax){
                                    f_roll -= rollSpeed;
                                    }
                  else{
                                   goingRight = 0;
                                    //levelling = 1;
                                    }
                                    }             
      else if(goingLeft){
                         if(f_roll < rollMax){
                                    f_roll += rollSpeed;
                                    }
                         else{
                                    goingLeft = 0;
                                    //levelling = 1;
                                    }
                                    }
      if(noRoll){
                    if(f_roll > 0.0f){
                               f_roll -=rollLevel;
                    }
                    if(f_roll < 0.0f){
                               f_roll += rollLevel;
                               }
                  //  if( -0.1f <= f_pitch <= 0.01f){
                  //             f_pitch = 0;
      
                                              }
      //move the fighter via velocity
      f_x += f_vel_x;
      f_y += f_vel_y;

      //check for edges
      if(f_x>xmax){
                f_x = xmax;
                f_vel_x = 0;
                }
      if(f_x<xmin){
                 f_x = xmin;
                 f_vel_x = 0;
                 }
      if(f_y>ymax){
                f_y=ymax;
                f_vel_y=0;
                }
      if(f_y<ymin){
                 f_y=ymin;
                 f_vel_y=0;
                 }
      }
void updateStars(){
     for(int i = 0; i < fieldSize; i++){
             field[i].updatez(speed);
             if(field[i].getz() > 10){
                                    field[i].reset();
                                    }
             }
     }
void drawStars(){
     
     glColor3f(1,1,1);
     for(int i = 0; i < fieldSize; i++){
             glPointSize(field[i].getSize());
             glBegin(GL_POINTS);
             glVertex3f(field[i].getx(),field[i].gety(),field[i].getz());
             glEnd(); 
             }
                
}

void drawShot(){
     glBegin(GL_TRIANGLES);
   	 glColor3f(.9,.9,1);
   	 glVertex3f(-1.0, 0,-2.5);
   	 glVertex3f(-1.25,0.0, -50.00);
     glVertex3f(-.75,0.0, -50.00);

//     glColor3f(.9,.9,1);
   	 glVertex3f(1, 0.0,-2.5);
 	 glVertex3f(1.25,0.0, -50.00);
     glVertex3f(0.75,0.0, -50.00);
     // glVertex3f(1,-20.0,-20.0);
     glEnd();

}
     
void crosshair(){
     glEnable(GL_BLEND);
    glBegin(GL_QUADS);
    glColor4f(0.0f,1.0f,0.0f,0.40f);
    glVertex3f(-1.5,1.5,-50);
    glVertex3f(-1.5,-1.5,-50);
    glVertex3f(1.5,-1.5,-50);
    glVertex3f(1.5,1.5,-50);
    glEnd();
    glLineWidth(2.0f);
    glColor4f(0.0f,1.0f,0.0f,1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 1.0f, -45.8f);
    glVertex3f(0.0f, -1.0f, -45.8f);
    glVertex3f(-1.0f,0.0f,-45.8f);
    glVertex3f(1.0f,0.0f,-45.8f);
    glEnd();
    
    glDisable(GL_BLEND);
}
void drawRocks(){
     glColor3f(.7,.7,.2);
     for(int i = 0; i < numRocks; i++){
             if(!rocks[i].isDestroyed()){
             glTranslatef(rocks[i].getX(),rocks[i].getY(),rocks[i].getZ());
             glRotatef(rocks[i].getRotation(),0,1,1);
             glEnable(GL_TEXTURE_2D);
             gluSphere(quadricObj,1,20,20);
             glDisable(GL_TEXTURE_2D);
             glRotatef(-rocks[i].getRotation(),0,1,1);
             glTranslatef(-rocks[i].getX(),-rocks[i].getY(),-rocks[i].getZ());
             }
             }
     }
void updateRocks(){
     for(int i = 0; i < numRocks; i++){
             rocks[i].updateRotation();
             rocks[i].updateZ(rocks[i].getSpeed());
             
             if(rocks[i].getZ() > 10){
                                    rocks[i].reset();
                                    }
             }
     }
void drawScore(){
     
     glColor3f(1,1,1);
    
     glRasterPos3f(7,-7,3);
	bigText("Score: ");
}
void checkSpace(){
     for(int i = 0; i < numRocks; i++){
             if(rocks[i].getZ()>-50.0f){
                                        
                                        }
     }     
}

//including the header
#include "project3.h"

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
    glutAddMenuEntry("Quality",3);
    glutAddMenuEntry("Quit",4);
    
    //load the fighter
    modelAPI.Load("fighter.3ds");
    
    //and attaching it to an event (right-mouse click)
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    //creating star array
    for(int i = 0; i < fieldSize; i++){
            field[i].reset();
    }
   //and an asteroid/rock array
    for(int i = 0; i < numRocks; i++){
            rocks[i].reset(mode);
    }
    
    //show the main window as default
    glutSetWindow(mainWindow);
        
    //some settings about coordinate style
   	gluQuadricTexture(quadricObj, GLU_TRUE);
    	
   	//load the images into memory
    TextureImage[0] = auxDIBImageLoad("sy.bmp"); //load the image file
   	TextureImage[1] = auxDIBImageLoad("rock.bmp"); //load the image file
    TextureImage[2] = auxDIBImageLoad("aj.bmp"); //load the image file
    TextureImage[3] = auxDIBImageLoad("planet.bmp");
    TextureImage[4] = auxDIBImageLoad("rn.bmp");

    //pixel storage mode (drawing options)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /*
    * more texture things.
    * I'm not sure how all of these others work
    * Edit: I know it generates and binds textures now. We had a HUGE
    * issue about having multiple loaders and now we have to call this
    * after we use the other loader because it unbinds our stuff!
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

    //and process events   
    glutMainLoop();

    //we should never get here...
    return 0;
}


/*
* key-up handler. I couldn't handle velocity changes very well without
* the very useful glutKeyUpFunc 
* Thank the lord I made variable names for directions. It'd be horrible
* to have this hard-coded
*/
void mainKeyUp(unsigned char key, int pointx, int pointy){
     //check for which key is up, and reset its velocity
    key = toupper(key);
    if(key == up){
        f_vel_y = 0.0f;
        goingUp = 0;
        goingDown = 0;
        levelling = 1;
    }
    else if(key == down){
        f_vel_y = 0.0f;
        goingDown = 0;
        goingUp = 0;
        levelling = 1;
    }
    else if(key == left){
        f_vel_x = 0.0f;
        goingLeft = 0;
        goingRight = 0;
        noRoll = 1;
    }
    else if(key == right){
        f_vel_x = 0.0f;
        goingLeft = 0;
        goingRight = 0;
        noRoll = 1;
    }
}

//////////////////////////////////////////////////////
/*
* Main Window Display
* Big fat mess. Used boolean/ints to check for part of app we're in
* Makes sense, but not the best way to do things
*/
void myDisplay(void)
{ 
    //checking to see if we want to show instructions
    if(instructions){    
        //change view to parallel (for 2-d action)                 
        glOrtho(-1,1,-1,1,1,-1);
        glLoadIdentity();                    
        
        //clear black background
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //turn off depth-testing
        glDisable(GL_DEPTH_TEST);
        
        //housekeeping function
        updateIntro();
        
        //load asteroid texture 
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 
        0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data); 
        
        //move to the corner of the screen
        //and draw a textured asteroid... that spins!
        glTranslatef(-10,7,0);
        glEnable(GL_TEXTURE_2D);
        glRotatef(introRotation,0,1,0);
        gluSphere(quadricObj,3,20,20);//asteroid code
        glRotatef(-introRotation,0,1,0);
        glDisable(GL_TEXTURE_2D);
        glTranslatef(10,-7,0);//reset rotation and movement
        
        //draw a nice background color for the instructions
        glColor3f(0,0,.4);
        glBegin(GL_QUADS);
        glVertex2f(-6,9);
        glVertex2f(7,8.5);
        glVertex2f(7,-7);
        glVertex2f(-7,-5);
        glEnd();
        
        //set draw position and
        //change draw color to white
        glColor3f(1.0, 1.0,1.0); 
        
        //and now a bunch of text in different places
        glRasterPos2f(-2, 8);
        bigText("Space! (The game... that we lost)");
        glRasterPos2f(-1, 7);
        bigText("Controls:");
        glRasterPos2f(-5, 5);
        bigText("w,s,a,d - Move");
        glRasterPos2f(-5,4);
        bigText("Spacebar - Shoot");
        glRasterPos2f(-5,3);
        bigText("t - toggle 'quality'");
        glRasterPos2f(-5, 2);
        bigText("i - display this message");
        glRasterPos2f(-5, 1);
        bigText("c - close this screen");
        glRasterPos2f(-5, 0);
        bigText("n - sound (because s is for moving)");
        glRasterPos2f(-5, -1);
        bigText("p - pause");
        glRasterPos2f(-5, -2);
        bigText("q - quit/credits");

        //execute commands
        glutSwapBuffers();
        glutPostRedisplay();
        glEnable(GL_DEPTH_TEST);
    }
    else if(quitting){//display this if we're getting out of here
        //checking if we just started to quit
        if(quitStart){
        if(sound)
            PlaySound(TEXT("exp.wav"),NULL,SND_ASYNC);
            quitStart = 0;
        }
        //parallel view... again
        glOrtho(-1,1,-1,1,1,-1);
        
        //reset the matrix
        glLoadIdentity(); 
        
        //move the screen (starting at the bottom)
        glTranslatef(0,endHeight,0);
        
        //clear background
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        
        //big Red game over for you =)
        glColor3f(1,0,0);
        glRasterPos2f(-2,8);
        bigText("GAME OVER");
        
        //and more text
        glColor3f(1,1,1);
        glRasterPos2f(-3,7);
        bigText("Yeah yeah yeah, you lost it");
        glRasterPos2f(-2,6);
        bigText("Oh, your score:");
        glRasterPos2f(-1,5);
        char sscore[20]; //conversion from integer to character
        itoa(score,sscore,10);
        bigText(sscore);
        
        //and a LOT more text
        glRasterPos2f(-3,4);
        bigText("This software brought to you by:");
        glRasterPos2f(-9,2);
        bigText("This guy ^");
        glRasterPos2f(-9,1);
        bigText("Sunchol Yoo - xionwardz@gmail.com");
        glRasterPos2f(0,0);
        bigText("This guy >");
        glRasterPos2f(0,-1);
        bigText("Alex Bonilla - ajbonill@sfsu.edu");
        glRasterPos2f(-9,-2);
        bigText("and this one");
        glRasterPos2f(-9,-3);
        bigText("Ramil Nobleza - rome.mil@gmail.com www.odddiscoveries.com");
        
        //boxes and pictures
        glColor3f(1,1,1); 
        glBegin(GL_QUADS);
        glVertex2f(-8.25,5.25);
        glVertex2f(-4.75,5.25);
        glVertex2f(-4.75,9.25);
        glVertex2f(-8.25,9.25);
        glEnd();
        //load image (sunchol)
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 
        0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        glEnable(GL_TEXTURE_2D);
        //throw it on a quadrilateral
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-8,5.5);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-5,5.5);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f(-5,9);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f(-8,9);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        //this is all copy-pasted from the first set
        //I just changed the coordinates
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glVertex2f(8.25,0.75);
        glVertex2f(4.75,0.75);
        glVertex2f(4.75,5.25);
        glVertex2f(8.25,5.25);
        glEnd();
        //alex
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 
        0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);        
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(8,1);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(5,1);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f(5,5);
        glTexCoord2f(01.0f, 01.0f); 
        glVertex2f(8,5);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glVertex2f(-8.25,-4.75);
        glVertex2f(-4.75,-4.75);
        glVertex2f(-4.75,-9.25);
        glVertex2f(-8.25,-9.25);
        glEnd();
        //and me (ramil)
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->sizeX, TextureImage[4]->sizeY, 
        0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->data);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f(-8,-5);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f(-5,-5);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-5,-9);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-8,-9);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        

        //display stuff
        glutSwapBuffers();
        glutPostRedisplay();
        
        //raise the screen a little
        endHeight += .02;
        //check to see if we're done raising
        if(endHeight >= 0){	
        Sleep(5000); //wait for five seconds then quit
        exit(0);
        }
    }
    else if(pause){ 
         glutPostRedisplay();//if pause... do nothing.
    }
    else{ //now on to the "normal" stuff
        //create a nicely huge volume
        glFrustum (-1.0, 1.0, -1.0, 1.0, 2, 1000.0); 
        
        //place the camera somewhere
        gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
        
        //clear the buffers
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        
        //switch the matrixtype
        glMatrixMode (GL_MODELVIEW);  
        
        //and load the identity matrix
        glLoadIdentity();
        
        //bring in the planet texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 
        0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data); 
        
        //move down to the bottom-right
        glTranslatef(300,-275,-500);

        //make a (textured AND rotating) planet
        glEnable(GL_TEXTURE_2D);
        glRotatef(rotation,0,1,0);
        glRotatef(-90,1,0,0);
        gluSphere(quadricObj,200,200,200); //object generation
        glRotatef(90,1,0,0);               //de-rotate
        glRotatef(-rotation,0,1,0); //de-rotate some more
        rotation += rotationSpeed; //update rotation
        if(rotation>360) 
                rotation = 0;
        glDisable(GL_TEXTURE_2D);   //turn off textures
        glTranslatef(-300,275,500); //move back to identity
        
        //time to draw stars
        updateStars(); //update positions
        drawStars();   //and draw!
        
        //load in the asteroid texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 
        0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data); 
        //and same thing: update and draw
        updateRocks();
        drawRocks();        
        
        //figure out where the fighter/ship is going to be
        figureFighter();
        
        //move the draw points that way!
        glTranslatef(f_x,f_y,f_z);
        
        //and rotate too
        glRotatef(f_roll,0,1,0);
        glRotatef(f_pitch,1,0,0);
               
        //draw the fighter
        drawFighter();
        
        //draw the shot
        if(shoot){
        drawShot();
        }
        
        //and the crosshair/aiming box    
        crosshair();
        
        //reset the movement
        glRotatef(-f_pitch,1,0,0);
        glRotatef(-f_roll,0,1,0);
        glTranslatef(-f_x,-f_y,-f_z);
                
        //check for collisions
        checkSpace();
        
        //reset the shots
        shoot = 0;
        
        //display the score
        glColor3f(0,0,0);

        glRasterPos3f(6,-8,1);
        char ascore[20]; //conversion from integer to character
        itoa(score,ascore,10);
        bigText("Score:");    
        glRasterPos3f(8,-8,1);
        bigText(ascore);    
        
        //deflicker and re-display
        glutSwapBuffers();
        glutPostRedisplay();
        }
}

/*
* Fighter figure function (updates the fighter's position
*/
void drawFighter(void){
    if(draw3ds){ //if high-quality mode XD
        glRotatef(90,1,0,0); //we have to rotate for some reason
        modelAPI.lit = false; //I forgot why this is in here
        modelAPI.Draw(); //draw the fighter     
        glRotatef(-90,1,0,0); //rotate back
        
        //man, we have to re-gen the textures after using that draw()
        //inefficient, but it works
        glGenTextures(1, &myTexture);
        glBindTexture(GL_TEXTURE_2D, myTexture); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    else{ //if "low" quality mode

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
    }
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
		instructions = 1;
		break;
	case 2: 
		checkFullscreen();
		break;
	case 3:
         draw3ds = !(draw3ds);
         break;
	case 4: 
		quitting = 1;
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
    if(!quitting){ //if we're not on the quit screen
        if(!instructions){ //or in instructions
                           //process movement
            //check for keypress (switch doesn't take non-statics)
            //and set variables/do magic
            if(key == up){
                f_vel_y = vel_y;
                goingDown = 0;
                goingUp = 1;
                levelling = 0;
            }
            else if(key==down){
                f_vel_y = -vel_y;
                goingUp = 0;
                goingDown = 1;
                levelling = 0;
            }
            else if(key ==left){
                f_vel_x = -vel_x;
                goingRight = 0;
                goingLeft = 1;
                noRoll = 0;
            }
            else if(key==right){
                f_vel_x = vel_x;
                goingLeft = 0;
                goingRight = 1;
                noRoll = 0;
            }
            if(key == fire){
                if(sound){
                    PlaySound(TEXT("15.wav"),NULL,SND_ASYNC);
                    }
                shoot = 1;
                }
            }
            //check static keys
            switch(key)
            {
            case 'Q': //quit
                instructions = 0;
                quitting = 1;
                break;
            case 'I': //instructions
                instructions = 1;
                break;
            case 'F': //fullscreen
                checkFullscreen();
                break;
            case 'C': //close instructions
                instructions = 0;    
                break;
            case 'T': //toggle quality
                draw3ds = !(draw3ds);
                break;
            case 'M': // de-randomize asteroids
                mode = !(mode);
                break;
            case 'P': //pause
                pause = !(pause);
                break;
            case 'N': //sound
                sound = !(sound);
                break;
            default:
                //redisplay the screen... just in case
                glutPostRedisplay();
                break;
                }
            //redisplay the screen... just in case
            glutPostRedisplay();
            }
        else
            { //if quitting
            switch(key){
                case 'Q': //only allow 'Q'... to exit
                    exit(0);
                    break;
                default:
                    break;
            }     
        }
}

//////////////////////////////////////////////////////////////////////
/*
* bigText, taken from Kroll. Awesome stuff.
*/
void bigText(char *s){
	for (unsigned int i=0; i<strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
} 


//timer for good measure. 30 frames a second. Kind of heavy
void myTime(int time){
    glutPostRedisplay();
	glutTimerFunc(1000/30,myTime,1);
}

//find out where the fighter is
void figureFighter(){
    if(goingUp){ //see if we're rising
        if(f_pitch < pitchMax){ //check for max-phi(pitch)
            f_pitch += pitchSpeed;
        }
        else{ //if phi = max-phi, stop going up
            goingUp = 0;
        }
    }             
    else if(goingDown){ //same deal, but with min-phi(pitch)
        if(f_pitch >-pitchMax){
            f_pitch -= pitchSpeed;
        }
        else{
            goingDown = 0;
        }
    }
    if(levelling){ //check to see if we're levelling (setting phi to zero)
        if(f_pitch > 0.0f){
            f_pitch -=pitchLevel; //reset phi slowly
        }
        if(f_pitch < 0.0f){
            f_pitch += pitchLevel; //in both directions
        }
    }
    /*
    * The same logic from above with up-down and theta(pitch)
    * follows using left-right and phi(roll)
    */
    if(goingRight){  
        if(f_roll > -rollMax){
            f_roll -= rollSpeed;
        }
        else{
            goingRight = 0;
        }
    }             
    else if(goingLeft){
    if(f_roll < rollMax){
            f_roll += rollSpeed;
        }
        else{
            goingLeft = 0;
        }
    }
    //noRoll ~= levelling by the way
    if(noRoll){
        if(f_roll > 0.0f){
            f_roll -=rollLevel;
        }
        if(f_roll < 0.0f){
            f_roll += rollLevel;
        }
    }

    //move the fighter via velocity
    f_x += f_vel_x;
    f_y += f_vel_y;
    
    //check for edges
    //if we reach an edge, stop. duh.
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

/*
* Small book-keeping function, updates the positions of stars and
* resets them if they're out of bounds
*/
void updateStars(){
    for(int i = 0; i < fieldSize; i++){
        field[i].updatez(speed); //update the positions
        if(field[i].getz() > 10){ //check if they need to reset
            field[i].reset();
        }
    }
}
/*
* Actual drawing algorithm. 
* Cycles through stars and draws points
* each star has a random size that's why glBegin(GL_POINTS) is IN the loop
*/
void drawStars(){
     glColor3f(1,1,1); //star color to white
     for(int i = 0; i < fieldSize; i++){
         glPointSize(field[i].getSize());
         glBegin(GL_POINTS);
         glVertex3f(field[i].getx(),field[i].gety(),field[i].getz()); //draw!
         glEnd(); 
     }
                
}

/*
* Function to output the fighter's shot.
* Simple, didn't want to clutter any more the
* myDisplay function
*/
void drawShot(){
     glBegin(GL_TRIANGLES);
   	 glColor3f(.9,.9,1);
   	 glVertex3f(-1.0, 0,-2.5);
   	 glVertex3f(-1.25,0.0, -50.00);
     glVertex3f(-.75,0.0, -50.00);

   	 glVertex3f(1, 0.0,-2.5);
 	 glVertex3f(1.25,0.0, -50.00);
     glVertex3f(0.75,0.0, -50.00);
     glEnd();
}
     
//and a cross-hair (with alpha!) for good measure
void crosshair(){
     
    //enable alpha-blending
    glEnable(GL_BLEND);
    //box for crosshair
    glBegin(GL_QUADS);
    glColor4f(0.0f,1.0f,0.0f,0.40f);
    glVertex3f(-1.5,1.5,-50);
    glVertex3f(-1.5,-1.5,-50);
    glVertex3f(1.5,-1.5,-50);
    glVertex3f(1.5,1.5,-50);
    glEnd();
    
    //actual crosshair
    glLineWidth(2.0f);
    glColor4f(0.0f,1.0f,0.0f,1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 1.0f, -45.8f);
    glVertex3f(0.0f, -1.0f, -45.8f);
    glVertex3f(-1.0f,0.0f,-45.8f);
    glVertex3f(1.0f,0.0f,-45.8f);
    glEnd();
    //disable blending
    glDisable(GL_BLEND);
}

/*
* Rock-drawing algorithm. Like stars, but with a check to see
* if we're supposed to draw it in the first place
*/
void drawRocks(){
    glColor3f(.7,.7,.2);
    for(int i = 0; i < numRocks; i++){ //cycle through rocks
        if(!(rocks[i].isDestroyed())){ //if it still exists, draw!
            glTranslatef(rocks[i].getX(),rocks[i].getY(),rocks[i].getZ());
            glRotatef(rocks[i].getRotation(),0,1,1);
            glEnable(GL_TEXTURE_2D); //oh, and they're textured
            gluSphere(quadricObj,1,20,20);
            glDisable(GL_TEXTURE_2D);
            glRotatef(-rocks[i].getRotation(),0,1,1);
            glTranslatef(-rocks[i].getX(),-rocks[i].getY(),-rocks[i].getZ());
        }
    }
}
/*
* same as updateStars... but for Asteroids/rocks
*/
void updateRocks(){
    for(int i = 0; i < numRocks; i++){//cycle through rocks
        rocks[i].updateRotation(); //rotate a little more
        rocks[i].updateZ(rocks[i].getSpeed());  //move it up a little
        if(rocks[i].getZ() > 10){ //reset if it needs to
            rocks[i].reset(mode); //regenerate (if mode, random is off)
        }
    }
}

/*
* Yay, collision detection! I had logic errors here earlier
* apparently (xmin < x < xmax) != ((xmin < x) && (x < xmax))
* I think it shifts then compares in the first case.
*/
void checkSpace(){
    if(shoot){
        float x = f_x;
        float y = f_y;
        float z = f_z;
        for(int r = 0; r < 10000 ; r++){
        //it took me a little trig review and 10 minutes to 
        //figure these coordinates. It was a little harder 
        //because I have two rotations. I'm proud of me =)
            x = x - .01*sin(f_roll*(pi/180));
            y = y + .01*sin(f_pitch*(pi/180));
            z = z - .01*cos(f_roll*(pi/180))*cos(f_pitch*(pi/180));
            for(int i = 0; i < numRocks; i++){
                if(!(rocks[i].isDestroyed())){
                    //finding maxes
                    cxmax = (rocks[i].getX())+3.0f;
                    cymax = (rocks[i].getY())+3.0f;
                    czmax = (rocks[i].getZ())+3.0f;
                    //finding mins
                    cxmin = (rocks[i].getX())-3.0f;
                    cymin = (rocks[i].getY())-3.0f;
                    czmin = (rocks[i].getZ())-3.0f;
                    if( //HERE is where my logic error was
                    ((cxmin < x) && (x < cxmax))
                    &&  
                    ((cymin < y) && (y < cymax))
                    && 
                    ((czmin < z) && (z < czmax))){
                        rocks[i].destroy();
                        score +=1;
                    } //end destroying
                } //end if rocks exist
            } //end rock loop
        } //end shot check loop
    } //end if(shot)
    
    //and now we check for fighter-rock collision
    for(int j = 0; j < numRocks; j++){
        if(!(rocks[j].isDestroyed())){ //only check with existing rocks    
            //finding max values for bounding box
            cxmax = rocks[j].getX()+3.0f; //expanded X because wide fighter
            cymax = rocks[j].getY()+1.3f;
            czmax = rocks[j].getZ()+1.3f;
            //finding mins
            cxmin = rocks[j].getX()-3.0f;
            cymin = rocks[j].getY()-1.3f;
            czmin = rocks[j].getZ()-1.3f;
            if( //same logic error here
            ((cxmin < f_x) && (f_x < cxmax))
            &&  
            ((cymin < f_y) && (f_y < cymax))
            && 
            ((czmin < f_z) && (f_z < czmax))){
                quitting = 1;
            } //end quitting
        } //end isDestroyed check
    } //end rock loop
}
/*
* I think I went function crazy. This one is a simple update.
*/
void updateIntro(){
     introRotation += 0.5f;
}


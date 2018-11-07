/*

THIS GAME IS PREPARED BY
Atonu, Ahmed Zahin
14-28066-3
Islam, Sadiq
15-29599-2
Tapu, Taposhi Bain
15-29451-1
Khan, Nayeem-Uz-Zaman
14-28089-3


THE GAME SHOULD RUN IN 1366 X 768 RESOLUTION FOR BEST OUTPUT.


*/

#include<windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#include<fstream>
#include"imageloader.cpp"
#define UP 1
#define DOWN 2
#define RIGHT -1
#define LEFT -2

using namespace std;
GLuint _textureId;
int sd ;
int c = 0;
int x, y;
bool gameover = false;
float random;
int score;
string b = "Score";
string a=" ";





//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}



int _day = 1;

float _angle = 0.0;
float _move = 2.5;
int mv=2;

float _clmove1 = 0.0;
float _clmove2 = 0.0;
float _clmove3 = 0.0;

float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float angx = 1;
float angy = 0;
float angz = 0;
float zoom = 1;
int countkey = 0;
float rl = 0.0;
float ud = -2.3;
float ab = 5;
float boxlr = 0.0;
float startingspeed = 0.1;  /////////////////////speed//////////////////
float speed = startingspeed;
int red = 255;
int green = 0;
int blue = 0;
string Result;
int shape = 1;
int obstacle =1;
int decider_1=1;
int decider_2=1;
float currentspeed = 0.1;
int buttonDecider =0;
bool once =true;
string high,current;
bool ok=true;
int cr=0,hr=0;
bool inmenu = false;//////decides whether user is in menu or not ////////



//////////////Game over///////////////////
void game() //last black screen with gameover text
{
    speed =0;
    inmenu = false;
}
void text() //gameover text
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

	glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0); //Move forward 5 units



glClear(GL_COLOR_BUFFER_BIT);
glClearColor(1,1,1,0 );

glColor3ub(93, 109, 126 );
glBegin(GL_POLYGON);
glVertex3i(-9,-9,1);
glVertex3i(6,-9,1);
glVertex3i(6,6,1);
glVertex3i(-9,6,1);
glEnd();



glLoadIdentity(); //Reset the drawing perspective

	glTranslatef(1.0, 0.0, -7.0);


	string highscore="";
    ifstream resfile("result.txt");

    current=Result;
    getline(resfile,high);
    resfile.close();
    stringstream geek(high);
     hr = 0;
     geek >> hr;

    stringstream geek2(Result);
    cr = 0 ;
    geek2 >>cr;

    if(cr>hr)
    {

         ofstream reswrite("result.txt");
    reswrite<<Result;
    reswrite.close();
    }



    string myscore="Your Score : "+current;

    if(hr>=score){
        highscore="High score : "+high;
    }
    else{
        highscore="High score : "+current;
    }


    string go = "GAME OVER";
    string line = "PRESS 'SPACE' TO RESTART. ";


glColor3ub(255,255,255);


    glRasterPos3d(-1.3,.3,2);
	for(int i=0;go[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,go[i]);


    glRasterPos3d(-1.26,0,2);
	for(int i=0;myscore[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,myscore[i]);

        glRasterPos3d(-1.26,-.2,2);
	for(int i=0;highscore[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,highscore[i]);

        glRasterPos3d(-1.80,-.4,2);
	for(int i=0;line[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,line[i]);


}




//******************************************** DAY *******************************************//
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}






void initialize() {

	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.00, 1.0, 200.0);
	Image* image = loadBMP("star.bmp");

	_textureId = loadTexture(image);

	delete image;
}




void drawSceneDay() {

    inmenu = false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

	glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0); //Move forward 5 units



glClear(GL_COLOR_BUFFER_BIT);
glClearColor(1,1,1,0 );




glPushMatrix(); //Save the transformations performed thus far
///the cube starts




glPushMatrix();

glTranslatef( ab,-2.3, 0.0);//down up -(a+i)

glScalef(.5,0.5,0.5);
glColor3ub(255,160,160);
//glutSolidCube(1);


if (decider_1 % 2 == 0){
    if(decider_2%2==0)
    {
        glutSolidCube(1.2);
        obstacle=2;
    }
    else
    {
        glutSolidSphere(.7,20,20);
        obstacle =1;

    }
}
else
{
    if(decider_2%2==0)
    {
        glutSolidTorus(.25,.55,20,40);
        obstacle=3;
    }
    else
    {
        glPushMatrix();

    glColor3ub(66, 73, 73);
    glutSolidCube(1.2);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-0.04,0.03,.7);
	glScalef(.58,.60,1);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();

    glPopMatrix();

        obstacle=4;
    }
}






///the cube ends


glPopMatrix();
///the cube ends


///the dot starts

glTranslatef(-4, ud, 0.0); //Move to the center of the trapezoid
glScalef(zoom,zoom,zoom);
glRotated(angx,1.0, 0.0, 0.0);
glRotated(angy,0.0, 1.0, 0.0);
glRotated(angz,0.0, 0.0, 1.0);


glPushMatrix();

glColor3ub(145, 187, 228);

if(shape == 1){
        glutSolidSphere(0.32,30,30);
}
else if(shape == 2){
        glutSolidCube(0.5);
}
else if(shape == 3){
        glutSolidTorus(.06,.28,20,40);
}


else if(shape == 4){


    glPushMatrix();

    glColor3ub(66, 73, 73);
    glutSolidCube(.5);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(0,0,.26);
	glScalef(.24,.24,0);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();


	glPushMatrix();
	glRotatef(75,0.01,1,0.01);
	glRotatef(8,0.01,.01,1);
	glTranslatef(4,-.45,.26);
	glScalef(1,1,1);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();
    glPopMatrix();


    glPopMatrix();




    glPushMatrix();

	glTranslatef(0.04,.28,.14);
	glRotatef(-85,1,0,-0.1);
	glRotatef(-20,0,0,1);
	glScalef(0.28,0.13,0.2);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();
    glPopMatrix();


    glPopMatrix();





}





glPopMatrix();


///the dot ends



glPopMatrix();
glColor3ub(252, 243, 207);

	glRasterPos3d(-5,-2.0,0.0);


        if(gameover)
            {
                game();
                text();

            }
stringstream convert; // stringstream used for the conversion

convert << score;//add the value of Number to the characters in the stream

Result = convert.str();//set Result to the content of the stream




	glRasterPos3d(-1.30,.7,1);

	for(int i=0;b[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,b[i]);

	glRasterPos3d(-1.2,.5,1);

	for(int i=0;Result[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Result[i]);









//////////////////////////////////////SKY////////////////////////////////

glPushMatrix();

glTranslatef(-2,-2,-1.5);
glScalef(10,10,.01);

glPushMatrix();

glColor3ub(0,175,255);
/*glBegin(GL_POLYGON);
glVertex3f(0,0,0);
glVertex3f(2,0,0);
glVertex3f(2,2,0);
glVertex3f(0,2,0);
*/

glutSolidCube(2);
glEnd();

glPopMatrix();

glPopMatrix();



//////////////////////////////////////Cloud 1/////

glPushMatrix();
glTranslatef(_clmove1,2,0.0);
glScalef(2,2,0);
glPushMatrix();

glColor3ub(196,192,192);
glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.2,0,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();








//////////////////////////////////////Cloud 2////////////////

glPushMatrix();
glTranslatef(_clmove2,1,0.0);
glScalef(1.7,1.7,0);
glPushMatrix();

glColor3ub(192,192,192);
glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.2,0,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();





//////////////////////////////////////Cloud 3 white/////

glPushMatrix();
glTranslatef(_clmove3,1.5,0.0);
glScalef(2.4,2.4,0);
glPushMatrix();

glColor3ub(255,255,255);
glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.2,0,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();



//////////////////////////////////////////////////////SUN //////////////////////////////////////////

glPushMatrix();

//glTranslatef(-5.4,1.8,-1.5);
glTranslatef(-5.4,_move,-1.5);

glColor3ub(255,255,0);
glutSolidSphere(.5,50,50);

glPopMatrix();















//////////////
glPushMatrix();

glTranslatef(0,0,-1);

////////////////////////////////////////////////MOUNTAIN ///////////////////////////////////////

glPushMatrix();
glTranslatef(-7,-2,0.0);
glScalef(3.2,1.5,0);

glPushMatrix();

glColor3ub(0,95,0);
glBegin(GL_POLYGON);
glVertex3f(0,0,0);
glVertex3f(.5,2.5,0);
glVertex3f(1.2,0,0);
glEnd();

glPopMatrix();

//
glPushMatrix();


glColor3ub(0,95,0);
glBegin(GL_POLYGON);
glVertex3f(.5,0,0);
glVertex3f(1,1.6,0);
glVertex3f(1.6,0,0);
glEnd();

glPopMatrix();


//
glPushMatrix();


glColor3ub(0,95,0);
glBegin(GL_POLYGON);
glVertex3f(.9,0,0);
glVertex3f(1.7,1.6,0);
glVertex3f(2,0,0);
glEnd();

glPopMatrix();


//
glPushMatrix();


glColor3ub(0,95,0);
glBegin(GL_POLYGON);
glVertex3f(1.5,0,0);
glVertex3f(2.1,2,0);
glVertex3f(2.6,0,0);
glEnd();

glPopMatrix();

//
glPushMatrix();


glColor3ub(0,95,0);
glBegin(GL_POLYGON);
glVertex3f(2.1,0,0);
glVertex3f(2.7,2.4,0);
glVertex3f(3.1,0,0);
glEnd();

glPopMatrix();



//
glPushMatrix();


glColor3ub(0,95,0);
glBegin(GL_POLYGON);
glVertex3f(2.6,0,0);
glVertex3f(3,1.8,0);
glVertex3f(3.6,0,0);
glEnd();

glPopMatrix();



//
glPushMatrix();


glColor3ub(0,95,0);
glBegin(GL_POLYGON);
glVertex3f(2.9,0,0);
glVertex3f(3.6,1.5,0);
glVertex3f(4.1,0,0);
glEnd();

glPopMatrix();


glPopMatrix();




glPopMatrix();

















///////////////////////////////


glPushMatrix();

///////////////////////////////////////////////////////////Tree 2///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(-2.2,-1.7,0.0);
     glBegin(GL_QUADS);

        glColor3ub(175,95,0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();






    ///////////////////////////////////////////////////////////Tree 3///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(1.1,-1.7,0.0);
    glScalef(.5,1,0);
     glBegin(GL_QUADS);

        glColor3ub(175,95,0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();





///////////////////////////////////////////////////////////Tree 4///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(1.5,-1.7,0.0);
    glScalef(.8,.6,0);
     glBegin(GL_QUADS);

        glColor3ub(175,95,0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();






    ///////////////////////////////////////////////////////////Tree 1///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(-5,-1.7,0.0);
    glScalef(.6,.7,0);
     glBegin(GL_QUADS);

        glColor3ub(175,95,0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(15, 150, 15);
        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();



//////////////////////////////////////BUSH 1/////

glPushMatrix();
glTranslatef(-1.7,-1.5,0.0);
glPushMatrix();

glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();

glColor3ub(15, 150, 15);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();






//////////////////////////////////////BUSH 2/////

glPushMatrix();
glTranslatef(-2.5,-1.5,0.0);
glPushMatrix();

glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();

glColor3ub(15, 150, 15);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();




//////////////////////////////////////BUSH 3/////

glPushMatrix();
glTranslatef(-4.8,-1.5,0.0);
glPushMatrix();

glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();

glColor3ub(15, 150, 15);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();









//////////////////////////////////////BUSH 4/////

glPushMatrix();
glTranslatef(.9,-1.5,0.0);
glPushMatrix();

glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();

glColor3ub(15, 150, 15);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();
/////////////////////



///////////////////////////////////////// Lamp post 1 //////////////////////


glPushMatrix();

    glTranslatef(-1.5,-1.7,0.0);
     glBegin(GL_QUADS);

        glColor3ub(175,95,0);
        glVertex3f(0,0,0);
        glVertex3f(.1,0,0);
        glVertex3f(.1,1.4,0);
        glVertex3f(0,1.4,0);

        glEnd();

glBegin(GL_QUADS);

        glColor3ub(175,9,0);
        glVertex3f(0,1.3,0);
        glVertex3f(.6,1.3,0);
        glVertex3f(.6,1.4,0);
        glVertex3f(0,1.4,0);

        glEnd();

glBegin(GL_TRIANGLES);

        glColor3ub(0,0,0);
        glVertex3f(.4,1,0);
        glVertex3f(.8,1,0);
        glVertex3f(.6,1.3,0);

        glEnd();



glPopMatrix();




/*
///////////////////////////////////////// Lamp post 2 //////////////////////


glPushMatrix();

    glTranslatef(2,-1.7,0.0);
     glBegin(GL_QUADS);

        glColor3ub(175,95,0);
        glVertex3f(0,0,0);
        glVertex3f(.1,0,0);
        glVertex3f(.1,1.4,0);
        glVertex3f(0,1.4,0);

        glEnd();

glBegin(GL_QUADS);

        glColor3ub(175,9,0);
        glVertex3f(0,1.3,0);
        glVertex3f(.6,1.3,0);
        glVertex3f(.6,1.4,0);
        glVertex3f(0,1.4,0);

        glEnd();

glBegin(GL_TRIANGLES);

        glColor3ub(0,0,0);
        glVertex3f(.4,1,0);
        glVertex3f(.8,1,0);
        glVertex3f(.6,1.3,0);

        glEnd();



glPopMatrix();




*/


///////////////////////////////////////////// RED n Yellow Building 1 //////////////////////////////////////////////////////////

glPushMatrix();

    glTranslatef(-6.15,-1.7,0.0);
    glBegin(GL_QUADS);

        glColor3ub(255,255,0);
        glVertex3f( .2, 0, 0);
        glVertex3f(.4,0,0);
        glVertex3f(.4,.8,0);
        glVertex3f(.2,.8,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor3ub(255,255,0);
        glVertex3f(.6,0,0);
        glVertex3f(.8,0,0);
        glVertex3f(.8,.8,0);
        glVertex3f(.6,.8,0);

        glEnd();

       glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(.4,.9,0);
        glVertex3f(.6,.9,0);
        glVertex3f(.6,1.1,0);
        glVertex3f(.4,1.1,0);

        glEnd();

        glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(.4,1.2,0);
        glVertex3f(.6,1.2,0);
        glVertex3f(.6,1.4,0);
        glVertex3f(.4,1.4,0);

        glEnd();


      glBegin(GL_QUADS);

        glColor3ub(255,255,0);
        glVertex3f(.2,.9,0);
        glVertex3f(.8,.9,0);
        glVertex3f(.8,1.1,0);
        glVertex3f(.2,1.1,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor3ub(255,255,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(.8,1.2,0);
        glVertex3f(.8,1.4,0);
        glVertex3f(.2,1.4,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor3ub(255,0,0);
        glVertex3f( 0.0, 0.0, 0.0);

        glVertex3f(1.0,0.0, 0.0);

        glVertex3f( 1.0,1.5, 0.0);
        glVertex3f(0,1.5,0);

        glEnd();



    glPopMatrix();




///////////////////////////////////////////// Purple Building 2 //////////////////////////////////////////////////////////

glPushMatrix();

    glTranslatef(-.3,-1.7,0.0);


//
     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,1.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,1.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,1.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();
//


    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.25,1.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.5,1.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.75,1.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



//

     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,1.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,1.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,1.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



//



    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.25,1.05,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.5,1.05,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.75,1.05,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

//


     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



//

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.25,.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.5,.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.75,.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();


    //



     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



   /*   glBegin(GL_QUADS);

        glColor4f(0,0,0,1);
        glVertex3f(.2,.9,0);
        glVertex3f(.8,.9,0);
        glVertex3f(.8,1.1,0);
        glVertex3f(.2,1.1,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor4f(0,0,0,1);
        glVertex3f(.2,1.2,0);
        glVertex3f(.8,1.2,0);
        glVertex3f(.8,1.4,0);
        glVertex3f(.2,1.4,0);

        glEnd(); */

    glBegin(GL_QUADS);

        glColor3ub(95,0,95);
        glVertex3f( 0.05, 0.0, 0.0);

        glVertex3f(.95,0.0, 0.0);

        glVertex3f(.95,2.1, 0.0);
        glVertex3f(0.05,2.1,0);

        glEnd();

        //glTranslatef(6.1f,1.5f,0.0f);


    glPopMatrix();


//////////////////////////////////////////////////////  Building with triangle //////////////////////////////////////////

   glPushMatrix();

    glTranslatef(-4.8,-1.7,0.0);

    glBegin(GL_QUADS);

        glColor3ub(128,0,0);
        glVertex3f(0.3,.3,0);
        glVertex3f(.5,.3,0);
        glVertex3f(.5,0.6,0);
        glVertex3f(.3,.6,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor3ub(128,0,0);
        glVertex3f(1.5,.3,0);
        glVertex3f(1.7,.3,0);
        glVertex3f(1.7,0.6,0);
        glVertex3f(1.5,.6,0);

        glEnd();




     glBegin(GL_QUADS);

        glColor3ub(192,192,192);
        glVertex3f(0.8,0,0);
        glVertex3f(1.2,0,0);
        glVertex3f(1.2,0.8,0);
        glVertex3f(.8,.8,0);

        glEnd();




     glBegin(GL_QUADS);

        glColor3ub(0,128,128);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);
        glVertex3f(2,1.1,0);
        glVertex3f(0,1.1,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(215,175,0);
        glVertex3f(-0.3,1.1,0);
        glVertex3f(2.3,1.1,0);
        glVertex3f(1,2,0);


        glEnd();



    glPopMatrix();








////////////////////////////////////////Sphere Building //////////////////////////////////
glPushMatrix();

glTranslatef(2.3,-1.7,0.0);

glPushMatrix();


     glBegin(GL_QUADS);

        glColor3ub(0,0,0);
        glVertex3f(0,0,0);
        glVertex3f(1.5,0,0);
        glVertex3f(1.5,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


glRotatef(_angle,3,4,0);
 glPushMatrix();

    glTranslatef(.7,.95,0.0);

        glRotatef(90,1,0,1);
        glColor3ub(255, 71, 26);
        glutWireSphere(.8,8,8);

    glPopMatrix();


    glPopMatrix();




////////////////////////////////////////// ROAD STRIPE //////////////////////////////////


 glPushMatrix();

    glTranslatef(-5.7,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();

    glPushMatrix();

    glTranslatef(-4.3,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.8,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


        glPushMatrix();
        glTranslatef(-1.3,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


            glPushMatrix();
        glTranslatef(.2,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


            glPushMatrix();
        glTranslatef(1.7,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();

            glPushMatrix();
        glTranslatef(3.2,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();



    /////////////////////////////////////////////// Road ////////////////////////////////////////////

    glPushMatrix();

    glTranslatef(-6.5,-3,0.0);
     glBegin(GL_QUADS);

        glColor3ub(88,88,88);
        glVertex3f(0,0,0);
        glVertex3f(12,0,0);
        glVertex3f(12,1.3,0);
        glVertex3f(0,1.3,0);

        glEnd();

    glPopMatrix();

    string pause ="";
if(buttonDecider==0)
    pause = "PAUSE";
else if (buttonDecider==1)
    pause = "RESUME";

string instructions = "INSTRUCTIONS";
string credits = "CREDITS";
string exit = "EXIT";


    glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0);

glColor3ub(255, 255, 236);
glScalef(1.2,0.5,.01);
glTranslatef(-2.6,5,1);
glutSolidCube(1);


glTranslatef(1.1,0,1);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glutSolidCube(1);




//FOREGROUND
glPopMatrix();



glColor3ub(175, 122, 197);

    glRasterPos3d(-3.2,2.3,0.5);
	for(int i=0;pause[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,pause[i]);

    glRasterPos3d(-2.25,2.3,0.5);
	for(int i=0;instructions[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,instructions[i]);

    glRasterPos3d(-.8,2.3,0.5);
	for(int i=0;credits[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,credits[i]);

    glRasterPos3d(.55,2.3,0.5);
	for(int i=0;exit[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,exit[i]);


glutSwapBuffers();



}



void lightSetting()
{

	GLfloat ambientIntensity[4] = {0.6, 0.6, 0.6, 1.0};

	GLfloat position[4] = {0.0, 1.0, 0.0, 0.0};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientIntensity);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
}


void instructions() { ///////////instructions page//////////

    inmenu = true;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

	glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0); //Move forward 5 units



glClear(GL_COLOR_BUFFER_BIT);
glClearColor(1,1,1,0 );

glColor3ub(57, 112, 159);
glBegin(GL_POLYGON);
glVertex3i(-9,-9,0);
glVertex3i(6,-9,0);
glVertex3i(6,6,0);
glVertex3i(-9,6,0);
glEnd();

glColor3ub(249, 231, 159);


glScalef(1.9,1,0.001);
glTranslatef(-0.70,-0.3,0);
glutSolidCube(4);






glLoadIdentity();
glTranslatef(1.0, 0.0, -7.0);
glTranslatef(0.23, 0.025, 0);



string htp = "HOW TO PLAY";
string step1 = "*MATCH THE SHAPES OF THE TESSERACT WITH";
string step1_2 = "THE OBSTACLES TO AVOID YOUR ANNIHILATION!* ";

string step2 = "*PRESS 'W/A/S/D' OR 'LEFT/RIGHT/UP/DOWN/* BUTTONS TO CHANGE SHAPES* ";
string step3 = "*PRESS '1' FOR NIGHT MODE*";
string step4 = "*PRESS '2' FOR DAY MODE*";
string step5 = "*PRESS 'P' TO PAUSE*";
string step6 = "*PRESS 'R' TO RESUME*";
string pause ="RESUME";

string instructions = "INSTRUCTIONS";
string credits = "CREDITS";
string exit = "EXIT";

glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0);

glColor3ub(255, 255, 236);
glScalef(1.2,0.5,.01);
glTranslatef(-2.6,5,1);
glutSolidCube(1);


glTranslatef(1.1,0,1);
glColor3ub(244, 208, 63);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glColor3ub(255, 255, 236);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glutSolidCube(1);

//FOREGROUND
glPopMatrix();

glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0);


glColor3ub(175, 122, 197);

    glRasterPos3d(-3.2,2.3,0.5);
	for(int i=0;pause[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,pause[i]);

    glRasterPos3d(-2.25,2.3,0.5);
	for(int i=0;instructions[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,instructions[i]);

    glRasterPos3d(-.8,2.3,0.5);
	for(int i=0;credits[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,credits[i]);

    glRasterPos3d(.55,2.3,0.5);
	for(int i=0;exit[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,exit[i]);

    glRasterPos3d(-1.8,.9,2);
	for(int i=0;htp[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,htp[i]);


    glRasterPos3d(-3.77,.2,2);
	for(int i=0;step1[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,step1[i]);

    glRasterPos3d(-3.7,0,2);
	for(int i=0;step1_2[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,step1_2[i]);

    glRasterPos3d(-3.77,-.2,2);
	for(int i=0;step2[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,step2[i]);

    glRasterPos3d(-3.77,-0.4,2);
	for(int i=0;step3[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,step3[i]);

    glRasterPos3d(-3.77,-0.6,2);
	for(int i=0;step4[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,step4[i]);

    glRasterPos3d(-3.77,-0.8,2);
	for(int i=0;step5[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,step5[i]);

    glRasterPos3d(-3.77,-1,2);
	for(int i=0;step6[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,step6[i]);

glutSwapBuffers();



}



void credits() { //////////// CREDITS ///////////

    inmenu = true;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

	glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0); //Move forward 5 units



glClear(GL_COLOR_BUFFER_BIT);
glClearColor(1,1,1,0 );

glColor3ub(57, 112, 159);
glBegin(GL_POLYGON);
glVertex3i(-9,-9,0);
glVertex3i(6,-9,0);
glVertex3i(6,6,0);
glVertex3i(-9,6,0);
glEnd();

glColor3ub(249, 231, 159);


glScalef(1.7,1,0.001);
glTranslatef(-0.85,-0.3,0);
glutSolidCube(4);



//////////////////////////////////////credits////////////////////////////////

string crd = "THIS GAME IS PREPARED BY";
string Line1 = "Atonu, Ahmed Zahin";
string Line2 = "14-28066-3";
string Line3 = "Islam, Sadiq ";
string Line4 = "15-29599-2 ";
string Line5 = "Tapu, Taposhi Bain";
string Line6 = "15-29451-1";
string Line7 = "Khan, Nayeem-Uz-Zaman";
string Line8 = "14-28089-3";

string pause ="RESUME";
string instructions = "INSTRUCTIONS";
string credits = "CREDITS";
string exit = "EXIT";


glColor3ub(20,20,20);

    glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0);

glColor3ub(255, 255, 236);
glScalef(1.2,0.5,.01);
glTranslatef(-2.6,5,1);
glutSolidCube(1);


glTranslatef(1.1,0,1);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glColor3ub(244, 208, 63);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glColor3ub(255, 255, 236);
glutSolidCube(1);

//FOREGROUND
glPopMatrix();

glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0);


glColor3ub(175, 122, 197);

    glRasterPos3d(-3.2,2.3,0.5);
	for(int i=0;pause[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,pause[i]);

    glRasterPos3d(-2.25,2.3,0.5);
	for(int i=0;instructions[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,instructions[i]);

    glRasterPos3d(-.8,2.3,0.5);
	for(int i=0;credits[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,credits[i]);

    glRasterPos3d(.55,2.3,0.5);
	for(int i=0;exit[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,exit[i]);

    glRasterPos3d(-2.05,.9,2);
	for(int i=0;crd[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,crd[i]);


    glRasterPos3d(-1.83,.2,2);
	for(int i=0;Line1[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line1[i]);

    glRasterPos3d(-1.65,0,2);
	for(int i=0;Line2[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line2[i]);

    glRasterPos3d(-1.63,-.2,2);
	for(int i=0;Line3[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line3[i]);

    glRasterPos3d(-1.65,-0.4,2);
	for(int i=0;Line4[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line4[i]);

    glRasterPos3d(-1.8,-0.6,2);
	for(int i=0;Line5[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line5[i]);
    glRasterPos3d(-1.65,-0.8,2);
	for(int i=0;Line6[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line6[i]);
    glRasterPos3d(-1.93,-1,2);
	for(int i=0;Line7[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line7[i]);
    glRasterPos3d(-1.65,-1.2,2);
	for(int i=0;Line8[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Line8[i]);

glutSwapBuffers();



}



//******************************************** NIGHT *******************************************//


void drawSceneNight() {

    inmenu = false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

	glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0); //Move forward 5 units



glClear(GL_COLOR_BUFFER_BIT);
glClearColor(1,1,1,0 );




glPushMatrix(); //Save the transformations performed thus far
///the cube starts




glPushMatrix();

glTranslatef( ab,-2.3, 0.0);//down up -(a+i)

glScalef(.5,0.5,0.5);
glColor3ub(255,160,160);
//glutSolidCube(1);


if (decider_1 % 2 == 0){
    if(decider_2%2==0)
    {
        glutSolidCube(1.2);
        obstacle=2;
    }
    else
    {
        glutSolidSphere(.7,20,20);
        obstacle =1;

    }
}
else
{
    if(decider_2%2==0)
    {
        glutSolidTorus(.25,.55,20,40);
        obstacle=3;
    }
    else
    {
        glPushMatrix();

    glColor3ub(66, 73, 73);
    glutSolidCube(1.2);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-0.04,0.03,.7);
	glScalef(.58,.60,1);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();

    glPopMatrix();
        obstacle=4;
    }
}





///the cube ends


glPopMatrix();
///the cube ends


///the dot starts

glTranslatef(-4, ud, 0.0); //Move to the center of the trapezoid
glScalef(zoom,zoom,zoom);
glRotated(angx,1.0, 0.0, 0.0);
glRotated(angy,0.0, 1.0, 0.0);
glRotated(angz,0.0, 0.0, 1.0);

glPushMatrix();

glColor3ub(145, 187, 228);

if(shape == 1){
        glutSolidSphere(0.32,30,30);


}
else if(shape == 2){
        glutSolidCube(0.5);
}
else if(shape == 3){
        glutSolidTorus(.06,.28,20,40);
}


else if(shape == 4){
        glPushMatrix();

    glColor3ub(66, 73, 73);
    glutSolidCube(.5);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(0,0,.26);
	glScalef(.24,.24,0);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();


	glPushMatrix();
	glRotatef(75,0.01,1,0.01);
	glRotatef(8,0.01,.01,1);
	glTranslatef(4,-.45,.26);
	glScalef(1,1,1);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();
    glPopMatrix();


    glPopMatrix();




    glPushMatrix();

	glTranslatef(0.04,.28,.14);
	glRotatef(-85,1,0,-0.1);
	glRotatef(-20,0,0,1);
	glScalef(0.28,0.13,0.2);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();
    glPopMatrix();


    glPopMatrix();
}




glPopMatrix();


///the dot ends



glPopMatrix();
glColor3ub(242, 243, 244);

	glRasterPos3d(-5,-2.0,0.0);

	for(int i=0;a[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,a[i]);
        if(gameover)
            {
                game();
                text();
            }
stringstream convert; // stringstream used for the conversion

convert << score;//add the value of Number to the characters in the stream

Result = convert.str();//set Result to the content of the stream




	glRasterPos3d(-1.30,.7,1);

	for(int i=0;b[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,b[i]);

	glRasterPos3d(-1.2,.5,1);

	for(int i=0;Result[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Result[i]);






//////////////////////////////////////SKY////////////////////////////////

glPushMatrix();

glTranslatef(-2,-2,-1.5);
glScalef(10,10,.01);

glPushMatrix();

glColor3ub(0,31,51);


glutSolidCube(2);
glEnd();

glPopMatrix();

glPopMatrix();



//////////////////////////////////////Cloud 1/////

glPushMatrix();
glTranslatef(_clmove1,2,0.0);
glScalef(2,2,0);
glPushMatrix();

glColor3ub(50, 61, 41);
glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.2,0,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();








//////////////////////////////////////Cloud 2/////

glPushMatrix();
glTranslatef(_clmove2,1,0.0);
glScalef(1.7,1.7,0);
glPushMatrix();

glColor3ub(50, 61, 41);
glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.2,0,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();





//////////////////////////////////////Cloud 3 white/////

glPushMatrix();
glTranslatef(_clmove3,1.5,0.0);
glScalef(2.4,2.4,0);
glPushMatrix();

glColor3ub(190, 204, 179);
glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(.25,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.2,0,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();



//////////////////////////////////////////////////////SUN //////////////////////////////////////////

glPushMatrix();

//glTranslatef(-5.4,1.8,-1.5);
glTranslatef(-5.4,_move,-1.5);

glColor3ub(255,255,0);
glutSolidSphere(.5,50,50);

glPopMatrix();















//////////////
glPushMatrix();

glTranslatef(0,0,-1);

////////////////////////////////////////////////MOUNTAIN ///////////////////////////////////////

glPushMatrix();
glTranslatef(-7,-2,0.0);
glScalef(3.2,1.5,0);
glColor3ub(0, 26, 0);

glPushMatrix();


glBegin(GL_POLYGON);
glVertex3f(0,0,0);
glVertex3f(.5,2.5,0);
glVertex3f(1.2,0,0);
glEnd();

glPopMatrix();

//
glPushMatrix();


glBegin(GL_POLYGON);
glVertex3f(.5,0,0);
glVertex3f(1,1.6,0);
glVertex3f(1.6,0,0);
glEnd();

glPopMatrix();


//
glPushMatrix();


glBegin(GL_POLYGON);
glVertex3f(.9,0,0);
glVertex3f(1.7,1.6,0);
glVertex3f(2,0,0);
glEnd();

glPopMatrix();


//
glPushMatrix();


glBegin(GL_POLYGON);
glVertex3f(1.5,0,0);
glVertex3f(2.1,2,0);
glVertex3f(2.6,0,0);
glEnd();

glPopMatrix();

//
glPushMatrix();


glBegin(GL_POLYGON);
glVertex3f(2.1,0,0);
glVertex3f(2.7,2.4,0);
glVertex3f(3.1,0,0);
glEnd();

glPopMatrix();



//
glPushMatrix();


glBegin(GL_POLYGON);
glVertex3f(2.6,0,0);
glVertex3f(3,1.8,0);
glVertex3f(3.6,0,0);
glEnd();

glPopMatrix();



//
glPushMatrix();


glBegin(GL_POLYGON);
glVertex3f(2.9,0,0);
glVertex3f(3.6,1.5,0);
glVertex3f(4.1,0,0);
glEnd();

glPopMatrix();


glPopMatrix();




glPopMatrix();








glPushMatrix();

///////////////////////////////////////////////////////////Tree 2///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(-2.2,-1.7,0.0);
     glBegin(GL_QUADS);

        glColor3ub(77, 51, 0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves
        glColor3ub(0, 102, 0);
        glBegin(GL_TRIANGLES);


        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();






    ///////////////////////////////////////////////////////////Tree 3///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(1.1,-1.7,0.0);
    glScalef(.5,1,0);
     glBegin(GL_QUADS);

        glColor3ub(77, 51, 0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves
        glColor3ub(0, 102, 0);
        glBegin(GL_TRIANGLES);

        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();





///////////////////////////////////////////////////////////Tree 4///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(1.5,-1.7,0.0);
    glScalef(.8,.6,0);
     glBegin(GL_QUADS);

        glColor3ub(77, 51, 0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves
glColor3ub(0, 102, 0);

        glBegin(GL_TRIANGLES);

        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();






    ///////////////////////////////////////////////////////////Tree 1///////////////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(-5,-1.7,0.0);
    glScalef(.6,.7,0);
     glBegin(GL_QUADS);

        glColor3ub(77, 51, 0);
        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,1.2,0);
        glVertex3f(0,1.2,0);

        glEnd();



//leaves
glColor3ub(0, 102, 0);

        glBegin(GL_TRIANGLES);

        glVertex3f(-.7,1.2,0);
        glVertex3f(.9,1.2,0);
        glVertex3f(.1,2,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.5,1.5,0);
        glVertex3f(.7,1.5,0);
        glVertex3f(.1,2.3,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(-.3,1.9,0);
        glVertex3f(.5 ,1.9,0);
        glVertex3f(.1,2.5,0);

        glEnd();

    glPopMatrix();



//////////////////////////////////////BUSH 1/////

glPushMatrix();
glTranslatef(-1.7,-1.5,0.0);
glPushMatrix();
glColor3ub(0, 102, 0);

glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();


glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();






//////////////////////////////////////BUSH 2/////

glPushMatrix();
glTranslatef(-2.5,-1.5,0.0);
glPushMatrix();
glColor3ub(0, 102, 0);


glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();

glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();




//////////////////////////////////////BUSH 3/////

glPushMatrix();
glTranslatef(-4.8,-1.5,0.0);
glPushMatrix();
glColor3ub(0, 102, 0);

glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();

glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();









//////////////////////////////////////BUSH 4/////

glPushMatrix();
glTranslatef(.9,-1.5,0.0);
glPushMatrix();
glColor3ub(0, 102, 0);

glBegin(GL_QUADS);

        glVertex3f(0,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,-.2,0);
        glVertex3f(0,-.2,0);

        glEnd();


glutSolidSphere(.15,50,50);

glTranslatef(.2,0,0);
glutSolidSphere(.15,50,50);

glTranslatef(-.1,0.17,0);
glutSolidSphere(.15,50,50);


glPopMatrix();

glPopMatrix();
/////////////////////



///////////////////////////////////////// Lamp post 1 //////////////////////


glPushMatrix();

    glTranslatef(-1.5,-1.7,0.0);
     glBegin(GL_QUADS);

        glColor3ub(51, 33, 0);
        glVertex3f(0,0,0);
        glVertex3f(.1,0,0);
        glVertex3f(.1,1.4,0);
        glVertex3f(0,1.4,0);

        glEnd();

glBegin(GL_QUADS);

        glColor3ub(51, 0, 0);
        glVertex3f(0,1.3,0);
        glVertex3f(.6,1.3,0);
        glVertex3f(.6,1.4,0);
        glVertex3f(0,1.4,0);

        glEnd();

glBegin(GL_TRIANGLES);

        glColor3ub(0,0,0);
        glVertex3f(.4,1,0);
        glVertex3f(.8,1,0);
        glVertex3f(.6,1.3,0);

        glEnd();


        glBegin(GL_TRIANGLES);

        glColor4f(1,1,1,.4);
        glVertex3f(.2,0,0);
        glVertex3f(1,0,0);
        glVertex3f(.6,1,0);

        glEnd();



glPopMatrix();




///////////////////////////////////////////// RED n Yellow Building 1 //////////////////////////////////////////////////////////

glPushMatrix();

    glTranslatef(-6.15,-1.7,0.0);
    glBegin(GL_QUADS);

        glColor4f(1.0,1.0,0,.3);
        glVertex3f( .2, 0, 0);
        glVertex3f(.4,0,0);
        glVertex3f(.4,.8,0);
        glVertex3f(.2,.8,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor4f(1.0,1.0,0,1);
        glVertex3f(.6,0,0);
        glVertex3f(.8,0,0);
        glVertex3f(.8,.8,0);
        glVertex3f(.6,.8,0);

        glEnd();

       glBegin(GL_QUADS);

        glColor4f(1.0,1.0,1,1);
        glVertex3f(.4,.9,0);
        glVertex3f(.6,.9,0);
        glVertex3f(.6,1.1,0);
        glVertex3f(.4,1.1,0);

        glEnd();

        glBegin(GL_QUADS);

        glColor4f(1.0,1.0,1,1);
        glVertex3f(.4,1.2,0);
        glVertex3f(.6,1.2,0);
        glVertex3f(.6,1.4,0);
        glVertex3f(.4,1.4,0);

        glEnd();


      glBegin(GL_QUADS);

        glColor4f(1.0,1.0,0,1);
        glVertex3f(.2,.9,0);
        glVertex3f(.8,.9,0);
        glVertex3f(.8,1.1,0);
        glVertex3f(.2,1.1,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor4f(1.0,1.0,0,1);
        glVertex3f(.2,1.2,0);
        glVertex3f(.8,1.2,0);
        glVertex3f(.8,1.4,0);
        glVertex3f(.2,1.4,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor3ub(26, 0, 0);
        glVertex3f( 0.0, 0.0, 0.0);

        glVertex3f(1.0,0.0, 0.0);

        glVertex3f( 1.0,1.5, 0.0);
        glVertex3f(0,1.5,0);

        glEnd();



    glPopMatrix();




///////////////////////////////////////////// Purple Building 2 //////////////////////////////////////////////////////////

glPushMatrix();

    glTranslatef(-.3,-1.7,0.0);


//
     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,1.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,1.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,1.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();
//


    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.25,1.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.5,1.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.75,1.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



//

     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,1.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,1.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,1.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



//



    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.25,1.05,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.5,1.05,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.75,1.05,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

//


     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,.8,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



//

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.25,.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.5,.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,0);
    glTranslatef(.75,.55,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();


    //



     glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.3,.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.5,.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,255,0);
    glTranslatef(.7,.3,0.0);
    glutSolidSphere(.1,50,50);
    glPopMatrix();



   /*   glBegin(GL_QUADS);

        glColor4f(0,0,0,1);
        glVertex3f(.2,.9,0);
        glVertex3f(.8,.9,0);
        glVertex3f(.8,1.1,0);
        glVertex3f(.2,1.1,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor4f(0,0,0,1);
        glVertex3f(.2,1.2,0);
        glVertex3f(.8,1.2,0);
        glVertex3f(.8,1.4,0);
        glVertex3f(.2,1.4,0);

        glEnd(); */

    glBegin(GL_QUADS);

        glColor3ub(51, 0, 26);
        glVertex3f( 0.05, 0.0, 0.0);

        glVertex3f(.95,0.0, 0.0);

        glVertex3f(.95,2.1, 0.0);
        glVertex3f(0.05,2.1,0);

        glEnd();

        //glTranslatef(6.1f,1.5f,0.0f);


    glPopMatrix();


//////////////////////////////////////////////////////  Building with triangle //////////////////////////////////////////

   glPushMatrix();

    glTranslatef(-4.8,-1.7,0.0);

    glBegin(GL_QUADS);

        glColor3ub(128,0,0);
        glVertex3f(0.3,.3,0);
        glVertex3f(.5,.3,0);
        glVertex3f(.5,0.6,0);
        glVertex3f(.3,.6,0);

        glEnd();

    glBegin(GL_QUADS);

        glColor3ub(128,0,0);
        glVertex3f(1.5,.3,0);
        glVertex3f(1.7,.3,0);
        glVertex3f(1.7,0.6,0);
        glVertex3f(1.5,.6,0);

        glEnd();




     glBegin(GL_QUADS);

        glColor3ub(173, 173, 133);
        glVertex3f(0.8,0,0);
        glVertex3f(1.2,0,0);
        glVertex3f(1.2,0.8,0);
        glVertex3f(.8,.8,0);

        glEnd();




     glBegin(GL_QUADS);

        glColor3ub(0, 51, 51);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);
        glVertex3f(2,1.1,0);
        glVertex3f(0,1.1,0);

        glEnd();

        glBegin(GL_TRIANGLES);

        glColor3ub(128, 102, 0);
        glVertex3f(-0.3,1.1,0);
        glVertex3f(2.3,1.1,0);
        glVertex3f(1,2,0);


        glEnd();



    glPopMatrix();








////////////////////////////////////////Sphere Building //////////////////////////////////
glPushMatrix();

glTranslatef(2.3,-1.7,0.0);

glPushMatrix();


     glBegin(GL_QUADS);

        glColor3ub(0,0,0);
        glVertex3f(0,0,0);
        glVertex3f(1.5,0,0);
        glVertex3f(1.5,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


glRotatef(_angle,3,4,0);
 glPushMatrix();

    glTranslatef(.7,.95,0.0);

        glRotatef(90,1,0,1);
        glColor3ub(153, 31, 0);
        glutWireSphere(.8,8,8);

    glPopMatrix();


    glPopMatrix();




////////////////////////////////////////// ROAD STRIPE //////////////////////////////////


 glPushMatrix();

    glTranslatef(-5.7,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();

    glPushMatrix();

    glTranslatef(-4.3,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.8,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


        glPushMatrix();
        glTranslatef(-1.3,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


            glPushMatrix();
        glTranslatef(.2,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();


            glPushMatrix();
        glTranslatef(1.7,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();

            glPushMatrix();
        glTranslatef(3.2,-2.4,0.0);
     glBegin(GL_QUADS);

        glColor3ub(255,255,255);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.15,0);
        glVertex3f(0,.15,0);

        glEnd();

    glPopMatrix();



    /////////////////////////////////////////////// Road ////////////////////////////////////////////

    glPushMatrix();

    glTranslatef(-6.5,-3,0.0);
     glBegin(GL_QUADS);

        glColor3ub(31, 31, 20);
        glVertex3f(0,0,0);
        glVertex3f(12,0,0);
        glVertex3f(12,1.3,0);
        glVertex3f(0,1.3,0);

        glEnd();

    glPopMatrix();




string pause ="RESUME";


string instructions = "INSTRUCTIONS";
string credits = "CREDITS";
string exit = "EXIT";

glLoadIdentity(); //Reset the drawing perspective
	//
	glTranslatef(1.0, 0.0, -7.0);

glColor3ub(33, 97, 140);
glScalef(1.2,0.5,.01);
glTranslatef(-2.6,5,1);
glutSolidCube(1);


glTranslatef(1.1,0,1);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glutSolidCube(1);

glTranslatef(1.1,0,1);
glutSolidCube(1);

//FOREGROUND
glPopMatrix();


glColor3ub(171, 178, 185);

    glRasterPos3d(-3.2,2.3,0.5);
	for(int i=0;pause[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,pause[i]);

    glRasterPos3d(-2.25,2.3,0.5);
	for(int i=0;instructions[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,instructions[i]);

    glRasterPos3d(-.8,2.3,0.5);
	for(int i=0;credits[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,credits[i]);

    glRasterPos3d(.55,2.3,0.5);
	for(int i=0;exit[i] != '\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,exit[i]);

glutSwapBuffers();



}

//////////////////////////Main Menu////////////////////////



void mouse(int button, int state, int x, int y) {

    POINT mousepos;
    GetCursorPos(&mousepos);

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

            if (mousepos.x>=320 && mousepos.x<=480 && mousepos.y>=25 && mousepos.y<=85) {
                if(buttonDecider == 0)
                {
                    speed=0;
                    buttonDecider =1;
                }
                else if (buttonDecider =1)
                {
                    speed=currentspeed;
                    buttonDecider =0;
                    glutDisplayFunc(drawSceneDay);
                }

}

            if (mousepos.x>=495 && mousepos.x<=654 && mousepos.y>=25 && mousepos.y<=85) {

                speed=0;
                buttonDecider =1;

                glutDisplayFunc(instructions);
}

            if (mousepos.x>=671 && mousepos.x<=823 && mousepos.y>=25 && mousepos.y<=85) {
                speed=0;
                buttonDecider =1;
                glutDisplayFunc(credits);
}

            if (mousepos.x>=844 && mousepos.x<=1005 && mousepos.y>=25 && mousepos.y<=85) {
                gameover=true;
                exit(0);
}


}



}





void update(int value)
{
    if (mv==1)
    {
      _move -= .005f;
	if (_move < 0) {
		_move = 0;
		mv=2;
		glutDisplayFunc(drawSceneNight);
	}
    }
    if (mv==0)
    {
      _move += .005f;
	if (_move > 2.5) {
		_move = 2.5;
		mv=2;
		glutDisplayFunc(drawSceneDay);
	}
    }

    _clmove1 -= .005f;
	if (_clmove1 < -8) {
		_clmove1 = +13;
	}

	_clmove2 += .01f;
	if (_clmove2 > 5) {
		_clmove2 = -10;
	}

    _clmove3 += .002f;
	if (_clmove3 > 5) {
		_clmove3 = -10;
	}


    _angle += 1.0f;
	if (_angle > 360) {
		_angle -= 360;
	}



    ab -=speed;
    if(ab < -4 && ab > -4.3)
    {
        if(shape != obstacle)
        {
            gameover = true;
        }
    }
    if (ab < -8) {
        ab = 6;

        speed +=0.005;
        currentspeed = speed;

		score = score +1;
		Beep(1500,30);

        decider_1 = rand();
        decider_2 = rand();

    }


	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(1, update, 0);

}

void keyboard(unsigned char key, int x, int y)
{

if(speed!=0){
	switch (key)
	{

	    case 'a':
        case 'A':

	    shape =1;
        break;

        case 'd':
        case 'D':
	    shape =2;
        break;

        case 'w':
        case 'W':
	    shape =3;
        break;

        case 's':
        case 'S':
	    shape =4;
        break;

        case 'p':
        case 'P':
            speed =0;
        break;


        case '1':
        mv=1;
        break;

        case '2':
        mv=0;
        glutDisplayFunc(drawSceneDay);
        break;

        case 27:
        exit(0);
        break;
	}
}
else if(speed==0 && inmenu == false){
switch(key)
{
        case 27:
        exit(0);
        break;

        case 32:
        Beep(200,150);
        Beep(300,100);
        Beep(400,100);
        ab =6;
        speed=startingspeed;
        score =0;
	    gameover=false;
        break;

        case 'r':
        case 'R':
        speed =currentspeed;
        break;
}
}
else if (speed == 0 && inmenu == true)
{
        switch(key)
{
        case 27:
        exit(0);
        break;

}
}

}
void input(int key, int x, int y)
{
	switch (key)
	{

	case GLUT_KEY_RIGHT:
		if (sd != RIGHT)
            shape = 2;
			if(rl <5)
	rl = rl + 0.8;

		break;
	case GLUT_KEY_LEFT:
		if (sd != LEFT)
            shape = 1;
		break;

		case GLUT_KEY_UP:
		if (sd != UP)
            shape = 3;
		break;

		case GLUT_KEY_DOWN:
		if (sd != DOWN)
            shape = 4;



	}

}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(1360, 760);

	//Create the window

	glutCreateWindow("Tesseract Run");
	//gluOrtho2D(-800, 800, -800,800);
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initRendering();

	//Set handler functions

    initialize();
    PlaySound("skyhigh.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);


    glutDisplayFunc(drawSceneDay);

	glutReshapeFunc(handleResize);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

	glutSpecialFunc(input);

	glutTimerFunc(10, update, 0); //Add a timer
    glutFullScreen();
    lightSetting();
	glutMainLoop();
	return 0;
}


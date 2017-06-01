#include<cstdlib>
#include "glut.h"
#include "level.h"
#include "vecNormals.h"
#include "cam.h"
#include "player.h"
#include "skybox.h"
#include "level.h"
#include "lamp.h"
#include "cube.h"
#include "forks.h"
#include "glmNew.h"
#include "sats.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//		Main method variables and such
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
bool fullScreen = false; // start in window mode
int frame =0;
long time, timebase;
float PI_180=(3.1415926535897932/180);
vecNormals cp, cla;
GLfloat lampPos1[]={59.4,12.6,59,1.0};
GLfloat lampPos2[]={0.6,12.6,59.0,1.0};
GLfloat lampPos3[]={59.3,12.6,0.8,1.0};
GLfloat lampPos4[]={0.6,12.6,0.8,1.0};
float lampDir[]={0.0, sin(180*PI_180), 0.0};
bool daytime =  true;
bool nighttime = false;
// Screen size
int screenWidth=1200, screenHeight=720;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//		Method Prototypes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void reshape();
void renderDisplay();
void normalKeyPress();
void specialKeyPress();
void normalKeyRelease();
void specialKeyRelease();
void update();
void init();
void cubeUpdate();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//		Initialising Objects
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//camera
cam camera= cam();
//thePlayer
player thePlayer= player(vecNormals(10.0,0.75,10.0), 0,0.4,0.7,0.7);
forks theForks=forks(vecNormals(2.8,40.0,3.0),0.25,0.02,0.3, &thePlayer);
//theLevel
level theLevel = level();
//street lamps
lamp lamp1=lamp(vecNormals(59.4, 2.6, 59.0), 210.0);
lamp lamp2=lamp(vecNormals(0.6, 2.6, 59.0), -210.0);
lamp lamp3=lamp(vecNormals(59.3, 2.6,0.8), 320.0);
lamp lamp4=lamp(vecNormals(0.6, 2.6, 0.8), -320.0);
//cubes!
cube cube1=cube(vecNormals( 5.0, 0.3, 5.0),0.0);
cube cube2=cube(vecNormals( 5.0, 1.0, 5.0),0.0);
cube cube3=cube(vecNormals(34, 0.3, 25.0),0.0);
cube cube4=cube(vecNormals(35.0, 0.3, 35.0),0.0);
cube cube5=cube(vecNormals(12.0, 1.0, 12.0),0.0);
cube cube6=cube(vecNormals(12.0, 0.6, 12.0),0.0);
cube cube7=cube(vecNormals(12.0, 0.3, 12.0),0.0);
cube cube8=cube(vecNormals(45.0, 0.3, 10.0),0.0);
cube cube9=cube(vecNormals(45.0, 0.8, 10.0),0.0);
cube cube10=cube(vecNormals(45.0, 0.3, 45.0),0.0);
cube cube11=cube(vecNormals(55.0, 0.3, 55.0),0.0);
cube cube12=cube(vecNormals(35.0, 0.3, 35.0),0.0);
cube cube13=cube(vecNormals(45.0, 0.3, 45.0),0.0);
cube cube14=cube(vecNormals(55.0, 0.3, 55.0),0.0);
cube cube15=cube(vecNormals(30.0, 1.0, 30.0),0.0);
cube cube16=cube(vecNormals(30.0, 0.6, 28.0),0.0);
cube cube17=cube(vecNormals(30.0, 0.3, 28.0),0.0);
cube cube18=cube(vecNormals(28.6, 1.0, 28.0),0.0);
cube cube19=cube(vecNormals(28.6, 0.6, 28.0),0.0);
cube cube20=cube(vecNormals(28.6, 0.3, 28.0),0.0);
cube cube21=cube(vecNormals(28.2, 1.0, 28.0),0.0);
cube cube22=cube(vecNormals(28.2, 0.6, 28.0),0.0);
cube cube23=cube(vecNormals(28.2, 0.3, 28.0),0.0);
cube cube24=cube(vecNormals(25.0, 0.3, 48.0),0.0);

//model Pointers
GLMmodel* mpp;
GLMmodel* mfp;
GLMmodel* mlp;
GLMmodel* mcp;
//sats object and variables used for testing
sats testing = sats();
collRes tempResult;
vecNormals mv=vecNormals(0.0,0.0,0.0);
vecNormals mvny;

vecNormals gravity=vecNormals(0.0,-0.04,0.0);
vecNormals tempMTV=vecNormals(0.0,-0.01,0.0);
vecNormals smallMove = vecNormals(0.000,0.0,0.01);
vecNormals smallMove2 = vecNormals(-0.000,0.0,-0.01);
const int cubes=24;
cube allTheCubes[cubes];

int shh = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//	Reshaping and Rendering the Display
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void reshape(int width, int height)	
{
	if (height == 0)
		height = 1;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();									
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//				Camera
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	cp=camera.getLoc();
	cla=camera.getCamLookAt();
	gluLookAt(cp.x,cp.y,cp.z,cla.x, cla.y, cla.z, 0.0f,1.0f,0.0f);	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//			Start Draw Code
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
		glPushMatrix();
			glTranslatef(cp.x, cp.y, cp.z);
			drawSkyBox(1000.0);
		glPopMatrix();
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	theLevel.drawLevel();
	glPopMatrix();
	glPushMatrix();
		thePlayer.drawPlayer();
		theForks.drawForks();
	glPopMatrix();
	glPushMatrix();
		lamp1.drawLamp();
		lamp2.drawLamp();
		lamp3.drawLamp();
		lamp4.drawLamp();
	glPopMatrix();
	glPushMatrix();
		for(int i=0;i<cubes;i++){allTheCubes[i].drawCube();}
	glPopMatrix();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//			Ending Draw Code
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	if(daytime&&!nighttime)
	{	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	float pos[] = {-15.0,30.0,-15.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	}
	else if (nighttime&&!daytime)
	{	
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lampDir);
		glLightfv(GL_LIGHT1, GL_POSITION, lampPos1);
		//glLightfv(GL_LIGHT1, GL_POSITION, lampPos2);
		//glLightfv(GL_LIGHT1, GL_POSITION, lampPos3);
		//glLightfv(GL_LIGHT1, GL_POSITION, lampPos4);
	}
	glutSwapBuffers();
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//			Keyboard Code Begin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void normalKeyPress(unsigned char key, int x, int y) {

	switch (key){
	case 27 : exit(0); 
		break;
	case 'w':thePlayer.setPlayerState(1);
		break;
	case 's':thePlayer.setPlayerState(2);
		break;
	case 'a' :thePlayer.setPlayerTurnState(2);
		break;
	case 'd' :thePlayer.setPlayerTurnState(1);
		break;
	case '1':camera.setViewMode(0);
		break;
	case '2':camera.setViewMode(1);
		break;
	case '3':camera.setViewMode(2);
		break;
	case '4':camera.setViewMode(3);
		break;
	case'm':daytime=true;nighttime=false;cout<<"daytime"<<endl;
		break;
	case'n':nighttime=true;daytime=false;cout<<"nighttime"<<endl;
		break;
	case'e':theForks.setUp(true);
		break;
	case'q':theForks.setDown(true);
		break;
	case't':thePlayer.setDebug(true);theForks.setDebug(true);for(int i=0;i<cubes;i++){allTheCubes[i].setDebug(true);}
		break;
	case'u':thePlayer.setDebug(false);theForks.setDebug(false);for(int i=0;i<cubes;i++){allTheCubes[i].setDebug(false);}
		break;
	default:
		break;
	}
}

void specialKeyPress(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_F1:
		if (!fullScreen) {
			glutGameModeString("1920x1080:32");   
			glutFullScreen(); 
			fullScreen = true;
		}
		else {
			glutReshapeWindow(screenWidth, screenHeight);
			glutPositionWindow(100,50);
			fullScreen = false;
		}		
		break;
	default:
		break;
	}
}

void normalKeyRelease(unsigned char key, int x, int y)
{
	switch (key){
	case 'w':thePlayer.setPlayerState(0);
		break;
	case 's':thePlayer.setPlayerState(0);
		break;
	case 'a' :thePlayer.setPlayerTurnState(0);
		break;
	case 'd' :thePlayer.setPlayerTurnState(0);
		break;
	case'e':theForks.setUp(false);
		break;
	case'q':theForks.setDown(false);
		break;
	default:
		break;
	}
}

void specialKeyRelease(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_F1:
		break;
	default:
		break;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//			Keyboard Code End
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//			Update Method
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void cubeUpdate()
{
//code for exacting the gravity onto the boxes
	for(int a=0;a<cubes;a++)
	{
		if(allTheCubes[a].getPos().y > 0.3)
		{
			allTheCubes[a].updateCube(gravity);
		}
	}
//Code for the sats testing for the box interaction with each other and the player

	for (int y = 0; y < cubes; y++)
	{
		for (int z = 0; z < cubes; z++)
		{
			if (z > y){
				tempResult=testing.test(&allTheCubes[y], &allTheCubes[z]);
				if(tempResult.colliding)
				{
					allTheCubes[y].updateCube(tempResult.MTV);
					allTheCubes[z].updateCube(tempMTV-tempResult.MTV);
				}

			}
		}
		tempResult=testing.test(&allTheCubes[y], &theForks);
		if(tempResult.colliding)
		{
			allTheCubes[y].updateCube(tempResult.MTV);
		}
		tempResult=testing.test(&allTheCubes[y], &thePlayer);
		if(tempResult.colliding){
			allTheCubes[y].updateCube(tempResult.MTV);
		}
	}

}
void update()
{
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 10) 
	{
		frame = 0; 
		timebase = time; 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		//			Update Code Start
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		thePlayer.updatePlayer();
		camera.updateCam(thePlayer.getPosition(),thePlayer.getPlayerAngle());
		theForks.update(&thePlayer);
		cubeUpdate();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		//			Update Code End
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		glutPostRedisplay();
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//		Initialising Code
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void init()
{
	glClearColor(0.5,0.5,0.5,1.0);				
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_BLEND);
	//Initialise objects and such
	camera.setViewMode(1);
	//Load the Skybox textures and whatnot
	loadSkyTex();
	//Load the level textures and whatnot
	theLevel.loadLevel();
	//load the models for the player character
	mpp=glmReadOBJ("tings/forklift/noforks.obj");
	glmUnitize(mpp);
	thePlayer.loadPlayer(mpp);
	mfp=glmReadOBJ("tings/forklift/forks.obj");
	glmUnitize(mfp);
	theForks.loadForks(mfp);
	//load the model for the street lamps
	mlp=glmReadOBJ("tings/streetlamps/Light_Street_Rural.obj");
	glmUnitize(mlp);
	lamp1.loadLamp(mlp);
	lamp2.loadLamp(mlp);
	lamp3.loadLamp(mlp);
	lamp4.loadLamp(mlp);
	//load the model for cubes
	mcp=glmReadOBJ("tings/cube/the_rubik's_cube1.obj");
	glmUnitize(mcp);
	//deal with loading all the cube objects to an array (pain)
	cube1.loadCube(mcp);
	cube2.loadCube(mcp);
	cube3.loadCube(mcp);
	cube4.loadCube(mcp);
	cube5.loadCube(mcp);
	cube6.loadCube(mcp);
	cube7.loadCube(mcp);
	cube8.loadCube(mcp);
	cube9.loadCube(mcp);
	cube10.loadCube(mcp);
	cube11.loadCube(mcp);
	cube12.loadCube(mcp);
	cube13.loadCube(mcp);
	cube14.loadCube(mcp);
	cube15.loadCube(mcp);
	cube16.loadCube(mcp);
	cube17.loadCube(mcp);
	cube18.loadCube(mcp);
	cube19.loadCube(mcp);
	cube20.loadCube(mcp);
	cube21.loadCube(mcp);
	cube22.loadCube(mcp);
	cube23.loadCube(mcp);
	cube24.loadCube(mcp);
	allTheCubes[0] = cube1;
	allTheCubes[1] = cube2;
	allTheCubes[2] = cube3;
	allTheCubes[3] = cube4;
	allTheCubes[4] = cube5;
	allTheCubes[5] = cube6;
	allTheCubes[6] = cube7;
	allTheCubes[7] = cube8;
	allTheCubes[8] = cube9;
	allTheCubes[9] = cube10;
	allTheCubes[10] = cube11;
	allTheCubes[11] = cube12;
	allTheCubes[12] = cube13;
	allTheCubes[13] = cube14;
	allTheCubes[14] = cube15;
	allTheCubes[15] = cube16;
	allTheCubes[16] = cube17;
	allTheCubes[17] = cube18;
	allTheCubes[18] = cube19;
	allTheCubes[19] = cube20;
	allTheCubes[20] = cube21;
	allTheCubes[21] = cube22;
	allTheCubes[22] = cube23;
	allTheCubes[23] = cube24;
	// Initialise lighting.
	GLfloat ambcol[]={0.75f, 0.74f, 0.67f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambcol);
	if(daytime&&!nighttime)
	{
		float amb[]={0.0f,0.0f,0.0f,1.0f};
		float dif[] = {1.0f,1.0f,1.0f,0.0f};
		float spec[] = {1.0f,1.0f,1.0f,0.0f};
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
	}
	else if (nighttime&&!daytime)
	{
		float amb[]={0.0f,0.0f,0.0f,1.0f};
		float dif[] = {0.0f,0.0f,1.0f,1.0f};
		float spec[] = {0.0f,1.0f,1.0f,1.0f};
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 15.0f);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.000025);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT1);
	}
	glEnable(GL_LIGHTING);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//		The Main Method
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D game");
	init();
	glutDisplayFunc(renderDisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(normalKeyPress);
	glutSpecialFunc(specialKeyPress);
	glutKeyboardUpFunc(normalKeyRelease);
	glutSpecialUpFunc(specialKeyRelease);
	glutMainLoop();
	return 1;
}
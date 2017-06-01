#ifndef FORKS_H
#define FORKS_H
#include <iostream>
#include <cstdlib>
#include "glut.h"
#include "SOIL.h"
#include "vecNormals.h"
#include "glmNew.h"
#include "player.h"
#include "boundedBox.h"
using namespace std;

class forks: public boundedBox{
protected:
	bool up, down, debug;
	float yheight, height, width, depth, rot;
	float pitch;
	float yaw; 
	float roll;
	float oldPitch; 
	float oldYaw; 
	float oldRoll;
	GLMmodel* fm;
	GLuint fdl;
public:
	forks(vecNormals p, float x, float y, float z, player* forklift);
	void setUp(bool u);
	void setDown(bool d);
	void update(player* fl);
	void loadForks(GLMmodel* fmp);
	void drawForks();
	void setDebug(bool loob);
};
#endif
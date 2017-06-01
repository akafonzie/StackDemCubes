#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <cstdlib>
#include "glut.h"
#include "SOIL.h"
#include "glmNew.h"
#include "vecNormals.h"
#include "boundedBox.h"
#include "player.h"
class cube: public boundedBox{
protected:
	vecNormals vel, rot;
	unsigned int state;
	float p ,y, r, pp, py, pr, a, rots; //pitch, yaw, roll
	bool stacked, debug;
	GLMmodel* cm; //cube model
	GLuint cdl; //cube display list
	float miny; //the minimum y pos a cube can exist at(so it doesn't disappear under map)
public:
	cube();
	cube(vecNormals p, float r);
	void loadCube(GLMmodel* cmp);
	void drawCube();
	void updateCube(vecNormals v);
	vecNormals getVel();
	void collision(vecNormals mv);
	void setState(unsigned int s);
	float angleReset(float a);
	void setDebug(bool loob);
};
#endif
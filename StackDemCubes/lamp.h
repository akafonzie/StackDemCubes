#ifndef LAMP_H
#define LAMP_H
#include <iostream>
#include <cstdlib>
#include "glut.h"
#include "SOIL.h"
#include "glmNew.h"
#include "vecNormals.h"
class lamp{
protected:
	vecNormals pos;
	int rot;
	GLMmodel* lm;
	GLuint ldl;
public:
	lamp(vecNormals p, int r);
	void loadLamp(GLMmodel* lmp);
	void drawLamp();
};
#endif
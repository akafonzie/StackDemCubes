#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <cstdlib>
#include "glut.h"
#include "SOIL.h"
#include "vecNormals.h"
#include "glmNew.h"
using namespace std;

class level{
private:
	int width, depth, texRep;
	GLuint asphalt;
	GLuint levList;
	GLuint stone;
	GLuint hdl;
	GLMmodel* hm;
public:
	level();
	void loadLevel();
	void drawLevel();
};
#endif
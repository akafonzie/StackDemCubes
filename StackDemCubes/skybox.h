#ifndef SKYBOX_H
#define SKYBOX_H
#include<cstdlib>
#include "glut.h"
#include"SDL.h"
#include <iostream>
using namespace std;
const GLfloat SKY_HEIGHT=512, SKY_WIDTH=512;
void drawSkyBox(float size);
void loadSkyTex();
void destroySkyBox();
unsigned int loadTex(const char*);
#endif
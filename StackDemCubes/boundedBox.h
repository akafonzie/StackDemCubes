#ifndef BOUNDEDBOX_H
#define BOUNDEDBOX_H
#include<iostream>
#include<cstdlib>
#include "glut.h"
#include "Quaternion.h"
#include"MatrixRoutines.h"
#include"vecNormals.h"
using namespace std;
class boundedBox{
protected:
	double theMatrix[16],xMatrix[16],xyMatrix[16],theMatrixOrigin[3],theMatrixLocal[3];
	Quaternion temp;
	vecNormals pos;
	vecNormals corners[8];
	float bbWidth, bbHeight, bbDepth;
	void updateTM(double a, double b, double c);
public:
	boundedBox();
	boundedBox(vecNormals p, float a, float b, float c);
	vecNormals getLocalisedAxes(int a);
	vecNormals getPos();
	vecNormals getBBCP(int a);
	float getBBWidth();
	float getBBheight();
	float getBBDepth();
	void boundedBoxRotate(float a, float b, float c);
	void updateBBCP();
};
#endif
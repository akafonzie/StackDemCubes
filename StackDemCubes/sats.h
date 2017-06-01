#ifndef SATS_H
#define SATS_H
#include <iostream>
#include "glut.h"
#include "vecNormals.h"
#include "boundedBox.h"
using namespace std;
struct collRes {
	bool colliding;
	vecNormals MTV;
};

struct projRes {
	float min;
	float max;
};

class sats{
	public:
		sats();
		collRes test(boundedBox* A, boundedBox* B);
		projRes projectBox(vecNormals axis, boundedBox* box);
};
#endif

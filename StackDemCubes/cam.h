#ifndef CAM_H
#define CAM_H
#include<cstdlib>
#include "glut.h"
#include<GL\GL.h>
#include<GL\GLU.h>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include<cstdio>
#include<iostream>
#include<cmath>
#include "vecNormals.h"
#include "player.h"
using namespace std;

class cam{
	vecNormals loc;
	vecNormals camLookAt;
	float camPitch, camYaw, moveVel, PI_180,camHeight, camDist, camAng;
	unsigned int ViewMode;
	bool lookLeft, lookRight;
public:
	cam();
//Get that shit
	vecNormals getVec();
	vecNormals getLoc();
	vecNormals getCamLookAt();
	float getCamX();
	float getCamY();
	float getCamZ();
	float getCamPitch();
	float getCamYaw();
	float getMoveVel();
	float getCamAng();
	float getCamHeight();
	float getCamDist();
//Set that shit
	void setCamDist(float cd);
	void setCamHeight(float ch);
	void setCamPos(vecNormals scp); //scp= Set Cam pos
	void setCamRotL(bool loob);
	void setCamRotR(bool loob);
	void setLoc(vecNormals vec);
	void lookAt(float p, float y);
	void updateCam(vecNormals lap, float pa);//lap=look at position & pa = player angle
	void setViewMode(unsigned int voo);
};
#endif
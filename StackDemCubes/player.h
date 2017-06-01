#ifndef PLAYER_H
#define PLAYER_H

#include<cstdlib>
#include "glut.h"
#include<GL\GL.h>
#include<GL\GLU.h>
#include"glmNew.h"
#include<vector>
#include<string>
#include<cmath>
#include "vecNormals.h"
#include "level.h"
#include "boundedBox.h"

static const float MVEL=0.1f;
static const float CARACCEL=0.002f;
static const float CARDECEL=0.001;
static const float TURN=1.2f;
class player:public boundedBox{
	friend class forks;
protected:
	vecNormals bb[4];//array to hold the bounding box
	vecNormals wp[4];//array to hold the wheel points
	vecNormals grav; //gravity for level, not player
	vecNormals dir; //pos=pos+dir && dir=dir+grav
	//vecNormals pos;//player spawn position
	float psa, vel, angle, roll, pitch;//psa=player start angle
	float oldPitch; 
	float oldAngle;
	float oldRoll;
	bool movingF, movingB, debug;
	unsigned int state, turn;
	GLMmodel* pm;
	GLuint pdl;
public:
	player(vecNormals sp,float a, float b, float c, float d);
	~player();
	void updatePlayer();
	void drawPlayer();
	void loadPlayer(GLMmodel* pmp);
	void drawCube();
	//getter functions
	vecNormals getPosition();
	float getPlayerxPos();
	float getPlayeryPos();
	float getPlayerzPos();
	float getPlayerAngle();
	float getPlayerVel();
	unsigned int getPlayerState();
	float getPitch();
	float getRoll();
	//setter functions
	void setPosition(vecNormals currPos);
	void setPlayerxPos(float x);
	void setPlayeryPos(float y);
	void setPlayerzPos(float z);
	void setAngle(float a);
	void setVel(float v);
	void setPlayerState(unsigned int s);
	void setPlayerTurnState(unsigned int ts);
	void setPitch(float setPitch);
	void setRoll(float setRoll);
	void setDebug(bool loob);
	
};
#endif
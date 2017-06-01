#include "player.h"

player::player(vecNormals sp, float a, float b, float c, float d):boundedBox(sp,b,c,d)
{
	movingF=movingB=debug=false;
	vel=0.0;
	angle=a;
	state=turn=0;
	roll=pitch=0.0;
	boundedBoxRotate(0.0,0.0,0.0);
}
player::~player()
{
}
void player::updatePlayer()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//		Handling the movement states of the Player
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	switch (state)
	{
	case 0:
		if(vel>0)
		{
			movingF=true;
			movingB=false;
			vel-=CARDECEL*2;
			if(vel<0.01){vel=0;}
		}
		if(vel<0)
		{
			movingB=true;
			movingF=false;
			vel+=CARDECEL*2;
			if(vel>-0.01){vel=0;}
		}
		break;
	case 1:
		if(vel<MVEL){vel+=CARACCEL;}
		break;
	case 2:
		if(vel>-MVEL){vel-=CARACCEL;}
		break;
	default:
		break;
	}
	switch (turn)
	{
	case 0:
		break;
	case 1:
		if(vel>=0.02||vel<=-0.02)
		{
			angle-=(TURN);
			if(angle <-359){angle+=359;}
		}
		break;
	case 2:
		if(vel>=0.02||vel<=-0.02)
		{
			angle+=(TURN);
			if(angle>359){angle-=359;}
		}
		break;
	default:
		break;
	}
	float pitchChange = pitch - oldPitch;
	float angleChange = angle - oldAngle;
	float rollChange = roll - oldRoll;

	pos.x+=vel*(sin(angle * 3.14125269/180));
	pos.z+=vel*(cos(angle * 3.14125269/180));
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	//		Ensuring the player can't go OOB
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	if(movingF)
	{
		if(pos.x>58.8-bbWidth){pos.x=58.8-bbWidth;}
		else if(pos.x<1.2+bbWidth){pos.x=1.2+bbWidth;}
		if(pos.z>58.8-bbWidth){pos.z=58.8-bbWidth;}
		else if(pos.z<1.2+bbWidth){pos.z=1.2+bbWidth;}
	}
	if(movingB)
	{
		if(pos.x>59.0-(bbWidth-0.65)){pos.x=59.0-(bbWidth-0.65);}
		else if(pos.x<1.0+(bbWidth-0.65)){pos.x=1.0+(bbWidth-0.65);}
		if(pos.z>59.0-(bbWidth-0.65)){pos.z=59.0-(bbWidth-0.65);}
		else if(pos.z<1.0+(bbWidth-0.65)){pos.z=1.0+(bbWidth-0.65);}
	}
	boundedBoxRotate(pitchChange, angleChange, rollChange);
	oldPitch = pitch;
	oldAngle = angle;
	oldRoll = roll;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//			Loading the Forklift model
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void player::loadPlayer(GLMmodel* pmp)
{
	pm=pmp;
	pdl=glGenLists(1);
	glNewList(pdl, GL_COMPILE);
	glmList(pm, GLM_SMOOTH | GLM_TEXTURE);
	glEndList();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//				Drawing the Forklift
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void player::drawPlayer()
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glPushMatrix();
			glColor3f(0.5f,0.5f,0.5f);
			glMultMatrixd(theMatrix);
			glCallList(pdl);
		glPopMatrix();
	glPopMatrix();
	if(debug)
	{
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i < 8; i++)
		{
			glVertex3f(corners[i].x, corners[i].y, corners[i].z); 
		}
		glEnd();
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//				Getter Functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
vecNormals player::getPosition(){return pos;}
float player::getPlayerAngle(){	return angle;}
float player::getPlayerxPos(){return pos.getxPos();}
float player::getPlayeryPos(){return pos.getyPos();}
float player::getPlayerzPos(){return pos.getzPos();}
float player::getPlayerVel(){return vel;}
unsigned int player::getPlayerState(){return state;}
float player::getPitch(){return pitch;}
float player::getRoll(){return roll;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//				Setter Functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void player::setPosition(vecNormals currPos){pos=currPos;}
void player::setPlayerxPos(float x){pos.x=x;}
void player::setPlayeryPos(float y){pos.y=y;}
void player::setPlayerzPos(float z){pos.z=z;}
void player::setAngle(float a){angle=a;}
void player::setVel(float v){vel=v;}
void player::setPlayerState(unsigned int s){state=s;}
void player::setPlayerTurnState(unsigned int ts){turn=ts;}
void player::setPitch(float setPitch){pitch=setPitch;}
void player::setRoll(float setRoll){roll=setRoll;}
void::player::setDebug(bool loob){debug=loob;}
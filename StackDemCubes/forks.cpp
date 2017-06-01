#include "forks.h"
forks::forks(vecNormals p,float x, float y, float z, player* forklift):boundedBox(p,x,y,z)
{
	up=false;
	down=false;
	debug=false;
	yheight=0.0f;
	this->boundedBoxRotate(0.0,0.0,0.0);
}
void forks::setUp(bool u)
{
	up=u;
}
void forks::setDown(bool d)
{
	down=d;
}
void forks::setDebug(bool loob)
{
	debug=loob;
}
void forks::update(player* fl)
{
	pos=vecNormals((fl->theMatrixOrigin[0] - fl->theMatrix[8]*-1.15) + fl->pos.x,
		(fl->theMatrixOrigin[1] - fl->theMatrix[9]*-1.15) + fl->pos.y,
		(fl->theMatrixOrigin[2] - fl->theMatrix[10]*-1.15) + fl->pos.z);
	pos.y = yheight;
	if(up)
	{
		yheight += 0.008;
		pos.y=yheight;
		if(yheight>=1.0){yheight=1.0;}
	}
	else if(down)
	{
		yheight -=0.008;
		pos.y=yheight;
		if(yheight<=0.0){yheight=0.0;}
	}
	this->pitch = fl->pitch;
	this->yaw = fl->angle;
	this->roll = fl->roll;
	float pitchChange = pitch - oldPitch;
	float yawChange = yaw - oldYaw;
	float rollChange = roll - oldRoll;
	this->boundedBoxRotate(pitchChange, yawChange, rollChange);
	oldPitch = pitch;
	oldYaw = yaw;
	oldRoll = roll;

}

void forks::loadForks(GLMmodel* fmp)
{
	fm=fmp;
	fdl=glGenLists(1);
	glNewList(fdl, GL_COMPILE);
	glmList(fm, GLM_SMOOTH | GLM_TEXTURE);
	glEndList();
}

void forks::drawForks()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y+0.25, pos.z);
	glPushMatrix();
	glScalef(2.0f,2.0f,2.0f);
	glMultMatrixd(theMatrix);
	glCallList(fdl);
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
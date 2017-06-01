#include "cube.h"

cube::cube():boundedBox()
{
	p=y=r=pp=py=pr=0.0;
	rots=0.3;
	a=r;
	miny=0.3;
	vel=vecNormals(0.0,0.0,0.0);
	boundedBoxRotate(0.0,0.0,0.0);
}
cube::cube(vecNormals po, float r):boundedBox(po,0.3,0.3,0.3)
{
	p=y=r=pp=py=pr=0.0;
	debug=false;
	rots=0.3;
	a=r;
	miny=0.3;
	vel=vecNormals(0.0,0.0,0.0);
	boundedBoxRotate(0.0,0.0,0.0);
}
void cube::loadCube(GLMmodel* cmp)
{
	cm=cmp;
	cdl=glGenLists(1);
	glNewList(cdl, GL_COMPILE);
	glmList(cm, GLM_SMOOTH | GLM_TEXTURE);
	glEndList();
}
void cube::drawCube()
{
	glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glPushMatrix();
			glMultMatrixd(theMatrix);
			glScalef(0.3f,0.3f,0.3f);
			glCallList(cdl);
			glColor3f(1.0,1.0,1.0);
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
void cube::updateCube(vecNormals v)
{
	vel=v;
	pos += vel;
	if(pos.y < 0.3)
	{
		pos.y = 0.3;
	}
	boundedBoxRotate(0.0,0.0,0.0);
}
vecNormals cube::getVel()
{
	return vel;
}
void cube::collision(vecNormals mv)
{
	pos += mv;
	updateBBCP();
}

float cube::angleReset(float a)
{
	if(a>360){a=-360;}
	else if(a<-360){a=360;}
	return a;
}
void cube::setDebug(bool loob)
{
	debug=loob;
}
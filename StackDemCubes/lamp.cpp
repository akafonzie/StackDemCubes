#include "lamp.h"

lamp::lamp(vecNormals p, int r)
{
	pos=p;
	rot=r;
}
void lamp::loadLamp(GLMmodel* lmp)
{
	lm=lmp;
	ldl=glGenLists(1);
	glNewList(ldl, GL_COMPILE);
		glmList(lm, GLM_SMOOTH | GLM_TEXTURE);
	glEndList();
}
void lamp::drawLamp()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	glScalef(2.5f,2.5f,2.5f);
	glPushMatrix();
		glCallList(ldl);
	glPopMatrix();
	glPopMatrix();
}

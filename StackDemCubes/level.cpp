#include "level.h"
level::level()
{
	width = depth = 60.0f;
	texRep=25;
}

void level::loadLevel()
{
	asphalt=SOIL_load_OGL_texture("tings/asphalt.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	stone=SOIL_load_OGL_texture("tings/stone.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	if(asphalt==0||stone==0){cout<<"Could not load the level textures, Jabroni"<<endl;}
	else
	{
		cout<<"Level textures loaded correctly; Hooraaaay!!!1111!"<<endl;
		levList=glGenLists(1);
		//Build the display list for the level
		glNewList(levList, GL_COMPILE);

		//Floor texturing and drawing start
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, asphalt);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glColor3f(1.0f,1.0f,1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,texRep);
			glVertex3f(width,0.0f,0.0f);
			glTexCoord2f(texRep,texRep);
			glVertex3f(width,0.0f,depth);
			glTexCoord2f(texRep,0.0f);
			glVertex3f(0.0f,0.0f,depth);
		glEnd();
		//Floor texturing and drawing end

		//Wall texturing and drawing start

		glBindTexture(GL_TEXTURE_2D, stone);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		//wall one (right)
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 5.0f, 0.0f);
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(texRep/4, 1.0f);
			glVertex3f(0.0f, 0.0f, depth);
			glTexCoord2f(texRep/4, 0.0f);
			glVertex3f(0.0f, 5.0f, depth);
		//wall two (front)
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(depth, 5.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(width, 0.0f, 0.0f);
			glTexCoord2f(texRep/4, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(texRep/4, 0.0f);
			glVertex3f(0.0f, 5.0f, 0.0f);
		//wall three (left)
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(width, 5.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(width, 0.0f, 0.0f);
			glTexCoord2f(texRep/4, 1.0f);
			glVertex3f(width, 0.0f, depth);
			glTexCoord2f(texRep/4, 0.0f);
			glVertex3f(width, 5.0f, depth);
		//wall four (front)
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(width, 5.0f, depth);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(width, 0.0f, depth);
			glTexCoord2f(texRep/4, 1.0f);
			glVertex3f(0.0f, 0.0f , depth);
			glTexCoord2f(texRep/4, 0.0f);
			glVertex3f(0.0f, 5.0f, depth);
		glEnd();
		//Wall texturing and drawing end

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glEndList();
	}
}

void level::drawLevel()
{
	glCallList(levList);
}

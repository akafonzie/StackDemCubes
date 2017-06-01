#include "skybox.h"
#include "glext.h"


enum {SKY_FRONT=0, SKY_BACK, SKY_LEFT, SKY_RIGHT, SKY_TOP, SKY_BOTTOM};
unsigned int skyBox[6];


void loadSkyTex(){
	skyBox[SKY_FRONT]=loadTex("tings/skybox/front.bmp");
	skyBox[SKY_BACK]=loadTex("tings/skybox/back.bmp");
	skyBox[SKY_LEFT]=loadTex("tings/skybox/left.bmp");
	skyBox[SKY_RIGHT]=loadTex("tings/skybox/right.bmp");
	skyBox[SKY_TOP]=loadTex("tings/skybox/top.bmp");
	skyBox[SKY_BOTTOM]=loadTex("tings/skybox/bottom.bmp");
	}
	

void destroySkyBox(){
	glDeleteTextures(6, &skyBox[0]);
}


void drawSkyBox(float size){
	
	bool texEnable = glIsEnabled(GL_TEXTURE_2D);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//front face
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex3f(size/2,size/2,-size/2);
	glTexCoord2f(0,0);
	glVertex3f(-size/2,size/2,-size/2);
	glTexCoord2f(0,1);
	glVertex3f(-size/2,-size/2,-size/2);
	glTexCoord2f(1,1);
	glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	
	//back face
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(size/2,size/2,size/2);
	glTexCoord2f(1,0);
	glVertex3f(-size/2,size/2,size/2);
	glTexCoord2f(1,1);
	glVertex3f(-size/2,-size/2,size/2);
	glTexCoord2f(0,1);
	glVertex3f(size/2,-size/2,size/2);
	glEnd();

	//left face
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-size/2,size/2,size/2);
	glTexCoord2f(1,0);
	glVertex3f(-size/2,size/2,-size/2);
	glTexCoord2f(1,1);
	glVertex3f(-size/2,-size/2,-size/2);
	glTexCoord2f(0,1);
	glVertex3f(-size/2,-size/2,size/2);
	glEnd();
	
	//right face
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(size/2, size/2,-size/2);
	glTexCoord2f(1,0);
	glVertex3f(size/2, size/2, size/2);
	glTexCoord2f(1,1);
	glVertex3f(size/2,-size/2,size/2);
	glTexCoord2f(0,1);
	glVertex3f(size/2,-size/2,-size/2);
	glEnd();

	//top face
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_TOP]);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex3f(size/2,size/2,size/2);
	glTexCoord2f(0,0);
	glVertex3f(-size/2,size/2,size/2);
	glTexCoord2f(0,1);
	glVertex3f(-size/2,size/2,-size/2);
	glTexCoord2f(1,1);
	glVertex3f(size/2,size/2,-size/2);
	glEnd();

	//bottom face
	glBindTexture(GL_TEXTURE_2D, skyBox[SKY_BOTTOM]);
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(size/2,-size/2,size/2);
	glTexCoord2f(0,1);
	glVertex3f(-size/2,-size/2,size/2);
	glTexCoord2f(0,0);
	glVertex3f(-size/2,-size/2,-size/2);
	glTexCoord2f(1,0);
	glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	//glEnable(GL_LIGHTING);
	//glEnable(GL_DEPTH_TEST);
	if(!texEnable){glDisable(GL_TEXTURE_2D);}
}


unsigned int loadTex(const char* filename)  //load the filename named texture
{
    unsigned int num;       //the id for the texture
    glGenTextures(1,&num);  //we generate a unique one
    SDL_Surface* img=SDL_LoadBMP(filename); //load the bmp image
    glBindTexture(GL_TEXTURE_2D,num);       //and use the texture, we have just generated
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);      //we do it for vertically and horizontally (previous line)
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);        //we make the actual texture
    SDL_FreeSurface(img);   //we delete the image, we don't need it anymore
	cout<<"skybox image correctly loaded"<<endl;
    return num;     //and we return the id
}
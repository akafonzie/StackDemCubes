#include "cam.h"

float PI_180180=(3.141592653589/180);
const int screenWidth=1280, screenHeight =960;

cam::cam()
{
	loc=vecNormals(0.0,0.0,0.0);
	camLookAt=vecNormals(0.0,0.0,0.0);
	camYaw=0.0;
	camPitch=0.0;
	moveVel=0.0;
	camHeight=3;
	camDist=0;
	ViewMode=0;
	lookLeft=false;
	lookRight=false;
}
/*************************************************************************************************

							CAMERA GETTER METHODS

*************************************************************************************************/
//change the spherical coord system to cartesian
vecNormals cam::getVec()
{
	return(vecNormals(-cos(camPitch*PI_180/180)*sin(camYaw*PI_180/180),sin(camPitch*PI_180/180),-cos(camPitch*PI_180/180)*cos(camYaw*PI_180/180))); 
}
vecNormals cam::getLoc()
{
	return loc;
}

vecNormals cam::getCamLookAt()
{
	return camLookAt;
}

float cam::getCamX()
{
	return loc.x;
}

float cam::getCamY()
{
	return loc.y;
}

float cam::getCamZ()
{
	return loc.z;
}
float cam::getCamPitch()
{
	return camPitch;
}
float cam::getCamYaw()
{
	return camYaw;
}
float cam::getMoveVel()
{
	return moveVel;
}
float cam::getCamAng()
{
	return camAng;
}
float cam::getCamHeight()
{
	return camHeight;
}
float cam::getCamDist()
{
	return camDist;
}

/*************************************************************************************************

							CAMERA SETTER METHODS

*************************************************************************************************/

void cam::setCamDist(float cd)
{
	camDist=cd;
}
void cam::setCamHeight(float ch)
{
	camHeight=ch;
}
void cam::setCamPos(vecNormals scp)
{
	loc=scp;
}

void cam::setCamRotL(bool loob)
{
	lookLeft=loob;
}

void cam::setCamRotR(bool loob)
{
	lookRight=loob;
}
void cam::setLoc(vecNormals vec)
{
	loc.change(vec);
}
void cam::lookAt(float p, float y)
{
	camPitch=p;
	camYaw=y;
}


void cam::setViewMode(unsigned int View)
{
	if(View>=0&&View<=3)
	{
		ViewMode=View;
		if(ViewMode==0)//standard first person View
		{
			camHeight=1.0;
			camDist=1.5;
			camAng=0.0;
		}
		if (ViewMode==1)//third person View
		{
			camHeight=4.0;
			camDist=6.0;
			camAng=0.0;
		}
		if(ViewMode==2)//top down GTA style birds eye View
		{
			camHeight=10.0;
			camDist=0.1;
			camAng=0.0;
		}
		if(ViewMode==3)//side view
		{
			camHeight=3.0;
			camDist=5.0;
			camAng=-90.0;
		}
	}
}

void cam::updateCam(vecNormals lap, float pa)
{
	camLookAt=lap;
	pa=pa;
	switch(ViewMode)
	{
		case 0: //standard 1st person View
			loc.x=camLookAt.x-(sin((pa + camAng) * PI/180)*camDist);
			loc.y=camLookAt.y+camHeight;
			loc.z=camLookAt.z-(cos((pa + camAng) * PI/180)*camDist);
			break;
		case 1: //3rd person View
			loc.x=camLookAt.x-(sin((pa + camAng) * PI/180)*camDist);
			loc.y=camLookAt.y+camHeight;
			loc.z=camLookAt.z-(cos((pa + camAng) * PI/180)*camDist);
			break;
		case 2://top down View
			loc.x=camLookAt.x-(sin((pa + camAng) * PI/180)*camDist);
			loc.y=camLookAt.y+camHeight;
			loc.z=camLookAt.z-(cos((pa + camAng) * PI/180)*camDist);
			break;
		case 3://top down View
			loc.x=camLookAt.x-(sin((pa + camAng) * PI/180)*camDist);
			loc.y=camLookAt.y+camHeight;
			loc.z=camLookAt.z-(cos((pa + camAng) * PI/180)*camDist);
			break;
	}
	if(loc.x>=59.5f){loc.x=59.5f;}
	else if(loc.x<=0.05f){loc.x=0.05f;}
	if(loc.z>=59.5f){loc.z=59.5f;}
	else if(loc.z<=0.05f){loc.z=0.05f;}
}



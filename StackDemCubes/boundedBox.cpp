#include "boundedBox.h"
boundedBox::boundedBox()
{
	pos=vecNormals();
	bbWidth=bbHeight=bbDepth=0;
	theMatrixLocal[0]=0;
	theMatrixLocal[1]=0;
	theMatrixLocal[2]=0;
	MatrixRoutines::setToIdentity(theMatrix);
	MatrixRoutines::multiplyPoint(theMatrixLocal, theMatrix, theMatrixOrigin);
}
boundedBox::boundedBox(vecNormals p, float a, float b, float c)
{
	pos=p;
	this->bbWidth=a;
	this->bbHeight=b;
	this->bbDepth=c;
	theMatrixLocal[0]=0;
	theMatrixLocal[1]=0;
	theMatrixLocal[2]=0;
	MatrixRoutines::setToIdentity(theMatrix);
	MatrixRoutines::multiplyPoint(theMatrixLocal, theMatrix, theMatrixOrigin);
}
vecNormals boundedBox::getLocalisedAxes(int a)
{
	if(a==1){a=4;}
	if(a==2){a=8;}
	return vecNormals((theMatrixOrigin[0]+theMatrix[a]),(theMatrixOrigin[1]+theMatrix[a+1]),(theMatrixOrigin[2]+theMatrix[a+2]));
}
vecNormals boundedBox::getPos()
{
	return pos;
}
vecNormals boundedBox::getBBCP(int a)
{
	return corners[a];
}
float boundedBox::getBBWidth()
{
	return bbWidth;
}
float boundedBox::getBBheight()
{
	return bbHeight;
}
float boundedBox::getBBDepth()
{
	return bbDepth;
}
void boundedBox::boundedBoxRotate(float a, float b, float c)
{
	for(int i=0;i<3;i++)
	{
		theMatrixOrigin[i]=NULL;
		theMatrixLocal[i]=0;
	}
	MatrixRoutines::multiplyPoint(theMatrixLocal, theMatrix, theMatrixOrigin);
	updateTM(a,b,c);
	updateBBCP();
}
void boundedBox::updateBBCP()
{
	corners[2]=vecNormals( (theMatrixOrigin[0]+theMatrix[0]*bbWidth)-(theMatrixOrigin[0]+theMatrix[4]*bbHeight)+(theMatrixOrigin[0]+theMatrix[8]*bbDepth),
						   (theMatrixOrigin[1]+theMatrix[1]*bbWidth)-(theMatrixOrigin[1]+theMatrix[5]*bbHeight)+(theMatrixOrigin[1]+theMatrix[9]*bbDepth),
						   (theMatrixOrigin[2]+theMatrix[2]*bbWidth)-(theMatrixOrigin[2]+theMatrix[6]*bbHeight)+(theMatrixOrigin[2]+theMatrix[10]*bbDepth) );

	corners[3]=vecNormals( (theMatrixOrigin[0]+theMatrix[0]*bbWidth)+(theMatrixOrigin[0]+theMatrix[4]*bbHeight)+(theMatrixOrigin[0]+theMatrix[8]*bbDepth),
						   (theMatrixOrigin[1]+theMatrix[1]*bbWidth)+(theMatrixOrigin[1]+theMatrix[5]*bbHeight)+(theMatrixOrigin[1]+theMatrix[9]*bbDepth),
						   (theMatrixOrigin[2]+theMatrix[2]*bbWidth)+(theMatrixOrigin[2]+theMatrix[6]*bbHeight)+(theMatrixOrigin[2]+theMatrix[10]*bbDepth) );

	corners[5]=vecNormals( (theMatrixOrigin[0]+theMatrix[0]*bbWidth)+(theMatrixOrigin[0]+theMatrix[4]*bbHeight)-(theMatrixOrigin[0]+theMatrix[8]*bbDepth),
						   (theMatrixOrigin[1]+theMatrix[1]*bbWidth)+(theMatrixOrigin[1]+theMatrix[5]*bbHeight)-(theMatrixOrigin[1]+theMatrix[9]*bbDepth),
						   (theMatrixOrigin[2]+theMatrix[2]*bbWidth)+(theMatrixOrigin[2]+theMatrix[6]*bbHeight)-(theMatrixOrigin[2]+theMatrix[10]*bbDepth) );

	corners[6]=vecNormals( (theMatrixOrigin[0]+theMatrix[0]*bbWidth)-(theMatrixOrigin[0]+theMatrix[4]*bbHeight)-(theMatrixOrigin[0]+theMatrix[8]*bbDepth),
						   (theMatrixOrigin[1]+theMatrix[1]*bbWidth)-(theMatrixOrigin[1]+theMatrix[5]*bbHeight)-(theMatrixOrigin[1]+theMatrix[9]*bbDepth),
						   (theMatrixOrigin[2]+theMatrix[2]*bbWidth)-(theMatrixOrigin[2]+theMatrix[6]*bbHeight)-(theMatrixOrigin[2]+theMatrix[10]*bbDepth) );
	vecNormals origin=vecNormals(theMatrixOrigin[0],theMatrixOrigin[1],theMatrixOrigin[2]);
	corners[0]= origin-corners[6];
	corners[1]= origin-corners[5];
	corners[7]= origin-corners[3];
	corners[4]= origin-corners[2];
	for(int i=0;i<8;i++){corners[i] += pos;}
}

void boundedBox::updateTM(double a, double b, double c)
{
	temp.CreateFromAxisAngle(theMatrix[0],theMatrix[1],theMatrix[2],a);
	MatrixRoutines::matrixMultiply4x4RigidBody(temp.getMatrix(), theMatrix, xMatrix);
	temp.CreateFromAxisAngle(theMatrix[4],theMatrix[5],theMatrix[6],b);
	MatrixRoutines::matrixMultiply4x4RigidBody(temp.getMatrix(), xMatrix, xyMatrix);
	temp.CreateFromAxisAngle(theMatrix[8],theMatrix[9],theMatrix[10],c);
	MatrixRoutines::matrixMultiply4x4RigidBody(temp.getMatrix(),xyMatrix,theMatrix);
}
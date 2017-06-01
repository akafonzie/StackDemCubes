
#include <math.h>
#include <iostream>
using namespace std;

#include "Quaternion.h"

#define PI	3.14159265358979323846

Quaternion::Quaternion()
{
	m_x = m_y = m_z = 0.0f;
	m_x = 1.0f;
	m_w = 1.0f;
	
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(i==j)
				pMatrix[i*4+j] = 1;
			else
				pMatrix[i*4+j] = 0;
		}
	}
}

Quaternion::Quaternion(double w, double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
	
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(i==j)
				pMatrix[i*4+j] = 1;
			else
				pMatrix[i*4+j] = 0;
		}
	}
}

Quaternion::~Quaternion()
{

}

void Quaternion::CreateFromAxisAngle(double x, double y, double z, double degrees)
{
	// First we want to convert the degrees to radians 
	// since the angle is assumed to be in radians
	double angle = double((degrees / 180.0f) * PI);

	// Here we calculate the sin( theta / 2) once for optimization
	double result = (double)sin( angle / 2.0f );

	// Calcualte the w value by cos( theta / 2 )
	m_w = (double)cos( angle / 2.0f );

	// Calculate the x, y and z of the quaternion
	m_x = double(x * result);
	m_y = double(y * result);
	m_z = double(z * result);
}

void Quaternion::CreateFromMatrix(double *a)
{
  double trace = a[0] + a[5] + a[10] + 1.0f;
  if( trace > 0.0001 ) {
    double s = 0.5f / sqrtf(trace);
    m_w = 0.25f / s;
    m_x = ( a[6] - a[9] ) * s;
    m_y = ( a[8] - a[2] ) * s;
    m_z = ( a[1] - a[4] ) * s;
  } else {
    if ( a[0] > a[5] && a[0] > a[10] ) {
      double s = 2.0f * sqrtf( 1.0f + a[0] - a[5] - a[10]);
      m_w = (a[9] - a[6] ) / s;
      m_x = 0.25f * s;
      m_y = (a[4] + a[1] ) / s;
      m_z = (a[8] + a[2] ) / s;
    } else if (a[5] > a[10]) {
      double s = 2.0f * sqrtf( 1.0f + a[5] - a[0] - a[10]);
      m_w = (a[8] - a[2] ) / s;
      m_x = (a[4] + a[1] ) / s;
      m_y = 0.25f * s;
      m_z = (a[9] + a[6] ) / s;
    } else {
      double s = 2.0f * sqrtf( 1.0f + a[10] - a[0] - a[5] );
      m_w = (a[4] - a[1] ) / s;
      m_x = (a[8] + a[2] ) / s;
      m_y = (a[9] + a[6] ) / s;
      m_z = 0.25f * s;
    }
  }
}

void Quaternion::CreateMatrix(double *pMatrix2)
{
	// Make sure the matrix has allocated memory to store the rotation data
	if(!pMatrix2) return;

	// First column
	pMatrix2[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z ); 
	pMatrix2[ 1] = 2.0f * (m_x * m_y + m_z * m_w);
	pMatrix2[ 2] = 2.0f * (m_x * m_z - m_y * m_w);
	pMatrix2[ 3] = 0.0f;  

	// Second column
	pMatrix2[ 4] = 2.0f * ( m_x * m_y - m_z * m_w );  
	pMatrix2[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z ); 
	pMatrix2[ 6] = 2.0f * (m_z * m_y + m_x * m_w );  
	pMatrix2[ 7] = 0.0f;  

	// Third column
	pMatrix2[ 8] = 2.0f * ( m_x * m_z + m_y * m_w );
	pMatrix2[ 9] = 2.0f * ( m_y * m_z - m_x * m_w );
	pMatrix2[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );  
	pMatrix2[11] = 0.0f;  

	// Fourth column
	pMatrix2[12] = 0;  
	pMatrix2[13] = 0;  
	pMatrix2[14] = 0;  
	pMatrix2[15] = 1.0f;

	// Now pMatrix[] is a 4x4 homogeneous matrix that can be applied to an OpenGL Matrix
}
double* Quaternion::getMatrix()
{
	// Make sure the matrix has allocated memory to store the rotation data
	if(!pMatrix) return NULL;

	// First column
	pMatrix[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z ); 
	pMatrix[ 1] = 2.0f * (m_x * m_y + m_z * m_w);
	pMatrix[ 2] = 2.0f * (m_x * m_z - m_y * m_w);
	pMatrix[ 3] = 0.0f;  

	// Second column
	pMatrix[ 4] = 2.0f * ( m_x * m_y - m_z * m_w );  
	pMatrix[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z ); 
	pMatrix[ 6] = 2.0f * (m_z * m_y + m_x * m_w );  
	pMatrix[ 7] = 0.0f;  

	// Third column
	pMatrix[ 8] = 2.0f * ( m_x * m_z + m_y * m_w );
	pMatrix[ 9] = 2.0f * ( m_y * m_z - m_x * m_w );
	pMatrix[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );  
	pMatrix[11] = 0.0f;  

	// Fourth column
	pMatrix[12] = 0;  
	pMatrix[13] = 0;  
	pMatrix[14] = 0;  
	pMatrix[15] = 1.0f;

	// Now pMatrix[] is a 4x4 homogeneous matrix that can be applied to an OpenGL Matrix
	return pMatrix;
}

Quaternion Quaternion::operator *(Quaternion q)
{
	Quaternion r;

	r.m_w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
	r.m_x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
	r.m_y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
	r.m_z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;

	return(r);
}

Quaternion Quaternion::operator +(Quaternion q)
{
	Quaternion r;

	r.m_w = m_w+q.m_w;
	r.m_x = m_x+q.m_x;
	r.m_y = m_y+q.m_y;
	r.m_z = m_z+q.m_z;

	return(r);
}
Quaternion Quaternion::operator -(Quaternion q)
{
	Quaternion r;

	r.m_w = m_w-q.m_w;
	r.m_x = m_x-q.m_x;
	r.m_y = m_y-q.m_y;
	r.m_z = m_z-q.m_z;

	return(r);
}
#ifndef _MATRIX_ROUTINES_H
#define _MATRIX_ROUTINES_H

#include <math.h>
using namespace std;
#define PI 3.1415926535897932384626433832795
const double ToRadians = PI / 180.0;


class MatrixRoutines
{
public:
	static void setToIdentity(double m[16])
	{
		for(int i =0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				if(i==j)
					m[i*4+j] = 1.0;
				else
					m[i*4+j] = 0.0;
			}
		}
	}
	static void setToIdentityWithPosition(double x, double y, double z, double m[16])
	{
		setToIdentity(m);

		m[12] = x;
		m[13] = y;
		m[14] = z;
	}
	static void multiplyPoint(double point[3], double matrix[16], double resultingPoint[3])
	{
		resultingPoint[0] = matrix[0]*point[0] + matrix[4]*point[1] + matrix[8]*point[2] + matrix[12];
		resultingPoint[1] = matrix[1]*point[0] + matrix[5]*point[1] + matrix[9]*point[2] + matrix[13];
		resultingPoint[2] = matrix[2]*point[0] + matrix[6]*point[1] + matrix[10]*point[2] + matrix[14];
	}
	static void multiplyRotationVector(double vector[3], double matrix[16], double resultingVector[3])
	{
		resultingVector[0] = matrix[0]*vector[0] + matrix[4]*vector[1] + matrix[8]*vector[2];
		resultingVector[1] = matrix[1]*vector[0] + matrix[5]*vector[1] + matrix[9]*vector[2];
		resultingVector[2] = matrix[2]*vector[0] + matrix[6]*vector[1] + matrix[10]*vector[2];
	}
	static void matrixMultiply4x4RigidBody(double A[16], double B[16], double C[16])
	{
		C[0] = A[0]*B[0] + A[4]*B[1] + A[8]*B[2];
		C[1] = A[1]*B[0] + A[5]*B[1] + A[9]*B[2];
		C[2] = A[2]*B[0] + A[6]*B[1] + A[10]*B[2];
		C[3] = 0;

		C[4] = A[0]*B[4] + A[4]*B[5] + A[8]*B[6];
		C[5] = A[1]*B[4] + A[5]*B[5] + A[9]*B[6];
		C[6] = A[2]*B[4] + A[6]*B[5] + A[10]*B[6];
		C[7] = 0;

		C[8] = A[0]*B[8] + A[4]*B[9] + A[8]*B[10];
		C[9] = A[1]*B[8] + A[5]*B[9] + A[9]*B[10];
		C[10] = A[2]*B[8] + A[6]*B[9] + A[10]*B[10];
		C[11] = 0;

		C[12] = A[0]*B[12] + A[4]*B[13] + A[8]*B[14] + A[12];
		C[13] = A[1]*B[12] + A[5]*B[13] + A[9]*B[14] + A[13];
		C[14] = A[2]*B[12] + A[6]*B[13] + A[10]*B[14] + A[14];
		C[15] = 1;
	}
};

#endif _MATRIX_ROUTINES_H
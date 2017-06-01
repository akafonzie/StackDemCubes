#ifndef _QUATERNION_H
#define _QUATERNION_H

class Quaternion  
{
public:
	Quaternion operator *(Quaternion q);
	Quaternion operator +(Quaternion q);
	Quaternion operator -(Quaternion q);
	void CreateMatrix(double *pMatrix);
	double* getMatrix();
	void CreateFromMatrix(double *pMatrix);
	void CreateFromAxisAngle(double x, double y, double z, double degrees);
	Quaternion();
	Quaternion(double w, double x, double y, double z);
	virtual ~Quaternion();

	double m_w;
	double m_z;
	double m_y;
	double m_x;
	double pMatrix[16];
};

#endif _QUATERNION_H
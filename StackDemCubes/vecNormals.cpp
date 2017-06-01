#include "vecNormals.h"

vecNormals::vecNormals()
{
	x=y=z=0;
	vec[0]=x;
	vec[1]=y;
	vec[2]=z;
}
vecNormals::vecNormals(float a, float b)
{
	x=a;y=b;z=0;
	vec[0]=x;
	vec[1]=y;
	vec[2]=z;
}

vecNormals::vecNormals(float a, float b, float c)
{
	x=a;y=b;z=c;
	vec[0]=x;
	vec[1]=y;
	vec[2]=z;
}


float vecNormals::mag() const
{
	return sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
}
float vecNormals::magSqr() const
{
	return (vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
}


float vecNormals::dotProduct(const vecNormals &other) const
{
	return (x*other.x+y*other.y+z*other.z);
}

vecNormals vecNormals::crossProduct(const vecNormals &other) const
{
	return vecNormals((y*other.z-z*other.y),
					  (z*other.x-x*other.z),
					  (x*other.y-y*other.x));
						
}

float vecNormals::length()
{
	return sqrt(x*x+y*y+z*z);
}

vecNormals vecNormals::normalize()
{
	float temp=sqrt(x*x+y*y+z*z);
	return vecNormals(x/temp, y/temp, z/temp);
}

void vecNormals::change(float a, float b, float c)
{
	x=a;y=b;z=c;
}
void vecNormals::change(const vecNormals other)
{
	x=other.x;
	y=other.y;
	z=other.z;
}


void vecNormals::changeX(float a){x=a;}
void vecNormals::changeY(float a){y=a;}
void vecNormals::changeZ(float a){z=a;}

float vecNormals::getxPos()
{
	return x;
}
float vecNormals::getyPos()
{
	return y;
}
float vecNormals::getzPos()
{
	return z;
}

void vecNormals::setxPos(float xPos)
{
	x=xPos;
}

void vecNormals::setyPos(float yPos)
{
	y=yPos;
}
void vecNormals::setzPos(float zPos)
{
	z=zPos;
}

vecNormals vecNormals::operator+(const vecNormals &other) const
{
	return vecNormals(x+other.x, y+other.y,z+other.z);
}

vecNormals vecNormals::operator-(const vecNormals &other) const
{
	return vecNormals(x-other.x, y-other.y,z-other.z);
}

vecNormals vecNormals::operator*(float scale) const
{
	return vecNormals(x*scale,y*scale,z*scale);
}

vecNormals vecNormals::operator/(float scale) const
{
	if(scale!=0)
	return vecNormals(x/scale,y/scale,z/scale);
	else
		return vecNormals();
}

vecNormals &vecNormals::operator+=(const vecNormals& other)
{
	x+=other.x;
	y+=other.y;
	z+=other.z;
	return *this;
}

vecNormals &vecNormals::operator-=(const vecNormals& other)
{
	x-=other.x;
	y-=other.y;
	z-=other.z;
	return *this;
}

vecNormals &vecNormals::operator*=(float scale)
{
	x*=scale;
	y*=scale;
	z*=scale;
	return *this;
}

vecNormals &vecNormals::operator/=(float scale)
{
	if(scale!=0)
	x/=scale;
	y/=scale;
	z/=scale;
	return *this;
}
bool vecNormals::operator==(const vecNormals other)
{
	return (x==other.x, y==other.y, z==other.z);
}
bool vecNormals::operator!=(const vecNormals other)
{
	//!(*this==other);
	return false;
}

std::ostream& operator<<(std::ostream &out, const vecNormals &vec)
{
	cout<<'('<<vec.x<<", "<<vec.y<<", "<<vec.z<<')';
	return out;
}
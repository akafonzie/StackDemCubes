#ifndef VECNORMALS_H
#define VECNORMALS_H
#include<math.h>
#include <cstdlib>
#include<iostream>
using namespace std;

class vecNormals{
private:
	float vec[3];
public:
	float x,y,z;
	vecNormals();
	vecNormals(float a, float b);
	vecNormals(float a, float b, float c);
	float getxPos();
	float getyPos();
	float getzPos();
	void setxPos(float xPos);
	void setyPos(float yPos);
	void setzPos(float zPos);

	vecNormals operator+(const vecNormals &other) const;
	vecNormals operator-(const vecNormals &other) const;
	vecNormals operator*(float scale) const;
	vecNormals operator/(float scale) const;
	vecNormals& operator+=(const vecNormals &other);
	vecNormals& operator-=(const vecNormals &other);
	vecNormals& operator*=(float scale);
	vecNormals& operator/=(float scale);
	bool operator==(const vecNormals other);
	bool operator!=(const vecNormals other);

	float mag()const;
	float magSqr()const;
	vecNormals normalize();
	float dotProduct(const vecNormals &other)const;
	vecNormals crossProduct(const vecNormals &other)const;
	float length();

	void change(float a, float b, float c);
	void change(const vecNormals other);
	void changeX(float a);
	void changeY(float a);
	void changeZ(float a);

	friend std::ostream& operator<<(std::ostream& out, const vecNormals& vec);
};
#endif
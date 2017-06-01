#include "sats.h"
sats::sats()
{
}
projRes sats::projectBox(vecNormals axis, boundedBox* box)
{
	projRes result;
	float min, max;
	float dp;
	for (int j = 0; j <8; j++)
	{
		dp = box->getBBCP(j).dotProduct(axis);
		if (j == 0)
		{
			min = dp; 
			max = dp;
		}
		else
		{
			if (dp < min)
				min = dp;
			if (dp > max)
				max = dp;
		}
	}
	result.min = min;
	result.max = max;
	return result;
}

float getIntervalDistance (projRes projA, projRes projB)
{
	if (projA.min < projB.min)
		return projB.min - projA.max;
	else
		return projA.min - projB.max;
}

collRes sats::test(boundedBox* A, boundedBox*B)
{
	collRes result;
	projRes projA;
	projRes projB;
	vecNormals MTV = vecNormals(0.0f,0.0f,0.0f);
	vecNormals translationAxis  = vecNormals(0.0f,0.0f,0.0f);
	vecNormals axesToTest = vecNormals(0.0f,0.0f,0.0f);
	vecNormals distanceBetween = vecNormals(0.0f,0.0f,0.0f);
	float intDist = 0.0f;
	float minIntDist = 100.0f;
	for (int i = 0; i < 15; i++) 
	{
		if (i < 3)
			axesToTest = A->getLocalisedAxes(i).normalize();
		else if (i<6)
			axesToTest = B->getLocalisedAxes(i-3).normalize();
		else if (i<9)
			axesToTest = A->getLocalisedAxes(0).crossProduct(B->getLocalisedAxes(i-6)).normalize();
		else if (i<12)
			axesToTest = A->getLocalisedAxes(1).crossProduct(B->getLocalisedAxes(i-9)).normalize();
		else if (i<15)
			axesToTest = A->getLocalisedAxes(2).crossProduct(B->getLocalisedAxes(i-12)).normalize();
		projA = projectBox(axesToTest,A);
		projB = projectBox(axesToTest,B);
		intDist = getIntervalDistance(projA, projB);
		if (intDist > 0)
		{
			result.colliding = false;
			result.MTV = MTV;
			return result;
		}
        intDist = abs(intDist);
        if (intDist < minIntDist) 
		{
            minIntDist = intDist;
            translationAxis = axesToTest;

			distanceBetween = A->getPos() - B->getPos();
			if (distanceBetween.dotProduct(translationAxis) < 0)
                translationAxis = vecNormals(-translationAxis.x,-translationAxis.y,-translationAxis.z);
        }
	}
	result.MTV = translationAxis * minIntDist;
    return result;
}

#include"MathFunctions.h"

float rotation_difference(float r1, float r2)
{
	float d = r1 - r2;
	if (d > 180)
	d -= 360;
	else if (d <= -180)
	d += 360;
	return d;
}
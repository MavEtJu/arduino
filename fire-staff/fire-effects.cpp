
/******************CODE*****************/
/**************DO NOT TOUCH*************/
/*********unless you really need********/

#include "math.h"

float SineEaseOut(float p);
float QuadraticEaseInOut(float p);
float CubicEaseInOut(float p);

float CubicEaseInOut(float p)
{
	if (p < 0.5) {
		return 4 * p * p * p;
	} else {
		float f = ((2 * p) - 2);
		return 0.5 * f * f * f + 1;
	}
}

float QuadraticEaseInOut(float p)
{
	if (p < 0.5) {
		return 2 * p * p;
	} else {
		return (-2 * p * p) + (4 * p) - 1;
	}
}

float SineEaseOut(float p)
{
	return sin(p * M_PI_2);
}

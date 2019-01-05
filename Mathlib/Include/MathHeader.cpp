#include "MathHeader.h"

float MATH_DLL RadianToDegree(float radian)
{
	return radian / JEONG_PI * 180.0f;
}

float MATH_DLL DegreeToRadian(float degree)
{
	return degree / 180.f * JEONG_PI;
}

int MATH_DLL RandomRange(int R1, int R2)
{
	if (R1 <= 0 && R2 <= 0)
		return 0;

	return (int)(rand() % (R2 - R1 + 1)) + R1;
}

float Lerp(float Start, float End, float DeltaTime)
{
	return Start + DeltaTime * (End - Start);
}

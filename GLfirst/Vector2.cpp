#include "precompiled.h"
#include "Vector2.h"

Vector2::Vector2() : X(0), Y(0)
{
}
Vector2::Vector2(float x = 0, float y = 0): X(x), Y(y)
{
}
Vector2::~Vector2(void)
{
}
float Vector2::Distance(Vector2 dest)
{
	float X2_X1_plus_Y2_Y1;

	X2_X1_plus_Y2_Y1 = (dest.X - X) * (dest.X - X) + (dest.Y - Y) * (dest.Y - Y);

	float distance = sqrt(X2_X1_plus_Y2_Y1);

	return distance;
}

float Vector2::Distance(Vector2 src, Vector2 dest)
{
	float X2_X1_plus_Y2_Y1;

	X2_X1_plus_Y2_Y1 = (dest.X - src.X) * (dest.X - src.X) + (dest.Y - src.Y) * (dest.Y - src.Y);

	float distance = sqrt(X2_X1_plus_Y2_Y1);

	return distance;
}
float Vector2::Length()
{
	return sqrt((X * X) + (Y * Y));
}
void Vector2::Normalise()
{
	float length = Length();
	X /= length;
	Y /= length;
}
Vector2 Vector2::Rotate(float byRadians)
{
	return Vector2(	X * cos(byRadians) - Y * sin(byRadians),
					Y * cos(byRadians) + X * sin(byRadians)
					);
}
Vector2 Vector2::Rotate(Vector2 aboutPoint, float byRadians)
{
	Vector2 rotated = Vector2(Vector2(X,Y)-aboutPoint);
	rotated = rotated.Rotate(byRadians);
	return rotated+aboutPoint;
}
float Vector2::AngleRad()
{
	float angle = atan2(Y,X);
	if(angle < 0) angle += 2 * PI;
	return angle;
}
float Vector2::AngleDeg()
{
	return this->AngleRad()*TO_DEGREES;
}
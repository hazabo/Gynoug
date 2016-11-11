
#include "Vector2.h"

Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

Vector2::Vector2(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

Vector2::Vector2(float* a_fv2)
{
	x = a_fv2[0];
	y = a_fv2[1];
}

Vector2::~Vector2()
{
}

void Vector2::SetValue(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void Vector2::SetValue(const Vector2& a_v2)
{
	x = a_v2.x;
	y = a_v2.y;
}


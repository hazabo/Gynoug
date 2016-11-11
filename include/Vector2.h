
#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2 
{
public:
	//This is the constructor for a Vector 2 class
	Vector2();
	// This is another constructor that takes two arguments
	Vector2(float a_x, float a_y);
	//And another constructor taking one argument as a float vector/array
	Vector2(float* a_fv2);
	//Destructor - called when we call delete on a new'd object
	~Vector2();

	void SetValue(float a_x, float a_y);
	void SetValue(const Vector2& a_v2);

	//Overload Casting operators
	operator float*();
	operator const float*() const;

	//Overlaoad Operators for Addition and Plus Equals for ease of use
	Vector2 operator + (float a_fScalar);
	Vector2 operator +  (const Vector2& a_v2);
	Vector2& operator += (const Vector2& a_v2);
	
	union
	{
		struct
		{
			float x; float y;
		};
		struct 
		{
			float u; float v;
		};
		struct
		{
			float i[2];
		};
	};

private:
};

inline Vector2::operator float*()
{
	return static_cast<float*>(i);
}

inline Vector2::operator const float*() const
{
	return static_cast<const float*>(i);
}

inline Vector2 Vector2::operator + (float a_fScalar)
{
	return Vector2(x + a_fScalar, y + a_fScalar);
}

inline Vector2 Vector2::operator + (const Vector2& a_v2)
{
	return Vector2( x + a_v2.x, y + a_v2.y);
}

inline Vector2& Vector2::operator += (const Vector2& a_v2)
{
	x += a_v2.x;
	y += a_v2.y;
	return *this;
}
#endif //__VECTOR2_H__
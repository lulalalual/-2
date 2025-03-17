#pragma once
#include"cmath"

//2D向量类
class Vector2
{
public:
	float x = 0;
	float y = 0;
public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y) : x(x), y(y) {};

	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator+=(const Vector2& vec) 
	{
		x += vec.x,y += vec.y;
	}

	void operator-=(const Vector2& vec) 
	{
		x -= vec.x, y -= vec.y;
	}

	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	float operator*(const Vector2& vec)const
	{
		return x * vec.x+ y * vec.y;
	}

	Vector2 operator*(float  vec) const
	{
		return Vector2(x * vec, y * vec);
	}

	void operator*=(float  vec)
	{
		x *= vec, y *= vec;
	}

	float length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2 normalize()
	{
		float len = length();
		if (len == 0)
			return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}
	//向量标准化
};
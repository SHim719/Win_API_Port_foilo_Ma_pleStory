#pragma once


#include <cmath>

struct Vec2
{
	static Vec2 Zero;
	static Vec2 One;

	static float Dot(Vec2& v1, Vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	float x, y;

	Vec2() : x(0), y(0) {}
	Vec2(float _x, float _y) : x(_x), y(_y) { }

	Vec2 normalize()
	{
		float len = length();
		x /= len;
		y /= len;

		return *this;
	}

	inline float length()
	{
		return sqrt(x * x + y * y);
	}

	inline void Clear()
	{
		x = 0.f;
		y = 0.f;
	}

	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}

	Vec2 operator + (const Vec2& v)
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 operator - (const Vec2& v)
	{
		return Vec2(x - v.x, y - v.y);
	}

	Vec2 operator * (const Vec2& v)
	{
		return Vec2(x * v.x, y * v.y);
	}

	Vec2 operator / (const Vec2& v)
	{
		return Vec2(x / v.x, y / v.y);
	}

	Vec2 operator * (const float& f)
	{
		return Vec2(x * f, y * f);
	}

	Vec2 operator / (const float& f)
	{
		return Vec2(x / f, y / f);
	}

	void operator += (const Vec2& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator -= (const Vec2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	void operator *= (const Vec2& v)
	{
		x *= v.x;
		y *= v.y;
	}

	void operator *= (const float& f)
	{
		x *= f;
		y *= f;
	}

	bool operator == (const Vec2& v)
	{
		return (x == v.x) && (y == v.y);
	}

	bool operator != (const Vec2& v)
	{
		return !(*this == v);
	}
};


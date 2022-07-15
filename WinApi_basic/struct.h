#pragma once
struct vec2
{
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	vec2& Normalize()
	{
		float fLen = Length();
		if (fLen != 0)
		{
			x /= fLen;
			y /= fLen;
		}
		return *this;
	}

	vec2 operator+(const vec2 &_num)
	{
		return vec2(x + _num.x, y + _num.y);
	}

	vec2 operator-(const vec2& _num)
	{
		return vec2(x - _num.x, y - _num.y);
	}

	vec2 operator*(const vec2& _num)
	{
		return vec2(x * _num.x, y * _num.y);
	}

	vec2 operator/(const vec2& _num)
	{
		return vec2(x / _num.x, y / _num.y);
	}


	vec2():x(0.f),y(0.f)
	{}

	vec2(float _x,float _y) :x(_x), y(_y)
	{}

	vec2(int _x,int _y):x(float(_x)),y(float(_y))
	{}

	vec2(long _x, long _y) :x(float(_x)), y(float(_y))
	{}

};
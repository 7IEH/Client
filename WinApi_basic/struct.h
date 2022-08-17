#pragma once
struct vec2
{
	float x;
	float y;

public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

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

	void operator+=(const vec2 _num)
	{
		x += _num.x;
		y += _num.y;
	}

	vec2 operator-(const vec2& _num)
	{
		return vec2(x - _num.x, y - _num.y);
	}

	vec2 operator*(const vec2& _num)
	{
		return vec2(x * _num.x, y * _num.y);
	}

	vec2 operator*(const int	_i)
	{
		return vec2(x * (float)_i, y *(float) _i);
	}

	vec2 operator*(const float	_i)
	{
		return vec2(x * _i, y * _i);
	}

	vec2 operator*(const UINT	_i)
	{
		return vec2(x * _i, y * _i);
	}

	vec2 operator/( vec2& _num)
	{
		return vec2(x / _num.x, y / _num.y);
	}

	vec2 operator/(float _f)
	{
		return vec2(x / _f, y / _f);
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
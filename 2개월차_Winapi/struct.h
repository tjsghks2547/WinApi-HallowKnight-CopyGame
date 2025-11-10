#pragma once


struct Vec2 //수학적 벡터(크기와 방향을 나타내는) 를 의미 
{
	float x;
	float y; 

public:

	bool IsZero()
	{
		if(x==0.f && y==0.f)
		{
			return true;
		}
		return false;
	}

	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float fLen = Length();
		
		assert(fLen != 0.f); // 에러메세지 띄움

		x /= fLen;
		y /= fLen;

		return *this; 
	}
public:
	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}


	Vec2 operator + (Vec2 vOther)
	{
		return Vec2(x + vOther.x, y + vOther.y);
	}



	void operator += (Vec2 vOther)
	{
		x += vOther.x; 
		y += vOther.y;
	}

	void operator -= (Vec2 vOther)
	{
		x -= vOther.x;
		y -= vOther.y;
	}

	void operator -= (float _f)
	{
		x -= _f;
		y -= _f;

	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;

	}

	Vec2 operator - (Vec2 vOther)
	{
		return Vec2(x - vOther.x, y - vOther.y);
	}

	Vec2 operator * (Vec2 vOther)
	{
		return Vec2(x * vOther.x, y * vOther.y);
	}

	Vec2 operator / (Vec2 vOther)
	{
		assert(!(0.f == vOther.x || 0.f == vOther.y));
		return Vec2(x / vOther.x, y / vOther.y);
	}

	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vec2(x /_f, y /_f);
	}


	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x *_f, y * _f);
	}


	bool operator != (Vec2 _Other)
	{
		if(x == _Other.x)
		{
			if(y ==_Other.y)
			{
				return false;
			}
		}

		return true; 
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
};
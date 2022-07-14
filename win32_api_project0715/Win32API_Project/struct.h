#pragma once

class Vector
{
public:
	float x;
	float y;

public:
	Vector()
		: x(0.f)
		, y(0.f)
	{

	}

	Vector(float _x, float _y)
		: x(_x), y(_y)
	{

	}

	~Vector(){}
};

typedef Vector Vec;
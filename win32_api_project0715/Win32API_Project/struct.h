#pragma once

class Vector
{
public:
	float x;
	float y;

public:

	float Length() // ������ ��ü ������ ����
	{
		return sqrtf(x * x + y * y);
	}

	void Nomalize()
	{
		float fLenght = sqrtf(x* x + y * y);
		x /= fLenght;
		y /= fLenght;
		// �̷��� �ϸ� ������ �Ȱ����� ���̸� 1�� ���� ���� ���Ͱ� ������ �ȴ�.
	}

	float Distance(Vector _vOther) // �� ���� ������ �Ÿ�
	{
		float _x = x - _vOther.x;
		float _y = y - _vOther.y;

		return sqrtf(_x * _x + _y * _y);
	}

	float Dot(Vector _vOther) // ���� ���͸� ������ ������ ���ϴ� �Լ�.
	{
		return x * _vOther.x + y * _vOther.y;
	}

	Vector operator + (Vector _vOther)
	{
		return Vector(x += _vOther.x, y += _vOther.y);
	}

	void operator += (Vector _vOther)
	{
		this->x += _vOther.x;
		this->y += _vOther.y;
	}

	void operator = (POINT _pt)
	{
		this->x = (float)_pt.x;
		this->y = (float)_pt.y;
	}

	void operator -= (Vector _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vector operator * (Vector _vOther)
	{
		return Vector(x * _vOther.x, y * _vOther.y);
	}

	Vector operator * (float _f)
	{
		return Vector(x * _f, y * _f);
	}

	void operator *= (Vector _vOther)
	{
		x *= _vOther.x, y *= _vOther.y;
	}

	void operator *= (float _f)
	{
		x *= _f, y *= _f;
	}

	Vector operator / (Vector _vOther)
	{
		assert(_vOther.x != 0.f && _vOther.y != 0.f);
		return Vector(x / _vOther.x, y / _vOther.y);
	}

	Vector operator / (float _f)
	{
		assert(_f != 0.f);
		return Vector(x / _f, y / _f);
	}

	void operator /= (Vector _vOther)
	{
		assert(_vOther.x != 0.f && _vOther.y != 0.f);
		x /= _vOther.x, y /= _vOther.y;
	}

	void operator /= (float _f)
	{
		assert(_f != 0.f);
		x /= _f, y /= _f;
	}

	Vector operator - (Vector _vOther)
	{
		return Vector(x - _vOther.x, y - _vOther.y);
	}

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

	Vector(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}

	~Vector(){}
};

typedef Vector Vec;

struct tSelectPen
{
private:
	HDC m_hDC;
	HPEN m_hPrevPen;

public:
	void SetPenColor(PEN_COLOR _color)
	{
		m_hPrevPen = (HPEN)SelectObject(m_hDC, CEngine::GetInst()->GetPen(_color));
	}

public:
	tSelectPen(HDC _dc)
		: m_hDC(_dc)
		, m_hPrevPen(0)
	{

	}

	tSelectPen(HDC _dc, PEN_COLOR _color)
		: m_hDC(_dc)
		, m_hPrevPen(0)
	{
		// SelectObject �Լ��� GDI Object ���� �۾��� �����Ǹ� DC �� ������ ����ϰ� �ִ� GDI Object�� �ڵ� ����, �����ϸ� null ���� ��ȯ.
		m_hPrevPen = (HPEN)SelectObject(m_hDC, CEngine::GetInst()->GetPen(_color));
	}

	~tSelectPen()
	{
		SelectObject(m_hDC, m_hPrevPen);
	}
};

struct tSelectBrush
{
private:
	HDC m_hDC;
	HBRUSH m_hPrevBrush;

public:
	tSelectBrush(HDC _dc)
		:m_hDC(_dc)
		, m_hPrevBrush(0)
	{

	}

	tSelectBrush(HDC _dc, BRUSH_COLOR _color)
		: m_hDC(_dc)
		, m_hPrevBrush(0)
	{
		m_hPrevBrush = (HBRUSH)SelectObject(m_hDC, CEngine::GetInst()->GetBrush(_color));
	}

	~tSelectBrush()
	{
		SelectObject(m_hDC, m_hPrevBrush);
	}
};

struct tEventInfo
{
	EVENT_TYPE eType;
	DWORD_PTR first;
	DWORD_PTR second;

};


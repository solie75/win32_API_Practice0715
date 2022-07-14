#pragma once

class CObject
{
private:
	Vec m_vPos;
	Vec m_vScale;

public:
	void SetPos(Vec _vPos)
	{
		m_vPos = _vPos;
	}
	void SetScale(Vec _vScale)
	{
		m_vScale = _vScale;
	}

	Vec GetPos()
	{
		return m_vPos;
	}
	Vec GetScale()
	{
		return m_vScale;
	}

	virtual void ObjTick() = 0;
	virtual void ObjRender(HDC _dc);

public:
	CObject();
	~CObject();
};


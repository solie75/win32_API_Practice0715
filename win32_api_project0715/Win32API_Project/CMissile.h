#pragma once
#include "CObject.h"

class CImage;

class CMissile :
    public CObject
{
private:
    CImage* m_MissileImage;
    float m_MissileSpeed;

    float m_fDir; // �̵����� (����)
    Vec m_vDir; // ����
    // �ӷ±��� �����ϰ� �ִ� ���� ���ٴ� ������ �ӷ���  float������ ���� �����ϰ�
    // ���⼺�� ���ͷ� ǥ���Ѵ�.

public:
    void SetDir(float _fDir) { m_fDir = _fDir; }
    void SetDir(Vec _vDir)
    { 
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

    Vec GetDir() { return m_vDir; }

    virtual void ObjTick() override;
    virtual void ObjRender(HDC _dc) override;

public:
    CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();
};


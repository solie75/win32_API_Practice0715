#pragma once
#include "CComponent.h"

class CAnimation;

class CAnimator :
    public CComponent
{
private:
    map<wstring,CAnimation*> m_mapAnim;
    CAnimation* m_pCurAnim;

    bool m_bRepeat; // �ݺ���� ����
public:

    virtual void ComponentTick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    void CreateAnimator(const wstring& _strName
        , CImage* _pImage, Vec _vLeftTop, Vec _vSize, Vec _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);
    // createAnimation ����(�̸�, �̹���, ������, ũ��, ���� �̹����� �������� ����, �ִϸ��̼� ������ ���� ������ ����, �� �������� ������ ���� �ð�)
    
    CAnimation* FindAnimator(const wstring& _strKey);
    void Play(const wstring& _strName, bool m_Repeat);
public:
    CAnimator();
    ~CAnimator();
};


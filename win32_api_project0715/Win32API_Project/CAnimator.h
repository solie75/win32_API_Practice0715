#pragma once
#include "CComponent.h"

class CAnimation;

class CAnimator :
    public CComponent
{
private:
    map<wstring,CAnimation*> m_mapAnim;
    CAnimation* m_pCurAnim;

    bool m_bRepeat; // 반복재생 유무
public:

    virtual void ComponentTick() override;
    virtual void ComponentRender(HDC _dc) override;

public:
    void CreateAnimator(const wstring& _strName
        , CImage* _pImage, Vec _vLeftTop, Vec _vSize, Vec _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);
    // createAnimation 인자(이름, 이미지, 기준점, 크기, 다음 이미지로 가기위한 간격, 애니메이션 수행을 위한 프레임 갯수, 한 프레임이 가지는 지속 시간)
    
    CAnimation* FindAnimator(const wstring& _strKey);
    void Play(const wstring& _strName, bool m_Repeat);
public:
    CAnimator();
    ~CAnimator();
};


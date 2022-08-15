#pragma once
#include "CEntity.h"

class Image;

struct tAnimFrm
{
    Vec vLeftTop;       // 이미지 내에서 최상단 픽셀 좌표
    Vec vSize;          // 좌상단으로부터 잘라 낼 가로 세로 픽셀 길이
    Vec vOffSet;        // 출력 위치 오프셋
    float fDuration;    // 해당 프레임 유지 시간

};

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_pAnimator;

    vector<tAnimFrm>    m_vecFrm; // 모든 프레임 정보
    CImage*             m_pImage; // Animation Frame Image

    int                 m_iCurFrm; // 현재 출력시킬 프레임의 정보
    float               m_fAccTime; // 누적시간

    bool                m_bCamRelation; // 카메라 영향
    bool                m_bFinish; // 애니메이션 1회 재생 완료

public:
    void AnimationTick();
    void AnimationRender(HDC _dc);
public:
    void CreateAnimation(CImage* _pImage, Vec _vLeftTop, Vec _vSize, Vec _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    void Reset()
    {
        m_iCurFrm = 0; // 프레임의 현재값을 처음으로 한다.
        m_bFinish = false;
        m_fAccTime = 0.f;
    }

    bool IsFinish() { return m_bFinish; }

public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};


#pragma once
#include "CEntity.h"

class Image;

struct tAnimFrm
{
    Vec vLeftTop; // 이미지 내에서 최상단 픽셀 좌표
    Vec vSize; // 좌상단으로부터 잘라 낼 가로 세로 픽셀 길이
    Vec vOffSet;
    float fTerm;  // 해당 프레임 유지 시간
};

class CAnimation :
    public CEntity
{
private:
    vector<tAnimFrm>    m_vecFrm; // 모든 프레임 정보
    CImage*             m_pImage; // Animation Frame Image

public:
    void AnimationTick();

public:
    CAnimation();
    ~CAnimation();
};


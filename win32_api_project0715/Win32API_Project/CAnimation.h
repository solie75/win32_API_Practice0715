#pragma once
#include "CEntity.h"

class Image;

struct tAnimFrm
{
    Vec vLeftTop; // �̹��� ������ �ֻ�� �ȼ� ��ǥ
    Vec vSize; // �»�����κ��� �߶� �� ���� ���� �ȼ� ����
    Vec vOffSet;
    float fTerm;  // �ش� ������ ���� �ð�
};

class CAnimation :
    public CEntity
{
private:
    vector<tAnimFrm>    m_vecFrm; // ��� ������ ����
    CImage*             m_pImage; // Animation Frame Image

public:
    void AnimationTick();

public:
    CAnimation();
    ~CAnimation();
};


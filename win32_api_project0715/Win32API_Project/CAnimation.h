#pragma once
#include "CEntity.h"

class Image;

struct tAnimFrm
{
    Vec vLeftTop;       // �̹��� ������ �ֻ�� �ȼ� ��ǥ
    Vec vSize;          // �»�����κ��� �߶� �� ���� ���� �ȼ� ����
    Vec vOffSet;        // ��� ��ġ ������
    float fDuration;    // �ش� ������ ���� �ð�

};

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_pAnimator;

    vector<tAnimFrm>    m_vecFrm; // ��� ������ ����
    CImage*             m_pImage; // Animation Frame Image

    int                 m_iCurFrm; // ���� ��½�ų �������� ����
    float               m_fAccTime; // �����ð�

    bool                m_bCamRelation; // ī�޶� ����
    bool                m_bFinish; // �ִϸ��̼� 1ȸ ��� �Ϸ�

public:
    void AnimationTick();
    void AnimationRender(HDC _dc);
public:
    void CreateAnimation(CImage* _pImage, Vec _vLeftTop, Vec _vSize, Vec _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    void Reset()
    {
        m_iCurFrm = 0; // �������� ���簪�� ó������ �Ѵ�.
        m_bFinish = false;
        m_fAccTime = 0.f;
    }

    bool IsFinish() { return m_bFinish; }

public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};


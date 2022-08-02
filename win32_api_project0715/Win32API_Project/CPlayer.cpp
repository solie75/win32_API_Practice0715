#include "stdafx.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CEngine.h"
#include "CImage.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CEventMgr.h"

CPlayer::CPlayer()
	: m_fSpeed(200.f)
	, m_AccTime(0.f)
{
	AddComponent(new CCollider);
	AddComponent(new CAnimator);

	GetCollider()->SetColliderScale(Vec(50.f, 50.f));
	GetCollider()->SetColliderOffset(Vec(0.f, 20.f));
}

CPlayer::~CPlayer()
{
}

void CPlayer::ObjTick()
{
	m_AccTime += DT;

	Vec vPos = GetPos();

	//if (GetAsyncKeyState('W') & 0x8000)
	if(IsPressed(KEY_TYPE::UP))
	{
		vPos.y -= m_fSpeed * DT;
	}
	if (IsPressed(KEY_TYPE::DOWN))
	{
		vPos.y += m_fSpeed * DT;
	}
	if (IsPressed(KEY_TYPE::LEFT))
	{
		vPos.x -= m_fSpeed * DT;
	}
	if (IsPressed(KEY_TYPE::RIGHT))
	{
		vPos.x += m_fSpeed * DT;
	}
	if (IsPressed(KEY_TYPE::SPACE))
	{
		if (m_AccTime >= 0.1f)
		{
			/*CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CMissile* pMissile = new CMissile;

			pMissile->SetPos(GetPos());
			pMissile->SetScale(Vec(20.f, 20.f));

			pCurScene->AddObject( pMissile, LAYER_TYPE::PLAYER_PROJECTILE);

			m_AccTime = 0.f;*/
			// ������ player.cpp ���� eventmgr�� ����ϴ� ������ ����

			CMissile* pMissile = new CMissile;
			pMissile->SetPos(GetPos() + Vec(0.f, -50.f));// CPlayer ��ü�� ��ġ�� �������� ����

			tEventInfo info = {};
			info.eType = EVENT_TYPE::CREATE_OBJECT;
			info.first = (DWORD_PTR)pMissile;
			info.second = (DWORD_PTR)LAYER_TYPE::PLAYER_PROJECTILE;
			// �̺�Ʈ �߰�

			CEventMgr::GetInst()->AddEvent(info);

			m_AccTime = 0.f;

		}
	}

	SetPos(vPos);

	// Tick()�� ȣ�� ����
	// CEngine�� EngineTick()
	// -> CSceneMgrTick()
	// -> ( purScene -> SceneTick() )
	// -> ( vecObject[i] -> ObjTick() )
	// -> ( arrComponent[i] -> ComponentTick() )

	// ������ CPlayer::ObjTick()�� CompoenentTick()�� ���� �� �� ���� ������
	// ��ü�� CompoenetTick()�� �����ϱ� ���ؼ��� �θ� Ŭ���� CObject�� ObjTick()�� ȣ���� ��� �Ѵ�.
	CObject::ObjTick();
}

void CPlayer::ObjRender(HDC _dc) // ���⿡�� ������ dc �� SecondDC �̴�.
{
	CImage* pImage = CResMgr::GetInst()->FindImg(L"PlayerImage");

	if (nullptr == pImage)
	{
		return;
	}

	//Vec vPos = GetPos();
 
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());

	//BitBlt(_dc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetImageDC(), 0, 0, SRCCOPY);
	TransparentBlt(_dc, (int)vPos.x - pImage->GetWidth() / 2, (int)vPos.y - pImage->GetHeight() / 2
		, pImage->GetWidth(), pImage->GetHeight()
		, pImage->GetImageDC(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));

	// �ڽ��� ������Ʈ���� ȭ�鿡 �׷����� �� ������ �θ� ���� ������ ȣ�����ش�.
	CObject::ObjRender(_dc);

}

void CPlayer::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	_pOtherCollider->GetOwnerObject();
}

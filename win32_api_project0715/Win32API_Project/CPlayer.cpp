#include "stdafx.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CGuidedMissile.h"
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
#include "CRigidBody.h"

CPlayer::CPlayer()
	: m_fSpeed(200.f)
	, m_AccTime(0.f)
{
	AddComponent(new CCollider);
	AddComponent(new CAnimator);
	AddComponent(new CRigidBody);

	GetCollider()->SetColliderScale(Vec(50.f, 50.f));
	GetCollider()->SetColliderOffset(Vec(0.f, 20.f));

	CImage* pPlayerAtlas = CResMgr::GetInst()->LoadImg(L"PlayerAtlas", L"image\\link.bmp");
	GetAnimator()->CreateAnimator(L"Walk_Up", pPlayerAtlas, Vec(0.f, 780.f), Vec(120.f, 130.f), Vec(0.f, -30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimator(L"Walk_Down", pPlayerAtlas, Vec(0.f, 520.f), Vec(120.f, 130.f), Vec(0.f, -30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimator(L"Walk_Left", pPlayerAtlas, Vec(0.f, 650.f), Vec(120.f, 130.f), Vec(0.f, -30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimator(L"Walk_Right", pPlayerAtlas, Vec(0.f, 910.f), Vec(120.f, 130.f), Vec(0.f, -30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimator(L"Standing", pPlayerAtlas, Vec(0.f, 0.f), Vec(120.f, 130.f), Vec(0.f, -30.f), 120.f, 10, 0.1f);

	GetAnimator()->Play(L"Standing", pPlayerAtlas);
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
		//vPos.y -= m_fSpeed * DT;
		GetRigidBody()->AddForce(Vec(0.f, -100.f));
	}
	if (IsPressed(KEY_TYPE::DOWN))
	{
		//vPos.y += m_fSpeed * DT;
		GetRigidBody()->AddForce(Vec(0.f, 100.f));
	}
	if (IsPressed(KEY_TYPE::LEFT))
	{
		//vPos.x -= m_fSpeed * DT;
		GetRigidBody()->AddForce(Vec(-100.f, 0.f));
	}
	if (IsPressed(KEY_TYPE::RIGHT))
	{
		//vPos.x += m_fSpeed * DT;
		GetRigidBody()->AddForce(Vec(100.f, 0.f));
	}
	
	// IsTap���� �� ���� ��� �ΰ��� Ű�� ���ÿ� ������ ���� �������� Tap �� Ű�� �ִϸ��̼��� play �ǰ��ִ�.
	// �̸� �����ϱ� ���� �ִϸ��̼��� ���� ���¸� ������� �ִϸ��̼��� ����Ǵ� ������ �ڵ带 ¥���Ѵ�.
	if (IsTap(KEY_TYPE::UP))
	{
		GetAnimator()->Play(L"Walk_Up", true);
	}
	if (IsTap(KEY_TYPE::DOWN))
	{
		GetAnimator()->Play(L"Walk_Down", true);
	}
	if (IsTap(KEY_TYPE::LEFT))
	{
		GetAnimator()->Play(L"Walk_Left", true);
	}
	if (IsTap(KEY_TYPE::RIGHT))
	{
		GetAnimator()->Play(L"Walk_Right", true);
	}


	if (IsPressed(KEY_TYPE::SPACE))
	{
		if (m_AccTime >= 0.2f)
		{
			/*CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CMissile* pMissile = new CMissile;

			pMissile->SetPos(GetPos());
			pMissile->SetScale(Vec(20.f, 20.f));

			pCurScene->AddObject( pMissile, LAYER_TYPE::PLAYER_PROJECTILE);

			m_AccTime = 0.f;*/
			// ������ player.cpp ���� eventmgr�� ����ϴ� ������ ����

			//CMissile* pMissile = new CMissile;
			//pMissile->SetPos(GetPos() + Vec(0.f, -50.f));// CPlayer ��ü�� ��ġ�� �������� ����

			//tEventInfo info = {};
			//info.eType = EVENT_TYPE::CREATE_OBJECT;
			//info.first = (DWORD_PTR)pMissile;
			//info.second = (DWORD_PTR)LAYER_TYPE::PLAYER_PROJECTILE;
			//// �̺�Ʈ �߰�

			//CEventMgr::GetInst()->AddEvent(info);
			// func.h ����  Instantiate()�� ��ü �߰�
			// �ٸ� ������ ���� �߰��� �� �ֵ��� ��ü�� �ּҰ��� ��ȯ�� �ش�.
			//CMissile* pMissile = Instantiate<CMissile>(GetPos() + Vec(0.f, -50.f), LAYER_TYPE::PLAYER_PROJECTILE);
			CMissile* pMissile = Instantiate<CGuidedMissile>(GetPos() + Vec(0.f, -50.f), LAYER_TYPE::PLAYER_PROJECTILE);
			//pMissile->SetDir(PI / 4.f);
			pMissile->SetDir(Vec(0.f, -1.f));

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

//void CPlayer::ObjRender(HDC _dc) // ���⿡�� ������ dc �� SecondDC �̴�.
//{
//	CImage* pImage = CResMgr::GetInst()->FindImg(L"PlayerImage");
//
//	if (nullptr == pImage)
//	{
//		return;
//	}
//
//	//Vec vPos = GetPos();
// 
//	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());
//
//	//BitBlt(_dc, (int)vPos.x - 61, (int)vPos.y - 62, 123, 124, pImage->GetImageDC(), 0, 0, SRCCOPY);
//	TransparentBlt(_dc, (int)vPos.x - pImage->GetWidth() / 2, (int)vPos.y - pImage->GetHeight() / 2
//		, pImage->GetWidth(), pImage->GetHeight()
//		, pImage->GetImageDC(), 0, 0, pImage->GetWidth(), pImage->GetHeight(), RGB(255, 0, 255));
//
//	// �ڽ��� ������Ʈ���� ȭ�鿡 �׷����� �� ������ �θ� ���� ������ ȣ�����ش�.
//	CObject::ObjRender(_dc);
//
//}

void CPlayer::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	_pOtherCollider->GetOwnerObject();
}

#include "stdafx.h"
#include "CScene_Logo.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"
#include "CForce.h"


CScene_Logo::CScene_Logo()
{
}

CScene_Logo::~CScene_Logo()
{
}


void CScene_Logo::SceneInit()
{
	// player ����
	CObject* Player1 = new CPlayer;
	Player1->SetPos(Vec(500.f, 500.f));
	Player1->SetScale(Vec(50.f, 50.f));
	AddObject(Player1, LAYER_TYPE::PLAYER);

	//  Monster ����
	CMonster* Monster1 = new CMonster;
	Monster1->SetPos(Vec((CEngine::GetInst()->GetResolution().x) / 2.f, 200.f));
	AddObject(Monster1, LAYER_TYPE::MONSTER);

	// cameraEffect
	//CCameraMgr::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);
	CCameraMgr::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 1.f);
	

	// �浹 üũ (�� Scene ���� üũ�� �浹�� ����)
	CCollisionMgr::GetInst()->Clear();

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::MONSTER);
}

void CScene_Logo::SceneTick()
{
	CScene::SceneTick();
	// ���콺 Ŭ���� ��ġ�� Force ����
	if (IsTap(KEY_TYPE::LBTN))
	{
		Vec vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec vObjectPos = CCameraMgr::GetInst()->GetRealPos(vMousePos);

		CForce* pForce = Instantiate<CForce>(vObjectPos, LAYER_TYPE::FORCE);
		pForce->SetForceInfo(500.f, 400.f, 1.f);
	}
}

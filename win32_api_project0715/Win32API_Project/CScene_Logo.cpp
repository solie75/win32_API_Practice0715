#include "stdafx.h"
#include "CScene_Logo.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"

void CScene_Logo::SceneInit()
{
	// player 생성
	CObject* Player1 = new CPlayer;
	Player1->SetPos(Vec(500.f, 500.f));
	Player1->SetScale(Vec(50.f, 50.f));
	AddObject(Player1, LAYER_TYPE::PLAYER);

	//  Monster 생성
	CMonster* Monster1 = new CMonster;
	Monster1->SetPos(Vec((CEngine::GetInst()->GetResolution().x) / 2.f, 200.f));
	AddObject(Monster1, LAYER_TYPE::MONSTER);

	// cameraEffect
	CCameraMgr::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);
	CCameraMgr::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 1.f);
	

	// 충돌 체크 (각 Scene 에서 체크할 충돌을 정의)
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::MONSTER);
}

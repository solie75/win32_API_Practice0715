#include "stdafx.h"
#include "CScene_Logo.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CEngine.h"

void CScene_Logo::SceneInit()
{
	CObject* Player1 = new CPlayer;

	Player1->SetPos(Vec(500.f, 500.f));
	Player1->SetScale(Vec(50.f, 50.f));
	
	AddObject(Player1, LAYER_TYPE::PLAYER);

	CMonster* Monster1 = new CMonster;
	Monster1->SetPos(Vec((CEngine::GetInst()->GetResolution().x) / 2.f, 200.f));
	AddObject(Monster1, LAYER_TYPE::MONSTER);
}

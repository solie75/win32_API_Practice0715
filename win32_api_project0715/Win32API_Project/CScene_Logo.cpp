#include "stdafx.h"
#include "CScene_Logo.h"
#include "CPlayer.h"

void CScene_Logo::SceneInit()
{
	CObject* Player1 = new CPlayer;

	Player1->SetPos(Vec(500.f, 500.f));
	Player1->SetScale(Vec(50.f, 50.f));
	
	AddObject(Player1);
}

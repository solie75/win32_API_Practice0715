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
	
	// IsTap으로 해 놓는 경우 두개의 키를 동시에 누르고 떼면 마지막에 Tap 된 키의 애니메이션이 play 되고있다.
	// 이를 방지하기 위해 애니메이션은 현재 상태를 기반으로 애니메이션이 실행되는 쪽으로 코드를 짜야한다.
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
			// 기존의 player.cpp 에서 eventmgr를 사용하는 것으로 변경

			//CMissile* pMissile = new CMissile;
			//pMissile->SetPos(GetPos() + Vec(0.f, -50.f));// CPlayer 객체의 위치를 기준으로 더함

			//tEventInfo info = {};
			//info.eType = EVENT_TYPE::CREATE_OBJECT;
			//info.first = (DWORD_PTR)pMissile;
			//info.second = (DWORD_PTR)LAYER_TYPE::PLAYER_PROJECTILE;
			//// 이벤트 추가

			//CEventMgr::GetInst()->AddEvent(info);
			// func.h 에서  Instantiate()로 객체 추가
			// 다른 설정을 또한 추가할 수 있도록 객체의 주소값을 반환해 준다.
			//CMissile* pMissile = Instantiate<CMissile>(GetPos() + Vec(0.f, -50.f), LAYER_TYPE::PLAYER_PROJECTILE);
			CMissile* pMissile = Instantiate<CGuidedMissile>(GetPos() + Vec(0.f, -50.f), LAYER_TYPE::PLAYER_PROJECTILE);
			//pMissile->SetDir(PI / 4.f);
			pMissile->SetDir(Vec(0.f, -1.f));

			m_AccTime = 0.f;

		}
	}

	SetPos(vPos);

	// Tick()의 호출 과정
	// CEngine의 EngineTick()
	// -> CSceneMgrTick()
	// -> ( purScene -> SceneTick() )
	// -> ( vecObject[i] -> ObjTick() )
	// -> ( arrComponent[i] -> ComponentTick() )

	// 현재의 CPlayer::ObjTick()은 CompoenentTick()을 실행 할 수 없기 때문에
	// 객체가 CompoenetTick()을 실행하기 위해서는 부모 클라스인 CObject의 ObjTick()을 호출해 줘야 한다.
	CObject::ObjTick();
}

//void CPlayer::ObjRender(HDC _dc) // 여기에서 들어오는 dc 는 SecondDC 이다.
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
//	// 자신의 컴포넌트들이 화면에 그려질수 도 있으니 부모 쪽의 랜더를 호출해준다.
//	CObject::ObjRender(_dc);
//
//}

void CPlayer::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	_pOtherCollider->GetOwnerObject();
}

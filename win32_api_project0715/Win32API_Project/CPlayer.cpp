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
			// 기존의 player.cpp 에서 eventmgr를 사용하는 것으로 변경

			CMissile* pMissile = new CMissile;
			pMissile->SetPos(GetPos() + Vec(0.f, -50.f));// CPlayer 객체의 위치를 기준으로 더함

			tEventInfo info = {};
			info.eType = EVENT_TYPE::CREATE_OBJECT;
			info.first = (DWORD_PTR)pMissile;
			info.second = (DWORD_PTR)LAYER_TYPE::PLAYER_PROJECTILE;
			// 이벤트 추가

			CEventMgr::GetInst()->AddEvent(info);

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

void CPlayer::ObjRender(HDC _dc) // 여기에서 들어오는 dc 는 SecondDC 이다.
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

	// 자신의 컴포넌트들이 화면에 그려질수 도 있으니 부모 쪽의 랜더를 호출해준다.
	CObject::ObjRender(_dc);

}

void CPlayer::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	_pOtherCollider->GetOwnerObject();
}

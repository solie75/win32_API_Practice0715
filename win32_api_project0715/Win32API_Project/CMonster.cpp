#include "stdafx.h"
#include "CMonster.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CEventMgr.h"
#include "CMissile.h"

CMonster::CMonster()
	: m_MonsterImage(nullptr)
	, m_pPlayer(nullptr)
{
	AddComponent(new CCollider);

	GetCollider()->SetColliderOffset(Vec(0.f, -35.f));
	GetCollider()->SetColliderScale(Vec(320.f, 130.f));


	m_MonsterImage = CResMgr::GetInst()->LoadImg(L"Monster", L"image\\Monster.bmp");
}

CMonster::~CMonster()
{
}

void CMonster::ObjTick()
{
	CObject::ObjTick();

	//IsValid(m_pPlayer);
}

void CMonster::ObjRender(HDC _dc)
{
	//Vec vPos = GetPos();
	Vec vPos = CCameraMgr::GetInst()->GetRenderPos(GetPos());

	/*TransparentBlt(_dc, (int)vPos.x - m_MonsterImage->GetWidth() / 2
		, (int)vPos.y - m_MonsterImage->GetHeight() / 2
		, m_MonsterImage->GetWidth(), m_MonsterImage->GetHeight()
		, m_MonsterImage->GetImageDC()
		,0, 0, m_MonsterImage->GetWidth(), m_MonsterImage->GetHeight(), RGB(255, 0, 255));*/

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.SourceConstantAlpha = 127;
	tFunc.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(_dc, (int)vPos.x - m_MonsterImage->GetWidth() / 2
		, (int)vPos.y - m_MonsterImage->GetHeight() / 2
		, m_MonsterImage->GetWidth(), m_MonsterImage->GetHeight()
		, m_MonsterImage->GetImageDC(), 0, 0, m_MonsterImage->GetWidth()
		, m_MonsterImage->GetHeight(), tFunc);

	CObject::ObjRender(_dc);
}

void CMonster::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	// 다운캐스팅을 했는데 충돌체의 오브젝트가 미사일 포인터까지 다운캐스팅이 가능하다는 것은 진짜 정체가 미사일이라는 소리
	// 여기에서 다운캐스팅을 사용하는 이유는?

	
	if (dynamic_cast<CMissile*>(_pOhterCollider->GetOwnerObject()))
	{
		tEventInfo info = {};
		info.eType = EVENT_TYPE::DELETE_OBJECT;
		info.first = (DWORD_PTR)this;
		CEventMgr::GetInst()->AddEvent(info);
	}
}

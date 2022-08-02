#include "stdafx.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CScene.h"
#include "CSceneMgr.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::EventMgrTick()
{
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		tEventInfo& evt = m_vecEvent[i];

		switch (evt.eType)
		{
			case EVENT_TYPE::CREATE_OBJECT:
			{
				CObject* pNewObject = (CObject*)evt.first;
				LAYER_TYPE eLayer = (LAYER_TYPE)evt.second;
				// 이와 같이 switch 의 case 구문에서 지역변수를 선언할 때에는 반드시 중괄호로 case 를 묶어 주어야 한다.

				CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
				pCurScene->AddObject(pNewObject, eLayer);
			}
			case EVENT_TYPE::DELETE_OBJECT:
			{
				CObject * pDeadObj = (CObject*)evt.first;
				pDeadObj->SetDead(); // 현재의 프레임에서 바로 죽이는(사라지게 하는) 것이 아니라 죽은 상태만 true 로 바꾸고 다음 프레임에 적용되게 한다.
			}
		}
	}

	m_vecEvent.clear();
}

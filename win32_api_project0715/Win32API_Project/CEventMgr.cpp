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
	// Dead Object 를 실제로 삭제한다.
	for (size_t i = 0; i < m_vecDeadObject.size(); ++i)
	{
		SAFE_DELETE(m_vecDeadObject[i]);
	}
	m_vecDeadObject.clear();

	// 이번 프레임에 쌓인 이벤트를 처리한다.
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
				break;
			case EVENT_TYPE::DELETE_OBJECT:
			{
				CObject * pDeadObj = (CObject*)evt.first;
				if (!pDeadObj->IsDead()) // Delete_object 에 해당하는 object의 m_pDeadObject 가 false 인 경우
				{
					m_vecDeadObject.push_back(pDeadObj);
					pDeadObj->SetDead(); // 현재의 프레임에서 바로 죽이는(사라지게 하는) 것이 아니라 죽은 상태만 true 로 바꾸고 다음 프레임에 적용되게 한다.
				}
			}
				break;
			case EVENT_TYPE::SCENE_CHANGE:
			{
				break;
			}
		}
	}

	m_vecEvent.clear();
}

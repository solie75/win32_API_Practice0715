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
				// �̿� ���� switch �� case �������� ���������� ������ ������ �ݵ�� �߰�ȣ�� case �� ���� �־�� �Ѵ�.

				CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
				pCurScene->AddObject(pNewObject, eLayer);
			}
			case EVENT_TYPE::DELETE_OBJECT:
			{
				CObject * pDeadObj = (CObject*)evt.first;
				pDeadObj->SetDead(); // ������ �����ӿ��� �ٷ� ���̴�(������� �ϴ�) ���� �ƴ϶� ���� ���¸� true �� �ٲٰ� ���� �����ӿ� ����ǰ� �Ѵ�.
			}
		}
	}

	m_vecEvent.clear();
}

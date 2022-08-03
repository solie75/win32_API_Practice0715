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
	// Dead Object �� ������ �����Ѵ�.
	for (size_t i = 0; i < m_vecDeadObject.size(); ++i)
	{
		SAFE_DELETE(m_vecDeadObject[i]);
	}
	m_vecDeadObject.clear();

	// �̹� �����ӿ� ���� �̺�Ʈ�� ó���Ѵ�.
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
				break;
			case EVENT_TYPE::DELETE_OBJECT:
			{
				CObject * pDeadObj = (CObject*)evt.first;
				if (!pDeadObj->IsDead()) // Delete_object �� �ش��ϴ� object�� m_pDeadObject �� false �� ���
				{
					m_vecDeadObject.push_back(pDeadObj);
					pDeadObj->SetDead(); // ������ �����ӿ��� �ٷ� ���̴�(������� �ϴ�) ���� �ƴ϶� ���� ���¸� true �� �ٲٰ� ���� �����ӿ� ����ǰ� �Ѵ�.
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

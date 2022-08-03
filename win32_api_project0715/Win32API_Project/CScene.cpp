#include "stdafx.h"
#include "CScene.h"
#include "CObject.h"


void CScene::SceneTick()
{
	for (size_t i = 0; i < (UINT)LAYER_TYPE::END ; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->ObjTick();
		}
	}

	
}


//void CScene::SceneTick()
//{
//	for (size_t i = 0; i < m_vecObject.size(); ++i)
//	{
//		m_vecObject[i]->ObjTick();
//	}
//}

void CScene::SceneRender(HDC _dc)
{
	/*for (size_t i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->ObjRender(_dc);
		}
	}*/

	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrLayer[i].begin(); // [i]�� �ش��ϴ� ���̾��� ù��° ������Ʈ
		for (; iter != m_arrLayer[i].end();) // ��� ������Ʈ�� ���Ͽ�
		{
			if ((*iter)->IsDead())
			{
				// ���� ������ ��ü�� ���� �����ϴ� �ڵ�
				iter = m_arrLayer[i].erase(iter); // vector �� erase �� ���� ��� ���� ��Ҹ� ��ȯ�Ѵ�.
			}
			else
			{
				(*iter)->ObjRender(_dc);
				++iter;
			}
		}
	}
}

//void CScene::SceneRender(HDC _dc)
//{
//	for (size_t i = 0; i < m_vecObject.size(); ++i)
//	{
//		m_vecObject[i]->ObjRender(_dc);
//	}
//}

CScene::CScene()
{
}

CScene::~CScene()
{
	for (size_t i = 0; i < (UINT)LAYER_TYPE::END ; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			SAFE_DELETE(m_arrLayer[i][j]);
		}
	}
}

//CScene::~CScene()
//{
//	for (size_t i = 0; i < m_vecObject.size(); ++i)
//	{
//		delete m_vecObject[i];
//	}
//}

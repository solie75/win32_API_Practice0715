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
		vector<CObject*>::iterator iter = m_arrLayer[i].begin(); // [i]에 해당하는 레이어의 첫번째 오브젝트
		for (; iter != m_arrLayer[i].end();) // 모든 오브젝트에 대하여
		{
			if ((*iter)->IsDead())
			{
				// 죽은 상태의 객체를 실제 삭제하는 코드
				iter = m_arrLayer[i].erase(iter); // vector 의 erase 는 지운 요소 다음 요소를 반환한다.
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

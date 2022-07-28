#include "stdafx.h"
#include "CCollisionMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::CollisionMgrTick()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		// m_matrix은 2개씩 동일한 경우이기 때문에 iCol의 시작점을 iRow 로 지정함으로써 총 살펴보아야 할 경우를 반으로 줄인다.
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (m_matrix[iRow] & (1 << iCol))
			{
				CollisionBtwLayer(pCurScene, (LAYER_TYPE)iRow, (LAYER_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(CScene* _pCurScene, LAYER_TYPE _layer1, LAYER_TYPE _layer2)
{
	const vector<CObject*>& vecObj1 = _pCurScene->GetObjects(_layer1);
	const vector<CObject*>& vecObj2 = _pCurScene->GetObjects(_layer2);

	for (size_t i = 0; i < vecObj1.size(); ++i)
	{
		// vecObj1에 충돌체가 없는 경우
		if (nullptr == vecObj1[i]->GetCollider())
		{
			continue;
		}
		for (size_t j = 0; j < vecObj2.size(); ++j)
		{
			// 두 객체가 동일하거나 vecObj2에 충돌체가 없는경우
			if (vecObj1[i] == vecObj2[j] || nullptr == vecObj2[j]->GetCollider()) // 자기 자신과 충돌하는 것으로 계산되는 경우
			{
				continue;
			}

			// 두 객체가 상이하며 각각 모두 충돌체가 있는경우
			// 두 충돌체의 ID 확인
			COLLIDER_ID id;
			id.FIRST_ID = vecObj1[i]->GetCollider()->GetID();
			id.SECOND_ID = vecObj2[j]->GetCollider()->GetID();
			// COLLIDER_ID는 union 으로 하나의 연결된 메모리 집단으로 이루어져있다. 
			// FIRST_ID 는 8바이트 인 ID 의 앞의  4바이트를 , SECOND_ID는 뒤의 4바이트를 구성하고 있디.
			// 따라서 이때 ID는 메모리 적으로 보았을 때 프로그램 내에 유일한 키값이 된다.
			id.ID;

			// 이전 충돌 정보를 검색한다.
			// map 의 bool 은 충돌의 여부 를 의미한다.
			map<LONGLONG,bool>::iterator CollisionInfoIter = m_mapColInfo.find(id.ID);
			// 충돌 정보가 아예 없는 경우 만들어 준다.
			if (CollisionInfoIter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(id.ID, false));
				// 추가 해준뒤 다시 검색하여 CollisionInfoIter에 담기게 한다.
				CollisionInfoIter = m_mapColInfo.find(id.ID);
			}

			if (IsCollision(vecObj1[i]->GetCollider(), vecObj2[j]->GetCollider()))
			{
				// 현재 프레임에 충돌이 시작되는 경우
				if (false == CollisionInfoIter->second)
				{
					vecObj1[i]->GetCollider()->CollisionBeginOverlap(vecObj2[j]->GetCollider());
					vecObj2[j]->GetCollider()->CollisionBeginOverlap(vecObj1[i]->GetCollider());
					CollisionInfoIter->second = true;
				}
				else
				{
					// 전에도 충돌하고 현재에도 충돌하고 있는 경우
					vecObj1[i]->GetCollider()->CollisionOverlap(vecObj2[j]->GetCollider());
					vecObj2[j]->GetCollider()->CollisionOverlap(vecObj1[i]->GetCollider());
				}
			}
			else 
			{
				// 충돌을 막 벗어아는 지섬
				if (CollisionInfoIter->second)
				{
					vecObj1[i]->GetCollider()->CollisionEndOverlap(vecObj2[j]->GetCollider());
					vecObj2[j]->GetCollider()->CollisionEndOverlap(vecObj1[i]->GetCollider());
					CollisionInfoIter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _collider1, CCollider* _collider2)
{
	Vec _collider1Pos = _collider1->GetColliderFinalPos();
	Vec _collider1Scale = _collider1->GetColliderScale();

	Vec _collider2Pos = _collider2->GetColliderFinalPos();
	Vec _collider2Scale = _collider2->GetColliderScale();

	// 두 충돌체의 중점 간의 거리과, 각 충돌체의 가로 세로 두 변의 절반끼리의 합을 비교하여
	// 각축(x,y) 별로 겹치는 부분이 동시에 존재하는지 체크한다.
	if (fabs(_collider1Pos.x - _collider2Pos.x) < (_collider1Scale.x / 2.f + _collider2Scale.x / 2.f)
		&& fabs(_collider1Pos.y - _collider2Pos.y) < (_collider1Scale.y / 2.f + _collider2Scale.y / 2.f))
	{
		return true;
	}
	
	return false;
}

void CCollisionMgr::CollisionLayerCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	// 더 작은 숫자를 행( 배열의 인덱스)으로 , 더 큰 숫자를 열(비트 위치) 로
	UINT iRow = 0;
	UINT iCol = 0;

	// 매트릭스의 반만 사용하기 위해 iRow 
	if ((UINT)_Layer1 < UINT(_Layer2))
	{
		iRow = (UINT)_Layer1;
		iCol = (UINT)_Layer2;
	}
	else
	{
		iRow = (UINT)_Layer2;
		iCol = (UINT)_Layer1;
	}

	// 충돌이 일어난 두 레이어중 LAYER_TYPE 이 낮은 레이어의 UINT 값이 iRow 큰 값이 iCol이라고 할때.
	// m_matrix[iRow] 와 (1 << iCol 을 통한 낮은 UINT 값의 레이어 비트 부분)을 비트연산 합으로 체크한다.
	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionLayerRelease(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	UINT iRow = 0;
	UINT iCol = 0;

	if ((UINT)_Layer1 < UINT(_Layer2))
	{
		iRow = (UINT)_Layer1;
		iCol = (UINT)_Layer2;
	}
	else
	{
		iRow = (UINT)_Layer2;
		iCol = (UINT)_Layer1;
	}

	m_matrix[iRow] &= ~(1 << iCol);
}


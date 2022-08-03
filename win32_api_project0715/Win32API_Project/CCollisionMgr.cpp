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
		// m_matrix�� 2���� ������ ����̱� ������ iCol�� �������� iRow �� ���������ν� �� ���캸�ƾ� �� ��츦 ������ ���δ�.
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
		// vecObj1�� �浹ü�� ���� ���
		if (nullptr == vecObj1[i]->GetCollider())
		{
			continue;
		}

		size_t j = 0;
		if (_layer1 == _layer2)
		{
			j = i + 1; // ������ ���͸� ������ �ʱ� ���ؼ�.
		}

		for (; j < vecObj2.size(); ++j)
		{
			//vecObj2�� �浹ü�� ���°��
			if ( nullptr == vecObj2[j]->GetCollider())
			{
				continue;
			}

			// �� ��ü�� �浹ü�� �ִ� ���
			CollisionBtwCollider(vecObj1[i]->GetCollider(), vecObj2[j]->GetCollider());
			
		}
	}
}

void CCollisionMgr::CollisionBtwCollider(CCollider* _pFirst, CCollider* _pSecond)
{
	// �� ��ü�� �����ϸ� ���� ��� �浹ü�� �ִ°��
			// �� �浹ü�� ID Ȯ��
	COLLIDER_ID id;
	id.FIRST_ID = _pFirst->GetID();
	id.SECOND_ID = _pSecond->GetID();
	// COLLIDER_ID�� union ���� �ϳ��� ����� �޸� �������� �̷�����ִ�. 
	// FIRST_ID �� 8����Ʈ �� ID �� ����  4����Ʈ�� , SECOND_ID�� ���� 4����Ʈ�� �����ϰ� �ֵ�.
	// ���� �̶� ID�� �޸� ������ ������ �� ���α׷� ���� ������ Ű���� �ȴ�.

	// ���� �浹 ������ �˻��Ѵ�.
	// map �� bool �� �浹�� ���� �� �ǹ��Ѵ�.
	map<LONGLONG, bool>::iterator CollisionInfoIter = m_mapColInfo.find(id.ID);
	// �浹 ������ �ƿ� ���� ��� ����� �ش�.
	if (CollisionInfoIter == m_mapColInfo.end())
	{
		m_mapColInfo.insert(make_pair(id.ID, false));
		// �߰� ���ص� �ٽ� �˻��Ͽ� CollisionInfoIter�� ���� �Ѵ�.
		CollisionInfoIter = m_mapColInfo.find(id.ID);
	}

	// �� �浹ü �� �ϳ� �̻��� Dead �����ΰ�
	bool IsDead = _pFirst->GetOwnerObject()->IsDead() || _pSecond->GetOwnerObject()->IsDead(); // �� �� �ϳ��� dead  ���¿���  true

	// ���� �浹������ �˻��Ѵ�
	if (IsCollision(_pFirst, _pSecond))
	{
		// ���� �����ӿ� �浹�� ���۵Ǵ� ���
		if (false == CollisionInfoIter->second)
		{
			// ���� ������ �ƴ� ��쿡�� beginOverlap �� ����
			if (!IsDead)
			{
				_pFirst->CollisionBeginOverlap(_pSecond);
				_pSecond->CollisionBeginOverlap(_pFirst);
				CollisionInfoIter->second = true;
			}
		}
		// �� �����ӿ��� �浹���̾��� ���
		else
		{
			// ���� ������ ���, �浹�� ���� ����
			if (IsDead)
			{
				_pFirst->CollisionEndOverlap(_pFirst);
				_pSecond->CollisionEndOverlap(_pSecond);
				CollisionInfoIter->second = false;
			}
			// ������ �浹�ϰ� ���翡�� �浹�ϰ� �ִ� ���
			_pFirst->CollisionOverlap(_pSecond);
			_pSecond->CollisionOverlap(_pFirst);
		}
	}
	// �浹���� ���� ���
	else
	{
		// �浹�� �� ����� ����
		if (CollisionInfoIter->second)
		{
			_pFirst->CollisionEndOverlap(_pSecond);
			_pSecond->CollisionEndOverlap(_pFirst);
			CollisionInfoIter->second = false;
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _collider1, CCollider* _collider2)
{
	Vec _collider1Pos = _collider1->GetColliderFinalPos();
	Vec _collider1Scale = _collider1->GetColliderScale();

	Vec _collider2Pos = _collider2->GetColliderFinalPos();
	Vec _collider2Scale = _collider2->GetColliderScale();

	// �� �浹ü�� ���� ���� �Ÿ���, �� �浹ü�� ���� ���� �� ���� ���ݳ����� ���� ���Ͽ�
	// ����(x,y) ���� ��ġ�� �κ��� ���ÿ� �����ϴ��� üũ�Ѵ�.
	if (fabs(_collider1Pos.x - _collider2Pos.x) < (_collider1Scale.x / 2.f + _collider2Scale.x / 2.f)
		&& fabs(_collider1Pos.y - _collider2Pos.y) < (_collider1Scale.y / 2.f + _collider2Scale.y / 2.f))
	{
		return true;
	}
	
	return false;
}

void CCollisionMgr::CollisionLayerCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	// �� ���� ���ڸ� ��( �迭�� �ε���)���� , �� ū ���ڸ� ��(��Ʈ ��ġ) ��
	UINT iRow = 0;
	UINT iCol = 0;

	// ��Ʈ������ �ݸ� ����ϱ� ���� iRow 
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

	// �浹�� �Ͼ �� ���̾��� LAYER_TYPE �� ���� ���̾��� UINT ���� iRow ū ���� iCol�̶�� �Ҷ�.
	// m_matrix[iRow] �� (1 << iCol �� ���� ���� UINT ���� ���̾� ��Ʈ �κ�)�� ��Ʈ���� ������ üũ�Ѵ�.
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
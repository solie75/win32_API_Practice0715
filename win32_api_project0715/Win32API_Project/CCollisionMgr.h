#pragma once
// 해당씬의 모든 충돌체의 정보를 취합 및 일대일 매칭하여 각 충돌체의 상태를 정한다.
class CScene;
class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	// 한번의 충돌이 어떤 충돌체 간의 충돌인지 저장하기 위해서 16개의 (16비트)WORD 자료형을 가지는 배열을 선언
	// m_matrix 에서의 과정
	// m_matrix는 하나의 요소를 별개의 레이어로 취급
	// 이때 요소는 WORD 자료형으로 16비트이다.
	// 이 16비트의 각 비트는 각기 다른 레이어로 취급한다.
	// 따라서 한 레이어(m_matrix의 요소 별)가 충돌한 다른 레이어(해당 요소의 비트 별)에 대하여 체크를 비트 단위로 진행한다.
	// 예를 들어 미사일 객체가 몬스터 객체와 충돌했을 경우
	// (m_matrix[4])[5] 혹은 (m_matrix[5])[4] 에 체크를 하면 된다. 이때 하나의 충돌 결과로 두개의 체크가 이루어 지므로
	// 더 작은 숫자가 앞으로 가도록 조건문 처리해 체크가 한번만 이루어 지도록 한다.

	WORD m_matrix[MAX_LAYER];

	// 하나의 객체가 가지는 충돌 정보
	map<LONGLONG, bool> m_mapColInfo;

public:
	void CollisionMgrTick();

// CollisionMgrTick에서 호출할 함수이기 때문에 공개할 필요가 없다.
private:
	void CollisionBtwLayer(CScene* _pCurScene, LAYER_TYPE _layer1, LAYER_TYPE _layer2);
	bool IsCollision(CCollider* _collider1, CCollider* _collider2);
public:
	void Clear() { memset(m_matrix, 0, sizeof(WORD) * MAX_LAYER); }; // m_matrix 배열의 모든 비트를 0 으로 만든다.
	void CollisionLayerCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2);
	void CollisionLayerRelease(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2);
};


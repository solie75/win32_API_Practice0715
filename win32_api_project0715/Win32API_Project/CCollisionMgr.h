#pragma once
// �ش���� ��� �浹ü�� ������ ���� �� �ϴ��� ��Ī�Ͽ� �� �浹ü�� ���¸� ���Ѵ�.
class CScene;
class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	// �ѹ��� �浹�� � �浹ü ���� �浹���� �����ϱ� ���ؼ� 16���� (16��Ʈ)WORD �ڷ����� ������ �迭�� ����
	// m_matrix ������ ����
	// m_matrix�� �ϳ��� ��Ҹ� ������ ���̾�� ���
	// �̶� ��Ҵ� WORD �ڷ������� 16��Ʈ�̴�.
	// �� 16��Ʈ�� �� ��Ʈ�� ���� �ٸ� ���̾�� ����Ѵ�.
	// ���� �� ���̾�(m_matrix�� ��� ��)�� �浹�� �ٸ� ���̾�(�ش� ����� ��Ʈ ��)�� ���Ͽ� üũ�� ��Ʈ ������ �����Ѵ�.
	// ���� ��� �̻��� ��ü�� ���� ��ü�� �浹���� ���
	// (m_matrix[4])[5] Ȥ�� (m_matrix[5])[4] �� üũ�� �ϸ� �ȴ�. �̶� �ϳ��� �浹 ����� �ΰ��� üũ�� �̷�� ���Ƿ�
	// �� ���� ���ڰ� ������ ������ ���ǹ� ó���� üũ�� �ѹ��� �̷�� ������ �Ѵ�.

	WORD m_matrix[MAX_LAYER];

	// �ϳ��� ��ü�� ������ �浹 ����
	map<LONGLONG, bool> m_mapColInfo;

public:
	void CollisionMgrTick();

// CollisionMgrTick���� ȣ���� �Լ��̱� ������ ������ �ʿ䰡 ����.
private:
	void CollisionBtwLayer(CScene* _pCurScene, LAYER_TYPE _layer1, LAYER_TYPE _layer2);
	void CollisionBtwCollider(CCollider* _pFirst, CCollider* _pSecond);
	bool IsCollision(CCollider* _collider1, CCollider* _collider2);
public:
	void Clear() { memset(m_matrix, 0, sizeof(WORD) * MAX_LAYER); }; // m_matrix �迭�� ��� ��Ʈ�� 0 ���� �����.
	void CollisionLayerCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2);
	void CollisionLayerRelease(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2);
};


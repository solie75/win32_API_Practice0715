#pragma
#include "CEntity.h"

class CObject;

class CScene
	: public CEntity
{
private:
	//vector<CObject*> m_vecObject;
	vector<CObject*> m_arrLayer[MAX_LAYER]; // 이중 벡터 구조 하나의 벡터의 요소가 또하나의 벡터인 구조

public:
	void AddObject(CObject* _pObject, LAYER_TYPE _eLayer) // m_arrLayer 의 어느 레이어 요소 부분에 어떠한 오브젝트를 넣을 것인지 
	{
		m_arrLayer[(UINT)_eLayer].push_back(_pObject);
	}

	// m_arrLayer 의 한 요소를 반환, 복사 비용을 만들지 않고 레퍼런스로 반환하며 동시에 원본이 손상 되지 않도록 const 화
	const vector<CObject*>& GetObjects(LAYER_TYPE _eType) { return m_arrLayer[(UINT)_eType]; };
public:
	virtual void SceneInit() = 0;
	virtual void SceneTick();
	virtual void SceneRender(HDC _dc);

public:
	CScene();
	~CScene();
};
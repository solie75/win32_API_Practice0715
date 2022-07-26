#pragma

class CObject;

class CScene
{
private:
	//vector<CObject*> m_vecObject;
	vector<CObject*> m_arrLayer[MAX_LAYER]; // 이중 벡터 구조 하나의 벡터의 요소가 또하나의 벡터인 구조

public:
	void AddObject(CObject* _pObject, LAYER_TYPE _eLayer) // m_arrLayer 의 어느 레이어 요소 부분에 어떠한 오브젝트를 넣을 것인지 
	{
		m_arrLayer[(UINT)_eLayer].push_back(_pObject);
	}
public:
	virtual void SceneInit() = 0;
	virtual void SceneTick();
	virtual void SceneRender(HDC _dc);

public:
	CScene();
	~CScene();
};
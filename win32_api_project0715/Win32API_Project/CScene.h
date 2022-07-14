#pragma

class CObject;

class CScene
{
private:
	vector<CObject*> m_vecObject;

public:
	void AddObject(CObject* _pObject)
	{
		m_vecObject.push_back(_pObject);
	}
public:
	virtual void SceneInit() = 0;
	virtual void SceneTick();
	virtual void SceneRender(HDC _dc);

public:
	CScene();
	~CScene();
};
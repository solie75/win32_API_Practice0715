#pragma once
class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	CScene* m_arrScene[SCENE_TYPE::END];
	CScene* m_pCurScene;

public:
	void CSceneMgrInit();

	void CSceneMgrTick();
	void CSceneMgrRender(HDC _dc);
};


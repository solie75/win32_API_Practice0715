#include "stdafx.h"
#include "CResMgr.h"

// CResMgr.h 에서 CResource 클래스를 전방선언함 그래놓고 실제로  CResMgr.cpp 에서 사용되니까 CResource 를 include 하는데
// 굳이 CResource를 CResMgr 의 뒤에 선언하는 이유는..?
#include "CResource.h"
#include "CImage.h"
#include "CPathMgr.h"


CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	map<wstring, CImage*>::iterator iter = m_mapImage.begin();

	for (; iter != m_mapImage.end(); ++iter)
	{
		delete(iter->second);
	}
}

void CResMgr::ResMgrInit()
{
	LoadImg(L"PlayerImage", L"image\\Fighter.bmp");
}

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 1. 같은 키가 존재하는 지 확인
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		// 해당키로 이미 로딩된게 있으면 해당 리소스를 반환
		return pImage;
	}

	// 키값 매개변수 로 로딩된 이미지가 없는경우
	// content 폴더 경로 + 상대 경로 = 최종 경로
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImage = new CImage;
	if (FAILED(pImage->Load(strFilePath)))
	{
		MessageBox(nullptr, L"이미지 로딩 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);
	m_mapImage.insert(make_pair(_strKey, pImage));


	return pImage;
}


CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CImage*>::iterator iter = m_mapImage.find(_strKey);

	// 이미 동일한 기값으로 다른 리소스가 map 에 존재하는 경우
	if (iter != m_mapImage.end())
	{
		return iter->second;
	}

	return nullptr;
}
#include "stdafx.h"
#include "CResMgr.h"

// CResMgr.h ���� CResource Ŭ������ ���漱���� �׷����� ������  CResMgr.cpp ���� ���Ǵϱ� CResource �� include �ϴµ�
// ���� CResource�� CResMgr �� �ڿ� �����ϴ� ������..?
#include "CResource.h"
#include "CImage.h"
#include "CPathMgr.h"


CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	/*map<wstring, CImage*>::iterator iter = m_mapImage.begin();

	for (; iter != m_mapImage.end(); ++iter)
	{
		delete(iter->second);
	}*/

	Safe_Del_Map(m_mapImage);
}

void CResMgr::ResMgrInit()
{
	LoadImg(L"PlayerImage", L"image\\Fighter.bmp");
}

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 1. ���� Ű�� �����ϴ� �� Ȯ��
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		// �ش�Ű�� �̹� �ε��Ȱ� ������ �ش� ���ҽ��� ��ȯ
		return pImage;
	}

	// Ű�� �Ű����� �� �ε��� �̹����� ���°��
	// content ���� ��� + ��� ��� = ���� ���
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImage = new CImage;
	if (FAILED(pImage->Load(strFilePath)))
	{
		MessageBox(nullptr, L"�̹��� �ε� ����", L"����", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);
	m_mapImage.insert(make_pair(_strKey, pImage));


	return pImage;
}

CImage* CResMgr::CreateImage(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	// Ű������ Ž��(�ߺ��� Ű�� ������ �ʵ���)
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		MessageBox(nullptr, L"�ߺ� Ű �߻�", L"�̹��� ���� ����", MB_OK);
		return nullptr;
	}

	// �ش� Ű�� ������ �̹����� ���� ���
	pImage = new CImage;
	if (FAILED(pImage->Create(_iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"�̹��� ���� ����", L"����", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}


CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CImage*>::iterator iter = m_mapImage.find(_strKey);

	// �̹� ������ �Ⱚ���� �ٸ� ���ҽ��� map �� �����ϴ� ���
	if (iter != m_mapImage.end())
	{
		return iter->second;
	}

	return nullptr;
}
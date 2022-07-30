#include "stdafx.h"
#include "CImage.h"
#include "CEngine.h"

CImage::CImage()
	: m_hBit(0)
	, m_hDC(0)
	, m_iWidth(0)
	, m_iHeight(0)
{

}

CImage::~CImage()
{
	DeleteObject(m_hDC);
	DeleteObject(m_hBit);
}
int CImage::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImageW(nullptr, _strFilePath.c_str()
		, IMAGE_BITMAP
		, 0, 0 // 0, 0 �̸� ���� ���� �״��
		, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// LoadImage�Լ��� ������ ��� nullptr �� ��ȯ�Ѵ�.
	if (nullptr == m_hBit)
	{
		return E_FAIL;
	}

	// ��Ʈ���� ���� Ȯ�� �κ�
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;

	HDC hMainDC = CEngine::GetInst()->GetMainDC();

	m_hDC = CreateCompatibleDC(hMainDC);

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit); // ����(������ �Ǵ� DC, �ִ� ������Ʈ)
	DeleteObject(hPrevBit);

	return S_OK;
}

int CImage::Create(UINT _iWidth, UINT _iHeight)
{
	// ���� ���۸�
	// ������ �ػ󵵿� ������ ũ���� ��Ʈ���� ����
	// ���� ������ ��Ʈ���� ����Ű�� ���� DC ����
	// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
	HDC hMainDC = CEngine::GetInst()->GetMainDC();
	m_hBit = CreateCompatibleBitmap(hMainDC, _iWidth, _iHeight);
	m_hDC = CreateCompatibleDC(hMainDC);

	if (0 == m_hBit || 0 == m_hDC)
	{
		return E_FAIL;
	}

	// DC �� �����ϸ� ���Ƿ� 1�ȼ��� ��Ʈ���� ����Ű�� �ֱ⿡ SelectObject �� ��ȯ���� ������ �־�� �Ѵ�.
	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hDefaultBitmap);

	// ��Ʈ�� ���� Ȯ��
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;

	return S_OK;
}

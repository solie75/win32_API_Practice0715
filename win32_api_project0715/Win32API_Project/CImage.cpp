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
		, 0, 0 // 0, 0 이면 원본 사진 그대로
		, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// LoadImage함수가 실패한 경우 nullptr 을 반환한다.
	if (nullptr == m_hBit)
	{
		return E_FAIL;
	}

	// 비트맵의 정보 확인 부분
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;

	HDC hMainDC = CEngine::GetInst()->GetMainDC();

	m_hDC = CreateCompatibleDC(hMainDC);

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit); // 인자(목적이 되는 DC, 넣는 오브젝트)
	DeleteObject(hPrevBit);

	return S_OK;
}



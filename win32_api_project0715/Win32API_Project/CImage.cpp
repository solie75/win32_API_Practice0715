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

int CImage::Create(UINT _iWidth, UINT _iHeight)
{
	// 이중 버퍼링
	// 윈도우 해상도와 동일한 크기의 비트맵을 생성
	// 새로 생선한 비트맵을 가리키는 전용 DC 생성
	// 새로 생성한 비트맵과 DC를 서로 연결
	HDC hMainDC = CEngine::GetInst()->GetMainDC();
	m_hBit = CreateCompatibleBitmap(hMainDC, _iWidth, _iHeight);
	m_hDC = CreateCompatibleDC(hMainDC);

	if (0 == m_hBit || 0 == m_hDC)
	{
		return E_FAIL;
	}

	// DC 를 생성하면 임의로 1픽셀의 비트맵을 가리키고 있기에 SelectObject 의 반환값을 삭제해 주어야 한다.
	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hDefaultBitmap);

	// 비트맵 정보 확인
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;

	return S_OK;
}

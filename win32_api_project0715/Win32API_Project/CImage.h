#pragma once
#include "CResource.h"
class CImage :
    public CResource
{
private:
    HBITMAP m_hBit;
    HDC m_hDC;

    UINT m_iWidth;
    UINT m_iHeight;

public:
    virtual int Load(const wstring& _strFilePath) override;
    HDC GetImageDC() { return m_hDC; }
    UINT GetWidth() { return m_iWidth; }
    UINT GetHeight() { return m_iHeight; }
public:
    CImage();
    ~CImage();
};


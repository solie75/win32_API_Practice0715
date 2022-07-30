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

private:
    virtual int Load(const wstring& _strFilePath) override;
    virtual int Create(UINT _iWidth, UINT _iHeight);

public:
    HDC GetImageDC() { return m_hDC; }
    UINT GetWidth() 
    {
        if (nullptr != this)
        {
            return m_iWidth;
        }
        return 0;
    }
    UINT GetHeight() {
        if (nullptr != this)
        {
            return m_iHeight;
        }
        return 0;
    }

private:
    CImage();
    ~CImage();

    friend class CResMgr;
};


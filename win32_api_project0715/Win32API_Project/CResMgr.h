#pragma once

class CResource;
class CImage;

class CResMgr
{
	SINGLE(CResMgr)
private:
	// 해당 map 구조가 삭제될 때 두번 째 인자가 포인트 형식 이므로 포인트만 지워지고 포인트가 가리키는 본래의 데이터는 남아있기에 소멸자에 반복문으로 일일히 데이터를 삭제한다.
	//map<wstring, CResource*> m_mapRes; // 같은 키를 가지고 누구는 이미지를 불러오고 싶고 누구는 오디오를 불러오고 싶은 경우가 생기기에 따로 관리한다
	map<wstring, CImage*> m_mapImage;
	//map<wstring, CSound*> m_mapSound;


public:
	void ResMgrInit();
	
public:
	CImage* LoadImg(const wstring& _strKey, const wstring& _strPath);// 리소스가 워낙 많기에 구별하기 위해서 키를 가진다.
	CImage* CreateImage(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	CImage* FindImg(const wstring& _strKey);
};


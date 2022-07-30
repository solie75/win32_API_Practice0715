#pragma once

class CResource;
class CImage;

class CResMgr
{
	SINGLE(CResMgr)
private:
	// �ش� map ������ ������ �� �ι� ° ���ڰ� ����Ʈ ���� �̹Ƿ� ����Ʈ�� �������� ����Ʈ�� ����Ű�� ������ �����ʹ� �����ֱ⿡ �Ҹ��ڿ� �ݺ������� ������ �����͸� �����Ѵ�.
	//map<wstring, CResource*> m_mapRes; // ���� Ű�� ������ ������ �̹����� �ҷ����� �Ͱ� ������ ������� �ҷ����� ���� ��찡 ����⿡ ���� �����Ѵ�
	map<wstring, CImage*> m_mapImage;
	//map<wstring, CSound*> m_mapSound;


public:
	void ResMgrInit();
	
public:
	CImage* LoadImg(const wstring& _strKey, const wstring& _strPath);// ���ҽ��� ���� ���⿡ �����ϱ� ���ؼ� Ű�� ������.
	CImage* CreateImage(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	CImage* FindImg(const wstring& _strKey);
};


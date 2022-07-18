#pragma once
class CResource
{
private:
	wstring m_strKey;
	wstring m_strPath;

public:
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetPath() { return m_strPath; }

	void SetKey(const wstring& _strKey)
	{
		m_strKey = _strKey;
	}
	void SetRelativePath(const wstring& _strRelativePath)
	{
		m_strPath = _strRelativePath;
	}

public:
	virtual int Load(const wstring& _strFilePath) = 0;

public:
	CResource();
	virtual ~CResource(); // 모든 Resource 클래스의 부모 클래스가 되는 것이기 때문에 소멸자를 가상함수로 선언한다.
};


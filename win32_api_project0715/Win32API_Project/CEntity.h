#pragma once
class CEntity
{
private:
	static UINT g_GlobalID;
private:
	wstring m_strName;
	const UINT m_ID;

public:
	void SetNAme(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetID() { return m_ID; }

public:

public:
	CEntity();
	// 아이디 까지 복사되는 문제를 막기 위해서 직접 복사 생성자를 구현
	CEntity(const CEntity& _other);
	virtual ~CEntity();
};


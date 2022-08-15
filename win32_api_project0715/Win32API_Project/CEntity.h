#pragma once
class CEntity
{
private:
	static UINT g_GlobalID;
private:
	wstring m_strName;
	const UINT m_ID;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetID() { return m_ID; }

public:

public:
	CEntity();
	// ���̵� ���� ����Ǵ� ������ ���� ���ؼ� ���� ���� �����ڸ� ����
	CEntity(const CEntity& _other);
	virtual ~CEntity();
};


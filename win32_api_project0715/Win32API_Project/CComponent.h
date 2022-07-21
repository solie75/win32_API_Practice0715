#pragma once
class CComponent
{
private:

	// AddComponent 에 의해서 컴포넌트가 생성될 때
	// 각 컴포넌트는 자신이 어떠한 컴포넌트 인지 인지라는 과정을 위해서 컴포넌트 타입을 상수로 지정한다.
	// 이때 상수로 지정한 맴버 상수는 초기화 를 하면 더이상 변하지 않으며 생성자의 초기화로만 (대입x) 값을 넣는 것이 가능하다.
	const COMPONENT_TYPE m_eType;

public:
	virtual void ComponentTick() = 0;

	// 충돌영역과 같이 보여야 할 경우가 있으므로.
	virtual void ComponentRender(HDC _dc);

	COMPONENT_TYPE GetComponentType() { return m_eType; };

public:
	// 생성자는 사용자가 설정할 경우 기본생성자가 생성되지 않는다.
	// new CComponent 로 컴포넌트를 생성할 때 그 컴포넌트의 종류를 인자로 주어서 상수 변수에 초기화 하게 함으로서
	// 각 컴포넌트가 개별 종류가 되게 한다.
	CComponent(COMPONENT_TYPE _eType)
		: m_eType(_eType)
	{};
	~CComponent(){};
};


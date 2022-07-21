#include "stdafx.h"
#include "CCollider.h"

void CCollider::ComponentTick()
{
}

void CCollider::ComponentRender(HDC _dc)
{
}

CCollider::CCollider()
// CCollider 의 생성자는 부모 클라스인 CComponent의 생성자를 호출한다.
// 이때 CComponent는 기본생성자 없이 인자를 가지는 생성자 만이 존재 하므로 그 인자를 가지는 생성자를 상속받는다고 표시한다.
// 및의 코드는 CCollider 클래스의 생성자가 부모 크래스인 CComponent 클래스의 생성자를 상속 받았다는 것이다.
	: CComponent(COMPONENT_TYPE::COLLIDER)
{
}

CCollider::~CCollider()
{
}

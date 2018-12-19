#include "stdafx.h"
#include "UserComponent_Base.h"

JEONG_USING

JEONG::UserComponent_Base::UserComponent_Base()
{
	m_isUserComponent = true;
}

JEONG::UserComponent_Base::UserComponent_Base(const UserComponent_Base & userCom)
	:Component_Base(userCom)
{
}

JEONG::UserComponent_Base::~UserComponent_Base()
{
}

bool JEONG::UserComponent_Base::Init()
{
	return false;
}

int JEONG::UserComponent_Base::Input(float DeltaTime)
{
	return 0;
}

int JEONG::UserComponent_Base::Update(float DeltaTime)
{
	return 0;
}

int JEONG::UserComponent_Base::LateUpdate(float DeltaTime)
{
	return 0;
}

void JEONG::UserComponent_Base::Collision(float DeltaTime)
{
}

void JEONG::UserComponent_Base::CollisionLateUpdate(float DeltaTime)
{
}

void JEONG::UserComponent_Base::Render(float DeltaTime)
{
}

JEONG::UserComponent_Base * JEONG::UserComponent_Base::Clone()
{
	return new UserComponent_Base(*this);
}

#include "stdafx.h"
#include "UserComponent_Base.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

UserComponent_Base::UserComponent_Base()
{
	m_isUserComponent = true;
	m_State = 0;
	m_PrevState = 0;
}

UserComponent_Base::UserComponent_Base(const UserComponent_Base & userCom)
	:Component_Base(userCom)
{
}

UserComponent_Base::~UserComponent_Base()
{
	int a = 0;
}

bool UserComponent_Base::Init()
{
	return true;
}

int UserComponent_Base::Input(float DeltaTime)
{
	return 0;
}

int UserComponent_Base::Update(float DeltaTime)
{
	return 0;
}

int UserComponent_Base::LateUpdate(float DeltaTime)
{
	return 0;
}

void UserComponent_Base::Collision(float DeltaTime)
{
}

void UserComponent_Base::CollisionLateUpdate(float DeltaTime)
{
}

void UserComponent_Base::Render(float DeltaTime)
{
}

UserComponent_Base * UserComponent_Base::Clone()
{
	return new UserComponent_Base(*this);
}

void UserComponent_Base::ChangeState(int State, string * AnimationName, Animation2D_Com * animation)
{
	m_PrevState = m_State;
	m_State = State;

	animation->ChangeClip(AnimationName[m_State]);
}

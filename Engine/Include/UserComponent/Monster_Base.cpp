#include "stdafx.h"
#include "Monster_Base.h"

JEONG_USING

Monster_Base::Monster_Base()
{
}

Monster_Base::Monster_Base(const Monster_Base & CopyData)
	:UserComponent_Base(CopyData)
{
}

Monster_Base::~Monster_Base()
{
}

bool Monster_Base::Init()
{
	return true;
}

int Monster_Base::Input(float DeltaTime)
{
	return 0;
}

int Monster_Base::Update(float DeltaTime)
{
	return 0;
}

int Monster_Base::LateUpdate(float DeltaTime)
{
	return 0;
}

void Monster_Base::Collision(float DeltaTime)
{
}

void Monster_Base::CollisionLateUpdate(float DeltaTime)
{
}

void Monster_Base::Render(float DeltaTime)
{
}

Monster_Base * Monster_Base::Clone()
{
	return new Monster_Base(*this);
}

void Monster_Base::AfterClone()
{
}

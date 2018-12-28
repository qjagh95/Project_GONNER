#include "stdafx.h"
#include "FollowM_Com.h"

JEONG_USING

FollowM_Com::FollowM_Com()
{
}

FollowM_Com::FollowM_Com(const FollowM_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

FollowM_Com::~FollowM_Com()
{
}

bool FollowM_Com::Init()
{
	return true;
}

int FollowM_Com::Input(float DeltaTime)
{
	return 0;
}

int FollowM_Com::Update(float DeltaTime)
{
	return 0;
}

int FollowM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void FollowM_Com::Collision(float DeltaTime)
{
}

void FollowM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void FollowM_Com::Render(float DeltaTime)
{
}

FollowM_Com * FollowM_Com::Clone()
{
	return new FollowM_Com(*this);
}

void FollowM_Com::AfterClone()
{
}

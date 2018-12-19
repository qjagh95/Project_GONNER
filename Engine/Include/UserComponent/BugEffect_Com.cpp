#include "stdafx.h"
#include "BugEffect_Com.h"

JEONG_USING

BugEffect_Com::BugEffect_Com()
{
}

BugEffect_Com::BugEffect_Com(const BugEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BugEffect_Com::~BugEffect_Com()
{
}

bool BugEffect_Com::Init()
{
	return true;
}

int BugEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int BugEffect_Com::Update(float DeltaTime)
{
	return 0;
}

int BugEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BugEffect_Com::Collision(float DeltaTime)
{
}

void BugEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BugEffect_Com::Render(float DeltaTime)
{
}

BugEffect_Com * BugEffect_Com::Clone()
{
	return new BugEffect_Com(*this);
}

void BugEffect_Com::AfterClone()
{
}

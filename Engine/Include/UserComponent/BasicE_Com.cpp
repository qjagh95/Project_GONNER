#include "stdafx.h"
#include "BasicE_Com.h"

JEONG_USING


BasicE_Com::BasicE_Com()
{
}


BasicE_Com::BasicE_Com(const BasicE_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BasicE_Com::~BasicE_Com()
{
}

bool BasicE_Com::Init()
{
	return true;
}

int BasicE_Com::Input(float DeltaTime)
{
	return 0;
}

int BasicE_Com::Update(float DeltaTime)
{
	return 0;
}

int BasicE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BasicE_Com::Collision(float DeltaTime)
{
}

void BasicE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BasicE_Com::Render(float DeltaTime)
{
}

BasicE_Com * BasicE_Com::Clone()
{
	return new BasicE_Com(*this);
}

void BasicE_Com::AfterClone()
{
}

void BasicE_Com::SetPos(const Vector3 & Pos)
{
}

#include "stdafx.h"
#include "ReflectE_Com.h"

JEONG_USING

ReflectE_Com::ReflectE_Com()
{
}


ReflectE_Com::ReflectE_Com(const ReflectE_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

ReflectE_Com::~ReflectE_Com()
{
}

bool ReflectE_Com::Init()
{
	return true;
}

int ReflectE_Com::Input(float DeltaTime)
{
	return 0;
}

int ReflectE_Com::Update(float DeltaTime)
{
	return 0;
}

int ReflectE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ReflectE_Com::Collision(float DeltaTime)
{
}

void ReflectE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ReflectE_Com::Render(float DeltaTime)
{
}

ReflectE_Com * ReflectE_Com::Clone()
{
	return new ReflectE_Com(*this);
}

void ReflectE_Com::AfterClone()
{
}

void ReflectE_Com::SetPos(const Vector3 & Pos)
{
}

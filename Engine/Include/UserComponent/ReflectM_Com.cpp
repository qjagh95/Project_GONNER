#include "stdafx.h"
#include "ReflectM_Com.h"

JEONG_USING

ReflectM_Com::ReflectM_Com()
{
}

ReflectM_Com::ReflectM_Com(const ReflectM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

ReflectM_Com::~ReflectM_Com()
{
}

bool ReflectM_Com::Init()
{
	return true;
}

int ReflectM_Com::Input(float DeltaTime)
{
	return 0;
}

int ReflectM_Com::Update(float DeltaTime)
{
	return 0;
}

int ReflectM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ReflectM_Com::Collision(float DeltaTime)
{
}

void ReflectM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ReflectM_Com::Render(float DeltaTime)
{
}

ReflectM_Com * ReflectM_Com::Clone()
{
	return new ReflectM_Com(*this);
}

void ReflectM_Com::AfterClone()
{
}

void ReflectM_Com::BulletHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
}

#include "stdafx.h"
#include "ShotEffect_Com.h"

JEONG_USING

ShotEffect_Com::ShotEffect_Com()
{
}


ShotEffect_Com::ShotEffect_Com(const ShotEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

ShotEffect_Com::~ShotEffect_Com()
{
}

bool ShotEffect_Com::Init()
{
	return true;
}

int ShotEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int ShotEffect_Com::Update(float DeltaTime)
{
	return 0;
}

int ShotEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ShotEffect_Com::Collision(float DeltaTime)
{
}

void ShotEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ShotEffect_Com::Render(float DeltaTime)
{
}

ShotEffect_Com * ShotEffect_Com::Clone()
{
	return new ShotEffect_Com(*this);
}

void ShotEffect_Com::AfterClone()
{
}

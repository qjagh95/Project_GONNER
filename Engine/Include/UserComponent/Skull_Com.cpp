#include "stdafx.h"
#include "Skull_Com.h"

JEONG_USING

Skull_Com::Skull_Com()
{
}

Skull_Com::Skull_Com(const Skull_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Skull_Com::~Skull_Com()
{
}

bool Skull_Com::Init()
{
	return true;
}

int Skull_Com::Input(float DeltaTime)
{
	return 0;
}

int Skull_Com::Update(float DeltaTime)
{
	return 0;
}

int Skull_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Skull_Com::Collision(float DeltaTime)
{
}

void Skull_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Skull_Com::Render(float DeltaTime)
{
}

Skull_Com * Skull_Com::Clone()
{
	return new Skull_Com(*this);
}

void Skull_Com::AfterClone()
{
}

#include "stdafx.h"
#include "AirDownE_Com.h"

JEONG_USING

AirDownE_Com::AirDownE_Com()
{
}

AirDownE_Com::AirDownE_Com(const AirDownE_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

AirDownE_Com::~AirDownE_Com()
{
}

bool AirDownE_Com::Init()
{
	return true;
}

int AirDownE_Com::Input(float DeltaTime)
{
	return 0;
}

int AirDownE_Com::Update(float DeltaTime)
{
	return 0;
}

int AirDownE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void AirDownE_Com::Collision(float DeltaTime)
{
}

void AirDownE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void AirDownE_Com::Render(float DeltaTime)
{
}

AirDownE_Com * AirDownE_Com::Clone()
{
	return new AirDownE_Com(*this);
}

void AirDownE_Com::AfterClone()
{
}

void AirDownE_Com::SetPos(const Vector3 & Pos)
{
}

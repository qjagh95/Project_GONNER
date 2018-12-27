#include "stdafx.h"
#include "AirDownM_Com.h"

JEONG_USING

AirDownM_Com::AirDownM_Com()
{
	m_Type = MT_AIRDOWN;
}

AirDownM_Com::AirDownM_Com(const AirDownM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

AirDownM_Com::~AirDownM_Com()
{
}

bool AirDownM_Com::Init()
{
	return true;
}

int AirDownM_Com::Input(float DeltaTime)
{
	return 0;
}

int AirDownM_Com::Update(float DeltaTime)
{
	return 0;
}

int AirDownM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void AirDownM_Com::Collision(float DeltaTime)
{
}

void AirDownM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void AirDownM_Com::Render(float DeltaTime)
{
}

AirDownM_Com * AirDownM_Com::Clone()
{
	return new AirDownM_Com(*this);
}

void AirDownM_Com::AfterClone()
{
}

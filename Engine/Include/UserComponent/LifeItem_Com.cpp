#include "stdafx.h"
#include "LifeItem_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

LifeItem_Com::LifeItem_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

LifeItem_Com::LifeItem_Com(const LifeItem_Com & CopyData)
{
}

LifeItem_Com::~LifeItem_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool LifeItem_Com::Init()
{
	return true;
}

int LifeItem_Com::Input(float DeltaTime)
{
	return 0;
}

int LifeItem_Com::Update(float DeltaTime)
{
	return 0;
}

int LifeItem_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void LifeItem_Com::Collision(float DeltaTime)
{
}

void LifeItem_Com::CollisionLateUpdate(float DeltaTime)
{
}

void LifeItem_Com::Render(float DeltaTime)
{
}

LifeItem_Com * LifeItem_Com::Clone()
{
	return new LifeItem_Com(*this);
}

void LifeItem_Com::AfterClone()
{
}

#include "stdafx.h"
#include "LifeItemUI_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

LifeItemUI_Com::LifeItemUI_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

LifeItemUI_Com::LifeItemUI_Com(const LifeItemUI_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

LifeItemUI_Com::~LifeItemUI_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool LifeItemUI_Com::Init()
{
	return true;
}

int LifeItemUI_Com::Input(float DeltaTime)
{
	return 0;
}

int LifeItemUI_Com::Update(float DeltaTime)
{
	return 0;
}

int LifeItemUI_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void LifeItemUI_Com::Collision(float DeltaTime)
{
}

void LifeItemUI_Com::CollisionLateUpdate(float DeltaTime)
{
}

void LifeItemUI_Com::Render(float DeltaTime)
{
}

LifeItemUI_Com * LifeItemUI_Com::Clone()
{
	return new LifeItemUI_Com(*this);
}

void LifeItemUI_Com::AfterClone()
{
}

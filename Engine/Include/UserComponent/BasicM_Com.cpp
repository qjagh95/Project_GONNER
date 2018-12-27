#include "stdafx.h"
#include "BasicM_Com.h"

JEONG_USING

BasicM_Com::BasicM_Com()
{
	m_Type = MT_TRACE;
}

BasicM_Com::BasicM_Com(const BasicM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

BasicM_Com::~BasicM_Com()
{
}

bool BasicM_Com::Init()
{
	return true;
}

int BasicM_Com::Input(float DeltaTime)
{
	return 0;
}

int BasicM_Com::Update(float DeltaTime)
{
	return 0;
}

int BasicM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BasicM_Com::Collision(float DeltaTime)
{
}

void BasicM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BasicM_Com::Render(float DeltaTime)
{
}

BasicM_Com * BasicM_Com::Clone()
{
	return new BasicM_Com(*this);
}

void BasicM_Com::AfterClone()
{
}

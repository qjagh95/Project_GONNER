#include "stdafx.h"
#include "TraceM_Com.h"

JEONG_USING

TraceM_Com::TraceM_Com()
{
	m_Type = MT_TRACE;
}

TraceM_Com::TraceM_Com(const TraceM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

TraceM_Com::~TraceM_Com()
{
}

bool TraceM_Com::Init()
{
	return true;
}

int TraceM_Com::Input(float DeltaTime)
{
	return 0;
}

int TraceM_Com::Update(float DeltaTime)
{
	return 0;
}

int TraceM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void TraceM_Com::Collision(float DeltaTime)
{
}

void TraceM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void TraceM_Com::Render(float DeltaTime)
{
}

TraceM_Com * TraceM_Com::Clone()
{
	return new TraceM_Com(*this);
}

void TraceM_Com::AfterClone()
{
}

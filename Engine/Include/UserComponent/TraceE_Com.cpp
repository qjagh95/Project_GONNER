#include "stdafx.h"
#include "TraceE_Com.h"

JEONG_USING

TraceE_Com::TraceE_Com()
{
}


TraceE_Com::TraceE_Com(const TraceE_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

TraceE_Com::~TraceE_Com()
{
}

bool TraceE_Com::Init()
{
	return true;
}

int TraceE_Com::Input(float DeltaTime)
{
	return 0;
}

int TraceE_Com::Update(float DeltaTime)
{
	return 0;
}

int TraceE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void TraceE_Com::Collision(float DeltaTime)
{
}

void TraceE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void TraceE_Com::Render(float DeltaTime)
{
}

TraceE_Com * TraceE_Com::Clone()
{
	return new TraceE_Com(*this);
}

void TraceE_Com::AfterClone()
{
}

void TraceE_Com::SetPos(const Vector3 & Pos)
{
}

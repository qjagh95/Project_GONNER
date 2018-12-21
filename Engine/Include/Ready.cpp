#include "stdafx.h"
#include "Ready.h"

#include "Component/Animation2D_Com.h"

JEONG_USING

Ready::Ready()
{
}

Ready::Ready(const Ready & CopyData)
	:UserComponent_Base(CopyData)
{
}

Ready::~Ready()
{
	SAFE_RELEASE(m_Renderer);
	SAFE_RELEASE(m_Material);
}

bool Ready::Init()
{
	return true;
}

int Ready::Input(float DeltaTime)
{
	return 0;
}

int Ready::Update(float DeltaTime)
{
	return 0;
}

int Ready::LateUpdate(float DeltaTime)
{
	return 0;
}

void Ready::Collision(float DeltaTime)
{
}

void Ready::CollisionLateUpdate(float DeltaTime)
{
}

void Ready::Render(float DeltaTime)
{
}

Ready * Ready::Clone()
{
	return new Ready(*this);
}

void Ready::AfterClone()
{
}

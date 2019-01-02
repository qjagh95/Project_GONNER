#include "ClientHeader.h"
#include "SnekeTail_Com.h"

#include <Component/Animation2D_Com.h>

SnekeTail_Com::SnekeTail_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

SnekeTail_Com::SnekeTail_Com(const SnekeTail_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

SnekeTail_Com::~SnekeTail_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool SnekeTail_Com::Init()
{
	return true;
}

int SnekeTail_Com::Input(float DeltaTime)
{
	return 0;
}

int SnekeTail_Com::Update(float DeltaTime)
{
	return 0;
}

int SnekeTail_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void SnekeTail_Com::Collision(float DeltaTime)
{
}

void SnekeTail_Com::CollisionLateUpdate(float DeltaTime)
{
}

void SnekeTail_Com::Render(float DeltaTime)
{
}

SnekeTail_Com * SnekeTail_Com::Clone()
{
	return new SnekeTail_Com(*this);
}

void SnekeTail_Com::AfterClone()
{
}

#include "ClientHeader.h"
#include "SnakeBody_Com.h"

#include <Component/Animation2D_Com.h>

SnakeBody_Com::SnakeBody_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

SnakeBody_Com::SnakeBody_Com(const SnakeBody_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}


SnakeBody_Com::~SnakeBody_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool SnakeBody_Com::Init()
{
	return true;
}

int SnakeBody_Com::Input(float DeltaTime)
{
	return 0;
}

int SnakeBody_Com::Update(float DeltaTime)
{
	return 0;
}

int SnakeBody_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void SnakeBody_Com::Collision(float DeltaTime)
{
}

void SnakeBody_Com::CollisionLateUpdate(float DeltaTime)
{
}

void SnakeBody_Com::Render(float DeltaTime)
{
}

SnakeBody_Com * SnakeBody_Com::Clone()
{
	return new SnakeBody_Com(*this);
}

void SnakeBody_Com::AfterClone()
{
}

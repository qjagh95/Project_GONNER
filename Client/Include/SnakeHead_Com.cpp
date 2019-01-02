#include "ClientHeader.h"
#include "SnakeHead_Com.h"

#include <Component/Animation2D_Com.h>
#include <Component/ColliderRect_Com.h>

SnakeHead_Com::SnakeHead_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

SnakeHead_Com::SnakeHead_Com(const SnakeHead_Com & CopyData)
{
}

SnakeHead_Com::~SnakeHead_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool SnakeHead_Com::Init()
{
	return true;
}

int SnakeHead_Com::Input(float DeltaTime)
{
	return 0;
}

int SnakeHead_Com::Update(float DeltaTime)
{
	return 0;
}

int SnakeHead_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void SnakeHead_Com::Collision(float DeltaTime)
{
}

void SnakeHead_Com::CollisionLateUpdate(float DeltaTime)
{
}

void SnakeHead_Com::Render(float DeltaTime)
{
}

SnakeHead_Com * SnakeHead_Com::Clone()
{
	return new SnakeHead_Com(*this);
}

void SnakeHead_Com::AfterClone()
{
}

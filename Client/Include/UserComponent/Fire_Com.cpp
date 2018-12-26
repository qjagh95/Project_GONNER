#include "ClientHeader.h"
#include "Fire_Com.h"

JEONG_USING

Fire_Com::Fire_Com()
{
}

Fire_Com::Fire_Com(const Fire_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Fire_Com::~Fire_Com()
{
}

bool Fire_Com::Init()
{
	return true;
}

int Fire_Com::Input(float DeltaTime)
{
	return 0;
}

int Fire_Com::Update(float DeltaTime)
{
	return 0;
}

int Fire_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Fire_Com::Collision(float DeltaTime)
{
}

void Fire_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Fire_Com::Render(float DeltaTime)
{
}

Fire_Com * Fire_Com::Clone()
{
	return new Fire_Com(*this);
}

void Fire_Com::AfterClone()
{
}

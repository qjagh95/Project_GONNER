#include "stdafx.h"
#include "GuardE_Com.h"
JEONG_USING

GuardE_Com::GuardE_Com()
{
}


GuardE_Com::GuardE_Com(const GuardE_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

GuardE_Com::~GuardE_Com()
{
}

bool GuardE_Com::Init()
{
	return true;
}

int GuardE_Com::Input(float DeltaTime)
{
	return 0;
}

int GuardE_Com::Update(float DeltaTime)
{
	return 0;
}

int GuardE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void GuardE_Com::Collision(float DeltaTime)
{
}

void GuardE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void GuardE_Com::Render(float DeltaTime)
{
}

GuardE_Com * GuardE_Com::Clone()
{
	return new GuardE_Com(*this);
}

void GuardE_Com::AfterClone()
{
}

void GuardE_Com::SetPos(const Vector3 & Pos)
{
}

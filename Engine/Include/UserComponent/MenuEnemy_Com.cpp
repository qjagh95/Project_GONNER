#include "stdafx.h"
#include "MenuEnemy_Com.h"

JEONG_USING

MenuEnemy_Com::MenuEnemy_Com()
{
}

MenuEnemy_Com::MenuEnemy_Com(const MenuEnemy_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

MenuEnemy_Com::~MenuEnemy_Com()
{
}

bool MenuEnemy_Com::Init()
{
	return true;
}

int MenuEnemy_Com::Input(float DeltaTime)
{
	return 0;
}

int MenuEnemy_Com::Update(float DeltaTime)
{
	return 0;
}

int MenuEnemy_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void MenuEnemy_Com::Collision(float DeltaTime)
{
}

void MenuEnemy_Com::CollisionLateUpdate(float DeltaTime)
{
}

void MenuEnemy_Com::Render(float DeltaTime)
{
}

MenuEnemy_Com * MenuEnemy_Com::Clone()
{
	return new MenuEnemy_Com(*this);
}

void MenuEnemy_Com::AfterClone()
{
}

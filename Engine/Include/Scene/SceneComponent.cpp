#include "stdafx.h"
#include "SceneComponent.h"

JEONG_USING

SceneComponent::SceneComponent()
	:m_Scene(NULLPTR)
{
	m_isInsert = true;
}

SceneComponent::~SceneComponent()
{
}

void SceneComponent::AfterInit()
{
}

int SceneComponent::Input(float DeltaTime)
{
	return 0;
}

int SceneComponent::Update(float DeltaTime)
{
	return 0;
}

int SceneComponent::LateUpdate(float DeltaTime)
{
	return 0;
}

void SceneComponent::Collision(float DeltaTime)
{
}

void SceneComponent::CollisionLateUpdate(float DeltaTime)
{
}

void SceneComponent::Render(float DeltaTime)
{
}

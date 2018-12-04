#pragma once
#include "Scene\SceneComponent.h"
#include "Component/Bar_Com.h"

JEONG_USING

class LoadingScene : public SceneComponent
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;

private:
	Bar_Com* m_LoadingBar;

public:
	LoadingScene();
	~LoadingScene();
};


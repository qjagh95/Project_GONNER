#pragma once
#include "Scene\SceneComponent.h"
#include <Component/NButton_Com.h>

JEONG_USING

class MenuScene : public SceneComponent
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;

	void StartButtonActive(float DeltaTime);
	void ExitButtonActive(float DeltaTime);

private:
	vector<NButton_Com*> m_vecButton;

private:
	void EnemyInit(Layer *UILayer);

private:
	int m_Index;

public:
	MenuScene();
	~MenuScene();
};


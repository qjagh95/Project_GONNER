#pragma once
#include "Scene/SceneComponent.h"
#include "Component/UIBar_Com.h"
#include "Component/Text_Com.h"

JEONG_USING
class MainScene : public SceneComponent
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
	UIBar_Com* m_TestBar;
	Text_Com* m_TestText;

public:
	MainScene();
	~MainScene();
};



#pragma once
#include <Scene/SceneComponent.h>
#include <UserComponent/Fade_Com.h>

JEONG_USING
class LogoScene : public SceneComponent
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
	void AlphaBatInit(Layer* layer);

private:
	float m_NextTimeVar;
	float m_NextTime;
	Fade_Com* m_FadeCom;

public:
	LogoScene();
	~LogoScene();
};


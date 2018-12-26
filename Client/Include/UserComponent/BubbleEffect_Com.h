#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING
class BubbleEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BubbleEffect_Com* Clone() override;
	void AfterClone() override;

private:
	void ChangeColor(float DeltaTime);
	void ScaleAction(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	Vector3 m_ScaleVar;
	float m_ChangeTimeVar;
	float m_ChangeTime;
	float m_StartTime;
	float m_StartTimeVar;

	bool m_isStart;

	Vector3 m_UpDir;

	Vector4 m_ChangeColor[3];

protected:
	BubbleEffect_Com();
	BubbleEffect_Com(const BubbleEffect_Com& CopyData);
	~BubbleEffect_Com();

public:
	friend class GameObject;
};
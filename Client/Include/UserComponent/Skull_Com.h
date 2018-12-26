#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING

class Skull_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Skull_Com* Clone() override;
	void AfterClone() override;
	
	static void SetTarget(GameObject* target) { m_Target = target; }
	Animation2D_Com* GetAnimation() const { return m_Animation; }

	static int m_LifeCount;

private:
	void ChangeColor(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	static GameObject* m_Target;
	Vector3 m_TargetPos;

	float m_ChangeColorTimeVar;
	float m_ChangeColorTime;

protected:
	Skull_Com();
	Skull_Com(const Skull_Com& CopyData);
	~Skull_Com();

public:
	friend class GameObject;
};
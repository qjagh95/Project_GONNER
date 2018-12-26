#pragma once
#include <UserComponent/UserComponent_Base.h>

#include <Component/ColliderRect_Com.h>
#include <Component/Animation2D_Com.h>

JEONG_USING

class ReloadBullet_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	ReloadBullet_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetTarget(GameObject* target) { m_Target = target; }

private:
	void ChangeColor(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	ColliderRect_Com* m_RectColl;
	GameObject* m_Target;
	Vector3 m_TargetPos;

	float m_ChangeColorTimeVar;
	float m_ChangeColorTime;

	float m_MoveTime;
	float m_MoveTimeVar;

	float m_MoveSpeed;
	bool m_isRot;

protected:
	ReloadBullet_Com();
	ReloadBullet_Com(const ReloadBullet_Com& CopyData);
	~ReloadBullet_Com();

public:
	friend class GameObject;
};
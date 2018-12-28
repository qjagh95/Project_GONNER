#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING
class HeartUI_Com;
class Heart_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Heart_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void ClearUI();

private:
	void ChangeColor(float DeltaTime);
	void CreateReloadBullet(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	float m_ChangeTimeVar;
	float m_ChangeTime;

	Vector4 m_Color[3];
	Vector3 m_TargetPos;

	GameObject* m_HeartUIObject;
	HeartUI_Com* m_HeartUI;

protected:
	Heart_Com();
	Heart_Com(const Heart_Com& CopyData);
	~Heart_Com();

public:
	friend class GameObject;
};
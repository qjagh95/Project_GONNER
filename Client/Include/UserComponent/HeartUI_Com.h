#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING

class HeartUI_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	HeartUI_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetPos(const Vector3& Pos);
	void SetTarget(GameObject* Target) { m_Target = Target; }

private:
	void Move(float DeltaTime);
	void ColorChange(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	bool m_isDelayTime;
	bool m_isMove;
	GameObject* m_Target;
	Vector3 m_GoingPos;
	Vector4 m_Color[3];

	float m_StaticTime;
	float m_StaticTimeVar;

	float m_ColorChangeTimeVar;
	float m_ColorChangeTime;

	bool m_isGoingPos;

protected:
	HeartUI_Com();
	HeartUI_Com(const HeartUI_Com& CopyData);
	~HeartUI_Com();

public:
	friend class GameObject;
};
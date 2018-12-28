#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING

class HeartItem_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	HeartItem_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetDrop(bool Value) { m_isDrop = Value; }

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	float m_ChangeTimeVar;
	float m_ChangeTime;

	bool m_isEquip;
	Vector4 m_Color[3];
	bool m_isDrop;
	float m_MoveRange;
	float m_MoveDir;

protected:
	HeartItem_Com();
	HeartItem_Com(const HeartItem_Com& CopyData);
	~HeartItem_Com();

public:
	friend class GameObject;
};
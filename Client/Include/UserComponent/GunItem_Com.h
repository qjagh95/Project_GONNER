#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING

class GunItem_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	GunItem_Com* Clone() override;
	void AfterClone() override;

	void SetDrop(bool Value) { m_isDrop = Value; }

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	float m_Rot;
	bool m_isDrop;
	float m_MoveRange;
	float m_MoveDir;

protected:
	GunItem_Com();
	GunItem_Com(const GunItem_Com& CopyData);
	~GunItem_Com();

public:
	friend class GameObject;
};
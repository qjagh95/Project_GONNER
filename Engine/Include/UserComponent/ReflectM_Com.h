#pragma once
#include "Monster_Base.h"

JEONG_BEGIN

class JEONG_DLL ReflectM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	ReflectM_Com* Clone() override;
	void AfterClone() override;

	void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime) override;
	void SetPos(const Vector3& Pos) override { m_Transform->SetWorldPos(Pos); }

protected:
	ReflectM_Com();
	ReflectM_Com(const ReflectM_Com& CopyData);
	~ReflectM_Com();

public:
	friend class GameObject;
};

JEONG_END
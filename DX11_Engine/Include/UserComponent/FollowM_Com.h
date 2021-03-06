#pragma once
#include "Monster_Base.h"

JEONG_BEGIN

class JEONG_DLL FollowM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	FollowM_Com* Clone() override;
	void AfterClone() override;

	void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime) override;
	void SetPos(const Vector3& Pos) override { m_Transform->SetWorldPos(Pos); }

protected:
	FollowM_Com();
	FollowM_Com(const FollowM_Com& CopyData);
	~FollowM_Com();

public:
	friend class GameObject;
};

JEONG_END
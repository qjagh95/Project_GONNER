#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class FollowE_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	FollowE_Com* Clone() override;
	void AfterClone() override;

	void SetPos(const Vector3& Pos);

protected:
	FollowE_Com();
	FollowE_Com(const FollowE_Com& CopyData);
	~FollowE_Com();

public:
	friend class GameObject;
};

JEONG_END
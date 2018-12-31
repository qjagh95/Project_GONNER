#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class BasicE_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BasicE_Com* Clone() override;
	void AfterClone() override;

	void SetPos(const Vector3& Pos);

protected:
	BasicE_Com();
	BasicE_Com(const BasicE_Com& CopyData);
	~BasicE_Com();

public:
	friend class GameObject;
};

JEONG_END
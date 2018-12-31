#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class TraceE_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	TraceE_Com* Clone() override;
	void AfterClone() override;

	void SetPos(const Vector3& Pos);

protected:
	TraceE_Com();
	TraceE_Com(const TraceE_Com& CopyData);
	~TraceE_Com();

public:
	friend class GameObject;
};

JEONG_END
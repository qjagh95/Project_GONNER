#pragma once
#include "Monster_Base.h"

JEONG_BEGIN
class JEONG_DLL TraceM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	TraceM_Com* Clone() override;
	void AfterClone() override;

protected:
	TraceM_Com();
	TraceM_Com(const TraceM_Com& CopyData);
	~TraceM_Com();

public:
	friend class GameObject;
};

JEONG_END
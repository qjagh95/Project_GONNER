#pragma once
#include "Monster_Base.h"

JEONG_BEGIN
class JEONG_DLL AirDownM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	AirDownM_Com* Clone() override;
	void AfterClone() override;

protected:
	AirDownM_Com();
	AirDownM_Com(const AirDownM_Com& CopyData);
	~AirDownM_Com();

public:
	friend class GameObject;
};

JEONG_END
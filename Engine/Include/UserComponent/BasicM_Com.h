#pragma once
#include "Monster_Base.h"

JEONG_BEGIN

class JEONG_DLL  BasicM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BasicM_Com* Clone() override;
	void AfterClone() override;

protected:
	BasicM_Com();
	BasicM_Com(const BasicM_Com& CopyData);
	~BasicM_Com();

public:
	friend class GameObject;
};

JEONG_END

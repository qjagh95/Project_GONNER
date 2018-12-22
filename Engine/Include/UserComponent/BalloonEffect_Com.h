#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class Animation2D_Com;
class BallonEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BallonEffect_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	BallonEffect_Com();
	BallonEffect_Com(const BallonEffect_Com& CopyData);
	~BallonEffect_Com();

public:
	friend class GameObject;
};

JEONG_END
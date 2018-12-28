#pragma once
#include "UserComponent_Base.h"


JEONG_BEGIN
class JEONG_DLL  BugEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BugEffect_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	float m_Alpha;

protected:
	BugEffect_Com();
	BugEffect_Com(const BugEffect_Com& CopyData);
	~BugEffect_Com();

public:
	friend class GameObject;
};

JEONG_END
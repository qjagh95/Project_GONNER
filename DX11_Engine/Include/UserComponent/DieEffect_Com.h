#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL DieEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	DieEffect_Com* Clone() override;
	void AfterClone() override;

	void SetPos(const Vector3& Pos);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	Vector3 m_SavePos;

protected:
	DieEffect_Com();
	DieEffect_Com(const DieEffect_Com& CopyData);
	~DieEffect_Com();

public:
	friend class GameObject;
};

JEONG_END
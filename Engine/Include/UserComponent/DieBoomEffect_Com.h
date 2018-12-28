#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL DieBoomEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	DieBoomEffect_Com* Clone() override;
	void AfterClone() override;

	void SetPos(const Vector3& Pos);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	DieBoomEffect_Com();
	DieBoomEffect_Com(const DieBoomEffect_Com& CopyData);
	~DieBoomEffect_Com();

public:
	friend class GameObject;
};

JEONG_END
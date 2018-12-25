#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL Skull_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Skull_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	Skull_Com();
	Skull_Com(const Skull_Com& CopyData);
	~Skull_Com();

public:
	friend class GameObject;
};

JEONG_END
#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL Heart_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Heart_Com* Clone() override;
	void AfterClone() override;

private:
	void ChangeColor(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	float m_ChangeTimeVar;
	float m_ChangeTime;

	bool m_isEquip;
	Vector4 m_Color[3];

protected:
	Heart_Com();
	Heart_Com(const Heart_Com& CopyData);
	~Heart_Com();

public:
	friend class GameObject;
};

JEONG_END
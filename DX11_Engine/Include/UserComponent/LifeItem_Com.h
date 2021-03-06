#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL LifeItem_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	LifeItem_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	LifeItem_Com();
	LifeItem_Com(const LifeItem_Com& CopyData);
	~LifeItem_Com();

public:
	friend class GameObject;
};

JEONG_END
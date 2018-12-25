#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN 

class JEONG_DLL LifeItemUI_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	LifeItemUI_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	LifeItemUI_Com();
	LifeItemUI_Com(const LifeItemUI_Com& CopyData);
	~LifeItemUI_Com();

public:
	friend class GameObject;
};

JEONG_END
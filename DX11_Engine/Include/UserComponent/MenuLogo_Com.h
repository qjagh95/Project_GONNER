#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL MenuLogo_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	MenuLogo_Com* Clone() override;
	void AfterClone() override;

	//void SetMonster(MENU_ENEMY_TYPE Type);

private:
	LogoCBuffer m_CBuffer;
	//MENU_ENEMY_TYPE m_Type;

protected:
	MenuLogo_Com();
	MenuLogo_Com(const MenuLogo_Com& CopyData);
	~MenuLogo_Com();

public:
	friend class GameObject;
};

JEONG_END


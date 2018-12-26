#pragma once

#include <UserComponent/UserComponent_Base.h>

JEONG_USING

class MenuLogo_Com : public UserComponent_Base
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

private:
	LogoCBuffer m_CBuffer;

protected:
	MenuLogo_Com();
	MenuLogo_Com(const MenuLogo_Com& CopyData);
	~MenuLogo_Com();

public:
	friend class GameObject;
};


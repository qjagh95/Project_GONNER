#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL MenuEnemy_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	MenuEnemy_Com* Clone() override;
	void AfterClone() override;

private:

protected:
	MenuEnemy_Com();
	MenuEnemy_Com(const MenuEnemy_Com& CopyData);
	~MenuEnemy_Com();

public:
	friend class GameObject;
};

JEONG_END


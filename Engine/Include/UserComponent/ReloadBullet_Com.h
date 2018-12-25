#pragma once
#include "UserComponent_Base.h"

#include "../Component/ColliderRect_Com.h"

JEONG_BEGIN

class JEONG_DLL ReloadBullet_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	ReloadBullet_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	ColliderRect_Com* m_RectColl;

protected:
	ReloadBullet_Com();
	ReloadBullet_Com(const ReloadBullet_Com& CopyData);
	~ReloadBullet_Com();

public:
	friend class GameObject;
};

JEONG_END
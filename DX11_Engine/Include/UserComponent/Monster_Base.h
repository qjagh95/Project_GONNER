#pragma once
#include "UserComponent_Base.h"
#include "../Component/ColliderRect_Com.h"

JEONG_BEGIN

class JEONG_DLL Monster_Base : public UserComponent_Base
{
public:
	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void CollisionLateUpdate(float DeltaTime) override;
	virtual void Render(float DeltaTime) override;
	virtual Monster_Base* Clone() override;
	virtual void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	Monster_Base();
	Monster_Base(const Monster_Base& CopyData);
	~Monster_Base();

public:
	friend class GameObject;
};

JEONG_END
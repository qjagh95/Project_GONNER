#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class Animation2D_Com;
class BoomEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BoomEffect_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	BoomEffect_Com();
	BoomEffect_Com(const BoomEffect_Com& CopyData);
	~BoomEffect_Com();

public:
	friend class GameObject;
};

JEONG_END


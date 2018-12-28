#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL ShotEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	ShotEffect_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	ShotEffect_Com();
	ShotEffect_Com(const ShotEffect_Com& CopyData);
	~ShotEffect_Com();

public:
	friend class GameObject;

};

JEONG_END
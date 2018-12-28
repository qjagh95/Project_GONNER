#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL HitEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	HitEffect_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetPos(const Vector3& Pos, const Vector4& Color);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	HitEffect_Com();
	HitEffect_Com(const HitEffect_Com& CopyData);
	~HitEffect_Com();

public:
	friend class GameObject;
};

JEONG_END
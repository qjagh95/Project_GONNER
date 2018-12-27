#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL BasicEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BasicEffect_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetRandomDirection(const Vector4& Color);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	float m_MoveSpeed;
	Vector3 m_Dir;

protected:
	BasicEffect_Com();
	BasicEffect_Com(const BasicEffect_Com& CopyData);
	~BasicEffect_Com();

public:
	friend class GameObject;
};


JEONG_END

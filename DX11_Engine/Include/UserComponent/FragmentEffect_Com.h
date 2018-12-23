#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL FragmentEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	FragmentEffect_Com* Clone() override;
	void AfterClone() override;
	void SetTargetPos(const Vector3& Pos) { m_TargetPos = Pos; }

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetDir(const Vector3& Dir) { m_Dir = Dir; }

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	Vector3 m_TargetPos;
	bool m_isMove;

	float m_StaticTime;
	float m_StaticTimeVar;

	float m_MoveSpeed;
	Vector3 m_Dir;

protected:
	FragmentEffect_Com();
	FragmentEffect_Com(const FragmentEffect_Com& CopyData);
	~FragmentEffect_Com();

public:
	friend class GameObject;
};

JEONG_END
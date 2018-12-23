#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

enum EFFECT_STATE
{
	ES_IDLE,
	ES_DIE,
};

class Animation2D_Com;
class JEONG_DLL BallonEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BallonEffect_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	Vector3 m_Scale;
	EFFECT_STATE m_State;

	float m_UpTimeVar;
	float m_UpTime;
	float m_UpSpeed;
	float m_MoveSpeed;
	bool m_isMove;

protected:
	BallonEffect_Com();
	BallonEffect_Com(const BallonEffect_Com& CopyData);
	~BallonEffect_Com();

public:
	friend class GameObject;
};

JEONG_END

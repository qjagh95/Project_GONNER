#pragma once
#include <UserComponent/UserComponent_Base.h>

JEONG_USING
class SnakeBody_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	SnakeBody_Com* Clone() override;
	void AfterClone() override;

	void SetPosRange(const Vector3& Pos, float AngleRange);
	void SetSpeed(float Speed) { m_Speed = Speed; }
	float GetSpeed() const { return m_Speed; }
	
private:
	void ChangeColor(float DeltaTime);
	void CircleMove(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	Vector4 m_ChangeColor[3];

	float m_AngleRange;
	Vector3 m_SavePos;
	float m_LeftAngle;
	float m_RightAngle;
	float m_Speed;
	float m_Angle;
	bool m_isTurn;

	float m_ChangeTimeVar;
	float m_ChangeTime;

protected:
	SnakeBody_Com();
	SnakeBody_Com(const SnakeBody_Com& CopyData);
	~SnakeBody_Com();

public:
	friend class GameObject;
};


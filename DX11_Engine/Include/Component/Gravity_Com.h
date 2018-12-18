#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class JEONG_DLL Gravity_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Gravity_Com* Clone() override;
	void AfterClone() override;
	
	static void SetGravity(float Gravity) { m_Gravity = Gravity; }
	static float GetGravity() { return m_Gravity; }
	void SetForce(float Force) { m_Force = Force;}
	float GetForce() { return m_Force; }

	void SetStage(Stage2D_Com* stage) { m_Stage = stage; }
	Stage2D_Com* GetStage() const { return m_Stage; }
	bool GetIsJump() const { return m_isJump; }

private:
	static float m_Gravity;
	float m_Force;
	Stage2D_Com* m_Stage;
	Vector3 m_ObjectScale;
	bool m_isJump;

protected:
	Gravity_Com();
	Gravity_Com(const Gravity_Com& CopyData);
	~Gravity_Com();

public:
	friend class GameObject;
};

JEONG_END
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
	
	void SetGravity(float Gravity) { m_Gravity = Gravity; }
	float GetGravity() const { return m_Gravity; }
	void SetStage(Stage2D_Com* stage) { m_Stage = stage; }
	Stage2D_Com* GetStage() const { return m_Stage; }

private:
	float m_Gravity;
	Stage2D_Com* m_Stage;

protected:
	Gravity_Com();
	Gravity_Com(const Gravity_Com& CopyData);
	~Gravity_Com();

public:
	friend class GameObject;
};

JEONG_END
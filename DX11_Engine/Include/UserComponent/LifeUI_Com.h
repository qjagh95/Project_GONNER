#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN 

enum LIFEUI_STATE
{
	LS_ON,
	LS_OFF,
	LS_MAX,
};

class JEONG_DLL LifeUI_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	LifeUI_Com* Clone() override;
	void AfterClone() override;

	void SetDisable(bool Value) { m_isDisable = Value; }
	void SetMove(bool Value) { m_isMove = Value; }
	void SetState(LIFEUI_STATE state) { m_State = state; }
	void SetIndex(int Index);
	void SetPos(int Index);

	static void SetTarget(GameObject* target) { m_Target = target; }

private:
	void GrayLightChange(float DeltaTime);
	void LightChange(float DeltaTime);
	void On(float DeltaTime);
	void Off(float DeltaTime);
	void TargetMove(float DeltaTime);
	void RotMove(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	bool m_isMove;
	bool m_isGoingPos;
	bool m_isDisable;

	float m_LightTimeVar;
	float m_LightTime;

	float m_StaticTime;
	float m_StaticTimeVar;
	int m_Index;
	float m_DirAngle;
	float m_RotSpeed;

	LIFEUI_STATE m_State;
	Vector3 m_GoingPos;
	Vector3 m_CirclePos;
	Vector3 m_ResultPos;

	static float m_Range;
	static float m_MoveSpeed;
	static GameObject* m_Target;

	Vector3 m_TargetPos;

protected:
	LifeUI_Com();
	LifeUI_Com(const LifeUI_Com& CopyData);
	~LifeUI_Com();

public:
	friend class GameObject;
};

JEONG_END
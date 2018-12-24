#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

enum BULLETUI_STATE
{
	BT_ON,
	BT_OFF,
	BT_MAX,
};

class Gun_Com;
class JEONG_DLL BulletUI_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BulletUI_Com* Clone() override;
	void AfterClone() override;

	void SetDisable(bool Value) { m_isDisable = Value; }
	void SetMove(bool Value) { m_isMove = Value; }
	void SetState(BULLETUI_STATE state) { m_State = state; }
	void SetIndex(int Index);
	void SetPos(int Index);
	static void SetTargetGun(Gun_Com* Gun) { m_TargetGun = Gun; }

private:
	void GrayLightChange(float DeltaTime);
	void YellowLightChange(float DeltaTime);
	void On(float DeltaTime);
	void Off(float DeltaTime);
	void Move(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	bool m_isMove;
	bool m_isDisable;

	float m_LightTimeVar;
	float m_LightTime;

	float m_StaticTime;
	float m_StaticTimeVar;
	int m_Index;

	Vector4 m_Color[BT_MAX];
	BULLETUI_STATE m_State;
	Vector3 m_GoingPos;
	Vector3 m_CirclePos;
	Vector3 m_ResultPos;

	static Vector3 m_GunPos;
	static Gun_Com* m_TargetGun;
	static float m_Range;
	static float m_MoveSpeed;

protected:
	BulletUI_Com();
	BulletUI_Com(const BulletUI_Com& CopyData);
	~BulletUI_Com();

public:
	friend class GameObject;
};

JEONG_END
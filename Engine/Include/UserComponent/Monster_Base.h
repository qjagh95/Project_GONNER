#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN
class Gravity_Com;
class JEONG_DLL Monster_Base : public UserComponent_Base
{
public:
	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void CollisionLateUpdate(float DeltaTime) override;
	virtual void Render(float DeltaTime) override;
	virtual Monster_Base* Clone() override;
	virtual void AfterClone() override;

	void SetHP(int Hp) { m_Hp = Hp; }
	void AddHp(int Hp) { m_Hp += Hp; }
	int GetHP() const { return m_Hp; }
	void SetIsJumpAttack(bool Value) { m_GonnerJumpAttack = Value; }

	virtual void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	virtual void SetPos(const Vector3& Pos) {};
	static GameObject* m_Target; //플레이어 - 클라 // 몬스터 - 엔진 어쩔수없이 한번 더 선언
	static Vector3 m_TargetPos;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	Material_Com* GetMaterial() const { return m_Material; }

protected:
	void ChangeColor(float DeltaTime);
	void HitChangeColor(float DeltaTime);
	void RangeTargetDirCheck(float DeltaTime);
	void HitEffectOut(float DeltaTime);

protected:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	ColliderRect_Com* m_RectColl;
	Gravity_Com* m_Gravity;
	MONSTER_TYPE m_Type;
	Layer* m_AfterEffect;
	Layer* m_PrevEffect;
	Vector3 m_Pos;
	Vector3 m_Scale;
	Vector3 m_CenterPos;
	Vector3 m_CenterLeftPos;
	Vector3 m_CenterRightPos;
	Vector3 m_DownLeftPos;
	Vector3 m_DownRightPos;
	Vector3 m_UpLeftPos;
	Vector3 m_UpRightPos;
	Vector3 m_UpPos;

	Tile2D_Com* m_UpTile;
	Tile2D_Com* m_DownTile;
	Tile2D_Com* m_LeftTile;
	Tile2D_Com* m_RightTile;
	Tile2D_Com* m_UpLeftTile;
	Tile2D_Com* m_UpRightTile;
	Tile2D_Com* m_DownLeftTile;
	Tile2D_Com* m_DownRightTile;

	Stage2D_Com* m_Stage;
	Vector3 m_CrossDir;

	string m_AniName[255];
	int m_Hp;
	float m_LookRange;
	float m_MoveDir;
	bool m_GonnerJumpAttack;
	Camera_Com* m_Camera;

private:
	float m_ChangeTime;
	float m_ChangeTimeVar;
	float m_DirCheckTime;
	float m_DirCheckTimeVar;

protected:
	Monster_Base();
	Monster_Base(const Monster_Base& CopyData);
	virtual ~Monster_Base();

public:
	friend class GameObject;
};

JEONG_END
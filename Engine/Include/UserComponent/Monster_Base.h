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

	virtual void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	static GameObject* m_Target; //플레이어 - 클라 // 몬스터 - 엔진 어쩔수없이 한번 더 선언
	static Vector3 m_TargetPos;

protected:
	void ChangeColor(float DeltaTime);
	void TargetDirCheck(float DeltaTime);

protected:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	ColliderRect_Com* m_RectColl;
	Gravity_Com* m_Gravity;
	MONSTER_TYPE m_Type;
	Layer* m_AfterEffect;
	Layer* m_PrevEffect;
	Vector3 m_Pos;

	Vector3 m_CrossDir;

	string m_AniName[255];
	int m_Hp;
	float m_Range;

private:
	float m_ChangeTime;
	float m_ChangeTimeVar;

protected:
	Monster_Base();
	Monster_Base(const Monster_Base& CopyData);
	virtual ~Monster_Base();

public:
	friend class GameObject;
};

JEONG_END
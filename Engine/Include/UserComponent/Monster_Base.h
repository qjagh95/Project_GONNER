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

	static GameObject* m_Target;

	void SetHP(int Hp) { m_Hp = Hp; }
	void AddHp(int Hp) { m_Hp += Hp; }
	int GetHP() const { return m_Hp; }

protected:
	virtual void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	void ChangeColor(float DeltaTime);

protected:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	ColliderRect_Com* m_RectColl;
	Gravity_Com* m_Gravity;
	MONSTER_TYPE m_Type;
	string m_AniName[255];
	int m_Hp;

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
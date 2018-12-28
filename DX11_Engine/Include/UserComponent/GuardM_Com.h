#pragma once
#include "Monster_Base.h"

JEONG_BEGIN

enum GUARD_STATE
{
	GS_IDLE,
	GS_MOVE,
	GS_HIT,
	GS_GUARD,
	GS_GUARDDOWN,
	GS_MAX,
};

class JEONG_DLL GuardM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	GuardM_Com* Clone() override;
	void AfterClone() override;

	void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime) override;

private:
	void FS_IDLE(float DeltaTime);
	void FS_MOVE(float DeltaTime);
	void FS_HIT(float DeltaTime);
	void FS_GUARD(float DeltaTime);
	void FS_GUARDDOWN(float DeltaTime);

private:
	float m_IdleTime;
	float m_IdleTimeVar;

	float m_GuardTime;
	float m_GuardTimeVar;

protected:
	GuardM_Com();
	GuardM_Com(const GuardM_Com& CopyData);
	~GuardM_Com();

public:
	friend class GameObject;
};

JEONG_END
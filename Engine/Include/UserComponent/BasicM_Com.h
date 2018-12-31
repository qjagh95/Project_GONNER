#pragma once
#include "Monster_Base.h"

JEONG_BEGIN

class Collider_Com;
class JEONG_DLL BasicM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	BasicM_Com* Clone() override;
	void AfterClone() override;

	void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime) override;
	void SetPos(const Vector3& Pos) override { m_Transform->SetWorldPos(Pos); }

private:
	void FS_IDLE(float DeltaTime);
	void FS_MOVE(float DeltaTime);
	void FS_HIT(float DeltaTime);

private:
	float m_IdleTime;
	float m_IdleTimeVar;

	float m_MoveTime;
	float m_MoveTimeVar;

protected:
	BasicM_Com();
	BasicM_Com(const BasicM_Com& CopyData);
	~BasicM_Com();

public:
	friend class GameObject;
};

JEONG_END

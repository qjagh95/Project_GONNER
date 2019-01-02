#pragma once
#include "Monster_Base.h"

JEONG_BEGIN
class JEONG_DLL TraceM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	TraceM_Com* Clone() override;
	void AfterClone() override;
	
	void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime) override;
	void SetPos(const Vector3& Pos) override { m_Transform->SetWorldPos(Pos); }

private:
	void FS_IDLE(float DeltaTime);
	void FS_TRACE(float DeltaTime);
	void FS_HIT(float DeltaTime);

	void TraceMove(float DeltaTime);
	void RangeCheck(float DeltaTime);

private:
	float m_HitAngle;
	float m_TraceTime;
	float m_TraceTimeVar;
	float m_IdleTime;
	float m_IdleTimeVar;
	float m_Dir;

protected:
	TraceM_Com();
	TraceM_Com(const TraceM_Com& CopyData);
	~TraceM_Com();

public:
	friend class GameObject;
};

JEONG_END
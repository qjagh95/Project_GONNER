#pragma once
#include "Monster_Base.h"

JEONG_BEGIN
class JEONG_DLL AirDownM_Com : public Monster_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	AirDownM_Com* Clone() override;
	void AfterClone() override;

	void BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime) override;
	void SetPos(const Vector3& Pos) override;

private:
	void FS_IDLE(float DeltaTime);
	void FS_DOWN(float DeltaTime);
	void FS_UP(float DeltaTime);

	void CircleMove(float DeltaTime);

private:
	Vector3 m_SavePos;
	float m_Angle;

protected:
	AirDownM_Com();
	AirDownM_Com(const AirDownM_Com& CopyData);
	~AirDownM_Com();

public:
	friend class GameObject;
};

JEONG_END
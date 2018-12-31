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
	
	void SetPos(const Vector3& Pos) override { m_Transform->SetWorldPos(Pos); }

private:
	void FS_IDLE(float DeltaTime);
	void TS_MOVE(float DeltaTime);
	void TS_TRACE(float DeltaTime);
	void TS_HIT(float DeltaTime);

	void TraceMove(float DeltaTime);
	void RangeCheck(float DeltaTime);

protected:
	TraceM_Com();
	TraceM_Com(const TraceM_Com& CopyData);
	~TraceM_Com();

public:
	friend class GameObject;
};

JEONG_END
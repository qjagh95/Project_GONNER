#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL Fire_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Fire_Com* Clone() override;
	void AfterClone() override;

private:
	LogoCBuffer m_CBuffer;

protected:
	Fire_Com();
	Fire_Com(const Fire_Com& CopyData);
	~Fire_Com();

public:
	friend class GameObject;
};

JEONG_END
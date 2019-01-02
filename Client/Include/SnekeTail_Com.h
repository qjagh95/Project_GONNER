#pragma once

#include <UserComponent/UserComponent_Base.h>
JEONG_USING
class SnekeTail_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	SnekeTail_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	SnekeTail_Com();
	SnekeTail_Com(const SnekeTail_Com& CopyData);
	~SnekeTail_Com();

public:
	friend class GameObject;
};


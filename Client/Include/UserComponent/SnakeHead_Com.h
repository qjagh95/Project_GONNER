#pragma once
#include <UserComponent/UserComponent_Base.h>
JEONG_USING
class SnakeHead_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	SnakeHead_Com* Clone() override;
	void AfterClone() override;

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

protected:
	SnakeHead_Com();
	SnakeHead_Com(const SnakeHead_Com& CopyData);
	~SnakeHead_Com();

public:
	friend class GameObject;
};


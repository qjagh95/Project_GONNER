#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING

class FragmentEffect_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	FragmentEffect_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetDirection(MOVE_DIR dir);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	float m_MoveSpeed;
	Vector3 m_Dir;

protected:
	FragmentEffect_Com();
	FragmentEffect_Com(const FragmentEffect_Com& CopyData);
	~FragmentEffect_Com();

public:
	friend class GameObject;
};
#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class Animation2D_Com;
class JEONG_DLL MenuEnemy_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	MenuEnemy_Com* Clone() override;
	void AfterClone() override;

	void SetEnemyType(MENU_ENEMY_TYPE Type, const Vector3& Pos, bool isRight ,float Rot = 0.0f);

private:
	Animation2D_Com* m_Animation;
	MENU_ENEMY_TYPE m_Type;
	Vector3 m_ResultScale;

	float m_ScaleStartTime;
	float m_ScaleStartTimeVar;

	float m_ColorChangeTime;
	float m_ColorChangeTimeVar;

	bool m_isScaleStart;
	bool m_isColorStart;

protected:
	MenuEnemy_Com();
	MenuEnemy_Com(const MenuEnemy_Com& CopyData);
	~MenuEnemy_Com();

public:
	friend class GameObject;
};

JEONG_END


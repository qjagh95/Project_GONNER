#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class Animation2D_Com;
class JEONG_DLL Gun_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Gun_Com* Clone() override;
	void AfterClone() override;

	void FS_IDLE(float DeltaTime);
	void FS_SHOT(float DeltaTime);

	void ChangeColor(float DeltaTime);
	Material_Com* GetMaterial() const { return m_Material; }
	Animation2D_Com* GetAnimation2D() const { return m_Animation; }
	void SetIsShot(bool Value) { m_isShot = Value; }
	bool GetIsShot() const { return m_isShot; }

	void SetBulletCount(int Count) { m_BulletCount = Count; }
	int GetBulletCount() const { return m_BulletCount; }

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;

	string m_AniName[GGS_MAX];
	Vector4 m_Color[3];

	float m_ChangeTimeVar;
	float m_ChangeTime;

	int m_BulletCount;
	bool m_isShot;

protected:
	Gun_Com();
	Gun_Com(const Gun_Com& CopyData);
	~Gun_Com();

public:
	friend class GameObject;
};

JEONG_END
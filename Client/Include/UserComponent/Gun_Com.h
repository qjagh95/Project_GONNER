#pragma once
#include <UserComponent/UserComponent_Base.h>
#include <Component/Animation2D_Com.h>

JEONG_USING
class BulletUI_Com;
class Gun_Com : public UserComponent_Base
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
	void FS_RELOAD(float DeltaTime);

	void ChangeColor(float DeltaTime);
	Material_Com* GetMaterial() const { return m_Material; }
	Animation2D_Com* GetAnimation() const { return m_Animation; }
	string* GetAniName() { return m_AniName; }
	void ClearUI();

	static bool m_isReloading;
	static bool m_isEquip;

private:
	void DelayTime(float DeltaTime);

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	Layer* m_AfterEffectLayer;
	Layer* m_DefaultLayer;

	Vector3 m_Pos;

	string m_AniName[GGS_MAX];
	Vector4 m_Color[3];

	float m_ChangeTimeVar;
	float m_ChangeTime;

	float m_ReloadTime;
	float m_ReloadTimeVar;

	float m_ReloadDelayTime;
	float m_ReloadDelayTimeVar;

	vector<GameObject*> m_vecBulletUIObject; //클리어제외 아무것도 안함.
	vector<BulletUI_Com*> m_vecBulletUI; //클리어제외 아무것도 안함.

protected:
	Gun_Com();
	Gun_Com(const Gun_Com& CopyData);
	~Gun_Com();

public:
	friend class GameObject;

};
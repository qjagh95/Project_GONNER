#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN
class Material_Com;
class Animation2D_Com;
class Stage2D_Com;
class JEONG_DLL Bullet_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Bullet_Com* Clone() override;
	void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void ColorLight(float DeltaTime);
	void SetAfterLayer(Layer* layer) { m_AfterEffectLayer = layer; }

private:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	Stage2D_Com* m_Stage;
	Vector3 m_Scale;
	Vector3 m_ScaleHalf;
	Layer* m_AfterEffectLayer;

	float m_LightTimeVar;
	float m_LightTime;

	int m_BallonCount;
	int m_FragmentCount;

protected:
	Bullet_Com();
	Bullet_Com(const Bullet_Com& CopyData);
	~Bullet_Com();

public:
	friend class GameObject;
};

JEONG_END
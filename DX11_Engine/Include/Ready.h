#pragma once
#include "UserComponent/UserComponent_Base.h"

JEONG_BEGIN

class Renderer_Com;
class Material_Com;
class Animation2D_Com;
class JEONG_DLL Ready : public UserComponent_Base
{
public:
	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void CollisionLateUpdate(float DeltaTime) override;
	virtual void Render(float DeltaTime) override;
	virtual Ready* Clone() override ;
	virtual void AfterClone() override ;

	Renderer_Com* GetRenderer() const { return m_Renderer; }
	Material_Com* GetMaterial() const { return m_Material; }

	void ChangeState(int State, string* AnimationName ,Animation2D_Com* animation);

protected:
	Renderer_Com* m_Renderer;
	Material_Com* m_Material;

	int m_State;
	int m_PrevState;

protected:
	Ready();
	Ready(const Ready& CopyData);
	~Ready();

public:
	friend class GameObject;
};

JEONG_END


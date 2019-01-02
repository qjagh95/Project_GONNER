#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL EditorMonster_Base : public UserComponent_Base
{
public:
	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void CollisionLateUpdate(float DeltaTime) override;
	virtual void Render(float DeltaTime) override;
	virtual EditorMonster_Base* Clone() override;
	virtual void AfterClone() override;

	Animation2D_Com* GetAnimation() const { return m_Animation; }
	void SetIndex(int Index) { m_Index = Index; }
	int GetIndex() const { return m_Index; }
	virtual void MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	static GameObject* m_SelectObject;

protected:
	Material_Com* m_Material;
	Animation2D_Com* m_Animation;
	ColliderRect_Com* m_RectColl;
	int m_Index;

protected:
	EditorMonster_Base();
	EditorMonster_Base(const EditorMonster_Base& CopyData);
	virtual~EditorMonster_Base();

public:
	friend class GameObject;
};

JEONG_END
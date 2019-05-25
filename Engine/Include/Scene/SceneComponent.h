#pragma once
#include "../RefCount.h"
JEONG_BEGIN

class Scene;
class JEONG_DLL SceneComponent : public RefCount
{
public:
	virtual bool Init() = 0;
	virtual void AfterInit();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void CollisionLateUpdate(float DeltaTime);
	virtual void Render(float DeltaTime);

	bool GetIsInsert() const { return m_isInsert; }

protected:
	Scene* m_Scene;
	bool m_isInsert;
	bool m_isBgmStart;
	string m_BgmName;

protected:
	SceneComponent();
	~SceneComponent();

public:
	friend class Scene;
};

JEONG_END


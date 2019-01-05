#pragma once

JEONG_BEGIN

class GameObject;
class Component_Base;
class Scene;
class JEONG_DLL StaticManager
{
public:
	bool Init();

	void AddStaticObject(GameObject* object);
	void ChangeScene(Scene* scene);
	bool CheckStaticObject(const string& TagName);
	GameObject* FindStaticObject(const string& TagName);
	list<GameObject*> m_staticObjectList;

private:

public:
	CLASS_IN_SINGLE(StaticManager)
};

JEONG_END


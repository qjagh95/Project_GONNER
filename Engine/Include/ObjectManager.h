#pragma once

JEONG_BEGIN

class JEONG_DLL ObjectManager
{
public:
	GameObject* FindDontDestroyObject(const string& TagName);
	void PushDontDestoryObject(GameObject* _pObject);
	bool RemoveDontDestroyObject(GameObject* _pObject);
	unordered_map<string, GameObject*>* GetMap();

private:
	unordered_map<string, GameObject*> m_DontMap;

public:
	CLASS_IN_SINGLE(ObjectManager)
};

JEONG_END
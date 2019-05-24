#include "stdafx.h"
#include "ObjectManager.h"

JEONG_USING
SINGLETON_VAR_INIT(ObjectManager)

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	Safe_Release_Map(m_DontMap);
}

GameObject * ObjectManager::FindDontDestroyObject(const string & TagName)
{
	auto FindIter = m_DontMap.find(TagName);

	if (FindIter == m_DontMap.end())
		return NULLPTR;

	return FindIter->second;
}

void ObjectManager::PushDontDestoryObject(GameObject * _pObject)
{
	if (FindDontDestroyObject(_pObject->GetTag()) != nullptr)
		return;

	_pObject->AddRefCount();
	m_DontMap.insert(make_pair(_pObject->GetTag(), _pObject));
}

bool ObjectManager::RemoveDontDestroyObject(GameObject * _pObject)
{
	GameObject* getObject = FindDontDestroyObject(_pObject->GetTag());

	if (getObject == NULLPTR)
	{
		TrueAssert(true);
		return false;
	}

	m_DontMap.erase(_pObject->GetTag());
	SAFE_RELEASE(getObject);

	return true;
}

unordered_map<string, GameObject*>* ObjectManager::GetMap()
{
	return &m_DontMap;
}
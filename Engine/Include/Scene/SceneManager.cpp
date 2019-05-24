#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "SceneComponent.h"

#include "../KeyInput.h"

JEONG_USING
SINGLETON_VAR_INIT(SceneManager)

SceneManager::SceneManager()
	:m_CurScene(NULLPTR), m_isChange(false)
{
	m_isStart = false;
}

SceneManager::~SceneManager()
{
	Safe_Delete_VecList(m_vecTemp);
}

bool SceneManager::Init()
{
	return true;
}

int SceneManager::Input(float DeltaTime)
{
	m_CurScene->Input(DeltaTime);
	return 0;
}

int SceneManager::Update(float DeltaTime)
{
	m_CurScene->Update(DeltaTime);
	return 0;
}

int SceneManager::LateUpdate(float DeltaTime)
{
	m_CurScene->LateUpdate(DeltaTime);
	return 0;
}

int SceneManager::Collision(float DeltaTime)
{
	m_CurScene->Collision(DeltaTime);
	return 0;
}

int SceneManager::CollsionLateUpdate(float DeltaTime)
{
	m_CurScene->CollisionLateUpdate(DeltaTime);
	return 0;
}

void SceneManager::Render(float DeltaTime)
{
	m_CurScene->Render(DeltaTime);
}

Scene * SceneManager::GetCurScene() const
{
	m_CurScene->AddRefCount();

	return m_CurScene;
}

void SceneManager::AddLayer(const string & TagName, int ZOrder)
{
	m_CurScene->AddLayer(TagName, ZOrder);
}

void SceneManager::ChangeLayerZOrder(const string & TagName, int ZOrder)
{
	m_CurScene->ChangeLayerZOrder(TagName, ZOrder);
}

Layer * SceneManager::FindLayer(const string & TagName)
{
	return m_CurScene->FindLayer(TagName);
}

GameObject * SceneManager::FindObject(const string & TagName)
{
	if (m_CurScene != NULLPTR)
		return m_CurScene->FindObject(TagName);

	return NULLPTR;
}

void SceneManager::ChangeScene(const string & KeyName)
{
	Scene* newScene = FindScene(KeyName);

	if (newScene == NULLPTR)
	{
		TrueAssert(true);
		return;
	}

	auto StartIter = ObjectManager::Get()->GetMap()->begin();
	auto EndIter = ObjectManager::Get()->GetMap()->end();

	for (; StartIter != EndIter; StartIter++)
	{
		StartIter->second->SetScene(newScene);
		StartIter->second->SetLayer(newScene->FindLayerNoneCount(StartIter->second->GetLayer()->GetTag()));
	}

	m_CurScene = newScene;
	m_isChange = true;
}

Scene * SceneManager::FindScene(const string & KeyName)
{
	auto FindIter = m_SceneMap.find(KeyName);

	if (FindIter == m_SceneMap.end())
		return NULLPTR;

	return FindIter->second;
}

void SceneManager::SetIsChange(bool isChange)
{
	m_isChange = isChange;
}

void SceneManager::Access()
{
	for (size_t i = 0; i < m_vecTemp.size(); i++)
	{
		auto StartIter = m_vecTemp[i]->m_LayerList.begin();
		auto EndIter = m_vecTemp[i]->m_LayerList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			auto StartIter1 = ObjectManager::Get()->GetMap()->begin();
			auto EndIter1 = ObjectManager::Get()->GetMap()->end();

			for (; StartIter1 != EndIter1; StartIter1++)
			{
				if (StartIter1->second->GetScene()->GetTag() == m_vecTemp[i]->GetTag())
					continue;

				if (m_vecTemp[i]->GetSceneComponent()->GetIsInsert() == false)
					continue;

				if ((*StartIter)->GetTag() == StartIter1->second->GetLayer()->GetTag())
					(*StartIter)->GetObjectList()->push_back(StartIter1->second);
			}
		}
	}

	AfterInit();
}

void SceneManager::AfterAccess(GameObject * object)
{
	//중간에 추가됐을때 경우

	for (size_t i = 1; i < m_vecTemp.size(); i++)
	{
		auto StartIter = m_vecTemp[i]->m_LayerList.begin();
		auto EndIter = m_vecTemp[i]->m_LayerList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			if (object->GetScene()->GetTag() == m_vecTemp[i]->GetTag())
				continue;

			if ((*StartIter)->GetTag() == object->GetLayer()->GetTag())
					(*StartIter)->GetObjectList()->push_back(object);
		}
	}
}

void SceneManager::AfterInit()
{
	for (size_t i = 0; i < m_vecTemp.size(); i++)
		m_vecTemp[i]->AfterInit();
}

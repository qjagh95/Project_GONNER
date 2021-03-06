#include "stdafx.h"
#include "Scene.h"
#include "Layer.h"
#include "SceneComponent.h"

#include "../GameObject.h"
#include "../Device.h"
#include "../CollsionManager.h"
#include "../KeyInput.h"

#include "../Component/Camera_Com.h"
#include "../Component/Transform_Com.h"

JEONG_USING

Scene::Scene()
{
}

Scene::~Scene()
{
	GameObject::DestroyProtoType();

	Safe_Release_Map(m_CameraMap);
	Safe_Release_VecList(m_LayerList);
	SAFE_RELEASE(m_SceneComponent);
	SAFE_RELEASE(m_MainCamera);
	SAFE_RELEASE(m_MainCameraObject);
	SAFE_RELEASE(m_UICamera);
	SAFE_RELEASE(m_UICameraObject);
}

bool Scene::Init()
{
	AddLayer("BackGround", INT_MIN);
	AddLayer("Tile", 0);
	AddLayer("PrevEffectLayer", 1);
	AddLayer("Default", 2);
	AddLayer("AfterEffectLayer", 3);
	AddLayer("UI", INT_MAX - 1);
	AddLayer("Fade", INT_MAX);

	m_MainCameraObject = CreateCamera("MainCamera", Vector3(0.0f, 0.0f, -5.0f), CT_ORTHO, (float)Device::Get()->GetWinSize().Width, (float)Device::Get()->GetWinSize().Height, 60.0f, 0.03f, 1000.0f);
	m_MainCameraTransform = m_MainCameraObject->GetTransform();
	m_MainCamera = m_MainCameraObject->FindComponentFromType<Camera_Com>(CT_CAMERA);

	m_UICameraObject = CreateCamera("UICamera", Vector3(0.0f, 0.0f, 0.0f), CT_ORTHO, (float)Device::Get()->GetWinSize().Width, (float)Device::Get()->GetWinSize().Height, 60.0f, 0.0f, 1000.0f);
	m_UICameraTransform = m_UICameraObject->GetTransform();
	m_UICamera = m_UICameraObject->FindComponentFromType<Camera_Com>(CT_CAMERA);

	//CreateCamera함수안에서 카메라 컴포넌트 생성 후 AddComponent

	SortLayer();

	m_WinSize = Device::Get()->GetWinSizeVector2();

	return true;
}

int Scene::Input(float DeltaTime)
{
	m_SceneComponent->Input(DeltaTime);

	list<Layer*>::iterator StartIter1 = m_LayerList.begin();
	list<Layer*>::iterator EndIter1 = m_LayerList.end();

	for (; StartIter1 != EndIter1; )
	{
		if ((*StartIter1)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter1));
			StartIter1 = m_LayerList.erase(StartIter1);
			continue;
		}
		else if ((*StartIter1)->GetIsShow() == false)
		{
			StartIter1++;
			continue;
		}

		(*StartIter1)->Input(DeltaTime);
		StartIter1++;
	}

	m_MainCameraObject->Input(DeltaTime);

	return 0;
}

int Scene::Update(float DeltaTime)
{
	m_SceneComponent->Update(DeltaTime);

	list<Layer*>::iterator StartIter1 = m_LayerList.begin();
	list<Layer*>::iterator EndIter1 = m_LayerList.end();

	for (; StartIter1 != EndIter1; )
	{
		if ((*StartIter1)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter1));
			StartIter1 = m_LayerList.erase(StartIter1);
			continue;
		}
		else if ((*StartIter1)->GetIsShow() == false)
		{
			StartIter1++;
			continue;
		}
		(*StartIter1)->Update(DeltaTime);
		StartIter1++;
	}

	m_MainCameraObject->Update(DeltaTime);
	return 0;
}

int Scene::LateUpdate(float DeltaTime)
{
	m_SceneComponent->LateUpdate(DeltaTime);

	list<Layer*>::iterator StartIter1 = m_LayerList.begin();
	list<Layer*>::iterator EndIter1 = m_LayerList.end();

	for (; StartIter1 != EndIter1; )
	{
		if ((*StartIter1)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter1));
			StartIter1 = m_LayerList.erase(StartIter1);
			continue;
		}
		else if ((*StartIter1)->GetIsShow() == false)
		{
			StartIter1++;
			continue;
		}

		(*StartIter1)->LateUpdate(DeltaTime);
		StartIter1++;
	}
	m_MainCameraObject->LateUpdate(DeltaTime);
	return 0;
}

void Scene::Collision(float DeltaTime)
{
	m_SceneComponent->Collision(DeltaTime);

	list<Layer*>::iterator StartIter1 = m_LayerList.begin();
	list<Layer*>::iterator EndIter1 = m_LayerList.end();

	for (; StartIter1 != EndIter1; )
	{
		if ((*StartIter1)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter1));
			StartIter1 = m_LayerList.erase(StartIter1);
			continue;
		}
		else if ((*StartIter1)->GetIsShow() == false)
		{
			StartIter1++;
			continue;
		}

		(*StartIter1)->Collision(DeltaTime);
		StartIter1++;
	}

	KeyInput::Get()->UpdateMousePos();
	CollsionManager::Get()->Collsion(DeltaTime);
}

void Scene::CollisionLateUpdate(float DeltaTime)
{
	m_SceneComponent->CollisionLateUpdate(DeltaTime);

	list<Layer*>::iterator StartIter1 = m_LayerList.begin();
	list<Layer*>::iterator EndIter1 = m_LayerList.end();

	for (; StartIter1 != EndIter1; )
	{
		if ((*StartIter1)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter1));
			StartIter1 = m_LayerList.erase(StartIter1);
			continue;
		}
		else if ((*StartIter1)->GetIsShow() == false)
		{
			StartIter1++;
			continue;
		}

		(*StartIter1)->CollisionLateUpdate(DeltaTime);
		StartIter1++;
	}
}

void Scene::Render(float DeltaTime)
{
	m_SceneComponent->Render(DeltaTime);

	if (m_WaveCBuffer.LiveTime > 0.0f)
		UpdateWaveCBuffer(DeltaTime);

	list<Layer*>::iterator StartIter1 = m_LayerList.begin();
	list<Layer*>::iterator EndIter1 = m_LayerList.end();

	for (; StartIter1 != EndIter1; )
	{
		if ((*StartIter1)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter1));
			StartIter1 = m_LayerList.erase(StartIter1);
			continue;
		}
		else if ((*StartIter1)->GetIsShow() == false)
		{
			StartIter1++;
			continue;
		}
		(*StartIter1)->Render(DeltaTime);
		StartIter1++;
	}
}

void Scene::AddLayer(const string & TagName, int ZOrder)
{
	Layer* newLayer = new Layer();
	newLayer->m_Scene = this;
	newLayer->SetTag(TagName);

	if (newLayer->Init() == false)
	{
		SAFE_RELEASE(newLayer);
		return;
	}

	m_LayerList.push_back(newLayer);
	newLayer->SetZOrder(ZOrder);
	SortLayer();
}

void Scene::ChangeLayerZOrder(const string & TagName, int ZOrder)
{
	list<Layer*>::iterator StartIter = m_LayerList.begin();
	list<Layer*>::iterator EndIter = m_LayerList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->SetZOrder(ZOrder);
			return;
		}
	}
}

void Scene::SortLayer()
{
	m_LayerList.sort(Scene::SortLayerFunc);
}

void Scene::SetEnableLayer(const string & TagName, bool isShow)
{
	list<Layer*>::iterator StartIter = m_LayerList.begin();
	list<Layer*>::iterator EndIter = m_LayerList.end();

	for (; StartIter != EndIter ; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->SetIsShow(isShow);
			return;
		}
	}
}

void Scene::SetLayerDie(const string & TagName, bool isActive)
{
	list<Layer*>::iterator StartIter = m_LayerList.begin();
	list<Layer*>::iterator EndIter = m_LayerList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
			(*StartIter)->SetIsActive(isActive);
	}
}

Layer * Scene::FindLayer(const string & TagName)
{
	list<Layer*>::iterator StartIter = m_LayerList.begin();
	list<Layer*>::iterator EndIter = m_LayerList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->AddRefCount();
			return (*StartIter);
		}
	}
	return NULLPTR;
}

Layer * Scene::FindLayerNoneCount(const string & TagName)
{
	list<Layer*>::iterator StartIter = m_LayerList.begin();
	list<Layer*>::iterator EndIter = m_LayerList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			return (*StartIter);
		}
	}
	return NULLPTR;
}

bool Scene::SortLayerFunc(const Layer * Src, const Layer * Dest)
{
	return Src->GetZOrder() < Dest->GetZOrder();
}

GameObject * Scene::FindObject(const string & TagName)
{
	list<Layer*>::iterator StartIter = m_LayerList.begin();
	list<Layer*>::iterator EndIter = m_LayerList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		GameObject* getObject = (*StartIter)->FindObject(TagName);

		if(getObject != NULLPTR)
			return getObject;
	}
	return NULLPTR;
}

GameObject * Scene::CreateCamera(const string & TagName, const Vector3 & Pos, CAMERA_TYPE eType, float Width, float Height, float ViewAngle, float Near, float Far)
{
	GameObject* newCameraObject = FindCamera(TagName);

	if (newCameraObject != NULLPTR)
		return newCameraObject;

	newCameraObject = GameObject::CreateObject(TagName);
	newCameraObject->GetTransform()->SetWorldPos(Pos);

	Camera_Com* newCameraCom = newCameraObject->AddComponent<Camera_Com>(TagName);
	newCameraCom->SetCameraInfo(eType, Width, Height, ViewAngle, Near, Far);
	SAFE_RELEASE(newCameraCom);

	newCameraObject->AddRefCount();

	m_CameraMap.insert(make_pair(TagName, newCameraObject));

	return newCameraObject;
}

void Scene::ChangeCamera(const string & TagName)
{
	GameObject* getCamera = FindCamera(TagName);

	if (getCamera == NULLPTR)
		return;

	SAFE_RELEASE(m_MainCamera);
	SAFE_RELEASE(m_MainCameraTransform);
	SAFE_RELEASE(m_MainCameraObject);

	m_MainCameraObject = getCamera;
	m_MainCameraTransform = getCamera->GetTransform();
	m_MainCamera = getCamera->FindComponentFromType<Camera_Com>(CT_CAMERA);
}

GameObject * Scene::FindCamera(const string & TagName)
{
	unordered_map<string, GameObject*>::iterator FindIter = m_CameraMap.find(TagName);

	if (FindIter == m_CameraMap.end())
		return NULLPTR;

	return FindIter->second;
}

void Scene::CreateWave(const Vector3 & Pos, float LiveTime, float Range)
{
	Vector3 pScreenPos;
	Vector3 cPos = m_MainCameraTransform->GetWorldPos();
	pScreenPos = Vector3(Pos.x, Pos.y, 0.0f) - cPos;

	m_WaveCBuffer.LiveTime = LiveTime;
	m_WaveCBuffer.InputUV.x = pScreenPos.x / m_WinSize.x;
	m_WaveCBuffer.InputUV.y = pScreenPos.y / m_WinSize.y;
	m_WaveCBuffer.Range = Range;
}

void Scene::UpdateWaveCBuffer(float DeltaTime)
{
	m_WaveCBuffer.LiveTime -= DeltaTime;
	m_WaveCBuffer.Range -= DeltaTime / 3.0f;

	ShaderManager::Get()->UpdateCBuffer("WaveCBuffer", &m_WaveCBuffer);

	if (m_WaveCBuffer.LiveTime <= 0.0f)
		m_WaveCBuffer.LiveTime = 0.0f;
}

void Scene::AfterInit()
{
	m_SceneComponent->AfterInit();
}

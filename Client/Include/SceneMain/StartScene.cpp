#include "ClientHeader.h"
#include "StartScene.h"
#include "GameObject.h"
#include "MainScene.h"
#include "LoadingScene.h"
#include "Device.h"

#include "Thread.h"
#include "ThreadManager.h"

#include "Scene/Scene.h"
#include "Scene/Layer.h"
#include "Scene/SceneManager.h"

#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Camera_Com.h"
#include "Component/ColliderRect_Com.h"
#include "Component/ColliderPixel_Com.h"
#include "Component/Material_Com.h"
#include "Component/Button_Com.h"
#include "Component/CheckBox_Com.h"
#include "Component/RadioButton_Com.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->SetNear(0.0f);

	Layer* Default = m_Scene->FindLayer("Default");
	Layer* UILayer = m_Scene->FindLayer("UI");

	GameObject* newButton = GameObject::CreateObject("StartButton", UILayer);
	newButton->GetTransform()->SetWorldPos(640.0f, 360.0f, 0.0f);
	newButton->GetTransform()->SetWorldScale(200.0f, 50.0f, 0.0f);

	Button_Com* buttonCom = newButton->AddComponent<Button_Com>("StartButton");
	buttonCom->SetCallBack(&StartScene::StartButtonActive, this);
	buttonCom->SetStateColor(BS_CLICK, Vector4::Red);
	buttonCom->SetStateColor(BS_MOUSEOVER, Vector4::White * 2.0f);

	GameObject* newCheck = GameObject::CreateObject("CheckBox", UILayer);
	newCheck->GetTransform()->SetWorldPos(300.0f, 360.0f, 0.0f);
	CheckBox_Com* CheckCom = newCheck->AddComponent<CheckBox_Com>("CheckBox");

	GameObject* newRadio = GameObject::CreateObject("CheckBox", UILayer);
	RadioButton_Com* RadioCom = newRadio->AddComponent<RadioButton_Com>("CheckBox");
	RadioCom->CreateRadioGroup("Group1", 30, 10, newRadio->GetTransform()->GetWorldPos());

	SAFE_RELEASE(newRadio);
	SAFE_RELEASE(RadioCom);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(newButton);
	SAFE_RELEASE(buttonCom);
	SAFE_RELEASE(mainCamera);
	SAFE_RELEASE(newCheck);
	SAFE_RELEASE(CheckCom);

	return true;
}

int StartScene::Input(float DeltaTime)
{
	return 0;
}

int StartScene::Update(float DeltaTime)
{
	return 0;
}

int StartScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void StartScene::Collision(float DeltaTime)
{

}

void StartScene::CollisionLateUpdate(float DeltaTime)
{

}

void StartScene::Render(float DeltaTime)
{

}

void StartScene::StartButtonActive(float DeltaTime)
{
	SceneManager::Get()->CreateNextScene();
	SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
}

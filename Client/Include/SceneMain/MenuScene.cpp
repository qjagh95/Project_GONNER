#include "ClientHeader.h"
#include "MenuScene.h"
#include "GameObject.h"
#include "MainScene.h"
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
#include "Component/BackColor_Com.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

bool MenuScene::Init()
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
	buttonCom->SetCallBack(&MenuScene::StartButtonActive, this);
	buttonCom->SetStateColor(BS_CLICK, Vector4::Red);
	buttonCom->SetStateColor(BS_MOUSEOVER, Vector4::White * 2.0f);

	GameObject* newColorObject = GameObject::CreateObject("BackColor", UILayer);
	BackColor_Com* newColorCom = newColorObject->AddComponent<BackColor_Com>("BackColor");

	Vector4 Color = ExcelManager::Get()->ReadVector4Data("BackColor", 0, 0);
	newColorCom->SetBackColor(Color);

	SAFE_RELEASE(newColorCom);
	SAFE_RELEASE(newColorObject);

	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(newButton);
	SAFE_RELEASE(buttonCom);
	SAFE_RELEASE(mainCamera);

	return true;
}

int MenuScene::Input(float DeltaTime)
{
	return 0;
}

int MenuScene::Update(float DeltaTime)
{
	return 0;
}

int MenuScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void MenuScene::Collision(float DeltaTime)
{

}

void MenuScene::CollisionLateUpdate(float DeltaTime)
{

}

void MenuScene::Render(float DeltaTime)
{

}

void MenuScene::StartButtonActive(float DeltaTime)
{
	SceneManager::Get()->CreateNextScene();
	SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
}

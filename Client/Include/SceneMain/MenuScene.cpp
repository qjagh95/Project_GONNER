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
#include "Component/BackColor_Com.h"

#include <UserComponent/Fade_Com.h>
#include <UserComponent/MenuLogo_Com.h>

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
	Layer* FadeLayer = m_Scene->FindLayer("Fade");
	Layer* UILayer = m_Scene->FindLayer("UI");

	GameObject* newButton = GameObject::CreateObject("StartButton", UILayer);
	newButton->GetTransform()->SetWorldPos(640.0f, 360.0f, 0.0f);
	newButton->GetTransform()->SetWorldScale(200.0f, 50.0f, 0.0f);

	Button_Com* buttonCom = newButton->AddComponent<Button_Com>("StartButton");
	buttonCom->SetCallBack(&MenuScene::StartButtonActive, this);
	buttonCom->SetStateColor(BS_CLICK, Vector4::Red);
	buttonCom->SetStateColor(BS_MOUSEOVER, Vector4::White * 2.0f);

	GameObject* newColorObject = GameObject::CreateObject("BackColor", UILayer, false);
	BackColor_Com* newColorCom = newColorObject->AddComponent<BackColor_Com>("BackColor");
	newColorCom->SetBackColor(Vector4(16.0f, 29.0f, 33.0f, 255.0f));

	GameObject* newLogoObject = GameObject::CreateObject("Logo", UILayer, false);
	MenuLogo_Com* newLogo = newLogoObject->AddComponent<MenuLogo_Com>("Logo");
	newLogoObject->GetTransform()->SetWorldPos(Device::Get()->GetWinSize().Width / 2.0f - 500.0f, Device::Get()->GetWinSize().Height - 400.0f, 0.0f);

	GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer, false);
	Fade_Com* newFadeCom = newFade->AddComponent<Fade_Com>("Fade");
	newFadeCom->SetFadeColor(Vector3(0.0f, 0.0f, 0.0f), FO_OUT);
	newFadeCom->Start();

	SAFE_RELEASE(newFade);
	SAFE_RELEASE(newFadeCom);
	SAFE_RELEASE(newColorCom);
	SAFE_RELEASE(newColorObject);
	SAFE_RELEASE(newLogo);
	SAFE_RELEASE(newLogoObject);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(FadeLayer);
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

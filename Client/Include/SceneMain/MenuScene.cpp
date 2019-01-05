#include "ClientHeader.h"
#include "MenuScene.h"
#include "GameObject.h"
#include "MainScene.h"
#include "Device.h"

#include "SoundManager.h"

#include <Core.h>

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

#include <UserComponent/MenuLogo_Com.h>
#include <UserComponent/MenuEnemy_Com.h>

#include <Component/Light_Com.h>

MenuScene::MenuScene()
{
	m_FadeCom = NULLPTR;
	SetTag("MenuScene");
}

MenuScene::~MenuScene()
{
	SAFE_RELEASE(m_FadeCom);
}

bool MenuScene::Init()
{
	m_isSelect = false;
	m_Index = 0;

	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->SetNear(0.0f);

	KeyInput::Get()->AddKey("ButtonUp", VK_UP);
	KeyInput::Get()->AddKey("ButtonDown", VK_DOWN);
	KeyInput::Get()->AddKey("ButtonEnter", VK_RETURN);
	KeyInput::Get()->AddKey("ButtonSpace", VK_SPACE);
	KeyInput::Get()->AddKey("0", VK_NUMPAD0);

	Vector2 WinSize = Device::Get()->GetWinSizeVector2();

	Layer* Default = m_Scene->FindLayer("Default");
	Layer* FadeLayer = m_Scene->FindLayer("Fade");
	Layer* UILayer = m_Scene->FindLayer("UI");

	GameObject* newColorObject = GameObject::CreateObject("BackColor", UILayer, false);
	BackColor_Com* newColorCom = newColorObject->AddComponent<BackColor_Com>("BackColor");
	newColorCom->SetBackColor(Vector4(16.0f, 29.0f, 33.0f, 255.0f));

	EnemyInit(UILayer);

	GameObject* newButton = GameObject::CreateObject("StartButton", UILayer);
	newButton->GetTransform()->SetWorldPos(WinSize.x / 2.0f, 400.0f, 0.0f);
	newButton->GetTransform()->SetWorldScale(100.0f, 30.0f, 0.0f);

	NButton_Com* buttonCom = newButton->AddComponent<NButton_Com>("StartButton");
	buttonCom->SetTexture("StartButton", TEXT("Button\\PlayOn_Kor-sharedassets1.assets-48.png"));
	buttonCom->SetCallBack(&MenuScene::StartButtonActive, this);
	buttonCom->SetStateColor(BS_MOUSEOVER, Vector4::White * 1.3f);
	buttonCom->SetStateColor(BS_NORMAL, Vector4::White * 0.7f);
	buttonCom->SetSaveScale(Vector3(100.0f, 30.0f, 1.0f));

	m_vecButton.push_back(buttonCom);

	GameObject* newButton2 = GameObject::CreateObject("ExitButton", UILayer);
	newButton2->GetTransform()->SetWorldPos(WinSize.x / 2.0f, 300.0f, 0.0f);
	newButton2->GetTransform()->SetWorldScale(50.0f, 30.0f, 1.0f);

	NButton_Com* buttonCom2 = newButton2->AddComponent<NButton_Com>("ExitButton");
	buttonCom2->SetTexture("ExitButton", TEXT("Button\\ExitOn_Kor-sharedassets1.assets-38.png"));
	buttonCom2->SetCallBack(&MenuScene::ExitButtonActive, this);
	buttonCom2->SetStateColor(BS_MOUSEOVER, Vector4::White * 1.3f);
	buttonCom2->SetStateColor(BS_NORMAL, Vector4::White * 0.7f);
	buttonCom2->SetSaveScale(Vector3(50.0f, 30.0f, 1.0f));

	m_vecButton.push_back(buttonCom2);

	GameObject* newLogoObject = GameObject::CreateObject("Logo", UILayer, false);
	MenuLogo_Com* newLogo = newLogoObject->AddComponent<MenuLogo_Com>("Logo");
	newLogoObject->GetTransform()->SetWorldPos(Device::Get()->GetWinSize().Width / 2.0f - 500.0f, Device::Get()->GetWinSize().Height - 400.0f, 0.0f);

	GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer, false);
	Fade_Com* newFadeCom = newFade->AddComponent<Fade_Com>("Fade");
	newFadeCom->SetFadeColor(Vector3(0.0f, 0.0f, 0.0f), FO_OUT);
	newFadeCom->Start();

	SAFE_RELEASE(newFadeCom);
	SAFE_RELEASE(newButton2);
	SAFE_RELEASE(buttonCom2);
	SAFE_RELEASE(newFade);
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
	int PrevIndex = m_Index;

	m_vecButton[PrevIndex]->LightOff();

	if(KeyInput::Get()->KeyDown("ButtonDown"))
	{
		if (m_isSelect == true)
			return 0;

		SoundManager::Get()->FindSoundEffect("Button")->Play();

		m_Index++;

		if (m_Index == m_vecButton.size())
			m_Index = 0;
	}

	if (KeyInput::Get()->KeyDown("ButtonUp"))
	{
		if (m_isSelect == true)
			return 0;

		SoundManager::Get()->FindSoundEffect("Button")->Play();

		m_Index--;

		if (m_Index < 0)
			m_Index = (int)m_vecButton.size() - 1;
	}

	if (KeyInput::Get()->KeyDown("ButtonSpace"))
	{
		if (m_isSelect == true)
		{
			SoundManager::Get()->FindSoundEffect("Button")->Play();
			return 0;
		}

		m_isSelect = true;
		m_vecButton[m_Index]->ActiveFunction(DeltaTime);
	}

	if (KeyInput::Get()->KeyDown("ButtonEnter"))
	{
		if (m_isSelect == true)
		{
			SoundManager::Get()->FindSoundEffect("Button")->Play();
			return 0;
		}

		m_isSelect = true;
		SoundManager::Get()->FindSoundEffect("Button")->Play();
		m_vecButton[m_Index]->ActiveFunction(DeltaTime);
	}

	m_vecButton[m_Index]->LightOn();

	return 0;
}

int MenuScene::Update(float DeltaTime)
{
	if (m_FadeCom != NULLPTR && m_FadeCom->GetIsOver() == true)
	{
		SceneManager::Get()->CreateNextScene();
		SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
	}
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
	Layer* FadeLayer = m_Scene->FindLayer("Fade");
	GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer, false);
	m_FadeCom = newFade->AddComponent<Fade_Com>("Fade");
	m_FadeCom->SetFadeColor(Vector3::Zero, FO_IN);
	m_FadeCom->Start();

#ifdef _DEBUG
	SceneManager::Get()->CreateNextScene();
	SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
#endif

	SAFE_RELEASE(FadeLayer);
	SAFE_RELEASE(newFade);
}

void MenuScene::ExitButtonActive(float DeltaTime)
{
	Core::Get()->ShotDown();
}

void MenuScene::EnemyInit(Layer * UILayer)
{
	Vector2 DevicePos;
	DevicePos.x = (float)Device::Get()->GetWinSize().Width;
	DevicePos.y = (float)Device::Get()->GetWinSize().Height;

	for (size_t y = 0; y < 11; y++)
	{
		for (size_t x = 0; x < 15; x++)
		{
			int Ran = RandomRange(ME_M1, ME_M15);
			float RanRot = (float)RandomRange(-5, 10);
			int RanDir = RandomRange(MD_LEFT, MD_RIGHT);
			float RanX = (float)RandomRange(0, 100);
			float RanY = (float)RandomRange(0, 40);

			GameObject* newEnemyObject = GameObject::CreateObject("Enemy", UILayer);
			MenuEnemy_Com* newEnemy = newEnemyObject->AddComponent<MenuEnemy_Com>("Enemy");
			newEnemy->SetEnemyType((MENU_ENEMY_TYPE)Ran, Vector3(x * 128.0f + RanX, y * 128.0f + RanY, 0.0f), (MOVE_DIR)RanDir, RanRot);

			SAFE_RELEASE(newEnemyObject);
			SAFE_RELEASE(newEnemy);
		}
	}

}

#include "ClientHeader.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "StaticTestScene.h"
#include "GameObject.h"

#include "Thread.h"
#include "ThreadManager.h"

#include "Scene/Scene.h"
#include "scene/Layer.h"

#include "Component/Component_Base.h"
#include "Component/ColliderPixel_Com.h"
#include "Component/Button_Com.h"
#include "Component/UICon_Com.h"
#include "Component/IconSlot_Com.h"
#include "Component/Stage2D_Com.h"
#include "Component/Tile2D_Com.h"
#include "Component/CheckBox_Com.h"
#include "Component/BackColor_Com.h"
#include "Component/Gravity_Com.h"

#include "../UserComponent/Gonner_Com.h"
#include "UserComponent/BubbleEffect_Com.h"
#include "UserComponent/GunItem_Com.h"
#include "UserComponent/HeartItem_Com.h"
#include "UserComponent/LifeItem_Com.h"
#include <UserComponent/GuardM_Com.h>

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

bool MainScene::Init()
{
	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->GetTransform()->SetWorldPos(Vector3(0.0f, 500.0f, 0.0f));
	mainCamera->SetCameraPosInfo(Vector3(5000.0f, 3000.0f, 0.0f));
	mainCamera->SetNear(0.0f);

	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* Default = m_Scene->FindLayer("Default");
	Layer* FadeLayer = m_Scene->FindLayer("Fade");
	Layer* UILayer = m_Scene->FindLayer("UI");
	Layer* TileLayer = m_Scene->FindLayer("Tile");

	GameObject* BackObject = GameObject::CreateObject("BackObject", BackLayer);
	BackColor_Com* BackCom = BackObject->AddComponent<BackColor_Com>("BackColor");
	BackCom->SetBackColor(ExcelManager::Get()->ReadVector4Data("BackColor", 0, 0));

	BineryRead Reader = BineryRead("TileInfo.tInfo");

	GameObject*	pStageObj = GameObject::CreateObject("StageObj", TileLayer);
	Stage2D_Com* pStage = pStageObj->AddComponent<Stage2D_Com>("Stage");
	pStage->Load(Reader);

#ifdef _DEBUG
	pStage->SetLineOn(true);
#else
	pStage->SetLineOn(false);
#endif

	StageManager::Get()->SetStageName("FirstStage");
	StageManager::Get()->InsertStage(pStage);

	GameObject* GonnerObject = GameObject::CreateObject("Gonner", Default, true);
	if (GonnerObject->EmptyComponent() == true)
	{
		Gonner_Com* gonner_Com = GonnerObject->AddComponent<Gonner_Com>("GonnerCom");
		gonner_Com->SetStage(pStage);
		SAFE_RELEASE(gonner_Com);
	}

	GameObject* gunItemObject = GameObject::CreateObject("GunItem", Default);
	GunItem_Com* gunItemCom = gunItemObject->AddComponent<GunItem_Com>("GunItem");
	gunItemObject->GetTransform()->SetWorldPos(300.0f, 800.0f, 1.0f);

	GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer, false);
	Fade_Com* newFadeCom = newFade->AddComponent<Fade_Com>("Fade");
	newFadeCom->SetFadeColor(Vector3(0.0f, 0.0f, 0.0f), FO_OUT);
	newFadeCom->Start();

	GameObject* heartItemObject = GameObject::CreateObject("HeartItem", Default);
	HeartItem_Com* heartItemCom = heartItemObject->AddComponent<HeartItem_Com>("HeartItem");
	heartItemObject->GetTransform()->SetWorldPos(500.0f, 800.0f, 1.0f);

	GameObject* LifeItemObject = GameObject::CreateObject("LifeItem", Default);
	LifeItem_Com* LifeItemCom = LifeItemObject->AddComponent<LifeItem_Com>("LifeItem");
	LifeItemObject->GetTransform()->SetWorldPos(600.0f, 800.0f, 1.0f);

	GameObject* GuardObject = GameObject::CreateObject("Guard", Default);
	GuardM_Com* GuardCom = GuardObject->AddComponent<GuardM_Com>("Guard");
	GuardObject->GetTransform()->SetWorldPos(900.0f, 1000.0f, 1.0f);
	GuardM_Com::m_Target = GonnerObject;

	SAFE_RELEASE(GuardObject);
	SAFE_RELEASE(GuardCom);
	SAFE_RELEASE(LifeItemObject);
	SAFE_RELEASE(LifeItemCom);
	SAFE_RELEASE(heartItemObject);
	SAFE_RELEASE(heartItemCom);
	SAFE_RELEASE(newFade);
	SAFE_RELEASE(newFadeCom);
	SAFE_RELEASE(gunItemCom);
	SAFE_RELEASE(gunItemObject);
	SAFE_RELEASE(BackCom);
	SAFE_RELEASE(BackObject);
	SAFE_RELEASE(pStage);
	SAFE_RELEASE(pStageObj);
	SAFE_RELEASE(mainCamera);
	SAFE_RELEASE(GonnerObject);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(FadeLayer);

#ifdef _DEBUG
#else
	auto findSound = SoundManager::Get()->FindSoundEffectInstance("LogoBGM");
	findSound->Stop();
#endif

	auto newSound = SoundManager::Get()->FindSoundEffect("StageBGM1")->CreateInstance();
	newSound->Play(true);
	SoundManager::Get()->CreateBGMList("StageBGM1", move(newSound));

	return true;
}

int MainScene::Input(float DeltaTime)
{
	if (GetAsyncKeyState(VK_HOME) & 0x8000)
	{
		SceneManager::Get()->CreateNextScene();
		SceneManager::Get()->AddSceneComponent<StaticTestScene>("StaticTestScene", false);
	}

	return 0;
}

int MainScene::Update(float DeltaTime)
{
	return 0;
}

int MainScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void MainScene::Collision(float DeltaTime)
{
}

void MainScene::CollisionLateUpdate(float DeltaTime)
{
}

void MainScene::Render(float DeltaTime)
{
}

//나중추가
void MainScene::Load()
{
}

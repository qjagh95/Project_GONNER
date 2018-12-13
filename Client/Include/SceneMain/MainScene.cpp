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

#include "../UserComponent/Player_Com.h"
#include "../UserComponent/Bullet_Com.h"
#include "../UserComponent/BulletRot_Com.h"
#include "../UserComponent/BulletBoom_Com.h"

#include "../UserComponent/Monster_Com.h"
#include <UserComponent/Fade_Com.h>


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
	mainCamera->SetCameraPosInfo(Vector3(5000.0f, 5000.0f, 0.0f), 300.0f);
	mainCamera->SetNear(0.0f);

	KeyInput::Get()->SetShowCursor(false);

	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* Default = m_Scene->FindLayer("Default");
	Layer* UILayer = m_Scene->FindLayer("UI");
	Layer* TileLayer = m_Scene->FindLayer("Tile");

	GameObject* BackObject = GameObject::CreateObject("BackObject", BackLayer);
	BackColor_Com* BackCom = BackObject->AddComponent<BackColor_Com>("BackColor");
	BackCom->SetBackColor(ExcelManager::Get()->ReadVector4Data("BackColor", 0, 0));

	ExcelManager::Get()->ReadVector4Data("BaclColor", 0, 0);

	SAFE_RELEASE(BackCom);
	SAFE_RELEASE(BackObject);

	BineryRead Reader = BineryRead("TileInfo.tInfo");

	GameObject*	pStageObj = GameObject::CreateObject("StageObj", TileLayer);
	Stage2D_Com* pStage = pStageObj->AddComponent<Stage2D_Com>("Stage");
	pStage->Load(Reader);
	pStage->SetLineOn(false);

	SAFE_RELEASE(pStage);
	SAFE_RELEASE(pStageObj);

	GameObject* MonsterObject = GameObject::CreateObject("Monster", Default);
	Monster_Com* monster_Com = MonsterObject->AddComponent<Monster_Com>("Monster_Com");
	SAFE_RELEASE(MonsterObject);
	SAFE_RELEASE(monster_Com);

	GameObject* PlayerObject = GameObject::CreateObject("Player", Default, true);
	if (PlayerObject->EmptyComponent() == true)
	{
		Player_Com* player_Com = PlayerObject->AddComponent<Player_Com>("Player_Com");
		SAFE_RELEASE(player_Com);
	}

	mainCamera->SetTarget(PlayerObject);

	SAFE_RELEASE(mainCamera);
	SAFE_RELEASE(PlayerObject);

	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(BackLayer);

	return true;
}

int MainScene::Input(float DeltaTime)
{
	////루프
	//if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	//{
	//	auto sound_effect_instance = SoundManager::Get()->FindSoundEffect("BGM")->CreateInstance();
	//	sound_effect_instance->Play(true);
	//	SoundManager::Get()->CreateBGMList("BGM", move(sound_effect_instance));
	//}

	////단발
	//if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
	//	SoundManager::Get()->FindSoundEffect("Effect")->Play();

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
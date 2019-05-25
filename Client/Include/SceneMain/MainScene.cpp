#include "ClientHeader.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "SecondScene.h"

#include <GameObject.h>
#include <ObjectManager.h>

#include <Scene/Scene.h>
#include <Scene/Layer.h>

#include <Component/Component_Base.h>
#include <Component/ColliderPixel_Com.h>
#include <Component/Button_Com.h>
#include <Component/UICon_Com.h>
#include <Component/IconSlot_Com.h>
#include <Component/Stage2D_Com.h>
#include <Component/Tile2D_Com.h>
#include <Component/CheckBox_Com.h>
#include <Component/BackColor_Com.h>
#include <Component/Gravity_Com.h>

#include "UserComponent/Gonner_Com.h"
#include "UserComponent/BubbleEffect_Com.h"
#include "UserComponent/GunItem_Com.h"
#include "UserComponent/HeartItem_Com.h"
#include "UserComponent/LifeItem_Com.h"
#include "UserComponent/SnakeHead_Com.h"
#include "UserComponent/SnakeBody_Com.h"
#include "UserComponent/SnekeTail_Com.h"

#include <UserComponent/GuardM_Com.h>
#include <UserComponent/BasicM_Com.h>
#include <UserComponent/AirDownM_Com.h>
#include <UserComponent/TraceM_Com.h>
#include <UserComponent/ReflectM_Com.h>

MainScene::MainScene()
{
	SetTag("MainScene");
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
	Layer* AfterEffect = m_Scene->FindLayer("AfterEffectLayer");

	GameObject* BackObject = GameObject::CreateObject("BackObject", BackLayer);
	BackColor_Com* BackCom = BackObject->AddComponent<BackColor_Com>("BackColor");
	BackCom->SetBackColor(ExcelManager::Get()->ReadVector4Data("BackColor", 0, 0));

	BineryRead Reader = BineryRead("TileInfo.tInfo");

	GameObject*	pStageObj = GameObject::CreateObject("StageObj", TileLayer);
	Stage2D_Com* pStage = pStageObj->AddComponent<Stage2D_Com>("Stage1");
	pStage->Load(Reader);

#ifdef _DEBUG
	pStage->SetLineOn(true);
#else
	pStage->SetLineOn(false);
#endif

	GameObject* GonnerObject = GameObject::CreateObject("Gonner", Default, true);
	Gonner_Com* gonner_Com = GonnerObject->AddComponent<Gonner_Com>("GonnerCom");
	CountManager::Get()->m_Gonner = gonner_Com;
	SAFE_RELEASE(gonner_Com);

	mainCamera->SetTarget(GonnerObject);

	GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer);
	Fade_Com* newFadeCom = newFade->AddComponent<Fade_Com>("Fade");
	newFadeCom->SetFadeColor(Vector3(0.0f, 0.0f, 0.0f), FO_OUT);
	newFadeCom->SetFadeSpeed(0.6f);
	newFadeCom->Start();

	GameObject* gunItemObject = GameObject::CreateObject("GunItem", Default);
	GunItem_Com* gunItemCom = gunItemObject->AddComponent<GunItem_Com>("GunItem");
	gunItemObject->GetTransform()->SetWorldPos(1306.0f, 1186.0f, 1.0f);

	GameObject* heartItemObject = GameObject::CreateObject("HeartItem", Default);
	HeartItem_Com* heartItemCom = heartItemObject->AddComponent<HeartItem_Com>("HeartItem");
	heartItemObject->GetTransform()->SetWorldPos(3075.0f, 1473.0f, 1.0f);

	GameObject* LifeItemObject = GameObject::CreateObject("LifeItem", Default);
	LifeItem_Com* LifeItemCom = LifeItemObject->AddComponent<LifeItem_Com>("LifeItem");
	LifeItemObject->GetTransform()->SetWorldPos(1406.0f, 1186.0f, 1.0f);
	
	Load(Default, GonnerObject);

	GameObject* SnakeObject = GameObject::CreateObject("Head", AfterEffect);
	SnakeHead_Com* SnakeHead = SnakeObject->AddComponent<SnakeHead_Com>("Head");
	SnakeHead->GetTransform()->SetWorldPos(Vector3(5012.0f - 430.0f, 830.0f, 1.0f));
	SnakeHead->SetNextStageTag("Stage2");
	SnakeHead->SetPlayerChangePos(Vector3(Vector3(524.0f, 2000.0f, 1.0f)));

	for (size_t i = 0; i < 20; i++)
	{
		GameObject* SnakeObject = GameObject::CreateObject("Head", AfterEffect);
		SnakeBody_Com* SnakeBody = SnakeObject->AddComponent<SnakeBody_Com>("Head");
		SnakeBody->SetPosRange(Vector3(5012.0f - 430.0f, 740.0f - i * 70.0f, 1.0f), (i + 1) * 2.0f);

		SAFE_RELEASE(SnakeObject);
		SAFE_RELEASE(SnakeBody);
	}

	SAFE_RELEASE(SnakeObject);
	SAFE_RELEASE(SnakeHead);
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
	SAFE_RELEASE(AfterEffect);

//#ifdef _DEBUG
//#else
//	auto findSound = SoundManager::Get()->FindSoundEffectInstance("LogoBGM");
//	findSound->Stop();
//#endif

	//auto newSound = SoundManager::Get()->FindSoundEffect("StageBGM1")->CreateInstance();
	//newSound->Play(true);
	//SoundManager::Get()->CreateBGMList("StageBGM1", move(newSound));
	//
	m_BgmName = "StageBGM1";

	return true;
}

int MainScene::Input(float DeltaTime)
{
	if (GetAsyncKeyState(VK_HOME) & 0x8000)
	{
		GameObject* getGonner = ObjectManager::Get()->FindDontDestroyObject("Gonner");
		getGonner->GetTransform()->SetWorldPos(Vector3(524.0f, 2000.0f, 1.0f));

		Gonner_Com* getCom = getGonner->FindComponentFromTypeNoneCount<Gonner_Com>(CT_GONNER);
		getCom->ChangeState(GS_IDLE, getCom->GetAniName(), getCom->GetAnimation());

		SceneManager::Get()->ChangeScene("Stage2");
	}

	return 0;
}

int MainScene::Update(float DeltaTime)
{
#ifdef _DEBUG
#else
	if (m_isBgmStart == false)
	{
		auto findSound = SoundManager::Get()->FindSoundEffectInstance("LogoBGM");
		findSound->Stop();
	}
#endif
	SceneComponent::Update(DeltaTime);


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

void MainScene::Load(Layer* Default, GameObject* GonnerObject)
{
	BineryRead Reader("OneData.data");

	size_t vecSize;
	Reader.ReadData(vecSize);

	for (size_t i = 0; i < vecSize; i++)
	{
		int type;
		Reader.ReadData(type);

		int Dir;
		Reader.ReadData(Dir);

		Vector3 Pos;
		Reader.ReadData(Pos);

		switch (type)
		{
		case MT_GUARD:
		{
			GameObject* newObject = GameObject::CreateObject("Guard", Default);
			GuardM_Com* newGuard = newObject->AddComponent<GuardM_Com>("Guard");
			newObject->GetTransform()->SetWorldPos(Pos);
			GuardM_Com::m_Target = GonnerObject;

			SAFE_RELEASE(newGuard);
			SAFE_RELEASE(newObject);
		}
		break;
		case MT_TRACE:
		{
			GameObject* newObject = GameObject::CreateObject("Trace", Default);
			TraceM_Com* newTrace = newObject->AddComponent<TraceM_Com>("Trace");
			newObject->GetTransform()->SetWorldPos(Pos);
			TraceM_Com::m_Target = GonnerObject;

			SAFE_RELEASE(newTrace);
			SAFE_RELEASE(newObject);

		}
		break;
		case MT_BASIC:
		{
			GameObject* newObject = GameObject::CreateObject("Basic", Default);
			BasicM_Com* newBasic = newObject->AddComponent<BasicM_Com>("Basic");
			newObject->GetTransform()->SetWorldPos(Pos);
			BasicM_Com::m_Target = GonnerObject;

			SAFE_RELEASE(newBasic);
			SAFE_RELEASE(newObject);
		}
		break;
		case MT_AIRDOWN:
		{
			GameObject* newObject = GameObject::CreateObject("AirDown", Default);
			AirDownM_Com* newAirDown = newObject->AddComponent<AirDownM_Com>("AirDown");
			newAirDown->SetPos(Pos);
			AirDownM_Com::m_Target = GonnerObject;

			SAFE_RELEASE(newAirDown);
			SAFE_RELEASE(newObject);
		}
		break;
		case MT_REFLECT:
		{
			GameObject* newObject = GameObject::CreateObject("Reflect", Default);
			ReflectM_Com* newReflect = newObject->AddComponent<ReflectM_Com>("Reflect");
			newObject->GetTransform()->SetWorldPos(Pos);
			ReflectM_Com::m_Target = GonnerObject;

			SAFE_RELEASE(newReflect);
			SAFE_RELEASE(newObject);
		}
		break;
		}
	}
}

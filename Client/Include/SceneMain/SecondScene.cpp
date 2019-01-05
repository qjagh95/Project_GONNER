#include "ClientHeader.h"
#include "SecondScene.h"
#include "MainScene.h"
#include "UserComponent/Gonner_Com.h"

#include "MenuScene.h"
#include "SecondScene.h"
#include "GameObject.h"

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


SecondScene::SecondScene()
{
	SetTag("SecondScene");
}

SecondScene::~SecondScene()
{
}

bool SecondScene::Init()
{
	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->GetTransform()->SetWorldPos(Vector3(0.0f, 500.0f, 0.0f));
	mainCamera->SetCameraPosInfo(Vector3(6000.0f, 3000.0f, 0.0f));
	mainCamera->SetNear(0.0f);

	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* Default = m_Scene->FindLayer("Default");
	Layer* FadeLayer = m_Scene->FindLayer("Fade");
	Layer* UILayer = m_Scene->FindLayer("UI");
	Layer* TileLayer = m_Scene->FindLayer("Tile");
	Layer* AfterEffect = m_Scene->FindLayer("AfterEffectLayer");
	Layer* PrevEffect = m_Scene->FindLayer("PrevEffectLayer");

	GameObject* BackObject = GameObject::CreateObject("BackObject", BackLayer);
	BackColor_Com* BackCom = BackObject->AddComponent<BackColor_Com>("BackColor");
	BackCom->SetBackColor(ExcelManager::Get()->ReadVector4Data("BackColor", 0, 0));

	BineryRead Reader = BineryRead("TileInfo2.tInfo");

	GameObject*	pStageObj = GameObject::CreateObject("StageObj", TileLayer);
	Stage2D_Com* pStage = pStageObj->AddComponent<Stage2D_Com>("Stage");
	pStage->Load(Reader);

#ifdef _DEBUG
	pStage->SetLineOn(true);
#else
	pStage->SetLineOn(false);
#endif

	StageManager::Get()->SetStageName("SecondStage");
	StageManager::Get()->InsertStage(pStage);

	GameObject* getGonnerObject = StaticManager::Get()->FindStaticObject("Gonner");

	GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer);
	Fade_Com* newFadeCom = newFade->AddComponent<Fade_Com>("Fade");
	newFadeCom->SetFadeColor(Vector3(0.0f, 0.0f, 0.0f), FO_OUT);
	newFadeCom->SetFadeSpeed(0.6f);
	newFadeCom->Start();

	GameObject* getGonner = StaticManager::Get()->FindStaticObject("Gonner");
	getGonner->GetTransform()->SetWorldPos(Vector3(524.0f, 2000.0f, 1.0f));
	Gonner_Com* getCom = getGonner->FindComponentFromTypeNoneCount<Gonner_Com>(CT_GONNER);
	getCom->ChangeState(GS_IDLE, getCom->GetAniName(), getCom->GetAnimation());
	getCom->SetStage(pStage);
	mainCamera->SetTarget(getCom);

	Load(Default, getGonnerObject);

	GameObject* SnakeObject = GameObject::CreateObject("Head", AfterEffect);
	SnakeHead_Com* SnakeHead = SnakeObject->AddComponent<SnakeHead_Com>("Head");
	SnakeHead->GetTransform()->SetWorldPos(Vector3(5012.0f - 720.0f, 1888.0f - 720.0f, 1.0f));
	SnakeHead_Com::m_isNext = false;

	for (size_t i = 0; i < 20; i++)
	{
		GameObject* SnakeObject = GameObject::CreateObject("Head", AfterEffect);
		SnakeBody_Com* SnakeBody = SnakeObject->AddComponent<SnakeBody_Com>("Head");
		SnakeBody->SetPosRange(Vector3(5012.0f, 1828.0f - (i + 1) * 70.0f, 1.0f), (i + 1) * 2.0f);

		SAFE_RELEASE(SnakeObject);
		SAFE_RELEASE(SnakeBody);
	}

	SAFE_RELEASE(SnakeObject);
	SAFE_RELEASE(SnakeHead);
	SAFE_RELEASE(newFade);
	SAFE_RELEASE(newFadeCom);
	SAFE_RELEASE(BackCom);
	SAFE_RELEASE(BackObject);
	SAFE_RELEASE(pStage);
	SAFE_RELEASE(pStageObj);
	SAFE_RELEASE(mainCamera);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(FadeLayer);
	SAFE_RELEASE(AfterEffect);

	return true;
}

int SecondScene::Input(float DeltaTime)
{
	return 0;
}

int SecondScene::Update(float DeltaTime)
{

	return 0;
}

int SecondScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void SecondScene::Collision(float DeltaTime)
{
}

void SecondScene::CollisionLateUpdate(float DeltaTime)
{
}

void SecondScene::Render(float DeltaTime)
{
}

void SecondScene::Load(Layer * Default, GameObject * GonnerObject)
{
	//º¹ºÙ
	BineryRead Reader("SecondData.data");

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

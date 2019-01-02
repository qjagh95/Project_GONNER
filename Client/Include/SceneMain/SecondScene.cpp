#include "ClientHeader.h"
#include "SecondScene.h"
#include "MainScene.h"
#include "UserComponent/Gonner_Com.h"

SecondScene::SecondScene()
{
}

SecondScene::~SecondScene()
{
}

bool SecondScene::Init()
{
	//Layer* Default = m_Scene->FindLayer("Default");
	//Layer* UILayer = m_Scene->FindLayer("UI");
	//Layer* StageLayer = m_Scene->FindLayer("Tile");

	//GameObject* PlayerObject = GameObject::CreateObject("Player", Default, true);

	//if (PlayerObject->EmptyComponent())
	//{
	//	Player_Com* player_Com = PlayerObject->AddComponent<Player_Com>("Player_Com");
	//	SAFE_RELEASE(player_Com);
	//}

	//SAFE_RELEASE(Default);
	//SAFE_RELEASE(StageLayer);
	//SAFE_RELEASE(UILayer);

	return true;
}

int SecondScene::Input(float DeltaTime)
{
	return 0;
}

int SecondScene::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_NEXT) & 0x8000)
	{
		SceneManager::Get()->CreateNextScene();
		SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
	}

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

#include "ClientHeader.h"
#include "LogoScene.h"
#include <Component/BackColor_Com.h>

#include <UserComponent/LogoAlphaBat_Com.h>


#include <SceneMain/MenuScene.h>

LogoScene::LogoScene()
{
	m_NextTime = 8.0f;
	m_NextTimeVar = 0.0f;
	m_FadeCom = NULLPTR;
}

LogoScene::~LogoScene()
{
	SAFE_RELEASE(m_FadeCom);
}

bool LogoScene::Init()
{
	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->SetNear(0.0f);

	Layer* UILayer = m_Scene->FindLayer("UI");

	GameObject* newColorObject = GameObject::CreateObject("BackColor", UILayer);
	BackColor_Com* newColorCom = newColorObject->AddComponent<BackColor_Com>("BackColor");
	
	Vector4 Color = ExcelManager::Get()->ReadVector4Data("BackColor", 0, 0);
	newColorCom->SetBackColor(Color);

	AlphaBatInit(UILayer);

	SAFE_RELEASE(newColorCom);
	SAFE_RELEASE(newColorObject);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(mainCamera);

	//·çÇÁ
	auto LogoBGM = SoundManager::Get()->FindSoundEffect("LogoBGM")->CreateInstance();
	LogoBGM->Play(true);
	SoundManager::Get()->CreateBGMList("LogoBGM", move(LogoBGM));

	return true;
}

int LogoScene::Input(float DeltaTime)
{
	return 0;
}

int LogoScene::Update(float DeltaTime)
{
	m_NextTimeVar += DeltaTime;

	Layer* FadeLayer = m_Scene->FindLayer("Fade");

	if (m_NextTimeVar >= m_NextTime)
	{
		m_NextTimeVar = 0.0f;

		GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer);
		m_FadeCom = newFade->AddComponent<Fade_Com>("Fade");
		m_FadeCom->SetFadeColor(Vector3(0.0f, 0.0f, 0.0f), FO_IN);
		m_FadeCom->Start();

		SAFE_RELEASE(newFade);

	}
	SAFE_RELEASE(FadeLayer);

	if (m_FadeCom != NULLPTR && m_FadeCom->GetIsOver() == true)
		SceneManager::Get()->ChangeScene("MenuScene");

	return 0;
}

int LogoScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void LogoScene::Collision(float DeltaTime)
{
}

void LogoScene::CollisionLateUpdate(float DeltaTime)
{
}

void LogoScene::Render(float DeltaTime)
{
}

void LogoScene::AlphaBatInit(Layer* layer)
{
	Vector2 WinSize;
	WinSize.x = (float)Device::Get()->GetWinSize().Width;
	WinSize.y = (float)Device::Get()->GetWinSize().Height;

	GameObject* newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	LogoAlphaBat_Com* newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	Vector3 Scale = newAlphaBat->GetTransform()->GetWorldScale();
	newLogoAlpha->SetLogoAlphaBat(LA_A);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - (Scale.x * 2.5f) + 30.0f, WinSize.y / 2.0f + (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_R);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - (Scale.x * 1.5f + 30.0f) + 30.0f, WinSize.y / 2.0f + (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_T);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - Scale.x - 20.0f + 30.0f, WinSize.y / 2.0f + (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_SPACAL);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - 100.0f + 30.0f, WinSize.y / 2.0f + (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_I);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f + 30.0f, WinSize.y / 2.0f + (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_N);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f + 70.0f + 30.0f, WinSize.y / 2.0f + (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_H);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - (Scale.x * 2.5f) + 30.0f, WinSize.y / 2.0f - (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_E);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - (Scale.x * 1.5f + 30.0f) + 30.0f, WinSize.y / 2.0f - (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_A);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - Scale.x - 20.0f + 30.0f, WinSize.y / 2.0f - (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_R);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f - 100.0f + 30.0f, WinSize.y / 2.0f - (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);

	newAlphaBat = GameObject::CreateObject("AlphaBat", layer);
	newLogoAlpha = newAlphaBat->AddComponent<LogoAlphaBat_Com>("AlphaBat");
	newLogoAlpha->SetLogoAlphaBat(LA_T);
	newLogoAlpha->GetTransform()->SetWorldPos(WinSize.x / 2.0f + 30.0f, WinSize.y / 2.0f - (Scale.y / 2.0f) - 50.0f, 0.0f);

	SAFE_RELEASE(newAlphaBat);
	SAFE_RELEASE(newLogoAlpha);
}

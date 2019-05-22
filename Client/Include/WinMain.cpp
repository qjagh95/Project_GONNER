#include "ClientHeader.h"
#include "Core.h"
#include "resource.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

#include "SceneMain/MainScene.h"
#include "SceneMain/LogoScene.h"
#include "SceneMain/MenuScene.h"
#include "SceneMain/SecondScene.h"

JEONG_USING

int APIENTRY wWinMain(_In_ HINSTANCE hIstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	if (Core::Get()->Init(hIstance, 1920, 1080, TEXT("JeongRealEngine"), TEXT("JeongRealEngine"), IDI_ICON1, IDI_ICON1, false) == false)
	{
		Core::Delete();
		return 0;
	}	
	Core::Get()->m_isEditor = false;
	//DLL���� ������ �̱��水ü�� ���⼭ ������ �̱��水ü�� ���� �ٸ���ü��.

	Core::Get()->SetGameMode(GM_2D);

	//MainScene�߰�
#ifdef _DEBUG
	SceneManager::Get()->AddScene<MenuScene>("MenuScene", "MenuScene");
	SceneManager::Get()->AddScene<MainScene>("Stage1", "Stage1");
	SceneManager::Get()->AddScene<SecondScene>("Stage2", "Stage2");

#else
	SceneManager::Get()->AddScene<LogoScene>("LogoScene", "LogoScene");
	SceneManager::Get()->AddScene<MenuScene>("MenuScene", "MenuScene");
	SceneManager::Get()->AddScene<MainScene>("Stage1", "Stage1");
	SceneManager::Get()->AddScene<SecondScene>("Stage2", "Stage2");
#endif
	//Run���� �޼��� ���ѷ�����(����) ����.
	//������ Delete, Result = 0
	//�̱��� ����

	int Result = Core::Get()->Run();
	Core::Delete();

	return Result;
}
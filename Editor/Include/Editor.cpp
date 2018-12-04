
// PunRealEditor.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "EditorHeader.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Editor.h"
#include "MainFrame.h"

#include "EditorDoc.h"
#include "EditorView.h"
#include "EditorForm.h"
#include <Component/FreeCamera_Com.h>
#include "EditScene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPunRealEditorApp

BEGIN_MESSAGE_MAP(EditorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &EditorApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CPunRealEditorApp ����

EditorApp::EditorApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
	SetAppID(_T("Editor.AppID.NoVersion"));
}

EditorApp theApp;

BOOL EditorApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(EditorDoc),RUNTIME_CLASS(MainFrame), RUNTIME_CLASS(EditorView));

	if (!pDocTemplate)
		return FALSE;

	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	AllocConsole();

	auto abc = ((MainFrame*)m_pMainWnd)->GetActiveView();

	Core::Get()->Init(m_hInstance, abc->m_hWnd, 1280, 720);
	Core::Get()->SetGameMode(GM_2D);

	SceneManager::Get()->AddSceneComponent<EditScene>("EditScene");

	Scene* CurScene = SceneManager::Get()->GetCurScene();
	GameObject* mainCameraObject = CurScene->GetMainCameraObject();
	FreeCamera_Com* freeCamera = mainCameraObject->AddComponent<FreeCamera_Com>("FreeCamera");

	SAFE_RELEASE(freeCamera);
	SAFE_RELEASE(CurScene);

	return TRUE;
}

int EditorApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	Core::Get()->Delete();

	return CWinApp::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void EditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

int EditorApp::Run()
{
	return CWinApp::Run();
}

//TODO
BOOL EditorApp::OnIdle(LONG lCount)
{
	if (m_pMainWnd->IsIconic())
		return FALSE;
	else
		Core::Get()->Logic();

	return TRUE;
}

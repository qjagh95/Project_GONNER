#include "EditorHeader.h"
#include "Editor.h"
#include "MonsterEdit.h"
#include "afxdialogex.h"
#include "EditorForm.h"

IMPLEMENT_DYNAMIC(MonsterEdit, CDialogEx)

MonsterEdit::MonsterEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOBTOOL, pParent)
	, m_isLeft(FALSE)
	, m_CurPosX(0.0f)
	, m_CurPosY(0.0f)
	, m_SelectPosX(0.0f)
	, m_SelectPosY(0)
{
	m_EditorForm = NULLPTR;
	m_CurType = ((MONSTER_TYPE)0);
}

MonsterEdit::~MonsterEdit()
{
}

void MonsterEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_MonsterList);
	DDX_Control(pDX, IDC_COMBO2, m_MobListCombo);
	DDX_Check(pDX, IDC_CHECK1, m_isLeft);
	DDX_Text(pDX, IDC_EDIT1, m_CurPosX);
	DDX_Text(pDX, IDC_EDIT3, m_CurPosY);
	DDX_Text(pDX, IDC_EDIT2, m_SelectPosX);
	DDX_Text(pDX, IDC_EDIT5, m_SelectPosY);
}

BEGIN_MESSAGE_MAP(MonsterEdit, CDialogEx)
	ON_BN_CLICKED(IDC_CLOSE, &MonsterEdit::OnBnClickedClose)
	ON_CBN_SELCHANGE(IDC_COMBO2, &MonsterEdit::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_CHECK1, &MonsterEdit::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &MonsterEdit::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MonsterEdit::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &MonsterEdit::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &MonsterEdit::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &MonsterEdit::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT5, &MonsterEdit::OnEnChangeEdit5)
END_MESSAGE_MAP()


// MonsterEdit 메시지 처7리기
void MonsterEdit::OnBnClickedClose()
{
	m_EditorForm->AddWorkText("Tool Close");
	EditorForm::m_isOpenTool = false;
	this->DestroyWindow();
}

void MonsterEdit::OnCbnSelchangeCombo2()
{
	//몬스터리스트
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void MonsterEdit::OnBnClickedCheck1()
{
	//왼쪽보기 체크박스
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void MonsterEdit::OnBnClickedButton2()
{
	//SaveButton
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void MonsterEdit::OnBnClickedButton3()
{
	//ClearButton
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void MonsterEdit::OnEnChangeEdit1()
{
	//CurPosX
	UpdateData(TRUE);

	Scene* curScene = SceneManager::Get()->GetCurScene();

	m_CurPosX = KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().x + curScene->GetMainCameraTransform()->GetWorldPos().x;

	UpdateData(FALSE);
	SAFE_RELEASE(curScene);
}


void MonsterEdit::OnEnChangeEdit3()
{
	//CurPosY
	UpdateData(TRUE);
	Scene* curScene = SceneManager::Get()->GetCurScene();

	m_CurPosY = KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().y + curScene->GetMainCameraTransform()->GetWorldPos().y;

	UpdateData(FALSE);
	SAFE_RELEASE(curScene);
}

void MonsterEdit::OnEnChangeEdit2()
{
	//SelectPosX
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void MonsterEdit::OnEnChangeEdit5()
{
	//SelectPosY
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void MonsterEdit::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	EditorForm::m_isOpenTool = false;

	CDialogEx::OnOK();
}


void MonsterEdit::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	EditorForm::m_isOpenTool = false;
}

#include "EditorHeader.h"
#include "Editor.h"
#include "MonsterEdit.h"
#include "afxdialogex.h"
#include "EditorForm.h"
#include "EditScene.h"

#include <Component/Animation2D_Com.h>
#include <Scene/Scene.h>

#include <UserComponent/GuardE_Com.h>
#include <UserComponent/AirDownE_Com.h>
#include <UserComponent/BasicE_Com.h>
#include <UserComponent/TraceE_Com.h>
#include <UserComponent/ReflectE_Com.h>

IMPLEMENT_DYNAMIC(MonsterEdit, CDialogEx)

MonsterEdit::MonsterEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOBTOOL, pParent)
	, m_isLeft(FALSE)
	, m_CurPosX(0.0f)
	, m_CurPosY(0.0f)
	, m_SelectPosX(0.0f)
	, m_SelectPosY(0)
	, m_EditScene(NULLPTR)
	, m_ListIndex(0)
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
	DDX_LBIndex(pDX, IDC_LIST1, m_ListIndex);
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
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_LBN_SELCHANGE(IDC_LIST1, &MonsterEdit::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON4, &MonsterEdit::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_MONLOAD, &MonsterEdit::OnBnClickedMonload)
END_MESSAGE_MAP()


void MonsterEdit::ReDrawWindow()
{
	::RedrawWindow(this->m_hWnd, NULLPTR, NULLPTR, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

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

	::RedrawWindow(this->m_hWnd, NULLPTR, NULLPTR, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

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

	const TCHAR* Filter = TEXT("MonsterData(*.data)|*.data|모든파일(*.*)|*.*||");
	CFileDialog	FileDlg(FALSE, TEXT(".data"), NULLPTR, OFN_OVERWRITEPROMPT, Filter);

	if (FileDlg.DoModal() == IDOK)
	{
		CString	fileName = FileDlg.GetFileName();
		BineryWrite Writer(fileName.GetString());
		
		Writer.WriteData(m_EditScene->m_vecSaveData.size());

		for (size_t i = 0; i < m_EditScene->m_vecSaveData.size(); i++)
		{
			Writer.WriteData(m_EditScene->m_vecSaveData[i].Type);
			Writer.WriteData(m_EditScene->m_vecSaveData[i].Dir);
			Writer.WriteData(m_EditScene->m_vecSaveData[i].Pos);
		}
	}

	UpdateData(FALSE);
}

void MonsterEdit::OnBnClickedButton3()
{

}

void MonsterEdit::OnEnChangeEdit1()
{
	//CurPosX
	UpdateData(TRUE);

	Scene* curScene = SceneManager::Get()->GetCurScene();
	
	m_CurPosX = KeyInput::Get()->GetMouseWorldPos().x;

	UpdateData(FALSE);
	SAFE_RELEASE(curScene);
}

void MonsterEdit::OnEnChangeEdit3()
{
	//CurPosY
	UpdateData(TRUE);
	Scene* curScene = SceneManager::Get()->GetCurScene();

	m_CurPosY = KeyInput::Get()->GetMouseWorldPos().y;

	UpdateData(FALSE);
	SAFE_RELEASE(curScene);
}

void MonsterEdit::OnEnChangeEdit2()
{
	//SelectPosX
	UpdateData(TRUE);

	m_EditScene->m_vecSaveData[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1].Pos.x = m_SelectPosX;
	m_EditScene->m_vecSaveData[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1].Pos.y = m_SelectPosY;
	m_EditScene->m_vecSaveObject[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1]->GetTransform()->SetWorldPos(Vector3(m_SelectPosX, m_SelectPosY, 0.0f));

	UpdateData(FALSE);
}

void MonsterEdit::OnEnChangeEdit5()
{
	//SelectPosY
	UpdateData(TRUE);

	m_EditScene->m_vecSaveData[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1].Pos.x = m_SelectPosX;
	m_EditScene->m_vecSaveData[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1].Pos.y = m_SelectPosY;
	m_EditScene->m_vecSaveObject[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1]->GetTransform()->SetWorldPos(Vector3(m_SelectPosX, m_SelectPosY, 0.0f));

	UpdateData(FALSE);
}

void MonsterEdit::OnCancel()
{
	EditorForm::m_isOpenTool = false;
	this->DestroyWindow();
}

int MonsterEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_TexturePath = PathManager::Get()->FindPath(TEXTURE_PATH);

	return 0;
}

void MonsterEdit::OnPaint()
{
	CPaintDC dc(this);
	
	if (m_MobListCombo.GetCurSel() == -1)
		return;

	TCHAR FileName[255];
	wstring sFileName;
	wstring Temp = L"Editor";
	m_MobListCombo.GetLBText(m_MobListCombo.GetCurSel(), FileName);
	sFileName = Temp + FileName;
	sFileName += L".png";

	wstring FullPath = m_TexturePath + sFileName;

	CImage newImage;
	newImage.Destroy();
	newImage.Load(FullPath.c_str());

	newImage.StretchBlt(dc.m_hDC, 250, 20, 190, 110);
}


void MonsterEdit::OnLbnSelchangeList1()
{
	UpdateData(TRUE);

	if (m_EditorForm->m_MobTool->m_MonsterList.GetCurSel() == -1)
		return;

	float SaveX = m_EditScene->m_vecSaveData[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1].Pos.x;
	float SaveY = m_EditScene->m_vecSaveData[m_MonsterList.GetCount() - m_MonsterList.GetCurSel() - 1].Pos.y;

	m_SelectPosX = SaveX;
	m_SelectPosY = SaveY;

	Scene* getScene = SceneManager::Get()->GetCurScene();
	getScene->GetMainCameraTransform()->SetWorldPos(Vector3(SaveX - 1920 / 2.0f, SaveY - 1080 / 2.0f, 0.0f));

	SAFE_RELEASE(getScene);
	UpdateData(FALSE);
}

void MonsterEdit::OnBnClickedButton4()
{
	//ClearButton
	UpdateData(TRUE);

	for (size_t i = 0; i < m_EditScene->m_vecSaveObject.size(); i++)
		m_EditScene->m_vecSaveObject[i]->SetIsActive(false);

	m_EditScene->m_Index = 0;
	m_EditScene->m_vecSaveObject.clear();
	m_EditScene->m_vecSaveData.clear();
	m_MonsterList.ResetContent();
	m_SelectPosX = 0.0f;
	m_SelectPosY = 0.0f;

	UpdateData(FALSE);
}

void MonsterEdit::OnBnClickedMonload()
{
	UpdateData(TRUE);

	const TCHAR* Filter = TEXT("MonsterData(*.data)|*.data|모든파일(*.*)|*.*||");
	//파일 다이얼로그 띄우기OFN_HIDEREADONLY
	CFileDialog	FileDlg(TRUE, TEXT(".data"), NULLPTR, OFN_HIDEREADONLY, Filter);
	
	Scene* getScene = SceneManager::Get()->GetCurScene();
	Layer* Default = getScene->FindLayerNoneCount("Default");
	SAFE_RELEASE(getScene);

	if (FileDlg.DoModal() == IDOK)
	{
		for (size_t i = 0; i < m_EditScene->m_vecSaveObject.size(); i++)
			m_EditScene->m_vecSaveObject[i]->SetIsActive(false);

		m_EditScene->m_Index = 0;
		m_EditScene->m_vecSaveObject.clear();
		m_EditScene->m_vecSaveData.clear();
		m_MonsterList.ResetContent();
	
		CString	fileName = FileDlg.GetFileName();
		BineryRead Reader(fileName.GetString());
	
		size_t vecSize;
		Reader.ReadData(vecSize);
	
		for (size_t i = 0; i < vecSize; i++)
		{
			SaveData Save;
	
			int type;
			Reader.ReadData(type);
	
			Save.Type = (MONSTER_TYPE)type;
	
			int Dir;
			Reader.ReadData(Dir);
	
			Save.Dir = (MOVE_DIR)Dir;
	
			Vector3 Pos;
			Reader.ReadData(Pos);
	
			Save.Pos = Pos;
	
			switch (type)
			{
			case MT_GUARD:
			{
				GameObject* newObject = GameObject::CreateObject("Guard", Default);
				GuardE_Com* newGuard = newObject->AddComponent<GuardE_Com>("Guard");
				newObject->GetTransform()->SetWorldPos(Pos);
				newGuard->GetAnimation()->SetDir((MOVE_DIR)Dir);
				newGuard->SetIndex(m_EditScene->m_Index);
	
				TCHAR Buffer[255] = {};
				wsprintf(Buffer, L"Guard몬스터 추가 Index : %d", m_EditScene->m_Index);
				m_MonsterList.InsertString(0, Buffer);
	
				m_EditScene->m_vecSaveObject.push_back(newObject);
				m_EditScene->m_vecSaveData.push_back(Save);

				SAFE_RELEASE(newGuard);
				SAFE_RELEASE(newObject);
	
				m_EditScene->m_Index++;
			}
			break;
			case MT_TRACE:
			{
				GameObject* newObject = GameObject::CreateObject("Trace", Default);
				TraceE_Com* newTrace = newObject->AddComponent<TraceE_Com>("Trace");
				newTrace->GetAnimation()->SetDir((MOVE_DIR)Dir);
				newObject->GetTransform()->SetWorldPos(Pos);
				newTrace->SetIndex(m_EditScene->m_Index);
	
				TCHAR Buffer[255] = {};
				wsprintf(Buffer, L"Trace몬스터 추가 Index : %d", m_EditScene->m_Index);
				m_MonsterList.InsertString(0, Buffer);

				m_EditScene->m_vecSaveObject.push_back(newObject);
				m_EditScene->m_vecSaveData.push_back(Save);

				SAFE_RELEASE(newTrace);
				SAFE_RELEASE(newObject);
	
				m_EditScene->m_Index++;
			}
			break;
			case MT_BASIC:
			{
				GameObject* newObject = GameObject::CreateObject("Basic", Default);
				BasicE_Com* newBasic = newObject->AddComponent<BasicE_Com>("Basic");
				newBasic->GetAnimation()->SetDir((MOVE_DIR)Dir);
				newObject->GetTransform()->SetWorldPos(Pos);
				newBasic->SetIndex(m_EditScene->m_Index);
	
				TCHAR Buffer[255] = {};
				wsprintf(Buffer, L"Basic몬스터 추가 Index : %d", m_EditScene->m_Index);
				m_MonsterList.InsertString(0, Buffer);
	
				m_EditScene->m_vecSaveObject.push_back(newObject);
				m_EditScene->m_vecSaveData.push_back(Save);

				SAFE_RELEASE(newBasic);
				SAFE_RELEASE(newObject);

				m_EditScene->m_Index++;
			}
			break;
			case MT_AIRDOWN:
			{
				GameObject* newObject = GameObject::CreateObject("AirDown", Default);
				AirDownE_Com* newAirDown = newObject->AddComponent<AirDownE_Com>("AirDown");
				newAirDown->GetAnimation()->SetDir((MOVE_DIR)Dir);
				newObject->GetTransform()->SetWorldPos(Pos);
				newAirDown->SetIndex(m_EditScene->m_Index);
	
				TCHAR Buffer[255] = {};
				wsprintf(Buffer, L"AirDown몬스터 추가 Index : %d", m_EditScene->m_Index);
				m_MonsterList.InsertString(0, Buffer);
	
				m_EditScene->m_vecSaveObject.push_back(newObject);
				m_EditScene->m_vecSaveData.push_back(Save);

				SAFE_RELEASE(newAirDown);
				SAFE_RELEASE(newObject);
	
				m_EditScene->m_Index++;
			}
			break;
			case MT_REFLECT:
			{
				GameObject* newObject = GameObject::CreateObject("Reflect", Default);
				ReflectE_Com* newReflect = newObject->AddComponent<ReflectE_Com>("Reflect");
				newReflect->GetAnimation()->SetDir((MOVE_DIR)Dir);
				newObject->GetTransform()->SetWorldPos(Pos);
				newReflect->SetIndex(m_EditScene->m_Index);
	
				TCHAR Buffer[255] = {};
				wsprintf(Buffer, L"Reflect몬스터 추가 Index : %d", m_EditScene->m_Index);
				m_MonsterList.InsertString(0, Buffer);

				m_EditScene->m_vecSaveObject.push_back(newObject);
				m_EditScene->m_vecSaveData.push_back(Save);

				SAFE_RELEASE(newReflect);
				SAFE_RELEASE(newObject);
	
				m_EditScene->m_Index++;
			}
			break;
			}
		}
	}
	UpdateData(FALSE);
}

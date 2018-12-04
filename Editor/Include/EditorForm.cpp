// EditorForm.cpp : ���� �����Դϴ�.
//
#include "EditorHeader.h"
#include "Editor.h"
#include "EditorForm.h"
#include "afxwin.h"
#include <BineryReader.h>
#include <BineryWriter.h>

//�α׸� �ؽ�Ʈ���Ϸ� �ð��Է��ؼ�. (����)
//Control Z �ǵ�����..?

// EditorForm

IMPLEMENT_DYNCREATE(EditorForm, CFormView)

EditorForm::EditorForm()
	: CFormView(IDD_DIALOG_EDIT)
	, m_TileCountX(0)
	, m_TileCountY(0)
	, m_TileSizeX(0)
	, m_TileSizeY(0)
	, m_TagName(_T(""))
	, m_ScaleX(0)
	, m_ScaleY(0)
	, m_ScaleZ(0)
	, m_RotationX(0)
	, m_RotationY(0)
	, m_RotationZ(0)
	, m_PosX(0)
	, m_PosY(0)
	, m_PosZ(0)
	, m_StartPosX(0)
	, m_StartPosY(0)
	, m_BackColorR(0)
	, m_BackColorG(0)
	, m_BackColorB(0)
	, m_BackColorA(0)
	, m_TextCount(0)
	, m_isLine(TRUE)
	, m_isImageLoad(false)
	, m_ImageName(_T(""))
	, m_CreateTileCount(0)
{
	m_TileCountX = 0;
	m_TileCountY = 0;
	m_TileSizeX = 0;
	m_TileSizeY = 0;

	m_StageObject = NULLPTR;
	m_StageCom = NULLPTR;
	m_StageTransform = NULLPTR;

	m_Path = PathManager::Get()->FindPath(TEXTURE_PATH);
}

EditorForm::~EditorForm()
{
	SAFE_RELEASE(m_StageObject);
	SAFE_RELEASE(m_StageCom);
	SAFE_RELEASE(m_StageTransform);
}

void EditorForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TILESELECT, m_TileTypeBox);
	DDX_Control(pDX, IDC_TILEOPTIONSELECT, m_TileOptionBox);
	DDX_Control(pDX, IDC_TILEIMAGESELECT, m_TileImageBox);

	DDX_Text(pDX, IDC_SCALEX2, m_TileCountX);
	DDX_Text(pDX, IDC_SCALEX3, m_TileCountY);
	DDX_Text(pDX, IDC_SCALEX4, m_TileSizeX);
	DDX_Text(pDX, IDC_SCALEX5, m_TileSizeY);
	DDX_Text(pDX, IDC_TAGNAME, m_TagName);
	DDX_Text(pDX, IDC_SCALEX, m_ScaleX);
	DDX_Text(pDX, IDC_SCALEY, m_ScaleY);
	DDX_Text(pDX, IDC_SCALEZ, m_ScaleZ);
	DDX_Text(pDX, IDC_ROTATIONX, m_RotationX);
	DDX_Text(pDX, IDC_ROTATIONY, m_RotationY);
	DDX_Text(pDX, IDC_ROTATIONZ, m_RotationZ);
	DDX_Text(pDX, IDC_POSITIONX, m_PosX);
	DDX_Text(pDX, IDC_POSITIONY, m_PosY);
	DDX_Text(pDX, IDC_POSITIONZ, m_PosZ);
	DDX_Control(pDX, IDC_WORK, m_WorkList);
	DDX_Text(pDX, IDC_STARTPOSX, m_StartPosX);
	DDX_Text(pDX, IDC_STARTPOSY, m_StartPosY);
	DDX_Control(pDX, IDC_STARTPOSX, m_StartPosXControl);
	DDX_Control(pDX, IDC_STARTPOSY, m_StartPosYControl);
	DDX_Text(pDX, IDC_COLORR, m_BackColorR);
	DDX_Text(pDX, IDC_COLORG, m_BackColorG);
	DDX_Text(pDX, IDC_COLORB, m_BackColorB);
	DDX_Text(pDX, IDC_COLORA, m_BackColorA);
	DDX_Check(pDX, IDC_LINEON, m_isLine);
	DDX_CBString(pDX, IDC_TILEIMAGESELECT, m_ImageName);
	DDX_Text(pDX, IDC_CREATETILECOUNT, m_CreateTileCount);

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(true);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(true);
	}
	else if (m_TileTypeBox.GetCurSel() == 1)
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(false);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(true);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(true);
	}

	if (m_StageCom == NULLPTR || m_StageObject == NULLPTR)
		GetDlgItem(IDC_LINEON)->EnableWindow(false);
	else
		GetDlgItem(IDC_LINEON)->EnableWindow(true);
}

BEGIN_MESSAGE_MAP(EditorForm, CFormView)
	ON_EN_CHANGE(IDC_SCALEX, &EditorForm::OnEnChangeScalex)
	ON_EN_CHANGE(IDC_ROTATIONX, &EditorForm::OnEnChangeRotationx)
	ON_EN_CHANGE(IDC_POSITIONX, &EditorForm::OnEnChangePositionx)
	ON_EN_CHANGE(IDC_SCALEY, &EditorForm::OnEnChangeScaley)
	ON_EN_CHANGE(IDC_ROTATIONY, &EditorForm::OnEnChangeRotationy)
	ON_EN_CHANGE(IDC_POSITIONY, &EditorForm::OnEnChangePositiony)
	ON_EN_CHANGE(IDC_SCALEZ, &EditorForm::OnEnChangeScalez)
	ON_EN_CHANGE(IDC_ROTATIONZ, &EditorForm::OnEnChangeRotationz)
	ON_EN_CHANGE(IDC_POSITIONZ, &EditorForm::OnEnChangePositionz)
	ON_CBN_SELCHANGE(IDC_TILESELECT, &EditorForm::OnCbnSelchangeTileselect)
	ON_CBN_SELCHANGE(IDC_TILEOPTIONSELECT, &EditorForm::OnCbnSelchangeTileoptionselect)
	ON_CBN_SELCHANGE(IDC_TILEIMAGESELECT, &EditorForm::OnCbnSelchangeTileimageselect)
	ON_BN_CLICKED(IDC_TILECREATEBUTTON, &EditorForm::OnBnClickedTilecreatebutton)
	ON_BN_CLICKED(IDC_COLORSAVE, &EditorForm::OnBnClickedColorsave)
	ON_EN_CHANGE(IDC_COLORR, &EditorForm::OnEnChangeColorr)
	ON_EN_CHANGE(IDC_COLORG, &EditorForm::OnEnChangeColorg)
	ON_EN_CHANGE(IDC_COLORB, &EditorForm::OnEnChangeColorb)
	ON_EN_CHANGE(IDC_COLORA, &EditorForm::OnEnChangeColora)
	ON_EN_CHANGE(IDC_TILECOUNTX, &EditorForm::OnEnChangeTilecountx)
	ON_EN_CHANGE(IDC_TILECOUNTY, &EditorForm::OnEnChangeTilecounty)
	ON_EN_CHANGE(IDC_TILESIZEX, &EditorForm::OnEnChangeTilesizex)
	ON_EN_CHANGE(IDC_TILESIZEY, &EditorForm::OnEnChangeTilesizey)
	ON_EN_CHANGE(IDC_TAGNAME, &EditorForm::OnEnChangeTagname)
	ON_BN_CLICKED(IDC_TILECLEAR, &EditorForm::OnBnClickedTileclear)
	ON_BN_CLICKED(IDC_LINEON, &EditorForm::OnBnClickedLineon)
	ON_BN_CLICKED(IDC_TILELOAD, &EditorForm::OnBnClickedTileload)
	ON_BN_CLICKED(IDC_TILESAVE, &EditorForm::OnBnClickedTilesave)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_CREATETILECOUNT, &EditorForm::OnEnChangeCreatetilecount)
END_MESSAGE_MAP()

// EditorForm �����Դϴ�.

#ifdef _DEBUG
void EditorForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void EditorForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void EditorForm::AddWorkText(const wstring& Text, int Index)
{
	CTime Time = CTime::GetTickCount();

	wstring Temp2;
	
	Temp2 += to_wstring(Time.GetYear());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetMonth());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetDay());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetHour());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetMinute());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetSecond());
	Temp2 += L"�� ";

	m_WorkList.InsertString(Index, Text.c_str());
	ExcelManager::Get()->WriteData("EditorLog", 0, m_TextCount, Text);
	ExcelManager::Get()->WriteData("EditorLog", 6, m_TextCount, Temp2);

	m_TextCount++;
}

void EditorForm::AddWorkText(const string & Text, int Index)
{
	CTime Time = CTime::GetTickCount();

	wstring Temp2;

	Temp2 += to_wstring(Time.GetYear());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetMonth());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetDay());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetHour());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetMinute());
	Temp2 += L"�� ";
	Temp2 += to_wstring(Time.GetSecond());
	Temp2 += L"�� ";

	wstring Temp = CA2W(Text.c_str());
	m_WorkList.InsertString(Index, Temp.c_str());
	ExcelManager::Get()->WriteData("EditorLog", 0, m_TextCount, Text);
	ExcelManager::Get()->WriteData("EditorLog", 6, m_TextCount, Temp2);

	m_TextCount++;
}

void EditorForm::AddWorkText(const CString & Text, int Index)
{
	CTime Time = CTime::GetTickCount();
	string Temp3;

	Temp3 += to_string(Time.GetYear());
	Temp3 += "�� ";
	Temp3 += to_string(Time.GetMonth());
	Temp3 += "�� ";
	Temp3 += to_string(Time.GetDay());
	Temp3 += "�� ";
	Temp3 += to_string(Time.GetHour());
	Temp3 += "�� ";
	Temp3 += to_string(Time.GetMinute());
	Temp3 += "�� ";
	Temp3 += to_string(Time.GetSecond());
	Temp3 += "�� ";

	string	Temp = CT2CA(Text);
	wstring Temp2 = CA2W(Temp.c_str());

	m_WorkList.InsertString(Index, Temp2.c_str());
	ExcelManager::Get()->WriteData("EditorLog", 0, m_TextCount, Text);
	ExcelManager::Get()->WriteData("EditorLog", 6, m_TextCount, Temp3);

	m_TextCount++;
}

void EditorForm::AddWorkText(wchar_t * Text, int Index)
{
	wstring Temp = Text;
	AddWorkText(Temp, Index);
}

void EditorForm::AddWorkText(char * Text, int Index)
{
	string Temp = Text;
	AddWorkText(Temp, Index);
}

void EditorForm::SaveStage(CString FileName)
{
	string Temp = CW2A(FileName);
	
	BineryWrite WriteFile(Temp);
	m_StageCom->Save(WriteFile);
}

void EditorForm::LoadStage(CString FileName)
{
	string File = CT2CA(FileName);

	BineryRead ReadFile(File);

	Scene* getScene = SceneManager::Get()->GetCurScene();
	Layer* getStageLayer = getScene->FindLayer("Tile");

	m_StageObject = GameObject::CreateObject("StageObject", getStageLayer);

	m_StageCom = m_StageObject->AddComponent<Stage2D_Com>("Stage");
	m_StageCom->Load(ReadFile);
	m_StageTransform = m_StageObject->GetTransform();

	SAFE_RELEASE(getStageLayer);
	SAFE_RELEASE(getScene);

	m_TileTypeBox.SetCurSel(m_StageCom->GetStageTileType());
	m_TileCountX = (int)m_StageCom->GetTileXCount();
	m_TileCountY = (int)m_StageCom->GetTileYCount();
	m_TileSizeX = (int)m_StageCom->GetTileScale().x;
	m_TileSizeY = (int)m_StageCom->GetTileScale().y;
}

int EditorForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

TILE2D_OPTION EditorForm::GetTileOption() const
{
	CString getString;
	m_TileOptionBox.GetWindowTextW(getString);

	if (getString == "�̵��Ұ�")
		return T2D_NOMOVE;
	else if (getString == "�̵�����")
		return T2D_NORMAL;
	else
		return T2D_NORMAL;
}

STAGE2D_TILE_TYPE EditorForm::GetTileType() const
{
	CString getString;
	m_TileTypeBox.GetWindowTextW(getString);

	if (getString == "RectTile")
		return STT_TILE;
	else if (getString == "IsoMatric")
		return STT_ISO;
	else
		return STT_NONE;
}

void EditorForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//�ʱ�ȭ
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_TileTypeBox.SetCurSel(1);
	m_TileOptionBox.SetCurSel(0);

	m_TileImageBox.SetCurSel(1);

	for (size_t i = 1; i <= 72; i++)
	{
		wstring Temp = L"line_0";

		if (i < 10)
			Temp += L"0";

		Temp += to_wstring(i);
		Temp += L".png";

		m_TileImageBox.AddString(Temp.c_str());
	}
}

void EditorForm::OnEnChangeScalex()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"SacleX : %d ����", m_ScaleX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeScaley()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"SacleY : %d ����", m_ScaleY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeScalez()
{
	UpdateData(TRUE);

	if (RenderManager::Get()->GetGameMode() == GM_2D)
	{
		m_ScaleZ = 0;

		wchar_t Buffer[255];
		wsprintf(Buffer, L"Error! 2D ����϶� ScaleZ�� ����Ұ�");
		AddWorkText(Buffer);

		UpdateData(FALSE);
		return;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"SacleZ : %d ����", m_ScaleZ);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationx()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"RotationX : %d ����", m_RotationX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationy()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"RotationY : %d ����", m_RotationY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationz()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"RotationZ : %d ����", m_RotationZ);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositionx()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"PosX : %d ����", m_PosX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositiony()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"PosY : %d ����", m_PosY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositionz()
{
	UpdateData(TRUE);

	if (RenderManager::Get()->GetGameMode() == GM_2D)
	{
		m_PosZ = 0;

		wchar_t Buffer[255];
		wsprintf(Buffer, L"Error! 2D ����϶� PosZ�� ����Ұ�");
		AddWorkText(Buffer);

		UpdateData(FALSE);
		return;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"PosZ : %d ����", m_PosZ);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}


//��Ʈ�ѹڽ�
////////////////////////////////////////////////////////////////////////
void EditorForm::OnCbnSelchangeTileselect()
{
	UpdateData(TRUE);

	CString Buffer;
	m_TileTypeBox.GetLBText(m_TileTypeBox.GetCurSel(),Buffer);
	Buffer += " ����";

	AddWorkText(Buffer);

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		m_TileSizeY = m_TileSizeX / 2;

		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"Ÿ�� ������ġ X : %d ,Y : %d �ڵ��Է� \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	UpdateData(FALSE);
}

void EditorForm::OnCbnSelchangeTileoptionselect()
{
	UpdateData(TRUE);

	CString Buffer;
	m_TileOptionBox.GetLBText(m_TileOptionBox.GetCurSel(), Buffer);
	Buffer += " �ɼ� ����";

	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnCbnSelchangeTileimageselect()
{
	UpdateData(TRUE);

	CString Buffer;
	m_TileImageBox.GetLBText(m_TileImageBox.GetCurSel(), Buffer);
	Buffer += " Ÿ�� �̹��� ����";

	string Temp2 = CW2A(m_ImageName);

	m_Path = PathManager::Get()->FindPath(TEXTURE_PATH);
	m_Path += L"Tile\\";
	m_Path += CA2W(Temp2.c_str());

	AddWorkText(Buffer);

	//������ �ٽñ׸��� �Լ�
	::RedrawWindow(this->m_hWnd, NULLPTR, NULLPTR, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
	UpdateData(FALSE);
}

void EditorForm::OnBnClickedTilecreatebutton()
{
	if (m_StageObject != NULLPTR)
	{
		wchar_t Buffer[255];
		wsprintf(Buffer, L"Error! �̹� Ÿ���� �����մϴ�.");
		AddWorkText(Buffer);
		return;
	}

	UpdateData(TRUE);

	if (m_TileCountX == 0 || m_TileCountY == 0 || m_TileSizeX == 0 || m_TileSizeY == 0)
	{
		wchar_t Buffer[255];
		wsprintf(Buffer, L"Error! Ÿ�ϰ����� ����� ��Ȯ�� �Է��ϼ���");

		AddWorkText(Buffer);
		UpdateData(TRUE);

		return;
	}

	Scene* getScene = SceneManager::Get()->GetCurScene();
	Layer* TileLayer = getScene->FindLayer("Tile");

	m_StageObject = GameObject::CreateObject("StageObject", TileLayer);

	Renderer_Com* stageRender = m_StageObject->AddComponent<Renderer_Com>("StageRender");
	stageRender->SetMesh("TextureRect");
	SAFE_RELEASE(stageRender);

	Material_Com* stageMat = m_StageObject->FindComponentFromType<Material_Com>(CT_MATERIAL);
	stageMat->SetMaterial(Vector4::Black);
	
	SAFE_RELEASE(stageMat);

	m_StageCom = m_StageObject->AddComponent<Stage2D_Com>("Stage");

	Vector3	TileScale = Vector3((float)m_TileSizeX, (float)m_TileSizeY, 1.0f);

	switch (GetTileType())
	{
		case STT_TILE:
			m_StageCom->CreateTileMap(m_TileCountX, m_TileCountY, Vector3((float)m_StartPosX, (float)m_StartPosY, 0.0f), TileScale, STT_TILE);
			break;
		case STT_ISO:
			m_StageCom->CreateTileMap(m_TileCountX, m_TileCountY, Vector3((float)m_StartPosX, (float)m_StartPosY, 0.0f), TileScale, STT_ISO);
			break;
	}

	m_StageTransform = m_StageObject->GetTransform();

	SAFE_RELEASE(getScene);
	SAFE_RELEASE(TileLayer);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"Ÿ�� X : %d, Ÿ�� Y : %d, �� Ÿ�� : %d �߰�", m_TileCountX, m_TileCountY, m_TileCountX * m_TileCountY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnBnClickedColorsave()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"���� %d, %d, %d, %d �� ����", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer);

	ExcelManager::Get()->WriteData("BackColor", 0, 0, Vector4((float)m_BackColorR, (float)m_BackColorG, (float)m_BackColorB, (float)m_BackColorA));

	UpdateData(FALSE);
}


void EditorForm::OnEnChangeColorr()
{
	UpdateData(TRUE);

	if (m_BackColorR < 0)
		m_BackColorR = 0;
	else if (m_BackColorR > 255)
		m_BackColorR = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"R�� %d �Է�", m_BackColorR);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeColorg()
{
	UpdateData(TRUE);

	if (m_BackColorG < 0)
		m_BackColorG = 0;
	else if (m_BackColorG > 255)
		m_BackColorG = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"G�� %d �Է�", m_BackColorG);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d \n", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeColorb()
{
	UpdateData(TRUE);

	if (m_BackColorB < 0)
		m_BackColorB = 0;
	else if (m_BackColorB > 255)
		m_BackColorB = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"B�� %d �Է�", m_BackColorB);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d \n", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeColora()
{
	UpdateData(TRUE);

	if (m_BackColorA < 0)
		m_BackColorA = 0;
	else if (m_BackColorA > 255)
		m_BackColorA = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"A�� %d �Է�", m_BackColorA);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d \n", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilecountx()
{
	UpdateData(TRUE);

	if (m_TileCountX > 10000)
		m_TileCountX = 10000;
	else if (m_TileCountX < 0)
		m_TileCountX = 0;

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"Ÿ�� ������ġ X : %d ,Y : %d �ڵ��Է� \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"X�� Ÿ�� ���� : %d �Է�", m_TileCountX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilecounty()
{
	UpdateData(TRUE);

	if (m_TileCountY > 10000)
		m_TileCountY = 10000;
	else if (m_TileCountY < 0)
		m_TileCountY = 0;

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"Ÿ�� ������ġ X : %d ,Y : %d �ڵ��Է� \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"Y�� Ÿ�� ���� : %d �Է�", m_TileCountY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilesizex()
{
	UpdateData(TRUE);

	if (m_TileSizeX > 500)
		m_TileSizeX = 500;

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		if (m_TileSizeY > m_TileSizeX / 2)
			m_TileSizeY = m_TileSizeX / 2;

		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"Ÿ�� ������ġ X : %d ,Y : %d �ڵ��Է� \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2, 1);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"Ÿ�� ������X : %d �Է�", m_TileSizeX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilesizey()
{
	UpdateData(TRUE);

	if (m_TileSizeY > 500)
		m_TileSizeY = 500;

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		if (m_TileSizeY > m_TileSizeX / 2)
			m_TileSizeY = m_TileSizeX / 2;

		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"Ÿ�� ������ġ X : %d ,Y : %d �ڵ��Է� \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2, 1);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"Ÿ�� ������Y : %d �Է�", m_TileSizeY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTagname()
{
	UpdateData(TRUE);

	CString Buffer;
	Buffer = "TagName : ";
	Buffer += m_TagName;
	Buffer += " ����";

	AddWorkText(Buffer);

	UpdateData(FALSE);
}


void EditorForm::OnBnClickedTileclear()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];

	if (m_StageObject == NULLPTR || m_StageCom == NULLPTR)
	{
		m_isLine = TRUE;

		wsprintf(Buffer, L"Error! Ÿ���� ��������� �ʾҽ��ϴ�.");
		AddWorkText(Buffer);

		UpdateData(FALSE);
		return;
	}

	m_StageTransform->SetIsActive(false);
	m_StageCom->SetIsActive(false);
	m_StageObject->SetIsActive(false);
	
	SAFE_RELEASE(m_StageObject);
	SAFE_RELEASE(m_StageCom);
	SAFE_RELEASE(m_StageTransform);


	wsprintf(Buffer, L"Ÿ�� ��ü ���� : %d�� ����", m_TileCountX * m_TileCountY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnBnClickedLineon()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];

	if (m_StageObject == NULLPTR || m_StageCom == NULLPTR)
	{
		m_isLine = TRUE;

		wsprintf(Buffer, L"Error! Ÿ���� ����� �ּ���");
		AddWorkText(Buffer);

		UpdateData(FALSE);
		return;
	}

	if (m_isLine == TRUE)
	{
		m_StageCom->SetLineOn(m_isLine);

		wsprintf(Buffer, L"Greed On");
		AddWorkText(Buffer);
	}
	else
	{
		m_StageCom->SetLineOn(m_isLine);

		wsprintf(Buffer, L"Greed Off");
		AddWorkText(Buffer);
	}

	UpdateData(FALSE);
}


void EditorForm::OnBnClickedTileload()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];

	if (m_StageObject != NULLPTR || m_StageCom != NULLPTR)
	{
		m_StageTransform->SetIsActive(false);
		m_StageCom->SetIsActive(false);
		m_StageObject->SetIsActive(false);

		SAFE_RELEASE(m_StageObject);
		SAFE_RELEASE(m_StageCom);
		SAFE_RELEASE(m_StageTransform);

		wsprintf(Buffer, L"Ÿ�� ��ü ���� : %d�� ����", m_TileCountX * m_TileCountY);
		AddWorkText(Buffer);
	}

	//���� ����.
	const TCHAR* Filter = TEXT("StageFile(*.tInfo)|*.tInfo|�������(*.*)|*.*||");
	//���� ���̾�α� ����OFN_HIDEREADONLY
	CFileDialog	FileDlg(TRUE, TEXT(".tInfo"), NULLPTR, OFN_HIDEREADONLY, Filter);

	wstring Temp;

	if (FileDlg.DoModal() == IDOK)
	{
		CString	fileName = FileDlg.GetFileName();

		LoadStage(fileName);
		Temp = fileName;
	}

	Temp += L" ���� Ÿ������ �ε�";
	AddWorkText(Temp);

	UpdateData(FALSE);
}

void EditorForm::OnBnClickedTilesave()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];

	if (m_StageObject == NULLPTR || m_StageCom == NULLPTR)
	{
		wsprintf(Buffer, L"Error! Ÿ���� ��������� �ʾҽ��ϴ�.", m_TileCountX * m_TileCountY);
		AddWorkText(Buffer);

		UpdateData(FALSE);
		return;
	}

	//���� ����.
	const TCHAR* Filter = TEXT("StageFile(*.tInfo)|*.tInfo|�������(*.*)|*.*||");
	//���� ���̾�α� ����
	CFileDialog	FileDlg(FALSE, TEXT(".tInfo"), NULLPTR, OFN_OVERWRITEPROMPT, Filter);

	if (FileDlg.DoModal() == IDOK)
	{
		CString	fileName = FileDlg.GetFileName();
		SaveStage(fileName);
	}

	wsprintf(Buffer, L"Ÿ������ ����.");
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnDraw(CDC* pDC)
{
	m_TileImage.Destroy();

	if(FAILED(m_TileImage.Load(m_Path.c_str())))
		return;

	::SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
	m_TileImage.StretchBlt(pDC->m_hDC, 240, 333, 128, 128, SRCCOPY);
}

void EditorForm::OnEnChangeCreatetilecount()
{
	UpdateData(TRUE);

	m_CreateTileCount = RandomRange(1, 4);

	UpdateData(FALSE);
}

#include "EditorHeader.h"
#include "EditScene.h"
#include "MainFrame.h"
#include "EditorForm.h"
#include "resource.h"
#include <Component/Tile2D_Com.h>
#include <Component/FreeCamera_Com.h>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
	SAFE_RELEASE(m_BackColorCom);
}

bool EditScene::Init()
{
	Camera_Com*	pCamera = m_Scene->GetMainCamera();
	pCamera->SetCameraType(CT_ORTHO);
	pCamera->SetNear(0.0f);

	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* Default = m_Scene->FindLayer("Default");
	Layer* UILayer = m_Scene->FindLayer("UI");
	Layer* TileLayer = m_Scene->FindLayer("Tile");

	GameObject* BackObject = GameObject::CreateObject("BackObject", BackLayer);
	m_BackColorCom = BackObject->AddComponent<BackColor_Com>("BackColor");

	KeyInput::Get()->AddKey("TileOption", VK_CONTROL);
	KeyInput::Get()->AddKey("TileTab", VK_TAB);
	KeyInput::Get()->AddKey("PrevTileTab", VK_OEM_3);
	KeyInput::Get()->AddKey("CameraZero", VK_SPACE);
	KeyInput::Get()->AddKey("Shift", VK_SHIFT);
	KeyInput::Get()->AddKey("Angle", 'Q');
	KeyInput::Get()->AddKey("ImageInit", 'R');
	KeyInput::Get()->AddKey("RandomTile", VK_SHIFT);
	KeyInput::Get()->AddKey("TileClear", VK_F1);

	SAFE_RELEASE(BackObject);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(UILayer);

	RenderManager::Get()->SetIsZoomMode(true);

	ShowCursor(TRUE);

	return true;
}

int EditScene::Update(float DeltaTime)
{
	MainFrame* mainFrame = (MainFrame*)AfxGetMainWnd();
	EditorForm*	editorForm = mainFrame->GetEditorForm();

	KeyInput::Get()->SetCurSorPos(DeltaTime);

	m_BackColorCom->SetBackColor(Vector4((float)editorForm->m_BackColorR, (float)editorForm->m_BackColorG, (float)editorForm->m_BackColorB, (float)editorForm->m_BackColorA));

	Stage2D_Com* TileStage = editorForm->GetStageComponent();

	if (TileStage != NULLPTR)
	{ 
		Vector3	MouseWorld = KeyInput::Get()->GetMouseWorldPos();
		MouseWorld.y -= 720.0f;

		if (KeyInput::Get()->KeyPress("LButton"))
		{
			ChangeTile(MouseWorld, editorForm, TileStage);

			CString Temp;
			string Temp2 = "Tile//";

			if (editorForm->m_TileImageBox.GetCurSel() != -1)
			{
				if (editorForm->m_isRandomTile == TRUE)
				{
					int Range = RandomRange(editorForm->m_RandomRange1, editorForm->m_RandomRange2 - 1);
					editorForm->m_TileImageBox.GetLBText(Range, Temp);
				}

				else
					editorForm->m_TileImageBox.GetLBText(editorForm->m_TileImageBox.GetCurSel(), Temp);
				
				Temp2 += CW2A(Temp);
				TileStage->SetMainTileImage(MouseWorld, Temp2, editorForm->m_TileAngle);
				
				if(editorForm->m_CreateTileCount != 0)
					TileStage->SetSubTileImage(MouseWorld, Temp2, editorForm->m_CreateTileCount, editorForm->m_TileAngle);

			}
		}
		else if (KeyInput::Get()->KeyPress("RButton"))
			TileStage->ClearImage(MouseWorld);


		if (KeyInput::Get()->KeyDown("TileOption"))
		{
			if (editorForm->m_TileOptionBox.GetCurSel() == 0)
				editorForm->m_TileOptionBox.SetCurSel(1);
			else
				editorForm->m_TileOptionBox.SetCurSel(0);
		}
	}

	if (KeyInput::Get()->KeyDown("Angle"))
		editorForm->OnEnChangeTilerotation();

	if (KeyInput::Get()->KeyDown("TileTab"))
	{
		int Index = editorForm->m_TileImageBox.GetCurSel();

		if (editorForm->m_TileImageBox.GetCount() - 1 == Index)
				editorForm->m_TileImageBox.SetCurSel(0);
		else
			editorForm->m_TileImageBox.SetCurSel(Index + 1);

		editorForm->OnCbnSelchangeTileimageselect();
	}


	if (KeyInput::Get()->KeyDown("PrevTileTab"))
	{
		int Index = editorForm->m_TileImageBox.GetCurSel();

		if (editorForm->m_TileImageBox.GetCurSel() != -1)
		{
			if (editorForm->m_TileImageBox.GetCurSel() == 0)
				editorForm->m_TileImageBox.SetCurSel(editorForm->m_TileImageBox.GetCount() - 1);
			else
				editorForm->m_TileImageBox.SetCurSel(Index - 1);

			editorForm->OnCbnSelchangeTileimageselect();
		}
	}

	if (KeyInput::Get()->KeyDown("CameraZero"))
	{
		FreeCamera_Com* getFree = m_Scene->GetMainCameraObject()->FindComponentFromType<FreeCamera_Com>(CT_FREECAMERA);
		editorForm->AddWorkText(L"카메라가 0, 0위치로 이동합니다");

		getFree->GetTransform()->SetWorldPos(0.0f, 0.0f, 0.0f);

		SAFE_RELEASE(getFree);
	}

	if (KeyInput::Get()->KeyDown("ImageInit"))
	{
		editorForm->m_TileImageBox.SetCurSel(-1);
		editorForm->OnCbnSelchangeTileimageselect();
	}

	if (KeyInput::Get()->KeyDown("RandomTile"))
		editorForm->OnBnClickedCheck1();

	if (KeyInput::Get()->KeyDown("TileClear"))
		TileStage->ClearImage();
		

	return 0;
}

void EditScene::ChangeTile(const Vector3 & mPos, EditorForm* form, Stage2D_Com* TileStage)
{
	switch (form->GetTileType())
	{
		case STT_TILE:
		{
			if (form->GetTileOption() == T2D_NORMAL)
			{
				form->OnEnChangeCreatetilecount();

				TileStage->SetMoveMesh(mPos, STT_TILE);
				TileStage->SetTileOption(mPos, T2D_NORMAL);

			}
			else
			{
				form->OnEnChangeCreatetilecount();

				TileStage->SetNoMoveMesh(mPos, STT_TILE);
				TileStage->SetTileOption(mPos, T2D_NOMOVE);
			}
		}
		break;

		case STT_ISO:
		{
			if (form->GetTileOption() == T2D_NORMAL)
			{
				form->OnEnChangeCreatetilecount();

				TileStage->SetMoveMesh(mPos, STT_ISO);
				TileStage->SetTileOption(mPos, T2D_NORMAL);
			}
			else
			{
				form->OnEnChangeCreatetilecount();

				TileStage->SetNoMoveMesh(mPos, STT_ISO);
				TileStage->SetTileOption(mPos, T2D_NOMOVE);
			}
		}
		break;
	}
}

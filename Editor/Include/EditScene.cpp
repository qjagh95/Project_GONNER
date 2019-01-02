#include "EditorHeader.h"
#include "EditScene.h"
#include "MainFrame.h"
#include "EditorForm.h"
#include "MonsterEdit.h"
#include "resource.h"
#include <Component/Tile2D_Com.h>
#include <Component/FreeCamera_Com.h>
#include <Component/Animation2D_Com.h>

#include <UserComponent/BasicE_Com.h>
#include <UserComponent/GuardE_Com.h>
#include <UserComponent/AirDownE_Com.h>
#include <UserComponent/TraceE_Com.h>
#include <UserComponent/ReflectE_Com.h>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
	SAFE_RELEASE(m_BackColorCom);
}

bool EditScene::Init()
{
	m_Index = 0;
	m_isSelect = false;

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
	KeyInput::Get()->AddKey("Delete", VK_DELETE);

	SAFE_RELEASE(BackObject);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(UILayer);

	ShowCursor(TRUE);

	return true;
}

int EditScene::Update(float DeltaTime)
{
	KeyInput::Get()->SetCurSorPos(DeltaTime);

	m_MainFrame = (MainFrame*)AfxGetMainWnd();
	m_EditorForm = m_MainFrame->GetEditorForm();
	m_EditorForm->m_EditScene = this;

	if (m_EditorForm->m_MobTool != NULLPTR && m_EditorForm->m_MobTool->m_EditScene == NULLPTR)
		m_EditorForm->m_MobTool->m_EditScene = this;

	Scene* curScene = SceneManager::Get()->GetCurScene();
	Layer* Default = curScene->FindLayerNoneCount("Default");

	Vector2 mPos;
	mPos.x = KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().x + curScene->GetMainCameraTransform()->GetWorldPos().x;
	mPos.y = KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().y + curScene->GetMainCameraTransform()->GetWorldPos().y;

	SAFE_RELEASE(curScene);

	if (EditorForm::m_isOpenTool == true)
		ToolOnActive(DeltaTime, m_EditorForm);
	else
		ToolOffActive(DeltaTime);

	return 0;
}

void EditScene::CollisionLateUpdate(float DeltaTime)
{
	if (EditorMonster_Base::m_SelectObject != NULLPTR && m_isCreate == true)
	{
		GameObject* getObject = m_vecSaveObject[m_vecSaveObject.size() - 1];
		EditorMonster_Base* getCom = getObject->FindComponentFromTypeNoneCount<EditorMonster_Base>(CT_EDITOR);

		getObject->SetIsActive(false);

		m_vecSaveData.erase(m_vecSaveData.begin() + m_vecSaveObject.size() - 1);
		m_vecSaveObject.erase(m_vecSaveObject.begin() + m_vecSaveObject.size() - 1);
		m_isCreate = false;
		m_EditorForm->m_MobTool->m_MonsterList.DeleteString(0);
		m_Index--;
	}

	for (size_t i = 0; i < m_vecSaveObject.size(); i++)
	{
		if (m_vecSaveObject[i] != NULLPTR && m_vecSaveObject[i]->GetIsActive() == false)
		{
			EditorMonster_Base* getCom = m_vecSaveObject[i]->FindComponentFromTypeNoneCount<EditorMonster_Base>(CT_EDITOR);
			m_vecSaveData.erase(m_vecSaveData.begin() + i);
			m_vecSaveObject.erase(m_vecSaveObject.begin() + i);

			m_EditorForm->m_MobTool->m_MonsterList.DeleteString((UINT)(m_EditorForm->m_MobTool->m_MonsterList.GetCount() - 1 - i));
			m_Index--;
			break;
		}
	}
}

void EditScene::ToolOnActive(float DeltaTime, EditorForm * editorForm)
{
	Scene* curScene = SceneManager::Get()->GetCurScene();
	Layer* Default = curScene->FindLayerNoneCount("Default");

	Vector2 mPos;
	mPos.x = KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().x + curScene->GetMainCameraTransform()->GetWorldPos().x;
	mPos.y = KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().y + curScene->GetMainCameraTransform()->GetWorldPos().y;

	SAFE_RELEASE(curScene);

	m_EditorForm->m_MobTool->m_CurMobType = (MONSTER_TYPE)m_EditorForm->m_MobTool->m_MobListCombo.GetCurSel();
	MOVE_DIR Dir;

	if (m_EditorForm->m_MobTool->m_isLeft == TRUE)
		Dir = MD_LEFT;
	else
		Dir = MD_RIGHT;

	if (KeyInput::Get()->KeyDown("LButton"))
	{
		SaveData Save;

		if (KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().x >= 1920.0f || KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().y >= 1080.0f)
			return;
		else if (KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().x <= 0.0f || KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos().y <= 0.0f)
			return;

		m_isCreate = true;

		switch (m_EditorForm->m_MobTool->m_CurMobType)
		{
		case MT_GUARD:
		{
			GameObject* newObject = GameObject::CreateObject("Guard", Default);
			GuardE_Com* newGuard = newObject->AddComponent<GuardE_Com>("Guard");
			newObject->GetTransform()->SetWorldPos(Vector3(mPos.x, mPos.y, 0.0f));
			newGuard->GetAnimation()->SetDir(Dir);

			SAFE_RELEASE(newGuard);
			SAFE_RELEASE(newObject);

			Save.Pos = mPos;
			Save.Dir = Dir;
			Save.Type = MT_GUARD;

			TCHAR Buffer[255] = {};
			wsprintf(Buffer, L"Guard 몬스터 추가. Index : %d", m_Index);
			m_EditorForm->m_MobTool->m_MonsterList.InsertString(0, Buffer);

			m_vecSaveData.push_back(Save);
			m_Index++;
		}
		break;

		case MT_TRACE:
		{
			GameObject* newObject = GameObject::CreateObject("Trace", Default);
			TraceE_Com* newTrace = newObject->AddComponent< TraceE_Com>("Trace");
			newObject->GetTransform()->SetWorldPos(Vector3(mPos.x, mPos.y, 0.0f));
			newTrace->GetAnimation()->SetDir(Dir);
			newTrace->SetIndex(m_Index);

			m_vecSaveObject.push_back(newObject);

			SAFE_RELEASE(newTrace);
			SAFE_RELEASE(newObject);

			Save.Pos = mPos;
			Save.Dir = Dir;
			Save.Type = MT_GUARD;

			TCHAR Buffer[255] = {};
			wsprintf(Buffer, L"Trace 몬스터 추가. Index : %d", m_Index);
			m_EditorForm->m_MobTool->m_MonsterList.InsertString(0, Buffer);
			m_EditorForm->m_MobTool->m_MonsterList.SetCurSel(0);

			m_vecSaveData.push_back(Save);
			m_Index++;
		}
		break;

		case MT_BASIC:
		{
			GameObject* newObject = GameObject::CreateObject("Basic", Default);
			BasicE_Com* newBasic = newObject->AddComponent< BasicE_Com>("Basic");
			newObject->GetTransform()->SetWorldPos(Vector3(mPos.x, mPos.y, 0.0f));
			newBasic->GetAnimation()->SetDir(Dir);
			newBasic->SetIndex(m_Index);

			m_vecSaveObject.push_back(newObject);
			SAFE_RELEASE(newBasic);
			SAFE_RELEASE(newObject);

			Save.Pos = mPos;
			Save.Dir = Dir;
			Save.Type = MT_GUARD;

			TCHAR Buffer[255] = {};
			wsprintf(Buffer, L"Basic 몬스터 추가. Index : %d", m_Index);
			m_EditorForm->m_MobTool->m_MonsterList.InsertString(0, Buffer);
			m_EditorForm->m_MobTool->m_MonsterList.SetCurSel(0);

			m_vecSaveData.push_back(Save);
			m_Index++;
		}
		break;

		case MT_AIRDOWN:
		{
			GameObject* newObject = GameObject::CreateObject("AirDown", Default);
			AirDownE_Com* newAirDown = newObject->AddComponent< AirDownE_Com>("AirDown");
			newObject->GetTransform()->SetWorldPos(Vector3(mPos.x, mPos.y, 0.0f));
			newAirDown->GetAnimation()->SetDir(Dir);
			newAirDown->SetIndex(m_Index);

			m_vecSaveObject.push_back(newObject);
			SAFE_RELEASE(newAirDown);
			SAFE_RELEASE(newObject);

			Save.Pos = mPos;
			Save.Dir = Dir;
			Save.Type = MT_GUARD;

			TCHAR Buffer[255] = {};
			wsprintf(Buffer, L"AirDown 몬스터 추가. Index : %d", m_Index);
			m_EditorForm->m_MobTool->m_MonsterList.InsertString(0, Buffer);
			m_EditorForm->m_MobTool->m_MonsterList.SetCurSel(0);

			m_vecSaveData.push_back(Save);
			m_Index++;
		}
		break;

		case MT_REFLECT:
		{
			GameObject* newObject = GameObject::CreateObject("Reflect", Default);
			ReflectE_Com* newReflect = newObject->AddComponent<ReflectE_Com>("Reflect");
			newObject->GetTransform()->SetWorldPos(Vector3(mPos.x, mPos.y, 0.0f));
			newReflect->GetAnimation()->SetDir(Dir);
			newReflect->SetIndex(m_Index);

			m_vecSaveObject.push_back(newObject);
			SAFE_RELEASE(newReflect);
			SAFE_RELEASE(newObject);

			Save.Pos = mPos;
			Save.Dir = Dir;
			Save.Type = MT_GUARD;

			TCHAR Buffer[255] = {};
			wsprintf(Buffer, L"Reflect 몬스터 추가. Index : %d", m_Index);
			m_EditorForm->m_MobTool->m_MonsterList.InsertString(0, Buffer);
			m_EditorForm->m_MobTool->m_MonsterList.SetCurSel(0);

			m_vecSaveData.push_back(Save);
			m_Index++;
		}
		break;
		}

		m_EditorForm->m_MobTool->OnEnChangeEdit1();
		m_EditorForm->m_MobTool->OnEnChangeEdit3();
	}

	if (KeyInput::Get()->KeyUp("LButton"))
	{
		if (EditorMonster_Base::m_SelectObject == NULLPTR)
			return;

		GameObject* getObject = EditorMonster_Base::m_SelectObject;
		EditorMonster_Base* getCom = getObject->FindComponentFromTypeNoneCount<EditorMonster_Base>(CT_EDITOR);
		int Index = getCom->GetIndex();

		m_vecSaveData[Index].Pos = mPos;

		m_EditorForm->m_MobTool->OnEnChangeEdit1();
		m_EditorForm->m_MobTool->OnEnChangeEdit3();
	}

	if (KeyInput::Get()->KeyDown("TileTab"))
	{
		int Index = m_EditorForm->m_MobTool->m_MobListCombo.GetCurSel();

		if (m_EditorForm->m_MobTool->m_MobListCombo.GetCount() - 1 == Index)
			m_EditorForm->m_MobTool->m_MobListCombo.SetCurSel(0);
		else
			m_EditorForm->m_MobTool->m_MobListCombo.SetCurSel(Index + 1);

		m_EditorForm->m_MobTool->RedrawWindow();
	}

	if (KeyInput::Get()->KeyDown("PrevTileTab"))
	{
		int Index = m_EditorForm->m_MobTool->m_MobListCombo.GetCurSel();

		if (m_EditorForm->m_MobTool->m_MobListCombo.GetCurSel() != -1)
		{
			if (m_EditorForm->m_MobTool->m_MobListCombo.GetCurSel() == 0)
				m_EditorForm->m_MobTool->m_MobListCombo.SetCurSel(m_EditorForm->m_TileImageBox.GetCount() - 1);
			else
				m_EditorForm->m_MobTool->m_MobListCombo.SetCurSel(Index - 1);

			m_EditorForm->m_MobTool->RedrawWindow();
		}
	}

}

void EditScene::ToolOffActive(float DeltaTime)
{
	KeyInput::Get()->SetCurSorPos(DeltaTime);

	m_BackColorCom->SetBackColor(Vector4((float)m_EditorForm->m_BackColorR, (float)m_EditorForm->m_BackColorG, (float)m_EditorForm->m_BackColorB, (float)m_EditorForm->m_BackColorA));

	Stage2D_Com* TileStage = m_EditorForm->GetStageComponent();

	if (TileStage != NULLPTR)
	{
		Vector3	MouseWorld = KeyInput::Get()->GetMouseWorldPos();
		MouseWorld.y -= 720.0f;

		if (KeyInput::Get()->KeyPress("LButton"))
		{
			ChangeTile(MouseWorld, m_EditorForm, TileStage);

			CString Temp;
			string Temp2 = "Tile//";

			if (m_EditorForm->m_TileImageBox.GetCurSel() != -1)
			{
				if (m_EditorForm->m_isRandomTile == TRUE)
				{
					int Range = RandomRange(m_EditorForm->m_RandomRange1, m_EditorForm->m_RandomRange2 - 1);
					m_EditorForm->m_TileImageBox.GetLBText(Range, Temp);
				}

				else
					m_EditorForm->m_TileImageBox.GetLBText(m_EditorForm->m_TileImageBox.GetCurSel(), Temp);

				Temp2 += CW2A(Temp);
				TileStage->SetMainTileImage(MouseWorld, Temp2, m_EditorForm->m_TileAngle);

				if (m_EditorForm->m_CreateTileCount != 0)
					TileStage->SetSubTileImage(MouseWorld, Temp2, m_EditorForm->m_CreateTileCount, m_EditorForm->m_TileAngle);

			}
		}
		else if (KeyInput::Get()->KeyPress("RButton"))
			TileStage->ClearImage(MouseWorld);

		if (KeyInput::Get()->KeyDown("TileOption"))
		{
			if (m_EditorForm->m_TileOptionBox.GetCurSel() == 0)
				m_EditorForm->m_TileOptionBox.SetCurSel(1);
			else
				m_EditorForm->m_TileOptionBox.SetCurSel(0);
		}
	}

	if (KeyInput::Get()->KeyDown("Angle"))
		m_EditorForm->OnEnChangeTilerotation();

	if (KeyInput::Get()->KeyDown("TileTab"))
	{
		int Index = m_EditorForm->m_TileImageBox.GetCurSel();

		if (m_EditorForm->m_TileImageBox.GetCount() - 1 == Index)
			m_EditorForm->m_TileImageBox.SetCurSel(0);
		else
			m_EditorForm->m_TileImageBox.SetCurSel(Index + 1);

		m_EditorForm->OnCbnSelchangeTileimageselect();
	}

	if (KeyInput::Get()->KeyDown("PrevTileTab"))
	{
		int Index = m_EditorForm->m_TileImageBox.GetCurSel();

		if (m_EditorForm->m_TileImageBox.GetCurSel() != -1)
		{
			if (m_EditorForm->m_TileImageBox.GetCurSel() == 0)
				m_EditorForm->m_TileImageBox.SetCurSel(m_EditorForm->m_TileImageBox.GetCount() - 1);
			else
				m_EditorForm->m_TileImageBox.SetCurSel(Index - 1);

			m_EditorForm->OnCbnSelchangeTileimageselect();
		}
	}

	if (KeyInput::Get()->KeyDown("CameraZero"))
	{
		FreeCamera_Com* getFree = m_Scene->GetMainCameraObject()->FindComponentFromType<FreeCamera_Com>(CT_FREECAMERA);
		m_EditorForm->AddWorkText(L"카메라가 0, 0위치로 이동합니다");

		getFree->GetTransform()->SetWorldPos(0.0f, 0.0f, 0.0f);

		SAFE_RELEASE(getFree);
	}

	if (KeyInput::Get()->KeyDown("ImageInit"))
	{
		m_EditorForm->m_TileImageBox.SetCurSel(-1);
		m_EditorForm->OnCbnSelchangeTileimageselect();
	}

	if (KeyInput::Get()->KeyDown("RandomTile"))
		m_EditorForm->OnBnClickedCheck1();

	if (KeyInput::Get()->KeyDown("TileClear"))
		TileStage->ClearImage();

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

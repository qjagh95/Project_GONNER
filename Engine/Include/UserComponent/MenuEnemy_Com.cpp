#include "stdafx.h"
#include "MenuEnemy_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

MenuEnemy_Com::MenuEnemy_Com()
	:m_Animation(NULLPTR)
{
	m_ScaleStartTime = 0.0f;
	m_ScaleStartTimeVar = 0.0f;
	m_ColorChangeTime = 0.0f;
	m_ColorChangeTimeVar = 0.0f;
	m_LightChangeTimeVar = 0.0f;
	m_LightChangeTime = 0.0f;
	m_isScaleStart = false;
	m_isColorStart = false;

	m_Material = NULLPTR;
}

MenuEnemy_Com::MenuEnemy_Com(const MenuEnemy_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

MenuEnemy_Com::~MenuEnemy_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool MenuEnemy_Com::Init()
{
	m_ScaleStartTime = (float)RandomRange(1, 10);
	m_ColorChangeTime = (float)RandomRange(2, 4);

	int Random = RandomRange(1, 4);
	switch (Random)
	{
		case 1:
			m_LightChangeTime = 0.1f;
			break;
		case 2:
			m_LightChangeTime = 0.2f;
			break;
		case 3:
			m_LightChangeTime = 0.3f;
			break;
		case 4:
			m_LightChangeTime = 0.4f;
			break;
	}

	Renderer_Com* EnemyRender = m_Object->AddComponent<Renderer_Com>("MenuEnemyRender");
	EnemyRender->SetMesh("TextureRect");
	EnemyRender->SetRenderState(ALPHA_BLEND);
	EnemyRender->SetShader(MENUENEMY_SHADER);
	EnemyRender->CreateRendererCBuffer("MenuEnemyCBuffer", sizeof(MenuEnemyCBuffer));
	SAFE_RELEASE(EnemyRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4(31.0f / 255.0f, 71.0f / 255.0f, 67.0f / 255.0f, 1.0f));

	m_CBuffer.Light = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	return true;
}

int MenuEnemy_Com::Input(float DeltaTime)
{
	m_LightChangeTimeVar += DeltaTime;

	if (m_isScaleStart == false)
	{
		m_ScaleStartTimeVar += DeltaTime;

		if (m_ScaleStartTimeVar >= m_ScaleStartTime)
		{
			m_ScaleStartTimeVar = 0.0f;

			m_isScaleStart = true;
		}
	}

	if (m_isScaleStart == true)
	{
		Vector3 worldScale = m_Transform->GetWorldScale();
		
		if (worldScale.x >= m_ResultScale.x && worldScale.x >= m_ResultScale.x)
			m_isScaleStart = false;
		else
		{
			m_Transform->AddScaleXY(100.0f, DeltaTime);
			m_isColorStart = true;
		}

	}

	if (m_isColorStart == true)
		m_ColorChangeTimeVar += DeltaTime;

	if (m_ColorChangeTimeVar >= m_ColorChangeTime)
	{
		m_ColorChangeTimeVar = 0.0f;

		Material_Com* getMat = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
		int RanColor = RandomRange(1, 6);

		switch (RanColor)
		{
			case 1:
				getMat->SetMaterial(Vector4(76.0f / 255.0f, 83.0f / 255.0f, 45.0f / 255.0f, 1.0f));
				break;
			case 2:
				getMat->SetMaterial(Vector4(75.0f / 255.0f, 70.0f / 255.0f, 43.0f / 255.0f, 1.0f));
				break;
			case 3:
				getMat->SetMaterial(Vector4(31.0f / 255.0f, 66.0f / 255.0f, 64.0f / 255.0f, 1.0f));
				break;
			case 4:
				getMat->SetMaterial(Vector4(42.0f / 255.0f, 44.0f / 255.0f, 92.0f / 255.0f, 1.0f));
				break;
			case 5:
				getMat->SetMaterial(Vector4(30.0f / 255.0f, 58.0f / 255.0f, 71.0f / 255.0f, 1.0f));
				break;
				case 6:
				getMat->SetMaterial(Vector4(76.0f / 255.0f, 40.0f / 255.0f, 43.0f / 255.0f, 1.0f));
				break;
		}
		SAFE_RELEASE(getMat);
	}

	if (m_LightChangeTimeVar >= m_LightChangeTime)
	{
		m_LightChangeTimeVar = 0.0f;

		if (m_CBuffer.Light == Vector4::One)
			m_CBuffer.Light = Vector4(1.1f, 1.1f, 1.1f, 1.1f);
		else
			m_CBuffer.Light = Vector4::One;
	}

	return 0;
}

int MenuEnemy_Com::Update(float DeltaTime)
{
	return 0;
}

int MenuEnemy_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void MenuEnemy_Com::Collision(float DeltaTime)
{
}

void MenuEnemy_Com::CollisionLateUpdate(float DeltaTime)
{
}

void MenuEnemy_Com::Render(float DeltaTime)
{
	Renderer_Com* getRender = m_Object->FindComponentFromType< Renderer_Com>(CT_RENDER);
	getRender->UpdateRendererCBuffer("MenuEnemyCBuffer", &m_CBuffer, sizeof(MenuEnemyCBuffer));

	SAFE_RELEASE(getRender);
}

MenuEnemy_Com * MenuEnemy_Com::Clone()
{
	return new MenuEnemy_Com(*this);
}

void MenuEnemy_Com::AfterClone()
{
}

void MenuEnemy_Com::SetEnemyType(MENU_ENEMY_TYPE Type, const Vector3& Pos, MOVE_DIR Dir ,float Rot)
{
	m_Animation = m_Object->AddComponent<Animation2D_Com>("MenuMonster");

	int rDir = RandomRange(1, 10);

	if(rDir > 5)
		m_Animation->SetDir(MD_LEFT);
	else
		m_Animation->SetDir(MD_RIGHT);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	switch (Type)
	{
		case ME_M1:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 0.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 128.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy1", L"Monster\\HUD_sheet.png");

			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);
			vecClipFrame.clear();
		}
			break;
		case ME_M2:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy2", L"Monster\\smallenemies.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M3:
		{
			for (size_t i = 0; i < 5; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 64.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 128.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy3", L"Monster\\smallenemies.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
		break;
		case ME_M4:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 512.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 576.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy4", L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M5:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 320.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 384.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy5" , L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M6:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(256.0f + (i * 64.0f), 448.0f);
				tFrame.RightBottom = Vector2(256.0f + (i + 1) * 64.0f, 512.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy6", L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M7:
		{
			for (size_t i = 0; i < 10; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f , 576.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 640.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy8", L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M8:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(640.0f + i * 64.0f, 576.0f);
				tFrame.RightBottom = Vector2(640.0f + (i + 1) * 64.0f, 640.0f);

				vecClipFrame.push_back(tFrame);
			}

			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy8", L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M9:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 768.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 832.0f);

				vecClipFrame.push_back(tFrame);
			}


			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy9" , L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M10:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);

				vecClipFrame.push_back(tFrame);
			}
			
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy10", L"Monster\\sprites.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M11:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(128.0f + i * 64.0f, 384.0f);
				tFrame.RightBottom = Vector2(128.0f + (i + 1) * 64.0f, 448.0f);

				vecClipFrame.push_back(tFrame);
			}
		
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy11", L"Monster\\sprites.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M12:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 576.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 640.0f);

				vecClipFrame.push_back(tFrame);
			}
			
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy12", L"Monster\\sprites.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M13:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 256.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 384.0f);

				vecClipFrame.push_back(tFrame);
			}
		
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy13" , L"Monster\\bigsprites.png");
			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M14:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(128.0f + i * 128.0f, 128.0f);
				tFrame.RightBottom = Vector2(128.0f + (i + 1) * 128.0f, 256.0f);

				vecClipFrame.push_back(tFrame);
			}
		
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy14", L"Monster\\bigsprites3.png");
			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case ME_M15:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(256.0f + i * 128.0f, 640.0f);
				tFrame.RightBottom = Vector2(256.0f + (i + 1) * 128.0f, 768.0f);

				vecClipFrame.push_back(tFrame);
			}
		
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "MenuEnemy15", L"Monster\\bigsprites3.png");
			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
	}

	m_Animation->ChangeClip("Idle");
	m_Animation->SetDir(Dir);

	m_Transform->SetWorldPos(Pos);
	m_Transform->RotationZ(Rot);
}

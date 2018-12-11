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
	m_isScaleStart = false;
	m_isColorStart = false;
}

MenuEnemy_Com::MenuEnemy_Com(const MenuEnemy_Com & CopyData)
	:UserComponent_Base(CopyData)
{
	SAFE_RELEASE(m_Animation);
}

MenuEnemy_Com::~MenuEnemy_Com()
{
}

bool MenuEnemy_Com::Init()
{
	m_ScaleStartTime = (float)RandomRange(3, 10);
	m_ColorChangeTime = (float)RandomRange(2, 4);

	Renderer_Com* EnemyRender = m_Object->AddComponent<Renderer_Com>("MenuEnemyRender");
	EnemyRender->SetMesh("TextureRect");
	EnemyRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(EnemyRender);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	return true;
}

int MenuEnemy_Com::Input(float DeltaTime)
{

	if(m_isScaleStart == false)
		m_ScaleStartTimeVar += DeltaTime;

	if (m_ScaleStartTimeVar >= m_ScaleStartTime)
	{
		m_ScaleStartTimeVar = 0.0f;

		m_isScaleStart = true;
		m_isColorStart = true;
	}

	if (m_isScaleStart == true)
	{

	}

	if (m_isColorStart == true)
		m_ColorChangeTimeVar += DeltaTime;

	if (m_ColorChangeTimeVar >= m_ColorChangeTime)
	{
		m_ColorChangeTimeVar = 0.0f;

		Material_Com* getMat = m_Object->FindComponentFromType< Material_Com>(CT_MATERIAL);
		int RanColor = RandomRange(1, 4);

		switch (RanColor)
		{
			case 1:
			{
				getMat->SetMaterial(Vector4());
			}
				break;
			case 2:
			{
				getMat->SetMaterial(Vector4());
			}
				break;
			case 3:
			{
				getMat->SetMaterial(Vector4());
			}
				break;
			case 4:
			{
				getMat->SetMaterial(Vector4());
			}
				break;
		}
		SAFE_RELEASE(getMat);
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
}

MenuEnemy_Com * MenuEnemy_Com::Clone()
{
	return new MenuEnemy_Com(*this);
}

void MenuEnemy_Com::AfterClone()
{
}

void MenuEnemy_Com::SetEnemyType(MENU_ENEMY_TYPE Type, const Vector3& Pos, bool isRight ,float Rot)
{
	Material_Com* getMater = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	getMater->SetMaterial(Vector4::White);

	m_Animation = m_Object->AddComponent<Animation2D_Com>("MenuMonster");

	int rDir = RandomRange(1, 10);

	if(rDir > 5)
		m_Animation->SetDir(true);
	else
		m_Animation->SetDir(false);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	switch (Type)
	{
		case JEONG::ME_M1:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 0.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 128.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy1" , TEXT("Monster\\HUD_sheet.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy1", L"Monster\\HUD_sheet.png");

			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);
			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M2:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy2", TEXT("Monster\\smallenemies.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy2", L"Monster\\smallenemies.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M3:
		{
			for (size_t i = 0; i < 5; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 64.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 128.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy3", TEXT("Monster\\smallenemies.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy3", L"Monster\\smallenemies.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M4:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 544.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 576.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy4", TEXT("Monster\\player.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy4", L"Monster\\player.png.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M5:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 320.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 384.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy5", TEXT("Monster\\player.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy5" , L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M6:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(256.0f + (i * 64.0f), 448.0f);
				tFrame.RightBottom = Vector2(256.0f + (i + 1) * 64.0f, 512.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy6" , TEXT("Monster\\player.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy6", L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M7:
		{
			for (size_t i = 0; i < 10; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f , 576.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 640.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy7", TEXT("Monster\\player.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy8", L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M8:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(640.0f + i * 64.0f, 576.0f);
				tFrame.RightBottom = Vector2(640.0f + (i + 1) * 64.0f, 640.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy8", TEXT("Monster\\player.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy8", L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M9:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 768.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 832.0f);

				vecClipFrame.push_back(tFrame);
			}

			getMater->SetDiffuseTexture(0, "MenuEnemy9", TEXT("Monster\\player.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy9" , L"Monster\\player.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M10:
		{
			for (size_t i = 0; i < 10; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);

				vecClipFrame.push_back(tFrame);
			}
			getMater->SetDiffuseTexture(0, "MenuEnemy10", TEXT("Monster\\sprites.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy10", L"Monster\\sprites.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M11:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(128.0f + i * 64.0f, 384.0f);
				tFrame.RightBottom = Vector2(128.0f + i * 64.0f, 448.0f);

				vecClipFrame.push_back(tFrame);
			}
			getMater->SetDiffuseTexture(0, "MenuEnemy11" , TEXT("Monster\\sprites.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy11", L"Monster\\sprites.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M12:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 576.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 640.0f);

				vecClipFrame.push_back(tFrame);
			}
			getMater->SetDiffuseTexture(0, "MenuEnemy12" , TEXT("Monster\\sprites.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy12", L"Monster\\sprites.png");
			m_ResultScale = Vector3(64.0f, 64.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M13:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 256.0f);
				tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 384.0f);

				vecClipFrame.push_back(tFrame);
			}
			getMater->SetDiffuseTexture(0, "MenuEnemy13", TEXT("Monster\\bigsprites.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy13" , L"Monster\\bigsprites.png");
			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M14:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(128.0f + i * 128.0f, 128.0f);
				tFrame.RightBottom = Vector2(128.0f + (i + 1) * 128.0f, 256.0f);

				vecClipFrame.push_back(tFrame);
			}
			getMater->SetDiffuseTexture(0, "MenuEnemy14" , TEXT("Monster\\bigsprites3.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy14", L"Monster\\bigsprites3.png");
			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
		case JEONG::ME_M15:
		{
			for (size_t i = 0; i < 6; i++)
			{
				tFrame.LeftTop = Vector2(256.0f + i * 128.0f, 640.0f);
				tFrame.RightBottom = Vector2(256.0f + (i + 1) * 128.0f, 768.0f);

				vecClipFrame.push_back(tFrame);
			}
			getMater->SetDiffuseTexture(0, "MenuEnemy15" , TEXT("Monster\\bigsprites3.png"));
			m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "MenuEnemy15", L"Monster\\bigsprites3.png");
			m_ResultScale = Vector3(128.0f, 128.0f, 1.0f);

			vecClipFrame.clear();
		}
			break;
	}

	m_Animation->ChangeClip("Idle");
	m_Animation->SetDir(isRight);

	m_Transform->SetWorldPos(Pos);
	m_Transform->RotationZ(Rot);

	SAFE_RELEASE(getMater);
}

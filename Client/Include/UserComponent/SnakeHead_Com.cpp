#include "ClientHeader.h"
#include "SnakeHead_Com.h"
#include "Gonner_Com.h"

#include "SceneMain/SecondScene.h"

#include <Component/Animation2D_Com.h>
#include <Component/ColliderRect_Com.h>

#include <ObjectManager.h>

int SnakeHead_Com::m_RandNum = 0;
bool SnakeHead_Com::m_isNext = false;

SnakeHead_Com::SnakeHead_Com()
{
	m_ComType = CT_SNAKEHEAD;
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

SnakeHead_Com::SnakeHead_Com(const SnakeHead_Com & CopyData)
{
}

SnakeHead_Com::~SnakeHead_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool SnakeHead_Com::Init()
{
	m_ChangeColor[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_ChangeColor[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_ChangeColor[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	Renderer_Com* SnakeHeadRender = m_Object->AddComponent<Renderer_Com>("SnakeHead");
	SnakeHeadRender->SetMesh("TextureRect");
	SnakeHeadRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(SnakeHeadRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4::White);
	m_Material->SetDiffuseTexture(0, "SnakeHead", TEXT("Monster\\bigsprites2.png"));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("SnakeHeadAni");
	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 0.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "SnakeHead", L"Monster\\bigsprites2.png");
	vecClipFrame.clear();

	for (int i = 0; i < 2; ++i)
	{
		tFrame.LeftTop = Vector2(768.0f + i * 128.0f, 0.0f);
		tFrame.RightBottom = Vector2(768.0f + (i + 1) * 128.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	for (int i = 0; i < 8; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 128.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 256.0f);
		vecClipFrame.push_back(tFrame);
	}

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 256.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Eat", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "SnakeHead", L"Monster\\bigsprites2.png");
	vecClipFrame.clear();

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("SnakeHeadBody");
	RectColl->SetInfo(Vector3(30.0f, 0.0f, 0.0f), Vector3(100.0f, 50.0f, 0.0f));
	SAFE_RELEASE(RectColl);

	m_AniName[0] = "Idle";
	m_AniName[1] = "Eat";

	ChangeState(0, m_AniName, m_Animation);

	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.1f;

	return true;
}

int SnakeHead_Com::Input(float DeltaTime)
{
	return 0;
}

int SnakeHead_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);

	if (m_Animation->GetClipName() == "Eat")
	{
		m_isNext = true;

		if (m_Animation->GetIsEnd() == true)
		{
			CountManager::Get()->m_Gonner->GetTransform()->SetWorldPos(m_NextStagePos);
			SceneManager::Get()->ChangeScene(m_NextStageTag);
			m_isNext = false;
		}
	}

	return 0;
}

int SnakeHead_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void SnakeHead_Com::Collision(float DeltaTime)
{
}

void SnakeHead_Com::CollisionLateUpdate(float DeltaTime)
{
}

void SnakeHead_Com::Render(float DeltaTime)
{
}

SnakeHead_Com * SnakeHead_Com::Clone()
{
	return new SnakeHead_Com(*this);
}

void SnakeHead_Com::AfterClone()
{
}

void SnakeHead_Com::ChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar > m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

		m_RandNum = RandomRange(1, 3);

		switch (SnakeHead_Com::m_RandNum)
		{
		case 1:
			m_Material->SetMaterial(m_ChangeColor[SnakeHead_Com::m_RandNum - 1]);
			break;
		case 2:
			m_Material->SetMaterial(m_ChangeColor[SnakeHead_Com::m_RandNum - 1]);
			break;
		case 3:
			m_Material->SetMaterial(m_ChangeColor[SnakeHead_Com::m_RandNum - 1]);
			break;
		}
	}
}

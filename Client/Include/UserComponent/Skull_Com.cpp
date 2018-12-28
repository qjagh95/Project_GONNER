#include "ClientHeader.h"
#include "Skull_Com.h"
#include "LifeUI_Com.h"
#include "Gonner_Com.h"

JEONG_USING

int Skull_Com::m_LifeCount = 5;

Skull_Com::Skull_Com()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
}

Skull_Com::Skull_Com(const Skull_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Skull_Com::~Skull_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool Skull_Com::Init()
{
	m_ChangeColorTimeVar = 0.0f;
	m_ChangeColorTime = 0.1f;

	Renderer_Com* SkullRender = m_Object->AddComponent<Renderer_Com>("Skull");
	SkullRender->SetMesh("TextureRect");
	SkullRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(SkullRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "Skull", TEXT("Monster\\player.png"));
	m_Material->SetMaterial(Vector4(175.0f / 255.0f, 228.0f / 255.0f, 238.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("SkullAni");
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 320.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Skull", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "Skull", L"Monster\\player.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("Skull");

	Layer* UILayer = m_Scene->FindLayer("UI");

	for (int i = 0; i < 5; i++)
	{
		GameObject* newLifeUI = GameObject::CreateObject("LifeUI", UILayer);
		LifeUI_Com* newLifeUICom = newLifeUI->AddComponent< LifeUI_Com>("LifeUI");
		newLifeUICom->SetIndex(i);

		SAFE_RELEASE(newLifeUI);
		SAFE_RELEASE(newLifeUICom);
	}

	SAFE_RELEASE(UILayer);
	return true;
}

int Skull_Com::Input(float DeltaTime)
{
	return 0;
}

int Skull_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);
	m_TargetPos = Gonner_Com::m_GonnerPos;

	if (m_Animation->GetDir() == MD_LEFT)
		m_Transform->SetWorldPos(m_TargetPos.x - 8.0f, m_TargetPos.y + 8.0f, 1.0f);
	else
		m_Transform->SetWorldPos(m_TargetPos.x + 8.0f, m_TargetPos.y + 8.0f, 1.0f);

	return 0;
}

int Skull_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Skull_Com::Collision(float DeltaTime)
{
}

void Skull_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Skull_Com::Render(float DeltaTime)
{
}

Skull_Com * Skull_Com::Clone()
{
	return new Skull_Com(*this);
}

void Skull_Com::AfterClone()
{
}

void Skull_Com::ChangeColor(float DeltaTime)
{
	m_ChangeColorTimeVar += DeltaTime;

	if (m_ChangeColorTimeVar > m_ChangeColorTime)
	{
		m_ChangeColorTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4(175.0f / 255.0f, 228.0f / 255.0f, 238.0f / 255.0f, 1.0f))
			m_Material->SetMaterial(m_Material->GetDiffuseLight() * 1.1f);
		else
			m_Material->SetMaterial(Vector4(175.0f / 255.0f, 228.0f / 255.0f, 238.0f / 255.0f, 1.0f));
	}
}

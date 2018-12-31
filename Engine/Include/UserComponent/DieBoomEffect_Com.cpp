#include "stdafx.h"
#include "DieBoomEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

DieBoomEffect_Com::DieBoomEffect_Com()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
}

DieBoomEffect_Com::DieBoomEffect_Com(const DieBoomEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

DieBoomEffect_Com::~DieBoomEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool DieBoomEffect_Com::Init()
{
	Renderer_Com* DieBoomEffectRender = m_Object->AddComponent<Renderer_Com>("DieBoomEffect");
	DieBoomEffectRender->SetMesh("TextureRect");
	DieBoomEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(DieBoomEffectRender);

	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "DieBoomEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("DieBoomEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 9; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 128.0f, 1024.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 128.0f, 1152.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("DieBoomEffect", A2D_ATLS, AO_ONCE_STOP, 1.0f, vecClipFrame, "DieBoomEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("DieBoomEffect");

	return true;
}

int DieBoomEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int DieBoomEffect_Com::Update(float DeltaTime)
{
	if (m_Animation->GetIsEnd() == true)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}

	return 0;
}

int DieBoomEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void DieBoomEffect_Com::Collision(float DeltaTime)
{
}

void DieBoomEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void DieBoomEffect_Com::Render(float DeltaTime)
{
}

DieBoomEffect_Com * DieBoomEffect_Com::Clone()
{
	return new DieBoomEffect_Com(*this);
}

void DieBoomEffect_Com::AfterClone()
{
}

void DieBoomEffect_Com::SetPos(const Vector3 & Pos)
{
	m_Transform->SetWorldPos(Pos);
}

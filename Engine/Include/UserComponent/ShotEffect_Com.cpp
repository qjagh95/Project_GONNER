#include "stdafx.h"
#include "ShotEffect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

ShotEffect_Com::ShotEffect_Com()
{
}


ShotEffect_Com::ShotEffect_Com(const ShotEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

ShotEffect_Com::~ShotEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool ShotEffect_Com::Init()
{
	Renderer_Com* ShotEffectRender = m_Object->AddComponent<Renderer_Com>("ShotEffect");
	ShotEffectRender->SetMesh("TextureRect");
	ShotEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(ShotEffectRender);

	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "ShotEffect", TEXT("Monster\\sprites.png"));
	m_Material->SetMaterial(Vector4(117.0f / 255.0f, 108.0f / 255.0f, 113.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("ShotEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("ShotEffect", A2D_ATLS, AO_ONCE_STOP, 0.3f, vecClipFrame, "ShotEffect", L"Monster\\sprites.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("ShotEffect");

	return true;
}

int ShotEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int ShotEffect_Com::Update(float DeltaTime)
{
	if (m_Animation->GetIsEnd() == true)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}
	return 0;
}

int ShotEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ShotEffect_Com::Collision(float DeltaTime)
{
}

void ShotEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ShotEffect_Com::Render(float DeltaTime)
{
}

ShotEffect_Com * ShotEffect_Com::Clone()
{
	return new ShotEffect_Com(*this);
}

void ShotEffect_Com::AfterClone()
{
}

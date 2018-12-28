#include "stdafx.h"
#include "DieEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

DieEffect_Com::DieEffect_Com()
{
}


DieEffect_Com::DieEffect_Com(const DieEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

DieEffect_Com::~DieEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool DieEffect_Com::Init()
{
	Renderer_Com* DieEffectRender = m_Object->AddComponent<Renderer_Com>("DieEffect");
	DieEffectRender->SetMesh("TextureRect");
	DieEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(DieEffectRender);

	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "DieEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("DieEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 11; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 128.0f, 640.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 128.0f, 768.0f);
		vecClipFrame.push_back(tFrame);
	}

	for (int i = 0; i < 5; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 768.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 896.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("DieEffect", A2D_ATLS, AO_ONCE_STOP, 1.0f, vecClipFrame, "DieEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("DieEffect");

	return true;
}

int DieEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int DieEffect_Com::Update(float DeltaTime)
{
	float RangeX = (float)RandomRange(-15, 15);
	float RangeY = (float)RandomRange(-15, 15);

	m_Transform->SetWorldPos(m_SavePos.x + RangeX, m_SavePos.y + RangeY, 1.0f);

	if (m_Animation->GetIsEnd() == true)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}

	return 0;
}

int DieEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void DieEffect_Com::Collision(float DeltaTime)
{
}

void DieEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void DieEffect_Com::Render(float DeltaTime)
{
}

DieEffect_Com * DieEffect_Com::Clone()
{
	return new DieEffect_Com(*this);
}

void DieEffect_Com::AfterClone()
{
}

void DieEffect_Com::SetPos(const Vector3 & Pos)
{
	m_Transform->SetWorldPos(Pos);
	m_SavePos = Pos;
}

#include "stdafx.h"
#include "BalloonEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

BallonEffect_Com::BallonEffect_Com()
{
}

BallonEffect_Com::BallonEffect_Com(const BallonEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BallonEffect_Com::~BallonEffect_Com()
{
}

bool BallonEffect_Com::Init()
{
	Renderer_Com* BallonEffectRender = m_Object->AddComponent<Renderer_Com>("BallonEffect");
	BallonEffectRender->SetMesh("TextureRect");
	BallonEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BallonEffectRender);

	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BallonEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BallonEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 8; ++i)
	{
		tFrame.LeftTop = Vector2(1024.0f + i * 128.0f, 1536.0f);
		tFrame.RightBottom = Vector2(1024.0f + (i + 1) * 128.0f, 1664.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BallonEffect", A2D_ATLS, AO_ONCE_DESTROY, 0.7f, vecClipFrame, "BallonEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("BallonEffect");

	return true;
}

int BallonEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int BallonEffect_Com::Update(float DeltaTime)
{
	return 0;
}

int BallonEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BallonEffect_Com::Collision(float DeltaTime)
{
}

void BallonEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BallonEffect_Com::Render(float DeltaTime)
{
}

BallonEffect_Com * BallonEffect_Com::Clone()
{
	return new BallonEffect_Com(*this);
}

void BallonEffect_Com::AfterClone()
{
}

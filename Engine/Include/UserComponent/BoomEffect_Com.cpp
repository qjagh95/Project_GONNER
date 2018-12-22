#include "stdafx.h"
#include "BoomEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

BoomEffect_Com::BoomEffect_Com()
{
}

BoomEffect_Com::BoomEffect_Com(const BoomEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BoomEffect_Com::~BoomEffect_Com()
{
}

bool BoomEffect_Com::Init()
{
	Renderer_Com* BoomEffectRender = m_Object->AddComponent<Renderer_Com>("BoomEffect");
	BoomEffectRender->SetMesh("TextureRect");
	BoomEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BoomEffectRender);

	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BoomEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BoomEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 8; ++i)
	{
		tFrame.LeftTop = Vector2(1024.0f + i * 128.0f, 1536.0f);
		tFrame.RightBottom = Vector2(1024.0f + (i + 1) * 128.0f, 1664.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BoomEffect", A2D_ATLS, AO_ONCE_DESTROY, 0.7f, vecClipFrame, "BoomEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("BoomEffect");

	return true;
}

int BoomEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int BoomEffect_Com::Update(float DeltaTime)
{
	return 0;
}

int BoomEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BoomEffect_Com::Collision(float DeltaTime)
{
}

void BoomEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BoomEffect_Com::Render(float DeltaTime)
{
}

BoomEffect_Com * BoomEffect_Com::Clone()
{
	return new BoomEffect_Com(*this);
}

void BoomEffect_Com::AfterClone()
{
}

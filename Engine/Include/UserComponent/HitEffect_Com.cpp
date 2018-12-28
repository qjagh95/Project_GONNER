#include "stdafx.h"
#include "HitEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

HitEffect_Com::HitEffect_Com()
{
}

HitEffect_Com::HitEffect_Com(const HitEffect_Com & CopyData)
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

HitEffect_Com::~HitEffect_Com()
{
}

bool HitEffect_Com::Init()
{
	//Renderer_Com* HitEffectRender = m_Object->AddComponent<Renderer_Com>("HitEffect");
	//HitEffectRender->SetMesh("TextureRect");
	//HitEffectRender->SetRenderState(ALPHA_BLEND);
	//SAFE_RELEASE(HitEffectRender);

	//m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	//m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	//m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	//m_Material->SetMaterial(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));

	//m_Animation = m_Object->AddComponent<Animation2D_Com>("HitEffectAni");

	//vector<Clip2DFrame>	vecClipFrame;
	//Clip2DFrame	tFrame = {};
	//for (int i = 0; i < 11; ++i)
	//{
	//	tFrame.LeftTop = Vector2(640.0f + i * 128.0f, 640.0f);
	//	tFrame.RightBottom = Vector2(640.0f + (i + 1) * 128.0f, 768.0f);
	//	vecClipFrame.push_back(tFrame);
	//}

	//m_Animation->AddClip("HitEffect", A2D_ATLS, AO_ONCE_STOP, 1.0f, vecClipFrame, "HitEffect", L"Monster\\bloodParticles.png");
	//vecClipFrame.clear();

	//m_Animation->ChangeClip("HitEffect");

	return true;
}

int HitEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int HitEffect_Com::Update(float DeltaTime)
{
	return 0;
}

int HitEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void HitEffect_Com::Collision(float DeltaTime)
{
}

void HitEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void HitEffect_Com::Render(float DeltaTime)
{
}

HitEffect_Com * HitEffect_Com::Clone()
{
	return new HitEffect_Com(*this);
}

void HitEffect_Com::AfterClone()
{
}

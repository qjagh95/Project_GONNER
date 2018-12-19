#include "stdafx.h"
#include "Gun_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

Gun_Com::Gun_Com()
{
}

Gun_Com::Gun_Com(const Gun_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Gun_Com::~Gun_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool Gun_Com::Init()
{
	Renderer_Com* BubbleRender = m_Object->AddComponent<Renderer_Com>("BubbleRender");
	BubbleRender->SetMesh("TextureRect");
	BubbleRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BubbleRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "Bubble", TEXT("Effect\\bloodParticles.png"));

	return true;
}

int Gun_Com::Input(float DeltaTime)
{
	return 0;
}

int Gun_Com::Update(float DeltaTime)
{
	return 0;
}

int Gun_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Gun_Com::Collision(float DeltaTime)
{
}

void Gun_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Gun_Com::Render(float DeltaTime)
{
}

Gun_Com * Gun_Com::Clone()
{
	return new Gun_Com(*this);
}

void Gun_Com::AfterClone()
{
}

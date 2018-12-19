#include "stdafx.h"
#include "GunItem_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

GunItem_Com::GunItem_Com()
{
}

GunItem_Com::GunItem_Com(const GunItem_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

GunItem_Com::~GunItem_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool GunItem_Com::Init()
{
	Renderer_Com* BubbleRender = m_Object->AddComponent<Renderer_Com>("GunItem");
	BubbleRender->SetMesh("TextureRect");
	BubbleRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BubbleRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "GunItem", TEXT("Effect\\bloodParticles.png"));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("GunItemAni");


	return true;
}

int GunItem_Com::Input(float DeltaTime)
{
	return 0;
}

int GunItem_Com::Update(float DeltaTime)
{
	return 0;
}

int GunItem_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void GunItem_Com::Collision(float DeltaTime)
{
}

void GunItem_Com::CollisionLateUpdate(float DeltaTime)
{
}

void GunItem_Com::Render(float DeltaTime)
{
}

GunItem_Com * GunItem_Com::Clone()
{
	return new GunItem_Com(*this);
}

void GunItem_Com::AfterClone()
{
}

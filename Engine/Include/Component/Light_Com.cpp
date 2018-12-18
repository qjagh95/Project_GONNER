#include "stdafx.h"
#include "Light_Com.h"

JEONG_USING

Light_Com::Light_Com()
{
}

Light_Com::Light_Com(const Light_Com & CopyData)
	:Component_Base(CopyData)
{
}

Light_Com::~Light_Com()
{
}

bool Light_Com::Init()
{
	Renderer_Com* LightRender = m_Object->AddComponent<Renderer_Com>("ButtonRender");
	LightRender->SetMesh("TextureRect");
	LightRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(LightRender);

	Material_Com* getMat = m_Object->FindComponentFromType< Material_Com>(CT_MATERIAL);
	getMat->SetDiffuseTexture(0, "Light", TEXT("Light.png"));
	getMat->SetMaterial(Vector4(1.0f, 0.0f, 0.0f, 0.5f));
	SAFE_RELEASE(getMat);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Transform->SetWorldScale(100.0f, 100.0f, 1.0f);

	return true;
}

int Light_Com::Input(float DeltaTime)
{
	return 0;
}

int Light_Com::Update(float DeltaTime)
{
	return 0;
}

int Light_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Light_Com::Collision(float DeltaTime)
{
}

void Light_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Light_Com::Render(float DeltaTime)
{
}

Light_Com * Light_Com::Clone()
{
	return nullptr;
}

void Light_Com::AfterClone()
{
}

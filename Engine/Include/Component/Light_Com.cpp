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
	Renderer_Com* ButtonRender = m_Object->AddComponent<Renderer_Com>("ButtonRender");
	ButtonRender->SetMesh("TextureRect");
	ButtonRender->SetRenderState(ALPHA_BLEND);
	ButtonRender->CreateRendererCBuffer("ButtonCBuffer", sizeof(ButtonCBuffer));
	SAFE_RELEASE(ButtonRender);

	Material_Com* getMat = m_Object->FindComponentFromType< Material_Com>(CT_MATERIAL);
	getMat->SetDiffuseTexture(1, "Light", TEXT("Light.png"));
	SAFE_RELEASE(getMat);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

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

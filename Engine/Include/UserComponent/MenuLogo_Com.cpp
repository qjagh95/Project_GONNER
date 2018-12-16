#include "stdafx.h"
#include "MenuLogo_Com.h"

JEONG_USING

MenuLogo_Com::MenuLogo_Com()
{
}

MenuLogo_Com::MenuLogo_Com(const MenuLogo_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

MenuLogo_Com::~MenuLogo_Com()
{
}

bool MenuLogo_Com::Init()
{
	Renderer_Com* LogoRender = m_Object->AddComponent<Renderer_Com>("LogoRender");
	LogoRender->SetMesh("TextureRect");
	LogoRender->SetRenderState(ALPHA_BLEND);
	LogoRender->SetShader(LOGO_SHADER);
	LogoRender->SetScreenRender(true);
	LogoRender->CreateRendererCBuffer("LogoCBuffer", sizeof(LogoCBuffer));

	Material_Com* LogoMat = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	LogoMat->SetDiffuseTexture(0, "Logo", TEXT("Gonner_Headerv2_bg_small.png"));
	LogoMat->SetSampler(1, CLAMP_SAMPLER);

	SAFE_RELEASE(LogoMat);
	SAFE_RELEASE(LogoRender);

	m_Transform->SetWorldScale(1013.0f, 500.0f, 1.0f);
	m_Transform->SetWorldPos(Vector3::Zero);

	m_CBuffer.UVSpeed = 0.0f;
	return true;
}

int MenuLogo_Com::Input(float DeltaTime)
{
	return 0;
}

int MenuLogo_Com::Update(float DeltaTime)
{
	m_CBuffer.UVSpeed += DeltaTime;

	return 0;
}

int MenuLogo_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void MenuLogo_Com::Collision(float DeltaTime)
{
}

void MenuLogo_Com::CollisionLateUpdate(float DeltaTime)
{
}

void MenuLogo_Com::Render(float DeltaTime)
{
	Renderer_Com* getRender = m_Object->FindComponentFromType< Renderer_Com>(CT_RENDER);
	getRender->UpdateRendererCBuffer("LogoCBuffer", &m_CBuffer, sizeof(LogoCBuffer));

	SAFE_RELEASE(getRender);
}

MenuLogo_Com * MenuLogo_Com::Clone()
{
	return new MenuLogo_Com(*this);
}

void MenuLogo_Com::AfterClone()
{
}

#include "stdafx.h"
#include "Fade_Com.h"

JEONG_USING

Fade_Com::Fade_Com()
{
	m_isStart = false;
	m_isOver = false;
	m_isInOut = false;
}

Fade_Com::Fade_Com(const Fade_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Fade_Com::~Fade_Com()
{
}

bool Fade_Com::Init()
{
	Renderer_Com* FadeRender = m_Object->AddComponent<Renderer_Com>("FadeRender");
	FadeRender->SetMesh("TextureRect");
	FadeRender->SetRenderState(ALPHA_BLEND);
	FadeRender->SetShader(FADE_SHADER);
	FadeRender->CreateRendererCBuffer("FadeCBuffer", sizeof(FadeCBuffer));
	FadeRender->SetScreenRender(true);

	SAFE_RELEASE(FadeRender);

	m_Transform->SetWorldScale(Vector3((float)Device::Get()->GetWinSize().Width, (float)Device::Get()->GetWinSize().Height, 1.0f));

	m_CBuffer.isStart = false;
	m_CBuffer.Light = Vector4(1.0f, 1.0f, 1.0f, 0.0f);
	m_CBuffer.Speed = 0.3f;

	return true;
}

int Fade_Com::Input(float DeltaTime)
{
	return 0;
}

int Fade_Com::Update(float DeltaTime)
{
	switch (m_Option)
	{
		case FO_IN:
			FadeIn(DeltaTime);
			break;
		case FO_OUT:
			FadeOut(DeltaTime);
			break;
		case FO_INOUT:
			FadeInOut(DeltaTime);
			break;
	}

	return 0;
}

int Fade_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Fade_Com::Collision(float DeltaTime)
{
}

void Fade_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Fade_Com::Render(float DeltaTime)
{
	Renderer_Com* getRender = m_Object->FindComponentFromType< Renderer_Com>(CT_RENDER);
	getRender->UpdateRendererCBuffer("FadeCBuffer", &m_CBuffer, sizeof(FadeCBuffer));
	SAFE_RELEASE(getRender);
}

Fade_Com * Fade_Com::Clone()
{
	return new Fade_Com(*this);
}

void Fade_Com::AfterClone()
{
}

void Fade_Com::Start()
{
	m_isStart = true;
}

void Fade_Com::SetFadeColor(const Vector3 & Color, FADE_OPTION Option)
{
	m_CBuffer.Light.r = Color.r;
	m_CBuffer.Light.g = Color.g;
	m_CBuffer.Light.b = Color.b;

	m_Option = Option;

	switch (Option)
	{
		case FO_IN:
			m_CBuffer.Light.a = 0.0f;
			break;
		case FO_OUT:
			m_CBuffer.Light.a = 1.0f;
			break;
		case FO_INOUT:
			m_CBuffer.Light.a = 0.0f;
			break;
	}
}

void Fade_Com::FadeIn(float DeltaTime)
{
	if (m_isStart == true)
		m_CBuffer.Light.a += m_CBuffer.Speed * DeltaTime;

	if (m_CBuffer.Light.a >= 1.0f)
	{
		m_isOver = true;
		m_isStart = false;
	}
}

void Fade_Com::FadeOut(float DeltaTime)
{
	if (m_isStart == true)
		m_CBuffer.Light.a -= m_CBuffer.Speed * DeltaTime;

	if (m_CBuffer.Light.a <= 0.0f)
	{
		m_isOver = true;
		m_isStart = false;
	}
}

void Fade_Com::FadeInOut(float DeltaTime)
{
	if (m_isStart == true)
	{
		m_CBuffer.Light.a += m_CBuffer.Speed * DeltaTime;

		if (m_CBuffer.Light.a >= 1.0f)
			m_isStart = false;
	}
	else 
	{
		m_CBuffer.Light.a -= m_CBuffer.Speed * DeltaTime;

		if (m_CBuffer.Light.a <= 0.0f)
			m_isInOut = true;
	}
	
}

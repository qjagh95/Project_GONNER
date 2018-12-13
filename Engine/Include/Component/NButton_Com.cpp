#include "stdafx.h"
#include "NButton_Com.h"
#include "ColliderRect_Com.h"

JEONG_USING

NButton_Com::NButton_Com()
{
	m_ComType = CT_BUTTON;
	SetTag("NButton");
	m_isMouse = false;
}

NButton_Com::NButton_Com(const NButton_Com & CopyData)
	:Component_Base(CopyData)
{
	m_ButtonState = BS_NORMAL;
	memcpy(m_ButtonColor, CopyData.m_ButtonColor, sizeof(Vector4) * BS_MAX);
}

NButton_Com::~NButton_Com()
{
	SAFE_RELEASE(m_RectColl);
}

bool NButton_Com::Init()
{
	Renderer_Com* ButtonRender = m_Object->AddComponent<Renderer_Com>("ButtonRender");
	ButtonRender->SetMesh("TextureRect");
	ButtonRender->SetRenderState(ALPHA_BLEND);
	ButtonRender->SetShader(BUTTON_SHADER);
	ButtonRender->CreateRendererCBuffer("ButtonCBuffer", sizeof(ButtonCBuffer));
	ButtonRender->SetScreenRender(true);
	SAFE_RELEASE(ButtonRender);

	m_RectColl = m_Object->AddComponent<ColliderRect_Com>("ButtonBody");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(200.0f, 50.0f, 0.0f));
	m_RectColl->SetCollisionGroup("UI");
	m_RectColl->SetCollsionCallback(CCT_DOING, this, &NButton_Com::MouseHit);
	m_RectColl->SetCollsionCallback(CCT_END, this, &NButton_Com::MouseOut);

	m_ButtonState = BS_NORMAL;

	m_ButtonColor[BS_DISABLE] = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_ButtonColor[BS_NORMAL] = Vector4(0.9f, 0.9f, 0.9f, 1.0f);
	m_ButtonColor[BS_MOUSEOVER] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_ButtonColor[BS_CLICK] = Vector4(0.7f, 0.7f, 0.7f, 1.0f);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	return true;
}

int NButton_Com::Input(float DeltaTime)
{
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), m_Transform->GetWorldScale());

	return 0;
}

int NButton_Com::Update(float DeltaTime)
{
	return 0;
}

int NButton_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void NButton_Com::Collision(float DeltaTime)
{
}

void NButton_Com::CollisionLateUpdate(float DeltaTime)
{
	switch (m_ButtonState)
	{
		case BS_NORMAL:
			m_Transform->SetWorldScale(m_SaveScale * 0.9f);
			break;
		case BS_MOUSEOVER:
			m_Transform->SetWorldScale(m_SaveScale * 1.1f);
			break;
	}
}

void NButton_Com::Render(float DeltaTime)
{
	m_ButtonCBuffer.DiffuseColor = m_ButtonColor[m_ButtonState];

	Renderer_Com* getRender = FindComponentFromType<Renderer_Com>(CT_RENDER);
	getRender->UpdateRendererCBuffer("ButtonCBuffer", &m_ButtonCBuffer, sizeof(ButtonCBuffer));
	SAFE_RELEASE(getRender);
}

NButton_Com * NButton_Com::Clone()
{
	return new NButton_Com(*this);
}

void NButton_Com::AfterClone()
{
}

void NButton_Com::Disable()
{
	m_ButtonState = BS_DISABLE;

}
void NButton_Com::SetNormal()
{
	m_ButtonState = BS_NORMAL;
}

void NButton_Com::SetStateColor(BUTTON_STATE eState, const Vector4 & Color)
{
	m_ButtonColor[eState] = Color;
}

void NButton_Com::SetStateColor(BUTTON_STATE eState, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_ButtonColor[eState] = Vector4(r, g, b, a);
}

void NButton_Com::MouseHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
}

void NButton_Com::MouseOut(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
}

void NButton_Com::SetTexture(const string& KeyName,const TCHAR* FileName)
{
	Material_Com* getMat = m_Object->FindComponentFromType< Material_Com>(CT_MATERIAL);
	getMat->SetDiffuseTexture(0, KeyName, FileName);
	SAFE_RELEASE(getMat);
}

void NButton_Com::ActiveFunction(float DeltaTime)
{
	m_ButtonCallBack(DeltaTime);
}
void NButton_Com::LightOn()
{
	m_ButtonState = BS_MOUSEOVER;
}

void NButton_Com::LightOff()
{
	m_ButtonState = BS_NORMAL;
}
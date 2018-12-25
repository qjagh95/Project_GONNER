#include "stdafx.h"
#include "HeartUI_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

HeartUI_Com::HeartUI_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

HeartUI_Com::HeartUI_Com(const HeartUI_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

HeartUI_Com::~HeartUI_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool HeartUI_Com::Init()
{

	Renderer_Com* HeartItemRender = m_Object->AddComponent<Renderer_Com>("HeartUIRender");
	HeartItemRender->SetMesh("TextureRect");
	HeartItemRender->SetScreenRender(true);
	HeartItemRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(HeartItemRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Animation = m_Object->AddComponent<Animation2D_Com>("HeartUIAni");
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("HeartUI", A2D_ATLS, AO_LOOP, 0.7f, vecClipFrame, "HeartUI", L"weapons.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("HeartUI");
	return true;
}

int HeartUI_Com::Input(float DeltaTime)
{
	return 0;
}

int HeartUI_Com::Update(float DeltaTime)
{
	return 0;
}

int HeartUI_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void HeartUI_Com::Collision(float DeltaTime)
{
}

void HeartUI_Com::CollisionLateUpdate(float DeltaTime)
{
}

void HeartUI_Com::Render(float DeltaTime)
{
}

HeartUI_Com * HeartUI_Com::Clone()
{
	return new  HeartUI_Com(*this);
}

void HeartUI_Com::AfterClone()
{
}

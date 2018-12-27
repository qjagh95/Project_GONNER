#include "stdafx.h"
#include "GuardM_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

GuardM_Com::GuardM_Com()
{
	m_Type = MT_GUARD;
}

GuardM_Com::GuardM_Com(const GuardM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

GuardM_Com::~GuardM_Com()
{
}

bool GuardM_Com::Init()
{
	Monster_Base::Init();

	m_Hp = 2;

	m_Animation = m_Object->AddComponent<Animation2D_Com>("GuardAni");
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 320.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Guard", L"weapons.png");
	vecClipFrame.clear();

	m_AniName[GS_IDLE] = "Idle";
	m_AniName[GS_MOVE] = "Move";
	m_AniName[GS_HIT] = "Hit";
	m_AniName[GS_GUARD] = "Guard";

	return true;
}

int GuardM_Com::Input(float DeltaTime)
{
	return 0;
}

int GuardM_Com::Update(float DeltaTime)
{
	return 0;
}

int GuardM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void GuardM_Com::Collision(float DeltaTime)
{
}

void GuardM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void GuardM_Com::Render(float DeltaTime)
{
}

GuardM_Com * GuardM_Com::Clone()
{
	return new GuardM_Com(*this);
}

void GuardM_Com::AfterClone()
{
}

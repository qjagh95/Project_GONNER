#include "stdafx.h"
#include "GuardM_Com.h"

#include "../Component/Animation2D_Com.h"
#include "../Component/ColliderRect_Com.h"
#include "../Component/Gravity_Com.h"

JEONG_USING

GuardM_Com::GuardM_Com()
{
	m_Type = MT_GUARD;

	m_IdleTime = 2.0f;
	m_IdleTimeVar = 0.0f;

	m_GuardTime = 2.0f;
	m_GuardTimeVar = 0.0f;
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

	m_Gravity = m_Object->AddComponent<Gravity_Com>("Gravity");
	m_Gravity->SetStage(StageManager::Get()->FindCurStage());

	m_Hp = 2;

	m_RectColl->SetInfo(Vector3::Zero, Vector3(128.0f, 128.0f, 1.0f));
	m_Material->SetDiffuseTexture(0, "Guard", TEXT("Monster\\bigsprites3.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("GuardAni");
	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(128.0f + i * 128.0f, 128.0f);
		tFrame.RightBottom = Vector2(128.0f + (i + 1) * 128.0f, 256.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Guard", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	tFrame.LeftTop = Vector2(896.0f, 128.0f);
	tFrame.RightBottom = Vector2(896.0f + 128.0f, 256.0f);
	vecClipFrame.push_back(tFrame);

	for (int i = 0; i < 5; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 256.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Move", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Guard", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	for (int i = 0; i < 3; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 128.0f, 256.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 128.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	tFrame.LeftTop = Vector2(0.0f, 384.0f);
	tFrame.RightBottom = Vector2(128.0f, 512.0f);
	vecClipFrame.push_back(tFrame);

	m_Animation->AddClip("Hit", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Guard", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	for (int i = 0; i < 7; ++i)
	{
		tFrame.LeftTop = Vector2(128.0f + i * 128.0f, 384.0f);
		tFrame.RightBottom = Vector2(128.0f + (i + 1) * 128.0f, 512.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Guard", A2D_ATLS, AO_ONCE_STOP, 0.5f, vecClipFrame, "Guard", L"Monster\\binsprites3.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 512.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 640.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("GuardDown", A2D_ATLS, AO_ONCE_STOP, 0.5f, vecClipFrame, "Guard", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	m_AniName[GS_IDLE] = "Idle";
	m_AniName[GS_MOVE] = "Move";
	m_AniName[GS_HIT] = "Hit";
	m_AniName[GS_GUARD] = "Guard";
	m_AniName[GS_GUARDDOWN] = "GuardDown";

	ChangeState(GS_GUARDDOWN, m_AniName, m_Animation);

	return true;
}

int GuardM_Com::Input(float DeltaTime)
{
	return 0;
}

int GuardM_Com::Update(float DeltaTime)
{
	Monster_Base::Update(DeltaTime);

	switch (m_State)
	{
		case GS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case GS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case GS_HIT:
			FS_HIT(DeltaTime);
			break;
		case GS_GUARD:
			FS_GUARD(DeltaTime);
			break;
		case GS_GUARDDOWN:
			FS_GUARDDOWN(DeltaTime);
			break;
	}

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

void GuardM_Com::FS_IDLE(float DeltaTime)
{
}

void GuardM_Com::FS_MOVE(float DeltaTime)
{
}

void GuardM_Com::FS_HIT(float DeltaTime)
{
}

void GuardM_Com::FS_GUARD(float DeltaTime)
{
}

void GuardM_Com::FS_GUARDDOWN(float DeltaTime)
{
}

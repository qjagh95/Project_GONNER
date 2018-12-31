#include "stdafx.h"
#include "TraceM_Com.h"

#include "../Component/Animation2D_Com.h"
#include "../Component/ColliderRect_Com.h"

JEONG_USING

TraceM_Com::TraceM_Com()
{
	m_Type = MT_TRACE;
}

TraceM_Com::TraceM_Com(const TraceM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

TraceM_Com::~TraceM_Com()
{
}

bool TraceM_Com::Init()
{
	Monster_Base::Init();

	m_Hp = 2;

	m_Material->SetDiffuseTexture(0, "Trace", TEXT("Monster\\smallenemies.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("Trace");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 1.0f));
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);
	m_Animation->SetDir(MD_RIGHT);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 128.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 192.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Trace", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 128.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 192.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Move", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Trace", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 64.0f, 128.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 64.0f, 192.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Hit", A2D_ATLS, AO_LOOP, 0.3f, vecClipFrame, "Trace", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	m_AniName[TRS_IDLE] = "Idle";
	m_AniName[TRS_MOVE] = "Move";
	m_AniName[TRS_TRACE] = "Move";
	m_AniName[TRS_HIT] = "Hit";

	ChangeState(TRS_IDLE, m_AniName, m_Animation);

	return true;
}

int TraceM_Com::Input(float DeltaTime)
{
	return 0;
}

int TraceM_Com::Update(float DeltaTime)
{
	Monster_Base::Update(DeltaTime);

	switch (m_State)
	{
	case TRS_IDLE:
		FS_IDLE(DeltaTime);
		break;
	case TRS_TRACE:
		FS_TRACE(DeltaTime);
		break;
	case TRS_HIT:
		FS_HIT(DeltaTime);
		break;
	}

	return 0;
}

int TraceM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void TraceM_Com::Collision(float DeltaTime)
{
}

void TraceM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void TraceM_Com::Render(float DeltaTime)
{
}

TraceM_Com * TraceM_Com::Clone()
{
	return new TraceM_Com(*this);
}

void TraceM_Com::AfterClone()
{
}

void TraceM_Com::FS_IDLE(float DeltaTime)
{
}

void TraceM_Com::FS_MOVE(float DeltaTime)
{
}

void TraceM_Com::FS_TRACE(float DeltaTime)
{
	TraceMove(DeltaTime);
}

void TraceM_Com::FS_HIT(float DeltaTime)
{
}

void TraceM_Com::TraceMove(float DeltaTime)
{
	Vector3 Look = m_TargetPos - m_Pos;
	Look.Nomallize();

	float Angle = m_Pos.GetAngle(m_TargetPos);

	m_Transform->SetWorldRotZ(Angle);
	m_Transform->Move(Look, 300.0f, DeltaTime);
}

void TraceM_Com::RangeCheck(float DeltaTime)
{
	float Range = 100;

	if (m_Pos.GetDistance(m_TargetPos) >= Range)
		return;

	ChangeState(TRS_TRACE, m_AniName, m_Animation);
}

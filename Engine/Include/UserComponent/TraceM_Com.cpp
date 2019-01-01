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
	m_HitAngle = 0.0f;
	m_TraceTime = 3.0f;
	m_TraceTimeVar = 0.0f;
	m_Dir = 0.0f;

	m_Material->SetDiffuseTexture(0, "Trace", TEXT("Monster\\smallenemies.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("Trace");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 1.0f));
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Animation->SetDir(MD_RIGHT);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 64.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Trace", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 64.0f, 64.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 64.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Move", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Trace", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(768.0f + i * 64.0f, 64.0f);
		tFrame.RightBottom = Vector2(768.0f + (i + 1) * 64.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Hit", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "Trace", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	m_AniName[TRS_IDLE] = "Idle";
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
	RangeCheck(DeltaTime);
}

void TraceM_Com::FS_TRACE(float DeltaTime)
{
	TraceMove(DeltaTime);
}

void TraceM_Com::FS_HIT(float DeltaTime)
{
	if (m_Dir == 1.0f)
	{
		if (m_LeftTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, -100.0f, DeltaTime);
	}
	else
	{
		if (m_RightTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, 100.0f, DeltaTime);
	}
	
	m_Transform->RotationZFromNoneAxis(1000.0f * DeltaTime);

	if (m_Transform->GetWorldRotationZ() >= 360.0f)
	{
		m_HitAngle = 0.0f;
		m_Transform->SetWorldRotZ(0.0f);

		if (m_Animation->GetIsEnd() == true)
			ChangeState(TRS_TRACE, m_AniName, m_Animation);
	}
}

void TraceM_Com::TraceMove(float DeltaTime)
{
	m_TraceTimeVar += DeltaTime;

	if (m_TraceTimeVar >= m_TraceTime)
	{
		m_TraceTimeVar = 0.0f;
		ChangeState(TRS_IDLE, m_AniName, m_Animation);
		return;
	}

	Vector3 Look = m_TargetPos - m_Pos;

	if (Look.x < 0.0f)
		m_Animation->SetDir(MD_LEFT);
	else
		m_Animation->SetDir(MD_RIGHT);

	Look.Nomallize();

	float Angle = m_TargetPos.GetAngle(m_Pos);
	m_Transform->SetWorldRotZ(-Angle);

	Vector3 LookPos = m_Pos + Look;
	LookPos += (m_Scale * Look);

	Tile2D_Com* LookTile = m_Stage->GetTile2D(LookPos);

	if (LookTile->GetTileOption() != T2D_NOMOVE)
		m_Transform->Move(Look, 200.0f, DeltaTime);
	else
		ChangeState(TRS_IDLE, m_AniName, m_Animation);
}

void TraceM_Com::RangeCheck(float DeltaTime)
{
	float Range = 200.0f;

	if (m_Pos.GetDistance(m_TargetPos) >= Range)
		return;

	ChangeState(TRS_TRACE, m_AniName, m_Animation);
}

void TraceM_Com::BulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		Vector3 dPos = Dest->GetGameObject()->GetTransform()->GetWorldPos();
		SoundManager::Get()->FindSoundEffect("BulletColl")->Play();
		Dest->GetGameObject()->SetIsActive(false);

		HitEffectOut(DeltaTime);

		if (m_Hp > 0)
		{
			Vector3 Look = Dest->GetGameObject()->GetTransform()->GetWorldPos();
			Look -= m_Pos;

			if (Look.x < 0.0f)
				m_Dir = -1.0f;
			else if(Look.x > 0.0f)
				m_Dir = 1.0f;

			m_Camera->SetShake(5.0f, 0.3f);
			m_Scene->CreateWave(m_CenterPos, 0.8f, 0.05f);
			ChangeState(TRS_HIT, m_AniName, m_Animation);
			m_Hp--;
		}
	}

	if (Dest->GetTag() == "GonnerBody")
	{
		if (m_GonnerJumpAttack == true)
		{
			if (m_Hp > 0)
			{
				m_Camera->SetShake(5.0f, 0.3f);
				ChangeState(TRS_HIT, m_AniName, m_Animation);
				m_Hp--;
			}
		}
	}
}
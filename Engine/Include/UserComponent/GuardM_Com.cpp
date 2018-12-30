#include "stdafx.h"
#include "GuardM_Com.h"
#include "BasicEffect_Com.h"
#include "HitEffect_Com.h"

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

	m_GuardRange = 200.0f;

	m_MoveTime = 3.0f;
	m_MoveTimeVar = 0.0f;
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

	m_Hp = 3;

	m_Material->SetDiffuseTexture(0, "Guard", TEXT("Monster\\bigsprites3.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("GuardAni");
	m_RectColl->SetInfo(Vector3(30.0f, 0.0f, 0.0f), Vector3(100.0f, 100.0f, 1.0f));
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

	m_Animation->AddClip("Hit", A2D_ATLS, AO_ONCE_STOP, 0.3f, vecClipFrame, "Guard", L"Monster\\bigsprites3.png");
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

	m_Animation->AddClip("GuardDown", A2D_ATLS, AO_ONCE_STOP, 0.3f, vecClipFrame, "Guard", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	m_AniName[GUS_IDLE] = "Idle";
	m_AniName[GUS_MOVE] = "Move";
	m_AniName[GUS_HIT] = "Hit";
	m_AniName[GUS_GUARD] = "Guard";
	m_AniName[GUS_GUARDDOWN] = "GuardDown";

	ChangeState(GUS_IDLE, m_AniName, m_Animation);

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
		case GUS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case GUS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case GUS_HIT:
			FS_HIT(DeltaTime);
			break;
		case GUS_GUARD:
			FS_GUARD(DeltaTime);
			break;
		case GUS_GUARDDOWN:
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

void GuardM_Com::BulletHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if(Dest->GetTag() == "BulletBody")
	{
		Vector3 dPos = Dest->GetGameObject()->GetTransform()->GetWorldPos();
		SoundManager::Get()->FindSoundEffect("BulletColl")->Play();
		Dest->GetGameObject()->SetIsActive(false);

		m_Camera->SetShake(5.0f, 0.3f);
		m_Scene->CreateWave(dPos, 0.8f, 0.1f);

		HitEffectOut(DeltaTime);

		if (m_Hp > 0)
		{
			if (m_State == GUS_GUARD || m_State == GUS_GUARDDOWN)
				return;

			ChangeState(GUS_HIT, m_AniName, m_Animation);
			m_Hp--;
		}
	}
}

void GuardM_Com::FS_IDLE(float DeltaTime)
{
	m_IdleTimeVar += DeltaTime;

	if (m_IdleTimeVar >= m_IdleTime)
	{
		m_IdleTimeVar = 0.0f;

		int RandNum = RandomRange(1, 2);

		switch (RandNum)
		{
		case 1:
			m_Animation->SetDir(MD_LEFT);
			break;
		case 2:
			m_Animation->SetDir(MD_RIGHT);
			break;
		}
		ChangeState(GUS_MOVE, m_AniName, m_Animation);
	}
	
	GuardRangeCheck(DeltaTime);
}

void GuardM_Com::FS_MOVE(float DeltaTime)
{
	m_MoveTimeVar += DeltaTime;

	RangeTargetDirCheck(DeltaTime);

	if (m_Animation->GetDir() == MD_LEFT)
	{
		if (m_LeftTile->GetTileOption() != T2D_NOMOVE || m_DownLeftTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, -200.0f, DeltaTime);
	}
	else if (m_Animation->GetDir() == MD_RIGHT)
	{
		if (m_RightTile->GetTileOption() != T2D_NOMOVE || m_DownRightTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, 200.0f, DeltaTime);
	}

	if (m_MoveTimeVar > m_MoveTime)
	{
		m_MoveTimeVar = 0.0f;
		ChangeState(GUS_IDLE, m_AniName, m_Animation);
	}

	GuardRangeCheck(DeltaTime);
}


void GuardM_Com::FS_HIT(float DeltaTime)
{
	Vector3	Dir = m_TargetPos - m_Pos;

	if (Dir.x <= 0.0f)
	{
		m_MoveDir = -1.0f;
		m_Animation->SetDir(MD_LEFT);
	}
	else if (Dir.x > 0.0f)
	{
		m_MoveDir = 1.0f;
		m_Animation->SetDir(MD_RIGHT);
	}

	if (m_Animation->GetDir() == MD_LEFT)
	{
		if (m_RightTile->GetTileOption() != T2D_NOMOVE || m_DownRightTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, 100.0f, DeltaTime);
	}
	else if (m_Animation->GetDir() == MD_RIGHT)
	{
		if (m_LeftTile->GetTileOption() != T2D_NOMOVE || m_DownLeftTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, -100.0f, DeltaTime);
	}

	if (m_Animation->GetIsEnd() == true)
	{
		int RandNum = RandomRange(1, 2);

		switch (RandNum)
		{
		case 1:
			ChangeState(GUS_IDLE, m_AniName, m_Animation);
			break;
		case 2:
			ChangeState(GUS_MOVE, m_AniName, m_Animation);
			break;
		}
	}
}

void GuardM_Com::FS_GUARD(float DeltaTime)
{
	m_GuardTimeVar += DeltaTime;

	if (m_GuardTimeVar >= m_GuardTime)
	{
		m_GuardTimeVar = 0.0f;
		ChangeState(GUS_GUARDDOWN, m_AniName, m_Animation);
	}
}

void GuardM_Com::FS_GUARDDOWN(float DeltaTime)
{
	if (m_Animation->GetFrame() == 3)
	{
		int RandNum = RandomRange(1, 2);

		switch (RandNum)
		{
		case 1:
			ChangeState(GUS_IDLE, m_AniName, m_Animation);
			break;
		case 2:
			ChangeState(GUS_MOVE, m_AniName, m_Animation);
			break;
		}
	}
}

void GuardM_Com::GuardRangeCheck(float DeltaTime)
{
	if (m_Pos.GetDistance(m_TargetPos) >= m_GuardRange)
		return;

	m_GuardTimeVar = 0.0f;
	m_MoveTimeVar = 0.0f;
	m_IdleTimeVar = 0.0f;

	ChangeState(GUS_GUARD, m_AniName, m_Animation);
}

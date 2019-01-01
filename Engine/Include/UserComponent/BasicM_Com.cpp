#include "stdafx.h"
#include "BasicM_Com.h"

#include "../Component/Animation2D_Com.h"
#include "../Component/Gravity_Com.h"
#include "../Component/ColliderRect_Com.h"


JEONG_USING

BasicM_Com::BasicM_Com()
{
	m_Type = MT_BASIC;

	m_IdleTime = 2.0f;
	m_IdleTimeVar = 0.0f;

	m_MoveTime = 3.0f;
	m_MoveTimeVar = 0.0f;
}

BasicM_Com::BasicM_Com(const BasicM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

BasicM_Com::~BasicM_Com()
{
}

bool BasicM_Com::Init()
{
	Monster_Base::Init();

	m_Gravity = m_Object->AddComponent<Gravity_Com>("Gravity");

	m_Hp = 2;

	m_Material->SetDiffuseTexture(0, "Basic", TEXT("Monster\\smallenemies.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("BasicAni");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 1.0f));
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Basic", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Move", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Basic", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(768.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(768.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Hit", A2D_ATLS, AO_ONCE_STOP, 0.3f, vecClipFrame, "Basic", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	m_AniName[BSM_IDLE] = "Idle";
	m_AniName[BSM_MOVE] = "Move";
	m_AniName[BSM_HIT] = "Hit";

	ChangeState(BSM_IDLE, m_AniName, m_Animation);

	return true;
}

int BasicM_Com::Input(float DeltaTime)
{
	return 0;
}

int BasicM_Com::Update(float DeltaTime)
{
	Monster_Base::Update(DeltaTime);

	switch (m_State)
	{
	case BSM_IDLE:
		FS_IDLE(DeltaTime);
		break;
	case BSM_MOVE:
		FS_MOVE(DeltaTime);
		break;
	case BSM_HIT:
		FS_HIT(DeltaTime);
		break;
	}

	return 0;
}

int BasicM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BasicM_Com::Collision(float DeltaTime)
{
}

void BasicM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BasicM_Com::Render(float DeltaTime)
{
}

BasicM_Com * BasicM_Com::Clone()
{
	return new BasicM_Com(*this);
}

void BasicM_Com::AfterClone()
{
}

void BasicM_Com::BulletHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		Vector3 dPos = Dest->GetGameObject()->GetTransform()->GetWorldPos();
		SoundManager::Get()->FindSoundEffect("BulletColl")->Play();
		Dest->GetGameObject()->SetIsActive(false);

		HitEffectOut(DeltaTime);

		if (m_Hp > 0)
		{
			Vector3	Dir = m_TargetPos - m_Pos;

			if (Dir.x <= 0.0f)
				m_Animation->SetDir(MD_LEFT);
			else if (Dir.x > 0.0f)
				m_Animation->SetDir(MD_RIGHT);

			m_Camera->SetShake(5.0f, 0.3f);
			m_Scene->CreateWave(m_CenterPos, 0.8f, 0.05f);

			ChangeState(BSM_HIT, m_AniName, m_Animation);
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
				ChangeState(BSM_HIT, m_AniName, m_Animation);
			}
		}
	}
}

void BasicM_Com::FS_IDLE(float DeltaTime)
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
}

void BasicM_Com::FS_MOVE(float DeltaTime)
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
}

void BasicM_Com::FS_HIT(float DeltaTime)
{
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
			ChangeState(BSM_IDLE, m_AniName, m_Animation);
			break;
		case 2:
			ChangeState(BSM_MOVE, m_AniName, m_Animation);
			break;
		}
	}
}

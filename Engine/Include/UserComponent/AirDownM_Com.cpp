#include "stdafx.h"
#include "AirDownM_Com.h"

#include "../Component/Animation2D_Com.h"
#include "../Component/ColliderRect_Com.h"

JEONG_USING

AirDownM_Com::AirDownM_Com()
{
	m_Type = MT_AIRDOWN;
}

AirDownM_Com::AirDownM_Com(const AirDownM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

AirDownM_Com::~AirDownM_Com()
{
}

bool AirDownM_Com::Init()
{
	Monster_Base::Init();

	m_Hp = 2;
	m_Angle = 0.0f;

	m_Material->SetDiffuseTexture(0, "AirDown", TEXT("Monster\\smallenemies.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("AirDown");
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

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "AirDown", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 64.0f, 128.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 64.0f, 192.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Down", A2D_ATLS, AO_LOOP, 0.3f, vecClipFrame, "AirDown", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	m_AniName[AIR_IDLE] = "Idle";
	m_AniName[AIR_DOWN] = "Down";
	m_AniName[AIR_UP] = "Idle";
	m_AniName[AIR_HIT] = "Idle";

	ChangeState(AIR_IDLE, m_AniName, m_Animation);

	return true;
}

int AirDownM_Com::Input(float DeltaTime)
{
	return 0;
}

int AirDownM_Com::Update(float DeltaTime)
{
	Monster_Base::Update(DeltaTime);
	
	switch (m_State)
	{
	case AIR_IDLE:
		FS_IDLE(DeltaTime);
		break;
	case AIR_DOWN:
		FS_DOWN(DeltaTime);
		break;
	case AIR_UP:
		FS_UP(DeltaTime);
		break;
	}

	return 0;
}

int AirDownM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void AirDownM_Com::Collision(float DeltaTime)
{
}

void AirDownM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void AirDownM_Com::Render(float DeltaTime)
{
}

AirDownM_Com * AirDownM_Com::Clone()
{
	return new AirDownM_Com(*this);
}

void AirDownM_Com::AfterClone()
{
}

void AirDownM_Com::BulletHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		Vector3 dPos = Dest->GetGameObject()->GetTransform()->GetWorldPos();
		SoundManager::Get()->FindSoundEffect("BulletColl")->Play();
		Dest->GetGameObject()->SetIsActive(false);

		HitEffectOut(DeltaTime);

		if (m_Hp > 0)
		{
			m_Camera->SetShake(5.0f, 0.3f);
			m_Scene->CreateWave(m_CenterPos, 0.8f, 0.05f);
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

void AirDownM_Com::FS_IDLE(float DeltaTime)
{
	CircleMove(DeltaTime);

	if (m_TargetPos.x >= m_Pos.x - 10.0f && m_TargetPos.x <= m_Pos.x + 10.0f)
		ChangeState(AIR_DOWN, m_AniName, m_Animation);
}

void AirDownM_Com::FS_DOWN(float DeltaTime)
{
	if (m_DownTile->GetTileOption() != T2D_NOMOVE)
		m_Transform->Move(AXIS_Y, -800.0f, DeltaTime);
	else if (m_DownTile->GetTileOption() == T2D_NOMOVE)
		ChangeState(AIR_UP, m_AniName, m_Animation);
}

void AirDownM_Com::FS_UP(float DeltaTime)
{
	bool Finish = false;

	if(m_Pos.y <= m_SavePos.y)
		m_Transform->Move(AXIS_Y, 800.0f, DeltaTime);
	if (m_Pos.y >= m_SavePos.y)
		Finish = true;

	if (Finish == true)
		ChangeState(AIR_IDLE, m_AniName, m_Animation);
}

void AirDownM_Com::CircleMove(float DeltaTime)
{
	float Rangle = 80.0f;

	m_Angle += 100.0f * DeltaTime;
	float X = cosf(DegreeToRadian(m_Angle));
	float Y = sinf(DegreeToRadian(m_Angle));

	m_Transform->Move(Vector3(X, Y, 0.0f), 50.0f, DeltaTime);
}

void AirDownM_Com::SetPos(const Vector3 & Pos)
{
	m_Transform->SetWorldPos(Pos);
	m_SavePos = Pos;
}
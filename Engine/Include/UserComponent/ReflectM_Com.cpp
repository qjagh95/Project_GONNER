#include "stdafx.h"
#include "ReflectM_Com.h"
#include "../Component/Animation2D_Com.h"
#include "../Component/ColliderRect_Com.h"

JEONG_USING

ReflectM_Com::ReflectM_Com()
{
}

ReflectM_Com::ReflectM_Com(const ReflectM_Com & CopyData)
	:Monster_Base(CopyData)
{
}

ReflectM_Com::~ReflectM_Com()
{
}

bool ReflectM_Com::Init()
{
	Monster_Base::Init();

	m_Hp = 2;
	m_Range = 200.0f;
	m_HitAngle = 0.0f;

	m_Material->SetDiffuseTexture(0, "Reflect", TEXT("Monster\\bigsprites3.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("ReflectAni");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 1.0f));
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(256.0f + i * 128.0f, 640.0f);
		tFrame.RightBottom = Vector2(256.0f + (i + 1) * 128.0f, 768.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Reflect", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 768.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 896.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Attack", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Reflect", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(512.0f + i * 128.0f, 768.0f);
		tFrame.RightBottom = Vector2(512.0f + (i + 1) * 128.0f, 896.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Hit", A2D_ATLS, AO_ONCE_STOP, 0.3f, vecClipFrame, "Reflect", L"Monster\\bigsprites3.png");
	vecClipFrame.clear();

	m_AniName[RS_IDLE] = "Idle";
	m_AniName[RS_ATTACK] = "Attack";
	m_AniName[RS_HIT] = "Hit";

	ChangeState(RS_IDLE, m_AniName, m_Animation);

	return true;
}

int ReflectM_Com::Input(float DeltaTime)
{
	return 0;
}

int ReflectM_Com::Update(float DeltaTime)
{
	Monster_Base::Update(DeltaTime);

	switch (m_State)
	{
	case RS_IDLE:
		FS_IDLE(DeltaTime);
		break;
	case RS_ATTACK:
		FS_ATTACK(DeltaTime);
		break;
	case RS_HIT:
		FS_HIT(DeltaTime);
		break;
	}

	return 0;
}

int ReflectM_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ReflectM_Com::Collision(float DeltaTime)
{
}

void ReflectM_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ReflectM_Com::Render(float DeltaTime)
{
}

ReflectM_Com * ReflectM_Com::Clone()
{
	return new ReflectM_Com(*this);
}

void ReflectM_Com::AfterClone()
{
}

void ReflectM_Com::BulletHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
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
			
			m_Hp--;
		}
	}

	if (Dest->GetTag() == "GonnerBody")
	{
		if (m_GonnerJumpAttack == true)
		{
			if (m_Hp > 0)
				m_Camera->SetShake(5.0f, 0.3f);
		}
	}
}

void ReflectM_Com::FS_IDLE(float DeltaTime)
{
	RangeCheck(DeltaTime);
}

void ReflectM_Com::FS_HIT(float DeltaTime)
{
	m_HitAngle += 600.0f * DeltaTime;
	m_Transform->RotationZ(600.0f, DeltaTime);

	if (m_Stage->GetTile2D(m_Pos + (m_MoveDir * m_Scale))->GetTileOption() != T2D_NOMOVE)
		m_Transform->Move(m_MoveDir, 300.0f, DeltaTime);

	if (m_HitAngle >= 360.0f)
	{
		m_HitAngle = 0.0f;
		m_Transform->SetWorldRotZ(0.0f);

		ChangeState(RS_IDLE, m_AniName, m_Animation);
	}
}

void ReflectM_Com::FS_ATTACK(float DeltaTime)
{
	//Base에 있는 Update -> 피봇 0.5, 0.0기준
	//0.5, 0.5로 다시계산해줌.
	Vector3 LeftPos = m_Pos;
	LeftPos.x -= m_Scale.x * 0.5f;
	Vector3 RightPos = m_Pos;
	RightPos.x += m_Scale.x * 0.5f;
	Vector3 UpPos = m_Pos;
	UpPos.y += m_Scale.y * 0.5f;
	Vector3 DownPos = m_Pos;
	DownPos.y -= m_Scale.y * 0.5f;
	Vector3 UpLeftPos = UpPos;
	UpLeftPos.x -= m_Scale.x * 0.5f;
	Vector3 UpRightPos = UpPos;
	UpRightPos.x += m_Scale.x * 0.5f;
	Vector3 DownRightPos = DownPos;
	DownRightPos.x += m_Scale.x * 0.5f;
	Vector3 DownLeftPos = m_Pos;
	DownLeftPos.x -= m_Scale.x * 0.5f;

	//8방향 타일체크
	m_LeftTile = m_Stage->GetTile2D(LeftPos);
	m_RightTile = m_Stage->GetTile2D(RightPos);
	m_UpTile = m_Stage->GetTile2D(UpPos);
	m_DownTile = m_Stage->GetTile2D(DownPos);
	m_UpLeftTile = m_Stage->GetTile2D(UpLeftPos);
	m_UpRightTile = m_Stage->GetTile2D(UpRightPos);
	m_DownLeftTile = m_Stage->GetTile2D(DownLeftPos);
	m_DownRightTile = m_Stage->GetTile2D(DownRightPos);

	if (m_Animation->GetDir() == MD_LEFT)
	{
		if (m_LeftTile->GetTileOption() == T2D_NOMOVE)
		{
			Vector3 Temp = Vector3::Reflect(Vector3::Nomallize(m_Pos), Vector3::Nomallize(m_Pos.Cross(m_LeftTile->GetTransform()->GetWorldPos())));
			ChangeState(RS_HIT, m_AniName, m_Animation);
			m_MoveDir = Vector3(Temp.x, Temp.y, 1.0f);
		}
		else if (m_DownTile->GetTileOption() == T2D_NOMOVE)
		{
			Vector3 Temp = Vector3::Reflect(Vector3::Nomallize(m_Pos), Vector3::Nomallize(m_Pos.Cross(m_DownTile->GetTransform()->GetWorldPos())));
			ChangeState(RS_HIT, m_AniName, m_Animation);
			m_MoveDir = Vector3(Temp.x * -1.0f, Temp.y, 1.0f);
		}
		else if (m_UpTile->GetTileOption() == T2D_NOMOVE)
		{
			Vector3 Temp = Vector3::Reflect(Vector3::Nomallize(m_Pos), Vector3::Nomallize(m_Pos.Cross(m_UpTile->GetTransform()->GetWorldPos())));
			ChangeState(RS_HIT, m_AniName, m_Animation);
			m_MoveDir = Vector3(Temp.x, Temp.y * -1.0f, 1.0f);
		}
		else
			m_Transform->Move(m_MoveDir, 300.0f, DeltaTime);
	}
	else
	{
		if (m_RightTile->GetTileOption() == T2D_NOMOVE)
		{
			Vector3 Temp = Vector3::Reflect(Vector3::Nomallize(m_Pos), Vector3::Nomallize(m_Pos.Cross(m_RightTile->GetTransform()->GetWorldPos())));
			ChangeState(RS_HIT, m_AniName, m_Animation);
			m_MoveDir = Vector3(Temp.x * -1.0f, Temp.y, 1.0f);
		}
		else if (m_DownTile->GetTileOption() == T2D_NOMOVE)
		{
			Vector3 Temp = Vector3::Reflect(Vector3::Nomallize(m_Pos), Vector3::Nomallize(m_Pos.Cross(m_DownTile->GetTransform()->GetWorldPos())));
			ChangeState(RS_HIT, m_AniName, m_Animation);
			m_MoveDir = Vector3(Temp.x, Temp.y, 1.0f);
		}
		else if (m_UpTile->GetTileOption() == T2D_NOMOVE)
		{
			Vector3 Temp = Vector3::Reflect(Vector3::Nomallize(m_Pos), Vector3::Nomallize(m_Pos.Cross(m_UpTile->GetTransform()->GetWorldPos())));
			ChangeState(RS_HIT, m_AniName, m_Animation);
			m_MoveDir = Vector3(Temp.x, Temp.y * -1.0f, 1.0f);
		}
		else
			m_Transform->Move(m_MoveDir, 300.0f, DeltaTime);
	}

	m_MoveDir.z = 0.0f;
}

void ReflectM_Com::RangeCheck(float DeltaTime)
{
	if (m_Pos.GetDistance(m_TargetPos) >= m_Range)
		return;

	Vector3 Look = m_TargetPos - m_Pos;

	if (Look.x <= 0.0f)
		m_Animation->SetDir(MD_LEFT);
	else if(Look.x >= 0.0f)
		m_Animation->SetDir(MD_RIGHT);

	Look.Nomallize();
	m_MoveDir = Look;

	ChangeState(RS_ATTACK, m_AniName, m_Animation);
}

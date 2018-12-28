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

	//m_Material->SetDiffuseTexture(0, "Guard", TEXT("Monster\\bigsprites3.png"));
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

	m_Animation->AddClip("Hit", A2D_ATLS, AO_ONCE_STOP, 0.6f, vecClipFrame, "Guard", L"Monster\\bigsprites3.png");
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

	TargetDirCheck(DeltaTime);

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

		m_Camera->SetShake(5.0f, 0.3f);
		m_Scene->CreateWave(dPos, 0.8f, 0.1f);
		Dest->GetGameObject()->SetIsActive(false);

		if (m_Hp > 0)
		{
			ChangeState(GUS_HIT, m_AniName, m_Animation);
			m_Hp--;
		}

		int RandNum = RandomRange(10, 20);

		for (size_t i = 0; i < RandNum; i++)
		{
			GameObject* newEffect = GameObject::CreateObject("ReloadEffect", m_AfterEffect);
			BasicEffect_Com* BasicEffect = newEffect->AddComponent<BasicEffect_Com>("ReloadEffect");
			BasicEffect->GetTransform()->SetWorldPos(m_Pos.x, m_Pos.y, 1.0f);
			BasicEffect->SetRandomDirection(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));

			SAFE_RELEASE(newEffect);
			SAFE_RELEASE(BasicEffect);
		}

		GameObject* newHitEffect = GameObject::CreateObject("ReloadEffect", m_AfterEffect);
		HitEffect_Com* HitEffect = newHitEffect->AddComponent<HitEffect_Com>("ReloadEffect");
		HitEffect->SetPos(Vector3(m_Pos.x, m_Pos.y + m_Scale.y * 0.5f, 1.0f), Vector4(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f)));
		SAFE_RELEASE(newHitEffect);
		SAFE_RELEASE(HitEffect);
	}
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

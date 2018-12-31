#include "stdafx.h"
#include "Monster_Base.h"
#include "DieEffect_Com.h"
#include "DieBoomEffect_Com.h"
#include "BallonEffect_Com.h"
#include "BasicEffect_Com.h"
#include "HitEffect_Com.h"

#include "../Core.h"
#include "../Component/Gravity_Com.h"
#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"
#include "../Component/Tile2D_Com.h"

JEONG_USING

GameObject* Monster_Base::m_Target;
Vector3 Monster_Base::m_TargetPos;

Monster_Base::Monster_Base()
{
	m_ComType = CT_MONSTER;

	m_Camera = NULLPTR;
	m_UpTile = NULLPTR;
	m_DownTile = NULLPTR;
	m_LeftTile = NULLPTR;
	m_RightTile = NULLPTR;
	m_Stage = NULLPTR;
	m_UpLeftTile = NULLPTR;
	m_UpRightTile = NULLPTR;
	m_DownLeftTile = NULLPTR;
	m_DownRightTile = NULLPTR;

	m_DirCheckTime = 0.1f;
	m_DirCheckTimeVar = 0.0f;

	m_GonnerJumpAttack = false;
	m_MoveDir = 1.0f;

	int RendNum = RandomRange(1, 4);

	switch (RendNum)
	{
		case 1:
			m_ChangeTime = 0.1f;
			break;
		case 2:
			m_ChangeTime = 0.15f;
			break;
		case 3:
			m_ChangeTime = 0.2f;
			break;
		case 4:
			m_ChangeTime = 0.25f;
			break;
	}
	
	m_ChangeTimeVar = 0.0f;

	m_Gravity = NULLPTR;
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
	m_RectColl = NULLPTR;

	m_LookRange = 300.0f;
}

Monster_Base::Monster_Base(const Monster_Base & CopyData)
	:UserComponent_Base(CopyData)
{
}

Monster_Base::~Monster_Base()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_RectColl);
	SAFE_RELEASE(m_Gravity);
}

bool Monster_Base::Init()
{
	m_Camera = m_Scene->GetMainCamera();

	m_Hp = 1;

	m_AfterEffect = m_Scene->FindLayerNoneCount("AfterEffectLayer");
	m_PrevEffect = m_Scene->FindLayerNoneCount("PrevEffectLayer");

	Renderer_Com* MonsterRender = m_Object->AddComponent<Renderer_Com>("MonsterRender");
	MonsterRender->SetMesh("TextureRect");
	MonsterRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(MonsterRender);

	m_RectColl = m_Object->AddComponent<ColliderRect_Com>("MonsterBody");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	m_RectColl->SetMyTypeName("Monster");
	m_RectColl->SetCollsionCallback(CCT_FIRST, this, &Monster_Base::BulletHit);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);

	return true;
}

int Monster_Base::Input(float DeltaTime)
{
	return 0;
}

int Monster_Base::Update(float DeltaTime)
{
	if (Core::m_isEditor == true)
		return 0;

	if (m_Stage == NULLPTR)
		m_Stage = StageManager::Get()->FindCurStage();

	m_Scale = m_Transform->GetWorldScale();
	Vector3 ScaleHalf = m_Scale * 0.5f;

	m_Pos = m_Transform->GetWorldPos();
	m_TargetPos = m_Target->GetTransform()->GetWorldPos();
	m_CenterPos = Vector3(m_Pos.x, m_Pos.y + ScaleHalf.y, 1.0f);
	m_CenterLeftPos = Vector3(m_CenterPos.x - ScaleHalf.x, m_CenterPos.y, 1.0f);
	m_CenterRightPos = Vector3(m_CenterPos.x + ScaleHalf.x, m_CenterPos.y, 1.0f);
	m_UpPos = Vector3(m_Pos.x, m_Pos.y + m_Scale.y, 1.0f);
	m_DownLeftPos = Vector3(m_Pos.x - ScaleHalf.x, m_Pos.y, 1.0f);
	m_DownRightPos = Vector3(m_Pos.x + ScaleHalf.x, m_Pos.y, 1.0f);
	m_UpLeftPos = Vector3(m_UpPos.x - ScaleHalf.x , m_UpPos.y, 1.0f);
	m_UpRightPos = Vector3(m_UpPos.x + ScaleHalf.x, m_UpPos.y, 1.0f);

	m_UpTile = m_Stage->GetTile2D(m_UpPos);
	m_DownTile = m_Stage->GetTile2D(m_Pos);
	m_LeftTile = m_Stage->GetTile2D(m_CenterLeftPos);
	m_RightTile = m_Stage->GetTile2D(m_CenterRightPos);
	m_UpLeftTile = m_Stage->GetTile2D(m_UpLeftPos);
	m_UpRightTile = m_Stage->GetTile2D(m_UpRightPos);
	m_DownLeftTile = m_Stage->GetTile2D(m_DownLeftPos);
	m_DownRightTile = m_Stage->GetTile2D(m_DownRightPos);

	ChangeColor(DeltaTime);

	if (m_Hp <= 0)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);

		GameObject* DieBoomEffect = GameObject::CreateObject("DieEffect", m_PrevEffect);
		DieBoomEffect_Com* DieBoomEffectCom = DieBoomEffect->AddComponent<DieBoomEffect_Com>("DieEffect");
		DieBoomEffectCom->SetPos(Vector3(m_Pos.x, m_Pos.y + m_Scale.y * 0.5f, 1.0f));

		GameObject* DieEffect = GameObject::CreateObject("DieEffect", m_AfterEffect);
		DieEffect_Com* DieEffectCom = DieEffect->AddComponent<DieEffect_Com>("DieEffect");
		DieEffectCom->SetPos(Vector3(m_Pos.x, m_Pos.y + m_Scale.y * 0.5f, 1.0f));

		int RandNum = RandomRange(1, 4);

		for (int i = 0; i < RandNum; i++)
		{
			GameObject* BullonObject = GameObject::CreateObject("DieEffect", m_AfterEffect);
			BallonEffect_Com* BullonCom = BullonObject->AddComponent<BallonEffect_Com>("DieEffect");
			BullonCom->SetPos(Vector3(m_Pos.x, m_Pos.y + m_Scale.y, 1.0f), Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 0.2f));

			SAFE_RELEASE(BullonObject);
			SAFE_RELEASE(BullonCom);
		}

		SAFE_RELEASE(DieEffect);
		SAFE_RELEASE(DieEffectCom);
		SAFE_RELEASE(DieBoomEffect);
		SAFE_RELEASE(DieBoomEffectCom);

		SoundManager::Get()->FindSoundEffect("MonsterDie")->Play();
		SoundManager::Get()->FindSoundEffect("DieBoom")->Play();
	}

	return 0;
}

int Monster_Base::LateUpdate(float DeltaTime)
{
	return 0;
}

void Monster_Base::Collision(float DeltaTime)
{
}

void Monster_Base::CollisionLateUpdate(float DeltaTime)
{
}

void Monster_Base::Render(float DeltaTime)
{
}

Monster_Base * Monster_Base::Clone()
{
	return new Monster_Base(*this);
}

void Monster_Base::AfterClone()
{
}

void Monster_Base::BulletHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
}

void Monster_Base::ChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar >= m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f))
			m_Material->SetMaterial(m_Material->GetDiffuseLight() * 1.1f);
		else
			m_Material->SetMaterial(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));
	}
}

void Monster_Base::HitChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar >= m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f))
			m_Material->SetMaterial(m_Material->GetDiffuseLight() * 1.1f);
		else
			m_Material->SetMaterial(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));
	}
}

void Monster_Base::RangeTargetDirCheck(float DeltaTime)
{
	if (m_Pos.GetDistance(m_TargetPos) >= m_LookRange)
		return;

	m_DirCheckTimeVar += DeltaTime;

	if (m_DirCheckTimeVar >= m_DirCheckTime)
	{
		m_DirCheckTimeVar = 0.0f;

		m_CrossDir = m_TargetPos - m_Pos;

		if (m_CrossDir.x < 30.0f)
		{
			m_MoveDir = -1.0f;
			m_Animation->SetDir(MD_LEFT);
		}
		else if (m_CrossDir.x > 30.0f)
		{
			m_MoveDir = 1.0f;
			m_Animation->SetDir(MD_RIGHT);
		}
	}
}

void Monster_Base::HitEffectOut(float DeltaTime)
{
	int RandNum = RandomRange(10, 20);

	for (size_t i = 0; i < RandNum; i++)
	{
		GameObject* newEffect = GameObject::CreateObject("BasicEffect", m_AfterEffect);
		BasicEffect_Com* BasicEffect = newEffect->AddComponent<BasicEffect_Com>("BasicEffect");
		BasicEffect->GetTransform()->SetWorldPos(m_Pos.x, m_Pos.y, 1.0f);
		BasicEffect->SetRandomDirection(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));

		SAFE_RELEASE(newEffect);
		SAFE_RELEASE(BasicEffect);
	}

	GameObject* newHitEffect = GameObject::CreateObject("HitEffect", m_AfterEffect);
	HitEffect_Com* HitEffect = newHitEffect->AddComponent<HitEffect_Com>("HitEffect");
	HitEffect->SetPos(Vector3(m_Pos.x, m_Pos.y + m_Scale.y * 0.5f, 1.0f), Vector4(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f)));

	SAFE_RELEASE(newHitEffect);
	SAFE_RELEASE(HitEffect);
}

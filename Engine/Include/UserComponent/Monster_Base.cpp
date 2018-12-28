#include "stdafx.h"
#include "Monster_Base.h"
#include "DieEffect_Com.h"
#include "DieBoomEffect_Com.h"
#include "BallonEffect_Com.h"

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

	m_Range = 300.0f;
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
	SAFE_RELEASE(m_AfterEffect);
	SAFE_RELEASE(m_PrevEffect);
}

bool Monster_Base::Init()
{
	m_Camera = m_Scene->GetMainCamera();

	m_Hp = 1;

	m_AfterEffect = m_Scene->FindLayer("AfterEffectLayer");
	m_PrevEffect = m_Scene->FindLayer("PrevEffectLayer");

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

	m_Stage = StageManager::Get()->FindCurStage();

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

	m_Scale = m_Transform->GetWorldScale();
	m_Pos = m_Transform->GetWorldPos();
	m_TargetPos = m_Target->GetTransform()->GetWorldPos();
	m_CenterPos = Vector3(m_Pos.x, m_Pos.y + m_Scale.y * 0.5f, 1.0f);
	m_CenterLeftPos = Vector3(m_CenterPos.x - m_Scale.x * 0.5f, m_CenterPos.y, 1.0f);
	m_CenterRightPos = Vector3(m_CenterPos.x + m_Scale.x * 0.5f, m_CenterPos.y, 1.0f);
	m_UpPos = Vector3(m_Pos.x, m_Pos.y + m_Scale.y, 1.0f);

	m_UpTile = m_Stage->GetTile2D(m_UpPos);
	m_DownTile = m_Stage->GetTile2D(m_Pos);
	m_LeftTile = m_Stage->GetTile2D(m_CenterLeftPos);
	m_RightTile = m_Stage->GetTile2D(m_CenterRightPos);

	ChangeColor(DeltaTime);

	if (m_Hp == 0)
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

void Monster_Base::TargetDirCheck(float DeltaTime)
{
	if (m_Pos.GetDistance(m_TargetPos) >= m_Range)
		return;

	m_CrossDir = m_TargetPos - m_Pos;

	if (m_CrossDir.x <= 0.0f)
		m_Animation->SetDir(MD_LEFT);
	else if(m_CrossDir.x > 0.0f)
		m_Animation->SetDir(MD_RIGHT);
}
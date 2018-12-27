#include "stdafx.h"
#include "Monster_Base.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

bool Monster_Base::m_isEditor = false;

Monster_Base::Monster_Base()
{
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

	ZeroMemory(m_AniName, sizeof(string*));
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
}

bool Monster_Base::Init()
{
	m_Hp = 1;

	Renderer_Com* MonsterRender = m_Object->AddComponent<Renderer_Com>("MonsterRender");
	MonsterRender->SetMesh("TextureRect");
	MonsterRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(MonsterRender);

	m_RectColl = m_Object->AddComponent<ColliderRect_Com>("MonsterBody");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	m_RectColl->SetMyTypeName("Monster");

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 1.0f));

	return true;
}

int Monster_Base::Input(float DeltaTime)
{
	return 0;
}

int Monster_Base::Update(float DeltaTime)
{
	if (m_isEditor == true)
		return;

	if (m_Hp == 0)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);

		//ÀÌÆåÆ®»ý¼º
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

#include "stdafx.h"
#include "Bullet_Com.h"

#include "../Component/Animation2D_Com.h"
#include "../Component/ColliderRect_Com.h"

JEONG_USING

Bullet_Com::Bullet_Com()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
}

Bullet_Com::Bullet_Com(const Bullet_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Bullet_Com::~Bullet_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool Bullet_Com::Init()
{
	//불릿 애니메이션 , 이펙트클래스3개추가, 아이템UI추가
	Renderer_Com* BulletRender = m_Object->AddComponent<Renderer_Com>("BulletRender");
	BulletRender->SetMesh("TextureRect");
	BulletRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BulletRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Animation = m_Object->AddComponent<Animation2D_Com>("Bullet");
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Bullet", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Bullet", L"weapons.png");
	vecClipFrame.clear();

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("BulletBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	RectColl->SetMyTypeName("Bullet");
	RectColl->PushContinueTypeName("Gonner");
	SAFE_RELEASE(RectColl);

	m_Material->SetMaterial(Vector4::Yellow);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);

	m_Scale = Vector3(64.0f, 64.0f, 1.0f);
	m_ScaleHalf = m_Scale * 0.5f;
	m_LightTimeVar = 0.0f;
	m_LightTime = 0.2f;

	m_Stage = StageManager::Get()->FindCurStage();
	m_Animation->ChangeClip("Bullet");

	return true;
}

int Bullet_Com::Input(float DeltaTime)
{
	return 0;
}

int Bullet_Com::Update(float DeltaTime)
{
	Vector3 leftPos = m_Transform->GetWorldPos();
	Vector3 rightPos = m_Transform->GetWorldPos();

	leftPos.x -= m_ScaleHalf.x;
	rightPos.x += m_ScaleHalf.x;

	if (m_Animation->GetDir() == MD_LEFT)
	{
		Tile2D_Com* leftTile = m_Stage->GetTile2D(rightPos);
		
		if (leftTile->GetTileOption() == T2D_NOMOVE)
		{
			//이펙트생성
			m_Object->SetIsActive(false);
			SetIsActive(false);
		}

		m_Transform->Move(AXIS_X, -600.0f, DeltaTime);
	}
	else
	{
		Tile2D_Com* rightTile = m_Stage->GetTile2D(leftPos);

		if (rightTile->GetTileOption() == T2D_NOMOVE)
		{
			//이펙트생성
			m_Object->SetIsActive(false);
			SetIsActive(false);
		}

		m_Transform->Move(AXIS_X, 600.0f, DeltaTime);
	}
	return 0;
}

int Bullet_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Bullet_Com::Collision(float DeltaTime)
{
}

void Bullet_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Bullet_Com::Render(float DeltaTime)
{
}

Bullet_Com * Bullet_Com::Clone()
{
	return new Bullet_Com(*this);
}

void Bullet_Com::AfterClone()
{
}

void Bullet_Com::ColorLight(float DeltaTime)
{
	m_LightTimeVar += DeltaTime;

	if (m_LightTimeVar >= m_LightTime)
	{
		m_LightTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4::Yellow)
			m_Material->SetMaterial(m_Material->GetDiffuseLight() * 1.1f);
		else
			m_Material->SetMaterial(Vector4::Yellow);
	}
}

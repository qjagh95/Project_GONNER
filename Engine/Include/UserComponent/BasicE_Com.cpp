#include "stdafx.h"
#include "BasicE_Com.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING


BasicE_Com::BasicE_Com()
{
}


BasicE_Com::BasicE_Com(const BasicE_Com & CopyData)
	:EditorMonster_Base(CopyData)
{
}

BasicE_Com::~BasicE_Com()
{
}

bool BasicE_Com::Init()
{
	EditorMonster_Base::Init();

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
	m_Animation->ChangeClip("Idle");

	return true;
}

int BasicE_Com::Input(float DeltaTime)
{
	return 0;
}

int BasicE_Com::Update(float DeltaTime)
{
	EditorMonster_Base::Update(DeltaTime);

	return 0;
}

int BasicE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BasicE_Com::Collision(float DeltaTime)
{
}

void BasicE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BasicE_Com::Render(float DeltaTime)
{
}

BasicE_Com * BasicE_Com::Clone()
{
	return new BasicE_Com(*this);
}

void BasicE_Com::AfterClone()
{
}

void BasicE_Com::SetPos(const Vector3 & Pos)
{
}

void BasicE_Com::MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	EditorMonster_Base::MouseHit(Src, Dest, DeltaTime);
}
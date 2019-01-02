#include "stdafx.h"
#include "AirDownE_Com.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

AirDownE_Com::AirDownE_Com()
{
}

AirDownE_Com::AirDownE_Com(const AirDownE_Com & CopyData)
	:EditorMonster_Base(CopyData)
{
}

AirDownE_Com::~AirDownE_Com()
{
	int a = 0;
}

bool AirDownE_Com::Init()
{
	EditorMonster_Base::Init();

	m_Material->SetDiffuseTexture(0, "AirDown", TEXT("Monster\\smallenemies.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("AirDown");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 1.0f));
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

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
	m_Animation->ChangeClip("Idle");
	
	return true;
}

int AirDownE_Com::Input(float DeltaTime)
{
	return 0;
}

int AirDownE_Com::Update(float DeltaTime)
{
	EditorMonster_Base::Update(DeltaTime);
	return 0;
}

int AirDownE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void AirDownE_Com::Collision(float DeltaTime)
{
}

void AirDownE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void AirDownE_Com::Render(float DeltaTime)
{
}

AirDownE_Com * AirDownE_Com::Clone()
{
	return new AirDownE_Com(*this);
}

void AirDownE_Com::AfterClone()
{
}

void AirDownE_Com::SetPos(const Vector3 & Pos)
{
}

void AirDownE_Com::MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	EditorMonster_Base::MouseHit(Src, Dest, DeltaTime);
}
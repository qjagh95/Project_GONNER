#include "stdafx.h"
#include "TraceE_Com.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

TraceE_Com::TraceE_Com()
{
}

TraceE_Com::TraceE_Com(const TraceE_Com & CopyData)
	:EditorMonster_Base(CopyData)
{
}

TraceE_Com::~TraceE_Com()
{
}

bool TraceE_Com::Init()
{
	EditorMonster_Base::Init();

	m_Material->SetDiffuseTexture(0, "Trace", TEXT("Monster\\smallenemies.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("Trace");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 1.0f));
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 64.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Trace", L"Monster\\smallenemies.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("Idle");
	return true;
}

int TraceE_Com::Input(float DeltaTime)
{
	return 0;
}

int TraceE_Com::Update(float DeltaTime)
{
	EditorMonster_Base::Update(DeltaTime);

	return 0;
}

int TraceE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void TraceE_Com::Collision(float DeltaTime)
{
}

void TraceE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void TraceE_Com::Render(float DeltaTime)
{
}

TraceE_Com * TraceE_Com::Clone()
{
	return new TraceE_Com(*this);
}

void TraceE_Com::AfterClone()
{
}

void TraceE_Com::SetPos(const Vector3 & Pos)
{
}

void TraceE_Com::MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	EditorMonster_Base::MouseHit(Src, Dest, DeltaTime);
}

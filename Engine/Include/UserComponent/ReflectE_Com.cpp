#include "stdafx.h"
#include "ReflectE_Com.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

ReflectE_Com::ReflectE_Com()
{
}


ReflectE_Com::ReflectE_Com(const ReflectE_Com & CopyData)
	:EditorMonster_Base(CopyData)
{
}

ReflectE_Com::~ReflectE_Com()
{
}

bool ReflectE_Com::Init()
{
	EditorMonster_Base::Init();

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

	m_Animation->ChangeClip("Idle");

	return true;
}

int ReflectE_Com::Input(float DeltaTime)
{
	return 0;
}

int ReflectE_Com::Update(float DeltaTime)
{
	EditorMonster_Base::Update(DeltaTime);

	return 0;
}

int ReflectE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ReflectE_Com::Collision(float DeltaTime)
{
}

void ReflectE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ReflectE_Com::Render(float DeltaTime)
{
}

ReflectE_Com * ReflectE_Com::Clone()
{
	return new ReflectE_Com(*this);
}

void ReflectE_Com::AfterClone()
{
}

void ReflectE_Com::SetPos(const Vector3 & Pos)
{
}

void ReflectE_Com::MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	EditorMonster_Base::MouseHit(Src, Dest, DeltaTime);
}


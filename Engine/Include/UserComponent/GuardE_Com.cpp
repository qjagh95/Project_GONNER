#include "stdafx.h"
#include "GuardE_Com.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

GuardE_Com::GuardE_Com()
{
}


GuardE_Com::GuardE_Com(const GuardE_Com & CopyData)
	:EditorMonster_Base(CopyData)
{
}

GuardE_Com::~GuardE_Com()
{
}

bool GuardE_Com::Init()
{
	EditorMonster_Base::Init();

	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_RectColl->SetInfo(Vector3(30.0f, 0.0f, 0.0f), Vector3(100.0f, 100.0f, 1.0f));
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);

	m_Material->SetDiffuseTexture(0, "Guard", TEXT("Monster\\bigsprites3.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("GuardAni");

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

	m_Animation->ChangeClip("Idle");
	return true;
}

int GuardE_Com::Input(float DeltaTime)
{
	return 0;
}

int GuardE_Com::Update(float DeltaTime)
{
	EditorMonster_Base::Update(DeltaTime);

	return 0;
}

int GuardE_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void GuardE_Com::Collision(float DeltaTime)
{
}

void GuardE_Com::CollisionLateUpdate(float DeltaTime)
{
}

void GuardE_Com::Render(float DeltaTime)
{
}

GuardE_Com * GuardE_Com::Clone()
{
	return new GuardE_Com(*this);
}

void GuardE_Com::AfterClone()
{
}

void GuardE_Com::SetPos(const Vector3 & Pos)
{
}

void GuardE_Com::MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	EditorMonster_Base::MouseHit(Src, Dest, DeltaTime);
}
#include "stdafx.h"
#include "ReloadBullet_Com.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

ReloadBullet_Com::ReloadBullet_Com()
{
	m_RectColl = NULLPTR;
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

ReloadBullet_Com::ReloadBullet_Com(const ReloadBullet_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

ReloadBullet_Com::~ReloadBullet_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_RectColl);
}

bool ReloadBullet_Com::Init()
{
	Renderer_Com* ReloadBulletRender = m_Object->AddComponent<Renderer_Com>("ReloadBulletRender");
	ReloadBulletRender->SetMesh("TextureRect");
	ReloadBulletRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(ReloadBulletRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Animation = m_Object->AddComponent<Animation2D_Com>("ReloadBulletAni");
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

	m_Animation->AddClip("ReloadBullet", A2D_ATLS, AO_LOOP, 0.7f, vecClipFrame, "ReloadBullet", L"weapons.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("ReloadBullet");

	m_RectColl = m_Object->AddComponent<ColliderRect_Com>("ReloadBulletBody");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	m_RectColl->SetMyTypeName("ReloadBullet");
	m_RectColl->PushContinueTypeName("Bullet");
	m_RectColl->PushContinueTypeName("Monster");
	//초반 바로생성 후 나오자마자 사라지는 걸 막음.
	m_RectColl->SetIsShow(false);

	//true는 외적 계산 후 방향판단할때 true

	return true;
}

int ReloadBullet_Com::Input(float DeltaTime)
{
	//if(m_Animation->GetDir() == MD_LEFT)
	//{
	//}
	//else if (m_Animation->GetDir() == MD_RIGHT)
	//{
	//}

	return 0;
}

int ReloadBullet_Com::Update(float DeltaTime)
{
	return 0;
}

int ReloadBullet_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ReloadBullet_Com::Collision(float DeltaTime)
{
}

void ReloadBullet_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ReloadBullet_Com::Render(float DeltaTime)
{
}

ReloadBullet_Com * ReloadBullet_Com::Clone()
{
	return new ReloadBullet_Com(*this);
}

void ReloadBullet_Com::AfterClone()
{
}

#include "ClientHeader.h"
#include "LifeItem_Com.h"

#include <Component/ColliderRect_Com.h>

JEONG_USING

LifeItem_Com::LifeItem_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

LifeItem_Com::LifeItem_Com(const LifeItem_Com & CopyData)
{
}

LifeItem_Com::~LifeItem_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool LifeItem_Com::Init()
{
	Renderer_Com* LifeItemRender = m_Object->AddComponent<Renderer_Com>("LifeItem");
	LifeItemRender->SetMesh("TextureRect");
	LifeItemRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(LifeItemRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4::White);

	m_Animation = m_Object->AddComponent<Animation2D_Com>("LifeItemAni");
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 320.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("LifeItem", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "LifeItem", L"Monster\\player.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("LifeItem");

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("LifeItemBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	RectColl->SetMyTypeName("LifeItem");
	RectColl->PushContinueTypeName("Bullet");
	RectColl->PushContinueTypeName("Monster");
	SAFE_RELEASE(RectColl);

	return true;
}

int LifeItem_Com::Input(float DeltaTime)
{
	return 0;
}

int LifeItem_Com::Update(float DeltaTime)
{
	return 0;
}

int LifeItem_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void LifeItem_Com::Collision(float DeltaTime)
{
}

void LifeItem_Com::CollisionLateUpdate(float DeltaTime)
{
}

void LifeItem_Com::Render(float DeltaTime)
{
}

LifeItem_Com * LifeItem_Com::Clone()
{
	return new LifeItem_Com(*this);
}

void LifeItem_Com::AfterClone()
{
}

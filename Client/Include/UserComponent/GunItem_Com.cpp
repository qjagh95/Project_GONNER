#include "ClientHeader.h"
#include "GunItem_Com.h"

#include <Component/ColliderRect_Com.h>

JEONG_USING

GunItem_Com::GunItem_Com()
{
	m_ComType = CT_GUNITEM;
	m_isDrop = false;

	m_Material = NULLPTR;
	m_Animation = NULLPTR;
}

GunItem_Com::GunItem_Com(const GunItem_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

GunItem_Com::~GunItem_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool GunItem_Com::Init()
{
	Renderer_Com* GunItemRender = m_Object->AddComponent<Renderer_Com>("GunItem");
	GunItemRender->SetMesh("TextureRect");
	GunItemRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(GunItemRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "GunItem", TEXT("weapons.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("GunItemAni");
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

	m_Animation->AddClip("GunItem", A2D_ATLS, AO_LOOP, 0.7f, vecClipFrame, "GunItem", L"weapons.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("GunItem");

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("GunItemBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	RectColl->SetMyTypeName("GunItem");
	SAFE_RELEASE(RectColl);

	m_Rot = 20.0f;
	
	int RandNum = RandomRange(1, 3);
	switch (RandNum)
	{ 
		case 1:
			m_MoveRange = 50.0f;
			break;
		case 2:
			m_MoveRange = 60.0f;
			break;
		case 3:
			m_MoveRange = 80.0f;
			break;
	}

	int RandNum2 = RandomRange(1, 2);
	switch (RandNum2)
	{
		case 1:
			m_MoveDir = 1.0f;
			break;
		case 2:
			m_MoveDir = -1.0f;
			break;
	}

	return true;
}

int GunItem_Com::Input(float DeltaTime)
{
	if (m_Transform->GetWorldRotationZ() >= 90.0f || m_Transform->GetWorldRotationZ() <= -90.0f)
		m_Rot *= -1.0f;

	if(m_isDrop == false)
		m_Transform->RotationZ(m_Rot, DeltaTime);
	else
	{
		m_MoveRange -= 100.0f * DeltaTime;

		if (m_MoveRange >= 0.0f)
			m_Transform->Move(AXIS_X, 100.0f * m_MoveDir, DeltaTime);
	}

	return 0;
}

int GunItem_Com::Update(float DeltaTime)
{
	return 0;
}

int GunItem_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void GunItem_Com::Collision(float DeltaTime)
{
}

void GunItem_Com::CollisionLateUpdate(float DeltaTime)
{
}

void GunItem_Com::Render(float DeltaTime)
{
}

GunItem_Com * GunItem_Com::Clone()
{
	return new GunItem_Com(*this);
}

void GunItem_Com::AfterClone()
{
}
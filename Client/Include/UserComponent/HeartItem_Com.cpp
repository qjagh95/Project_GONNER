#include "ClientHeader.h"
#include "HeartItem_Com.h"

#include <Component/Animation2D_Com.h>
#include <Component/ColliderRect_Com.h>

JEONG_USING

HeartItem_Com::HeartItem_Com()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
	m_isDrop = false;
}

HeartItem_Com::HeartItem_Com(const HeartItem_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

HeartItem_Com::~HeartItem_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool HeartItem_Com::Init()
{
	Renderer_Com* HeartItemRender = m_Object->AddComponent<Renderer_Com>("HeartItemRender");
	HeartItemRender->SetMesh("TextureRect");
	HeartItemRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(HeartItemRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "HeartItem", TEXT("Monster\\player.png"));
	m_Material->SetMaterial(Vector4::White);
	
	m_Animation = m_Object->AddComponent<Animation2D_Com>("HeartItemAni");
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 64.0f, 576.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 64.0f, 640.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("HeartItem", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "HeartItem", L"Monster\\player.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("HeartItem");

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("HeartItemBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	RectColl->SetMyTypeName("HeartItem");
	RectColl->PushContinueTypeName("Bullet");
	RectColl->PushContinueTypeName("Monster");
	SAFE_RELEASE(RectColl);

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

int HeartItem_Com::Input(float DeltaTime)
{
	return 0;
}

int HeartItem_Com::Update(float DeltaTime)
{
	if (m_isDrop == true)
	{
		m_MoveRange -= 100.0f * DeltaTime;

		if (m_MoveRange >= 0.0f)
			m_Transform->Move(AXIS_X, 100.0f * m_MoveDir, DeltaTime);
	}

	return 0;
}

int HeartItem_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void HeartItem_Com::Collision(float DeltaTime)
{
}

void HeartItem_Com::CollisionLateUpdate(float DeltaTime)
{
}

void HeartItem_Com::Render(float DeltaTime)
{
}

HeartItem_Com * HeartItem_Com::Clone()
{
	return new HeartItem_Com(*this);
}

void HeartItem_Com::AfterClone()
{
}
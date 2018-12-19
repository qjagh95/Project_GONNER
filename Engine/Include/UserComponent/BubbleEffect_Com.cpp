#include "stdafx.h"
#include "BubbleEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

BubbleEffect_Com::BubbleEffect_Com()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
}

BubbleEffect_Com::BubbleEffect_Com(const BubbleEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
	m_Material = CopyData.m_Material;
	m_Animation = CopyData.m_Animation;

	m_ScaleVar = CopyData.m_ScaleVar;

	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = CopyData.m_ChangeTime;

	memcpy(m_ChangeColor, CopyData.m_ChangeColor, sizeof(Vector4) * 3);
}

BubbleEffect_Com::~BubbleEffect_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool BubbleEffect_Com::Init()
{
	Renderer_Com* BubbleRender = m_Object->AddComponent<Renderer_Com>("BubbleRender");
	BubbleRender->SetMesh("TextureRect");
	BubbleRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BubbleRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "Bubble", TEXT("Effect\\bloodParticles.png"));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BubbleAnimation");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 128.0f, 512.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 128.0f, 640.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BubbleEffect", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "Bubble", L"Effect\\bloodParticles.png");
	vecClipFrame.clear();

	int RandNum = RandomRange(1, 4);

	switch (RandNum)
	{
		case 1:
			m_Transform->SetWorldScale(100.0f, 100.0f, 1.0f);
			break;
		case 2:
			m_Transform->SetWorldScale(80.0f, 80.0f, 1.0f);
			break;
		case 3:
			m_Transform->SetWorldScale(60.0f, 60.0f, 1.0f);
			break;
		case 4:
			m_Transform->SetWorldScale(40.0f, 40.0f, 1.0f);
			break;
	}

	m_Transform->SetWorldPos(Vector3::Zero);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.1f;

	m_ChangeColor[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_ChangeColor[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_ChangeColor[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	m_Animation->ChangeClip("BubbleEffect");
	
	m_UpDir.x = cosf(DegreeToRadian((float)RandomRange(45, 140)));
	m_UpDir.y = sinf(DegreeToRadian((float)RandomRange(45, 140)));

	return true;
}

int BubbleEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int BubbleEffect_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);
	ScaleAction(DeltaTime);

	//45 ~ -45 사이 랜덤방향 
	m_Transform->Move(m_UpDir, 300.0f, DeltaTime);

	return 0;
}

int BubbleEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BubbleEffect_Com::Collision(float DeltaTime)
{
}

void BubbleEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BubbleEffect_Com::Render(float DeltaTime)
{
}

BubbleEffect_Com * BubbleEffect_Com::Clone()
{
	return new BubbleEffect_Com(*this);
}

void BubbleEffect_Com::AfterClone()
{
}

void BubbleEffect_Com::ChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar > m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

		int RandNum = RandomRange(1, 3);

		switch (RandNum)
		{
			case 1:
				m_Material->SetMaterial(m_ChangeColor[RandNum - 1]);
				break;
			case 2:
				m_Material->SetMaterial(m_ChangeColor[RandNum - 1]);
				break;
			case 3:
				m_Material->SetMaterial(m_ChangeColor[RandNum - 1]);
				break;
		}
	}
}

void BubbleEffect_Com::ScaleAction(float DeltaTime)
{
	m_Transform->AddScaleXY(-100.0f, DeltaTime);

	if (m_Transform->GetWorldScale() <= Vector3::Zero)
	{
		m_Object->SetIsActive(false);
		SetIsActive(false);
	}
}

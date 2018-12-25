#include "stdafx.h"
#include "HeartUI_Com.h"
#include "Gun_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

HeartUI_Com::HeartUI_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
	m_isGoingPos = false;
	m_isMove = false;
}

HeartUI_Com::HeartUI_Com(const HeartUI_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

HeartUI_Com::~HeartUI_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool HeartUI_Com::Init()
{
	m_StaticTime = 2.0f;
	m_StaticTimeVar = 0.0f;
	m_GoingPos = Vector3(200.0f, 200.0f, 1.0f);

	m_ColorChangeTimeVar = 0.0f;
	m_ColorChangeTime = 0.2f;

	m_Color[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_Color[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_Color[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	Renderer_Com* HeartItemRender = m_Object->AddComponent<Renderer_Com>("HeartUIRender");
	HeartItemRender->SetMesh("TextureRect");
	HeartItemRender->SetScreenRender(true);
	HeartItemRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(HeartItemRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Animation = m_Object->AddComponent<Animation2D_Com>("HeartUIAni");
	m_Transform->SetWorldScale(100.0f, 100.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 64.0f, 576.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 64.0f, 640.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("HeartUI", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "HeartUI", L"Monster\\player.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("HeartUI");

	return true;
}

int HeartUI_Com::Input(float DeltaTime)
{
	return 0;
}

int HeartUI_Com::Update(float DeltaTime)
{

	Vector3 TargetPos = m_Target->GetTransform()->GetWorldPos();

	m_StaticTimeVar += DeltaTime;

	if (m_StaticTimeVar >= m_StaticTime)
		m_isMove = true;

	if (m_isMove == false)
		SetPos(TargetPos);

	if (m_isMove == true)
		Move(DeltaTime);

	if (Gun_Com::m_isReloading == true)
	{
		m_Transform->SetWorldScale(32.0f, 32.0f, 1.0f);
		m_Material->SetMaterial(Vector4(201.0f / 255.0f, 112.0f / 255.0f, 97.0f / 255.0f, 1.0f));
	}
	else
	{
		m_Transform->SetWorldScale(100.0f, 100.0f, 1.0f);
		ColorChange(DeltaTime);
	}

	return 0;
}

int HeartUI_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void HeartUI_Com::Collision(float DeltaTime)
{
}

void HeartUI_Com::CollisionLateUpdate(float DeltaTime)
{
}

void HeartUI_Com::Render(float DeltaTime)
{
}

HeartUI_Com * HeartUI_Com::Clone()
{
	return new  HeartUI_Com(*this);
}

void HeartUI_Com::AfterClone()
{
}

void HeartUI_Com::SetPos(const Vector3 & Pos)
{
	Vector3 CameraPos = m_Scene->GetMainCameraTransform()->GetWorldPos();
	Vector3 ResultPos = Pos;
	ResultPos -= CameraPos;
	ResultPos.z = 0.0f;

	m_Transform->SetWorldPos(ResultPos.x - 300.0f, ResultPos.y, 1.0f);
}

void HeartUI_Com::Move(float DeltaTime)
{
	Vector3 Lerp = Vector3::Lerp(m_Transform->GetWorldPos(), m_GoingPos, DeltaTime * 3.0f);
	m_Transform->SetWorldPos(Lerp);

	int intPosX;
	int intPosY;
	intPosX = (int)Lerp.x;
	intPosY = (int)Lerp.y;

	if (intPosX <= m_GoingPos.x && intPosY <= m_GoingPos.y)
		m_isGoingPos = true;
}

void HeartUI_Com::ColorChange(float DeltaTime)
{
	m_ColorChangeTimeVar += DeltaTime;

	if (m_ColorChangeTimeVar > m_ColorChangeTime)
	{
		m_ColorChangeTimeVar = 0.0f;

		int RandNum = RandomRange(1, 3);

		switch (RandNum)
		{
			case 1:
				m_Material->SetMaterial(m_Color[RandNum - 1]);
				break;
			case 2:
				m_Material->SetMaterial(m_Color[RandNum - 1]);
				break;
			case 3:
				m_Material->SetMaterial(m_Color[RandNum - 1]);
				break;
		}
	}
}

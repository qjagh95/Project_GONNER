#include "stdafx.h"
#include "BallonEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

BallonEffect_Com::BallonEffect_Com()
{
}

BallonEffect_Com::BallonEffect_Com(const BallonEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BallonEffect_Com::~BallonEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool BallonEffect_Com::Init()
{
	Renderer_Com* BallonEffectRender = m_Object->AddComponent<Renderer_Com>("BallonEffect");
	BallonEffectRender->SetMesh("TextureRect");
	BallonEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BallonEffectRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BallonEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(1.0f, 1.0f, 0.0f, 0.1f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BallonEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 128.0f, 1664.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 128.0f, 1792.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BallonEffect", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "BallonEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	for (int i = 0; i < 7; ++i)
	{
		tFrame.LeftTop = Vector2(1152.0f + i * 128.0f, 896.0f);
		tFrame.RightBottom = Vector2(1152.0f + (i + 1) * 128.0f, 1024.0f);
		vecClipFrame.push_back(tFrame);
	}

	for (int i = 0; i < 5; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 1024.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 1152.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Die", A2D_ATLS, AO_LOOP, 0.3f, vecClipFrame, "BallonEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_State = ES_IDLE;
	m_Animation->ChangeClip("BallonEffect");

	int RandNum = RandomRange(1, 3);
	switch (RandNum)
	{
		case 1:
			m_UpTime = 0.6f;
			m_UpSpeed = 80.0f;
			m_Transform->SetWorldScale(32.0f, 32.0f, 1.0f);
			m_Scale = Vector3(32.0f, 32.0f, 1.0f);
			break;
		case 2:
			m_UpTime = 0.5f;
			m_UpSpeed = 40.0f;
			m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
			m_Scale = Vector3(64.0f, 64.0f, 1.0f);
			break;
		case 3:
			m_UpTime = 0.4f;
			m_UpSpeed = 20.0f;
			m_Transform->SetWorldScale(92.0f, 92.0f, 1.0f);
			m_Scale = Vector3(92.0f, 92.0f, 1.0f);
			break;
	}

	m_MoveSpeed = (float)RandomRange(30, 70);

	m_isMove = true;
	m_UpTimeVar = 0.0f;

	return true;
}

int BallonEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int BallonEffect_Com::Update(float DeltaTime)
{
	m_UpTimeVar += DeltaTime;

	if (m_UpTimeVar >= m_UpTime)
		m_isMove = false;

	if (m_isMove == false)
	{
		if (m_MoveSpeed >= 0.0f)
			m_MoveSpeed -= 30.0f * DeltaTime;
		else
			m_MoveSpeed = 0.0f;

		m_Transform->Move(AXIS_Y, m_UpSpeed, DeltaTime);
	}

	//어차피 나중에 0됨.
	if (m_Animation->GetDir() == MD_LEFT)
		m_Transform->Move(AXIS_X, m_MoveSpeed, DeltaTime);
	else
		m_Transform->Move(AXIS_X, -m_MoveSpeed, DeltaTime);

	if (m_State == ES_IDLE)
		m_Transform->AddScaleXY(-5.0f, DeltaTime);

	Vector3 CurScale = m_Transform->GetWorldScale();

	if (CurScale <= m_Scale * 0.5f)
	{
		m_State = ES_DIE;

		if (m_Animation->GetClipName() != "Die")
			m_Animation->ChangeClip("Die");
	}

	if (m_State == ES_DIE && m_Animation->GetIsEnd() == true)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}

	return 0;
}

int BallonEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BallonEffect_Com::Collision(float DeltaTime)
{
}

void BallonEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BallonEffect_Com::Render(float DeltaTime)
{
}

BallonEffect_Com * BallonEffect_Com::Clone()
{
	return new BallonEffect_Com(*this);
}

void BallonEffect_Com::AfterClone()
{
}

void BallonEffect_Com::SetPos(const Vector3 & Pos, const Vector4 & Color)
{
	m_Transform->SetWorldPos(Pos);
	m_Material->SetMaterial(Color);
}

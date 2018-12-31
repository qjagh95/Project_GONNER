#include "stdafx.h"
#include "BasicEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

BasicEffect_Com::BasicEffect_Com()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
	m_MoveSpeed = 0.0f;
	m_Dir = Vector3::Zero;
}

BasicEffect_Com::BasicEffect_Com(const BasicEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BasicEffect_Com::~BasicEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool BasicEffect_Com::Init()
{
	Renderer_Com* FragmentEffectRender = m_Object->AddComponent<Renderer_Com>("FragmentEffect");
	FragmentEffectRender->SetMesh("TextureRect");
	FragmentEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(FragmentEffectRender);

	int RandNum = RandomRange(1, 4);
	switch (RandNum)
	{
		case 1:
			m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
			break;
		case 2:
			m_Transform->SetWorldScale(75.0f, 75.0f, 1.0f);
			break;
		case 3:
			m_Transform->SetWorldScale(90.0f, 90.0f, 1.0f);
			break;
		case 4:
			m_Transform->SetWorldScale(110.0f, 110.0f, 1.0f);
			break;
	}

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BasicEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(200.0f / 255.0f, 168.0f / 255.0f, 73.0f / 255.0f, 0.4f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BasicEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 14; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 0.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BasicEffect", A2D_ATLS, AO_ONCE_STOP, 0.4f, vecClipFrame, "BasicEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("BasicEffect");

	int RandNum2 = RandomRange(1, 4);

	switch (RandNum2)
	{
		case 1:
			m_MoveSpeed = 700.0f;
			break;
		case 2:
			m_MoveSpeed = 800.0f;
			break;
		case 3:
			m_MoveSpeed = 900.0f;
			break;
		case 4:
			m_MoveSpeed = 1000.0f;
			break;
	}

	return true;
}

int BasicEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int BasicEffect_Com::Update(float DeltaTime)
{
	if (m_Animation->GetDir() == MD_LEFT)
		m_Transform->Move(AXIS_Y, m_MoveSpeed, DeltaTime);
	else if (m_Animation->GetDir() == MD_RIGHT)
		m_Transform->Move(AXIS_Y, -m_MoveSpeed, DeltaTime);

	if (m_Animation->GetIsEnd() == true)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}

	return 0;
}

int BasicEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BasicEffect_Com::Collision(float DeltaTime)
{
}

void BasicEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BasicEffect_Com::Render(float DeltaTime)
{
}

BasicEffect_Com * BasicEffect_Com::Clone()
{
	return new BasicEffect_Com(*this);
}

void BasicEffect_Com::AfterClone()
{
}

void BasicEffect_Com::SetRandomDirection(const Vector4& Color)
{
	float Angle = 0.0f;

	Angle = (float)RandomRange(0, 360);
	m_Transform->SetWorldRotZ(Angle);
	m_Transform->SetWorldRotZFromNoneAxis(Angle - 180.0f);

	m_Material->SetMaterial(Color);
}

#include "stdafx.h"
#include "FragmentEffect_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

FragmentEffect_Com::FragmentEffect_Com()
{
}

FragmentEffect_Com::FragmentEffect_Com(const FragmentEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

FragmentEffect_Com::~FragmentEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool FragmentEffect_Com::Init()
{
	Renderer_Com* FragmentEffectRender = m_Object->AddComponent<Renderer_Com>("FragmentEffect");
	FragmentEffectRender->SetMesh("TextureRect");
	FragmentEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(FragmentEffectRender);

	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "FragmentEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(200.0f / 255.0f, 168.0f / 255.0f, 73.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BallonEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 128.0f, 384.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 128.0f, 512.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("FragmentEffect", A2D_ATLS, AO_ONCE_STOP, 0.6f, vecClipFrame, "FragmentEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("FragmentEffect");

	int RandNum = RandomRange(1, 4);

	switch (RandNum)
	{
		case 1:
			m_MoveSpeed = 900.0f;
			break;
		case 2:
			m_MoveSpeed = 1000.0f;
			break;
		case 3:
			m_MoveSpeed = 1100.0f;
			break;
		case 4:
			m_MoveSpeed = 1200.0f;
			break;
	}

	return true;
}

int FragmentEffect_Com::Input(float DeltaTime)
{
	if (m_Animation->GetIsEnd() == true)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}

	return 0;
}

int FragmentEffect_Com::Update(float DeltaTime)
{
	if (m_Animation->GetDir() == MD_LEFT)
		m_Transform->Move(AXIS_X, m_MoveSpeed);
	else if (m_Animation->GetDir() == MD_RIGHT)
		m_Transform->Move(AXIS_X, -m_MoveSpeed);

	return 0;
}

int FragmentEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void FragmentEffect_Com::Collision(float DeltaTime)
{
}

void FragmentEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void FragmentEffect_Com::Render(float DeltaTime)
{
}

FragmentEffect_Com * FragmentEffect_Com::Clone()
{
	return new FragmentEffect_Com(*this);
}

void FragmentEffect_Com::AfterClone()
{
}

void FragmentEffect_Com::SetDirection(MOVE_DIR dir)
{
	m_Animation->SetDir(dir);
	float Angle = 0.0f;

	if (m_Animation->GetDir() == MD_LEFT)
		Angle = (float)RandomRange(45, 135);
	else if (m_Animation->GetDir() == MD_RIGHT)
		Angle = (float)RandomRange(250, 310);

	m_Transform->RotationZ(Angle);
}
#include "ClientHeader.h"
#include "SnekeTail_Com.h"
#include "SnakeHead_Com.h"

#include <Component/Animation2D_Com.h>

SnekeTail_Com::SnekeTail_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

SnekeTail_Com::SnekeTail_Com(const SnekeTail_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

SnekeTail_Com::~SnekeTail_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool SnekeTail_Com::Init()
{
	m_ChangeColor[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_ChangeColor[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_ChangeColor[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.1f;

	m_ChangeColor[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_ChangeColor[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_ChangeColor[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	Renderer_Com* SnakeTailRender = m_Object->AddComponent<Renderer_Com>("SnakeTail");
	SnakeTailRender->SetMesh("TextureRect");
	SnakeTailRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(SnakeTailRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4::White);
	m_Material->SetDiffuseTexture(0, "SnakeTail", TEXT("Monster\\bigsprites2.png"));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("SnakeTailAni");
	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(512.0f + i * 128.0f, 768.0f);
		tFrame.RightBottom = Vector2(512.0f + (i + 1) * 128.0f, 896.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("SnakeTail", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "SnakeTail", L"Monster\\bigsprites2.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("SnakeTail");

	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.1f;

	return true;
}

int SnekeTail_Com::Input(float DeltaTime)
{
	return 0;
}

int SnekeTail_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);

	return 0;
}

int SnekeTail_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void SnekeTail_Com::Collision(float DeltaTime)
{
}

void SnekeTail_Com::CollisionLateUpdate(float DeltaTime)
{
}

void SnekeTail_Com::Render(float DeltaTime)
{
}

SnekeTail_Com * SnekeTail_Com::Clone()
{
	return new SnekeTail_Com(*this);
}

void SnekeTail_Com::AfterClone()
{
}

void SnekeTail_Com::ChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar > m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

		switch (SnakeHead_Com::m_RandNum)
		{
		case 1:
			m_Material->SetMaterial(m_ChangeColor[SnakeHead_Com::m_RandNum - 1]);
			break;
		case 2:
			m_Material->SetMaterial(m_ChangeColor[SnakeHead_Com::m_RandNum - 1]);
			break;
		case 3:
			m_Material->SetMaterial(m_ChangeColor[SnakeHead_Com::m_RandNum - 1]);
			break;
		}
	}
}

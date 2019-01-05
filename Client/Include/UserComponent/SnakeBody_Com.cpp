#include "ClientHeader.h"
#include "SnakeBody_Com.h"
#include "SnakeHead_Com.h"

#include <Component/Animation2D_Com.h>

SnakeBody_Com::SnakeBody_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

SnakeBody_Com::SnakeBody_Com(const SnakeBody_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

SnakeBody_Com::~SnakeBody_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool SnakeBody_Com::Init()
{
	m_LeftAngle = 0.0f;
	m_RightAngle = 0.0f;
	m_Angle = 360.0f;
	m_Speed = 10.0f;
	m_isTurn = false;

	m_ChangeColor[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_ChangeColor[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_ChangeColor[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	Renderer_Com* SnakeBodyRender = m_Object->AddComponent<Renderer_Com>("SnakeBody");
	SnakeBodyRender->SetMesh("TextureRect");
	SnakeBodyRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(SnakeBodyRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4::White);
	m_Material->SetDiffuseTexture(0, "SnakeBody", TEXT("Monster\\bigsprites2.png"));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("SnakeBodyAni");
	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(256.0f + i * 128.0f, 384.0f);
		tFrame.RightBottom = Vector2(256.0f + (i + 1) * 128.0f, 512.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("SnakeBody", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "SnakeBody", L"Monster\\bigsprites2.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("SnakeBody");

	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.1f;

	return true;
}

int SnakeBody_Com::Input(float DeltaTime)
{
	return 0;
}

int SnakeBody_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);
	CircleMove(DeltaTime);

	return 0;
}

int SnakeBody_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void SnakeBody_Com::Collision(float DeltaTime)
{
}

void SnakeBody_Com::CollisionLateUpdate(float DeltaTime)
{
}

void SnakeBody_Com::Render(float DeltaTime)
{
}

SnakeBody_Com * SnakeBody_Com::Clone()
{
	return new SnakeBody_Com(*this);
}

void SnakeBody_Com::AfterClone()
{
}

void SnakeBody_Com::SetPosRange(const Vector3 & Pos, float MoveRange)
{
	m_Transform->SetWorldPos(Pos);
	m_SavePos = Pos;
	m_AngleRange = MoveRange;

	m_LeftAngle = m_Angle + MoveRange;
	m_RightAngle = m_Angle - MoveRange;
}

void SnakeBody_Com::ChangeColor(float DeltaTime)
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

//LookAt쓰면 될거같긴한데.. 흠...일단은 야매
void SnakeBody_Com::CircleMove(float DeltaTime)
{
	float Dir = 1.0f;

	if (m_Angle <= m_RightAngle)
		m_isTurn = true;
	else if (m_Angle >= m_LeftAngle)
		m_isTurn = false;

	if (m_isTurn == true)
	{
		Dir = 1.0f;
		m_Angle += m_Speed * DeltaTime;
	}
	else
	{
		Dir = -1.0f;
		m_Angle -= m_Speed * DeltaTime;
	}

	float X = cosf(DegreeToRadian(m_Angle));
	float Y = sinf(DegreeToRadian(m_Angle));

	Vector3 Pos = m_Transform->GetWorldPos();
	m_Transform->SetWorldRotZ(m_Angle);
	m_Transform->Move(Vector3(X, Y, 0.0f), m_Speed, Dir * DeltaTime);

	//m_Transform->Move(Vector3(X, Y, 0.0f), m_Speed, DeltaTime);
}

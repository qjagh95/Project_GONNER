#include "stdafx.h"
#include "Heart_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

Heart_Com::Heart_Com()
{
}

Heart_Com::Heart_Com(const Skull_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Heart_Com::~Heart_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool Heart_Com::Init()
{
	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.1f;

	m_Color[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_Color[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_Color[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	return true;
}

int Heart_Com::Input(float DeltaTime)
{
	return 0;
}

int Heart_Com::Update(float DeltaTime)
{
	return 0;
}

int Heart_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Heart_Com::Collision(float DeltaTime)
{
}

void Heart_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Heart_Com::Render(float DeltaTime)
{
}

Heart_Com * Heart_Com::Clone()
{
	return new Heart_Com(*this);
}

void Heart_Com::AfterClone()
{
}

void Heart_Com::ChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar > m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

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

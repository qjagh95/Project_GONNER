#include "stdafx.h"
#include "Gravity_Com.h"

JEONG_USING

float Gravity_Com::m_Gravity = 1500.0f;

Gravity_Com::Gravity_Com()
{
	m_ComType = CT_GRAVITY;
	m_Stage = NULLPTR;
}

Gravity_Com::Gravity_Com(const Gravity_Com & CopyData)
	:Component_Base(CopyData)
{
	*this = CopyData;
}

Gravity_Com::~Gravity_Com()
{
}

bool Gravity_Com::Init()
{
	m_Force = 0.0f;
	m_isJump = false;

	m_ObjectScale = m_Object->GetTransform()->GetWorldScale();
	return true;
}

int Gravity_Com::Input(float DeltaTime)
{	
	return 0;
}

int Gravity_Com::Update(float DeltaTime)
{
	float ZAngle = abs(m_Object->GetTransform()->GetWorldRotationZ());

	m_Force -= m_Gravity * DeltaTime;
	m_Object->GetTransform()->Move(AXIS_Y, m_Force, DeltaTime);

	if (m_Force >= 0.0f)
		m_isJump = true;

	Vector3 dPos;
	dPos.x = m_Object->GetTransform()->GetWorldPos().x;
	dPos.y = m_Object->GetTransform()->GetWorldPos().y - m_ObjectScale.y * 0.5f;

	Vector3 uPos;
	uPos.x = dPos.x;
	uPos.y = dPos.y + m_ObjectScale.y;

	Tile2D_Com* downTile = m_Stage->GetTile2D(dPos);
	
	if (downTile->GetTileOption() == T2D_NOMOVE)
	{
		Vector3 tPos = downTile->GetTransform()->GetWorldPos();
		Vector3 tScale = downTile->GetTransform()->GetWorldScale();

		m_Object->GetTransform()->SetWorldPos(dPos.x, tPos.y + tScale.y +  m_ObjectScale.y * 0.5f, 1.0f);
		m_Force = 0.0f;
		m_isJump = false;
	}
	
	else if (m_Stage->GetTile2D(uPos)->GetTileOption() == T2D_NOMOVE)
	{
		float Amount = 2.0f;

		while (true)
		{
			m_Object->GetTransform()->Move(AXIS_Y, -Amount);
			Tile2D_Com* getTile = m_Stage->GetTile2D(m_Object->GetTransform()->GetWorldPos());

			if (getTile->GetTileOption() == T2D_NORMAL)
				break;
		}
		m_Force = 0.0f;
	}

	return 0;
}

int Gravity_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Gravity_Com::Collision(float DeltaTime)
{
}

void Gravity_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Gravity_Com::Render(float DeltaTime)
{
}

Gravity_Com * Gravity_Com::Clone()
{
	return new Gravity_Com(*this);
}

void Gravity_Com::AfterClone()
{
}

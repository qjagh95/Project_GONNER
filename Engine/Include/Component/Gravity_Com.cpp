#include "stdafx.h"
#include "Gravity_Com.h"

JEONG_USING

float Gravity_Com::m_Gravity;

Gravity_Com::Gravity_Com()
{
	m_ComType = CT_GRAVITY;
	m_Stage = NULLPTR;
	m_Force = 0.0f;
	m_Gravity = 1500.0f;
	m_ObjectScale = Vector3::Zero;
	m_isJump = false;
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
	m_Stage = NULLPTR;
	m_ObjectScale = m_Object->GetTransform()->GetWorldScale();

	return true;
}

int Gravity_Com::Input(float DeltaTime)
{	
	return 0;
}

int Gravity_Com::Update(float DeltaTime)
{
	if (m_Stage == NULLPTR)
		m_Stage = StageManager::Get()->FindCurStage();

	m_DeltaTime = DeltaTime;

	if (m_DeltaTime >= 0.1f)
		m_DeltaTime = 0.01f;
	
	m_Force -= m_Gravity * m_DeltaTime;
	m_Object->GetTransform()->Move(AXIS_Y, m_Force, m_DeltaTime);

	if (m_Force >= 0.0f)
		m_isJump = true;

	Vector3 dPos;
	dPos.x = m_Object->GetTransform()->GetWorldPos().x;
	dPos.y = m_Object->GetTransform()->GetWorldPos().y - m_ObjectScale.y * 0.5f;

	Vector3 uPos;
	uPos.x = dPos.x;
	uPos.y = dPos.y + m_ObjectScale.y;

	Tile2D_Com* downTile = m_Stage->GetTile2D(dPos);
	Tile2D_Com* upTile = m_Stage->GetTile2D(uPos);

	if (downTile != NULLPTR && downTile->GetTileOption() == T2D_NOMOVE)
	{
		Vector3 tPos = downTile->GetTransform()->GetWorldPos();
		Vector3 tScale = downTile->GetTransform()->GetWorldScale();

		m_Object->GetTransform()->SetWorldPos(dPos.x, tPos.y + tScale.y +  m_ObjectScale.y * 0.5f, 1.0f);
		m_Force = 0.0f;
		m_isJump = false;
	}
	else if (upTile != NULLPTR && upTile->GetTileOption()== T2D_NOMOVE)
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

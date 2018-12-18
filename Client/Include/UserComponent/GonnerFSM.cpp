#include "ClientHeader.h"
#include "Gonner_Com.h"

void Gonner_Com::FS_BUGDOWN(float DeltaTime)
{
	BugMove(DeltaTime);

	Tile2D_Com* downTile = m_Stage->GetTile2D(m_downPos);

	if (downTile->GetTileOption() == T2D_NOMOVE)
		ChangeState(GS_BUGIDLE, m_AniName, m_Animation);
}

void Gonner_Com::FS_BUGIDLE(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("MoveLeft") || KeyInput::Get()->KeyPress("MoveRight"))
	{
		m_GravityCom->SetForce(450.0f);
		m_BugAngle = 180.0f;
		m_Transform->SetWorldRotZFromNoneAxis(180.0f);
		ChangeState(GS_BUGJUMP, m_AniName, m_Animation);
	}
}

void Gonner_Com::FS_BUGJUMP(float DeltaTime)
{
	DirCheck();
	BugMove(DeltaTime);

	switch (m_Animation->GetDir())
	{
		case MD_LEFT:
		{
			m_BugAngle += 100.0f * DeltaTime;
			m_Transform->RotationZFromNoneAxis(m_BugAngle * DeltaTime);
		}
		break;
		case MD_RIGHT:
		{
			m_BugAngle += 100.0f * DeltaTime;
			m_Transform->RotationZFromNoneAxis(-m_BugAngle * DeltaTime);
		}
		break;
	} 

	if (m_GravityCom->GetIsJump() == false)
	{
		if (m_downTile->GetTileOption() == T2D_NOMOVE)
		{
			if (m_BugJumpMax <= m_BugJumpCount)
			{
				m_BugAngle = 0.0f;
				m_Transform->SetWorldRotZ(0.0f);

				ChangeState(GS_IDLE, m_AniName, m_Animation);
			}
			else
			{
				m_BugAngle = 0.0f;
				m_Transform->SetWorldRotZ(0.0f);

				m_BugJumpCount++;
				ChangeState(GS_BUGIDLE, m_AniName, m_Animation);
			}
		}
	}
}

void Gonner_Com::FS_IDLE(float DeltaTime)
{
	if(KeyInput::Get()->KeyPress("MoveLeft"))
		ChangeState(GS_RUN, m_AniName, m_Animation);
	else if(KeyInput::Get()->KeyPress("MoveRight"))
		ChangeState(GS_RUN, m_AniName, m_Animation);

	if (KeyInput::Get()->KeyDown("Jump"))
	{
		m_GravityCom->SetForce(650.0f);
		m_Scene->CreateWave(m_Pos, 0.8f, 0.1f);
		SoundManager::Get()->FindSoundEffect("Jump")->Play();

		ChangeState(GS_JUMP, m_AniName, m_Animation);
	}
}

void Gonner_Com::FS_RUN(float DeltaTime)
{
	DirCheck();

	if (KeyInput::Get()->KeyPress("MoveLeft") == false && KeyInput::Get()->KeyPress("MoveRight") == false)
		ChangeState(GS_IDLE, m_AniName, m_Animation);

	if (KeyInput::Get()->KeyDown("Jump"))
	{
		m_GravityCom->SetForce(650.0f);
		m_Scene->CreateWave(m_Pos, 0.8f, 0.1f);
		SoundManager::Get()->FindSoundEffect("Jump")->Play();
		
		ChangeState(GS_JUMP, m_AniName, m_Animation);
	}

	else
		Move(DeltaTime);
}

void Gonner_Com::FS_ATTACK(float DeltaTime)
{
	DirCheck();
}

void Gonner_Com::FS_JUMP(float DeltaTime)
{
	DirCheck();
	Move(DeltaTime);

	if (m_downTile ->GetTileOption() == T2D_NOMOVE)
		ChangeState(GS_IDLE, m_AniName, m_Animation);

	if (KeyInput::Get()->KeyDown("Jump"))
	{
		m_GravityCom->SetForce(650.0f);
		m_Scene->CreateWave(m_Pos, 0.8f, 0.1f);
		SoundManager::Get()->FindSoundEffect("Jump")->Play();

		ChangeState(GS_DOUBLEJUMP, m_AniName, m_Animation);
	}
}

void Gonner_Com::FS_DOUBLEJUMP(float DeltaTime)
{
	DirCheck();
}

void Gonner_Com::FS_WALLSTOP(float DeltaTime)
{
}

void Gonner_Com::FS_KNIGHT(float DeltaTime)
{
}

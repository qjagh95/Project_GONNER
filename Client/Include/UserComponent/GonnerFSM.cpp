#include "ClientHeader.h"
#include "Gonner_Com.h"

void Gonner_Com::FS_BUGDOWN(float DeltaTime)
{
	BugMove(DeltaTime);

	if (KeyInput::Get()->KeyPress("MoveLeft"))
	{
		m_DownAngle += 25.0f * DeltaTime;

		if(m_DownAngle <= 45.0f)
			m_Transform->SetWorldRotZFromNoneAxis(-m_DownAngle);
	}
	if(KeyInput::Get()->KeyPress("MoveRight"))
	{
		m_DownAngle += 25.0f * DeltaTime;
	
		if (m_DownAngle <= 45.0f)
			m_Transform->SetWorldRotZFromNoneAxis(m_DownAngle);
	}

	Tile2D_Com* downTile = m_Stage->GetTile2D(m_downPos);
	
	if (downTile->GetTileOption() == T2D_NOMOVE)
	{
		m_DownAngle = 0.0f;
		m_Transform->SetWorldRotZ(0.0f);
		ChangeState(GS_BUGIDLE, m_AniName, m_Animation);
	}
}

void Gonner_Com::FS_BUGIDLE(float DeltaTime)
{
	CreateBugEffect(DeltaTime);

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
	CreateBugEffect(DeltaTime);

	switch (m_Animation->GetDir())
	{
		case MD_LEFT:
		{
			if(KeyInput::Get()->KeyPress("MoveRight") == false)
				m_BugAngle += 100.0f * DeltaTime;
			else
				m_BugAngle += 1600.0f * DeltaTime;

			m_Transform->RotationZFromNoneAxis(m_BugAngle * DeltaTime);
		}
		break;
		case MD_RIGHT:
		{
			if (KeyInput::Get()->KeyPress("MoveLeft") == false)
				m_BugAngle += 100.0f * DeltaTime;
			else
				m_BugAngle += 1600.0f * DeltaTime;

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
				CreateBugChangeEffect(DeltaTime);
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

void Gonner_Com::FS_JUMP(float DeltaTime)
{
	DirCheck();
	Move(DeltaTime);

	if (m_downTile ->GetTileOption() == T2D_NOMOVE)
		ChangeState(GS_IDLE, m_AniName, m_Animation);

	if (m_leftTile->GetTileOption() == T2D_NOMOVE || m_rightTile->GetTileOption() == T2D_NOMOVE)
	{
		if (m_Animation->GetDir() == MD_LEFT)
			m_Animation->SetDir(MD_RIGHT);
		else if (m_Animation->GetDir() == MD_RIGHT)
			m_Animation->SetDir(MD_LEFT);

		m_GravityCom->SetForce(0.0f);
		ChangeState(GS_WALLSTOP, m_AniName, m_Animation);
	}

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

	if (m_downTile->GetTileOption() == T2D_NOMOVE)
		ChangeState(GS_IDLE, m_AniName, m_Animation);

	//벽상태도 추가
	if (m_Animation->GetDir() == MD_LEFT)
	{
		if(m_leftTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, -300.0f, DeltaTime);
	}

	else if (m_Animation->GetDir() == MD_RIGHT)
	{
		if (m_rightTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, 300.0f, DeltaTime);
	}

	if (m_leftTile->GetTileOption() == T2D_NOMOVE || m_rightTile->GetTileOption() == T2D_NOMOVE)
	{
		if (m_Animation->GetDir() == MD_LEFT)
			m_Animation->SetDir(MD_RIGHT);
		else if (m_Animation->GetDir() == MD_RIGHT)
			m_Animation->SetDir(MD_LEFT);

		m_GravityCom->SetForce(0.0f);
		ChangeState(GS_WALLSTOP, m_AniName, m_Animation);
	}
}

void Gonner_Com::FS_WALLSTOP(float DeltaTime)
{
	if (m_Animation->GetDir() == MD_LEFT)
	{
		if (KeyInput::Get()->KeyPress("MoveLeft"))
		{
			m_GravityCom->SetGravity(1500.0f);
			ChangeState(GS_RUN, m_AniName, m_Animation);
			return;
		}

		if (KeyInput::Get()->KeyPress("MoveRight"))
		{
			if (m_rightTile->GetTileOption() == T2D_NOMOVE)
				m_GravityCom->SetGravity(100.0f);
			else
			{
				m_GravityCom->SetGravity(1500.0f);
				ChangeState(GS_IDLE, m_AniName, m_Animation);
			}

			if (KeyInput::Get()->KeyDown("Jump"))
			{
				m_GravityCom->SetGravity(1500.0f);
				m_GravityCom->SetForce(700.0f);
				SoundManager::Get()->FindSoundEffect("Jump")->Play();
				ChangeState(GS_WALLJUMP, m_AniName, m_Animation);
			}
		}
		else
			m_GravityCom->SetGravity(1500.0f);
	}
	else
	{
		if (KeyInput::Get()->KeyPress("MoveRight"))
		{
			m_GravityCom->SetGravity(1500.0f);
			ChangeState(GS_RUN, m_AniName, m_Animation);
			return;
		}

		if (KeyInput::Get()->KeyPress("MoveLeft"))
		{
			if (m_leftTile->GetTileOption() == T2D_NOMOVE)
				m_GravityCom->SetGravity(100.0f);
			else
			{
				m_GravityCom->SetGravity(1500.0f);
				ChangeState(GS_IDLE, m_AniName, m_Animation);
				return;
			}

			if (KeyInput::Get()->KeyDown("Jump"))
			{
				m_GravityCom->SetGravity(1500.0f);
				m_GravityCom->SetForce(700.0f);
				SoundManager::Get()->FindSoundEffect("Jump")->Play();
				ChangeState(GS_WALLJUMP, m_AniName, m_Animation);
			}
		}
		else
			m_GravityCom->SetGravity(1500.0f);
	}

	if (m_downTile->GetTileOption() == T2D_NOMOVE)
	{
		m_GravityCom->SetGravity(1500.0f);
		ChangeState(GS_IDLE, m_AniName, m_Animation);
	}
}

void Gonner_Com::FS_KNIGHT(float DeltaTime)
{
}

void Gonner_Com::FS_WALLJUMP(float DeltaTime)
{
	DirCheck();

	if (m_GravityCom->GetForce() >= 0.0f)
	{
		if (m_Animation->GetDir() == MD_LEFT)
			m_Transform->Move(AXIS_X, 100.0f, DeltaTime);
		else if (m_Animation->GetDir() == MD_RIGHT)
			m_Transform->Move(AXIS_X, -100.0f, DeltaTime);
	}

	if (m_GravityCom->GetForce() <= 0.0f)
	{
		m_GravityCom->SetGravity(1500.0f);
		ChangeState(GS_JUMP, m_AniName, m_Animation);
		return;
	}
}
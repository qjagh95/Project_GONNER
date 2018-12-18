#include "ClientHeader.h"
#include "Gonner_Com.h"
#include "GameObject.h"
#include "KeyInput.h"

#include "Component/ColliderRect_Com.h"
#include "Component/ColliderCircle_Com.h"
#include "Component/ColliderOBB2D_Com.h"
#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Material_Com.h"
#include "Component/TitleBar_Com.h"
#include <Scene/Scene.h>

#include "../UserComponent/Bullet_Com.h"
#include "../UserComponent/BulletRot_Com.h"

Gonner_Com::Gonner_Com()
	: m_Animation(NULLPTR), m_GravityCom(NULLPTR)
{
	m_BugAngle = 0.0f;
	m_isBugJump = false;
	m_isDirChangeLeft = false;
	m_isDirChangeRight = false;

	m_BugJumpMax = 6;
	m_BugJumpCount = 0;

	m_downTile = NULLPTR;
	m_upTile = NULLPTR;
	m_leftTile = NULLPTR;
	m_rightTile = NULLPTR;
}

Gonner_Com::Gonner_Com(const Gonner_Com & userCom)
	:Ready(userCom)
{
	m_Animation = NULLPTR;
}

Gonner_Com::~Gonner_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_GravityCom);
}

bool Gonner_Com::Init()
{
	BasicInit();
	AnimationInit();

	m_GravityCom = m_Object->AddComponent<Gravity_Com>("Gravity");
	return true;
}

int Gonner_Com::Input(float DeltaTime)
{
	return 0;
}

int Gonner_Com::Update(float DeltaTime)
{
	m_Pos = m_Transform->GetWorldPos();

	m_upPos = Vector3(m_Pos.x, m_Pos.y + m_ScaleHalf.y + 1.0f, 0.0f);
	m_downPos = Vector3(m_Pos.x, m_Pos.y - m_ScaleHalf.y - 1.0f, 0.0f);
	m_leftPos = Vector3(m_Pos.x - m_ScaleHalf.x - 1.0f, m_Pos.y, 0.0f);
	m_rightPos = Vector3(m_Pos.x + m_ScaleHalf.x + 1.0f, m_Pos.y, 0.0f);

	m_downTile = m_Stage->GetTile2D(m_downPos);
	m_upTile = m_Stage->GetTile2D(m_upPos);
	m_leftTile = m_Stage->GetTile2D(m_leftPos);
	m_rightTile = m_Stage->GetTile2D(m_rightPos);

	switch (m_State)
	{
		case GS_BUGIDLE:
			FS_BUGIDLE(DeltaTime);
			break;
		case GS_BUGJUMP:
			FS_BUGJUMP(DeltaTime);
			break;
		case GS_BUGDOWN:
			FS_BUGDOWN(DeltaTime);
			break;
		case GS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case GS_RUN:
			FS_RUN(DeltaTime);
			break;
		case GS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
		case GS_JUMP:
			FS_JUMP(DeltaTime);
			break;
		case GS_DOUBLEJUMP:
			FS_DOUBLEJUMP(DeltaTime);
			break;
		case GS_WALLSTOP:
			FS_WALLSTOP(DeltaTime);
			break;
		case GS_KNIGHT:
			FS_KNIGHT(DeltaTime);
			break;
	}

	return 0;
}

int Gonner_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Gonner_Com::Collision(float DeltaTime)
{
}

void Gonner_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Gonner_Com::Render(float DeltaTime)
{
}

Gonner_Com * Gonner_Com::Clone()
{
	return new Gonner_Com(*this);
}

void Gonner_Com::Move(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("MoveRight"))
	{
		if(m_rightTile != NULLPTR && m_rightTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, 300.0f, DeltaTime);
	}
	else if (KeyInput::Get()->KeyPress("MoveLeft"))
	{
		if (m_leftTile != NULLPTR && m_leftTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, -300.0f, DeltaTime);
	}
}

void Gonner_Com::BugMove(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("MoveRight"))
	{
		Tile2D_Com* nextTile = m_Stage->GetTile2D(m_rightPos);

		if (nextTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, 180.0f, DeltaTime);
	}
	else if (KeyInput::Get()->KeyPress("MoveLeft"))
	{
		Tile2D_Com* nextTile = m_Stage->GetTile2D(m_leftPos);

		if (nextTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, -180.0f, DeltaTime);
	}
}

void Gonner_Com::DirCheck()
{
	if (KeyInput::Get()->KeyPress("MoveRight"))
		m_Animation->SetDir(MD_RIGHT);
	else if (KeyInput::Get()->KeyPress("MoveLeft"))
		m_Animation->SetDir(MD_LEFT);
}

void Gonner_Com::SetStage(Stage2D_Com * stage)
{
	m_Stage = stage;
	m_GravityCom->SetStage(m_Stage);
}

void Gonner_Com::BasicInit()
{
	m_WinSize = Device::Get()->GetWinSizeVector2();

	KeyInput::Get()->AddKey("S1", VK_F1);
	KeyInput::Get()->AddKey("S2", VK_F2);
	KeyInput::Get()->AddKey("S3", VK_F3);
	KeyInput::Get()->AddKey("S4", VK_F4);

	KeyInput::Get()->AddKey("Jump", VK_SPACE);

	m_Renderer = m_Object->AddComponent<Renderer_Com>("GonnerRender");
	m_Renderer->SetMesh("TextureRect");
	m_Renderer->SetRenderState(ALPHA_BLEND);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "Gonner", TEXT("Monster\\player.png"));

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("GonnerBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	RectColl->SetMyTypeName("Gonner");
	SAFE_RELEASE(RectColl);

	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Transform->SetWorldPos(500.0f, 1500.0f, 1.0f);

	m_Scale = Vector3(64.0f, 64.0f, 1.0f);
	m_ScaleHalf = m_Scale / 2.0f;

	m_BugAngle = 0.0f;
}

void Gonner_Com::AnimationInit()
{
	m_Animation = m_Object->AddComponent<Animation2D_Com>("GonnerAnimation");
	m_Animation->SetDir(MD_RIGHT);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(64.0f + i * 64.0f, 192.0f);
		tFrame.RightBottom = Vector2(64.0f + (i + 1) * 64.0f, 256.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BugIdle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Gonner", L"Monster\\player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 64.0f, 128.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 64.0f, 192.0f);
		vecClipFrame.push_back(tFrame);
	}

	tFrame.LeftTop = Vector2(0.0f, 192.0f);
	tFrame.RightBottom = Vector2(64.0f, 256.0f);
	vecClipFrame.push_back(tFrame);

	m_Animation->AddClip("BugMove", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "Gonner", L"Monster\\player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Gonner", L"Monster\\player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Run", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "Gonner", L"Monster\\player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(768.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(768.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	for (int i = 0; i < 5; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 64.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Jump", A2D_ATLS, AO_ONCE_STOP, 0.8f, vecClipFrame, "Gonner", L"Monster\\player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 4; ++i)
	{
		tFrame.LeftTop = Vector2(320.0f + i * 64.0f, 64.0f);
		tFrame.RightBottom = Vector2(320.0f + (i + 1) * 64.0f, 128.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("WallStop", A2D_ATLS, AO_LOOP, 0.8f, vecClipFrame, "Gonner", L"Monster\\player.png");
	vecClipFrame.clear();

	m_AniName[GS_BUGIDLE] = "BugIdle"; //1
	m_AniName[GS_BUGDOWN] = "BugMove"; //Move와 똑같은애니메이션
	m_AniName[GS_BUGJUMP] = "BugMove"; //1
	m_AniName[GS_IDLE] = "Idle"; //1
	m_AniName[GS_RUN] = "Run"; //1
	m_AniName[GS_ATTACK] = "Attack"; 
	m_AniName[GS_JUMP] = "Jump"; //1
	m_AniName[GS_DOUBLEJUMP] = "Jump"; //1
	m_AniName[GS_WALLSTOP] = "WallStop"; //1

	m_AniName[GS_KNIGHT] = "Knight";

	ChangeState(GS_BUGDOWN, m_AniName, m_Animation);
}

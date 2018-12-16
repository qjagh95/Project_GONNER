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
	m_WinSize = Device::Get()->GetWinSizeVector2();

	KeyInput::Get()->AddKey("S1", VK_F1);
	KeyInput::Get()->AddKey("S2", VK_F2);
	KeyInput::Get()->AddKey("S3", VK_F3);
	KeyInput::Get()->AddKey("S4", VK_F4);

	KeyInput::Get()->AddKey("Jump", VK_SPACE);

	m_Renderer = m_Object->AddComponent<Renderer_Com>("PlayerRender");
	m_Renderer->SetMesh("TextureRect");
	m_Renderer->SetRenderState(ALPHA_BLEND);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "Player", TEXT("Player.png"));
	m_Material->SetMaterial(Vector4::BlueViolet);

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("PlayerBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(128.0f, 128.0f, 0.0f));
	RectColl->SetMyTypeName("Player");
	SAFE_RELEASE(RectColl);

	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);
	m_Transform->SetWorldPos(500.0f, 1500.0f, 1.0f);

	m_Scale = Vector3(128.0f, 128.0f, 1.0f);

	m_Animation = m_Object->AddComponent<Animation2D_Com>("PlayerAnimation");
	m_Animation->SetDir((int)MD_RIGHT);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	for (int i = 0; i < 14; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 45.0f, 60.f);
		tFrame.RightBottom = Vector2(45.0f + i * 45.0f, 120.f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "Player", L"Player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 21; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 45.0f, 180.0f);
		tFrame.RightBottom = Vector2(45.0f + i * 45.0f, 240.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Attack", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "Player", L"Player.png");

	m_GravityCom = m_Object->AddComponent<Gravity_Com>("Gravity");
	return true;
}

int Gonner_Com::Input(float DeltaTime)
{
	Move(DeltaTime);
	DirCheck();

	return 0;
}

int Gonner_Com::Update(float DeltaTime)
{
	m_Pos = m_Transform->GetWorldPos();

	if (KeyInput::Get()->KeyDown("Jump"))
	{
		m_GravityCom->SetForce(1000.0f);
		m_Scene->CreateWave(m_Pos, 0.8f, 0.1f);
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
		Vector3 Pos;
		Pos.x = m_Pos.x + m_Transform->GetWorldScale().x * 0.5f;
		Pos.y = m_Pos.y + m_Transform->GetWorldScale().y * 0.5f;

		Tile2D_Com* nextTile = m_Stage->GetTile2D(Pos);

		if(nextTile != NULLPTR && nextTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, 500.0f, DeltaTime);
	}
	else if (KeyInput::Get()->KeyPress("MoveLeft"))
	{
		Vector3 Pos;
		Pos.x = m_Pos.x - m_Transform->GetWorldScale().x * 0.5f;
		Pos.y = m_Pos.y + m_Transform->GetWorldScale().y * 0.5f;

		Tile2D_Com* nextTile = m_Stage->GetTile2D(Pos);

		if (nextTile != NULLPTR && nextTile->GetTileOption() != T2D_NOMOVE)
			m_Transform->Move(AXIS_X, -500.0f, DeltaTime);
	}
}

void Gonner_Com::ChangeState(GONNER_STATE State)
{
	m_PrevState = m_State;
	m_State = State;

	m_Animation->ChangeClip(m_AniName[m_State]);
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

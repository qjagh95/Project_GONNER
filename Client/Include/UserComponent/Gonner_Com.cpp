#include "ClientHeader.h"
#include "Gonner_Com.h"
#include "Skull_Com.h"
#include "SnakeHead_Com.h"

#include <Core.h>

#include "Component/ColliderRect_Com.h"
#include "Component/ColliderCircle_Com.h"
#include "Component/ColliderOBB2D_Com.h"
#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Material_Com.h"
#include "Component/TitleBar_Com.h"
#include <Scene/Scene.h>

#include <UserComponent/BubbleEffect_Com.h>
#include <UserComponent/BugEffect_Com.h>
#include <UserComponent/HeartUI_Com.h>
#include <UserComponent/HeartItem_Com.h>
#include <UserComponent/LifeItem_Com.h>

Vector3 Gonner_Com::m_GonnerPos;
Vector3 Gonner_Com::m_GonnerScale = Vector3(64.0f, 64.0f, 1.0f);
Vector3 Gonner_Com::m_GonnerScaleHalf = Vector3(32.0f, 32.0f, 1.0f);

Gonner_Com::Gonner_Com()
{
	m_ComType = CT_GONNER;
	m_GravityCom = NULLPTR;
	m_Stage = NULLPTR;
	m_Camera = NULLPTR;
	m_downTile = NULLPTR;
	m_upTile = NULLPTR;
	m_leftTile = NULLPTR;
	m_rightTile = NULLPTR;
	m_GunObject = NULLPTR;
	m_Gun = NULLPTR;
	m_HeartObject = NULLPTR;
	m_Heart = NULLPTR;
	m_SkullObject = NULLPTR;
	m_Skull = NULLPTR;
	m_PrevEffectLayer = NULLPTR;
	m_AfterEffectLayer = NULLPTR;
	m_Animation = NULLPTR;
	m_Pos = Vector3::Zero;
	m_Scale = Vector3::Zero;
	m_ScaleHalf = Vector3::Zero;
	m_WinSize = Vector2::Zero;
	m_upPos = Vector3::Zero;
	m_leftPos = Vector3::Zero;
	m_downPos = Vector3::Zero;
	m_rightPos = Vector3::Zero;
	m_CBuffer = {};
	m_WaveCBuffer = {};
	m_BugAngle = 0.0f;
	m_BugJumpMax = 6;
	m_BugJumpCount = 0;
	m_PumpSpeed = 0.0f;
	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.0f;
	m_DownAngle = 0.0f;
	m_BubbleTimeVar = 0.0f;
	m_BubbleTime = 0.0f;
	m_BugEffectTime = 0.0f;
	m_BugEffectTimeVar = 0.0f;
	m_isSkullItem = false;
	m_isJumpAttack = false;
	m_isBugJump = false;
	m_isDirChangeLeft = false;
	m_isDirChangeRight = false;
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

	SAFE_RELEASE(m_AfterEffectLayer);
	SAFE_RELEASE(m_PrevEffectLayer);

	//강제 Release (어디서 카운트 + 되는지 못찾겠다 ㅜ)
	if(m_Gun != NULLPTR)
		m_Gun->Release();

	SAFE_RELEASE(m_Gun);
	SAFE_RELEASE(m_GunObject);
	
	SAFE_RELEASE(m_HeartObject);
	SAFE_RELEASE(m_Heart);

	SAFE_RELEASE(m_SkullObject);
	SAFE_RELEASE(m_Skull);
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
	m_Camera = m_Scene->GetMainCamera();
	m_PrevEffectLayer = m_Scene->FindLayer("PrevEffectLayer");
	m_AfterEffectLayer = m_Scene->FindLayer("AfterEffectLayer");

	if (m_Stage == NULLPTR)
		m_Stage = StageManager::Get()->FindCurStage();

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}

	m_isJumpAttack = false;
	return 0;
}

int Gonner_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);
	CreateBubbleEffect(DeltaTime);

	m_Stage = StageManager::Get()->FindCurStage();

	m_Pos = m_Transform->GetWorldPos();
	m_GonnerPos = m_Pos;

	m_upPos = Vector3(m_Pos.x, m_Pos.y + m_ScaleHalf.y + 1.0f, 1.0f);
	m_downPos = Vector3(m_Pos.x, m_Pos.y - m_ScaleHalf.y - 1.0f, 1.0f);
	m_leftPos = Vector3(m_Pos.x - m_ScaleHalf.x - 1.0f, m_Pos.y, 1.0f);
	m_rightPos = Vector3(m_Pos.x + m_ScaleHalf.x + 1.0f, m_Pos.y, 1.0f);

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
		case GS_JUMP:
			FS_JUMP(DeltaTime);
			break;
		case GS_DOUBLEJUMP:
			FS_DOUBLEJUMP(DeltaTime);
			break;
		case GS_WALLSTOP:
			FS_WALLSTOP(DeltaTime);
			break;
		case GS_HIT:
			FS_HIT(DeltaTime);
			break;
		case GS_WALLJUMP:
			FS_WALLJUMP(DeltaTime);
			break;
	}

	ItemUpdate(DeltaTime);

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
	if (SnakeHead_Com::m_isNext == true)
		return;

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

void Gonner_Com::ChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar > m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

		int RandNum = RandomRange(1, 3);

		switch (RandNum)
		{
			case 1:
				m_Material->SetMaterial(m_ChangeColor[RandNum - 1]);
				break;
			case 2:
				m_Material->SetMaterial(m_ChangeColor[RandNum - 1]);
				break;
			case 3:
				m_Material->SetMaterial(m_ChangeColor[RandNum - 1]);
				break;
		}
	}
}

void Gonner_Com::CreateBubbleEffect(float DeltaTime)
{
	if (m_isSkullItem == true)
		return;
	
	m_BubbleTimeVar += DeltaTime;

	if (m_BubbleTimeVar >= m_BubbleTime)
	{
		m_BubbleTimeVar = 0.0f;

		GameObject* newBubble = GameObject::CreateObject("BubbleEffect", m_PrevEffectLayer);
		BubbleEffect_Com* newBubbleCom = newBubble->AddComponent< BubbleEffect_Com>("BubbleEffect");
		newBubble->GetTransform()->SetWorldPos(m_Pos);

		SAFE_RELEASE(newBubble);
		SAFE_RELEASE(newBubbleCom);
	}
}

void Gonner_Com::CreateBugEffect(float DeltaTime)
{
	m_BugEffectTimeVar += DeltaTime;

	if (m_BugEffectTimeVar >= m_BugEffectTime)
	{
		m_BugEffectTimeVar = 0.0f;

		for (size_t i = 0; i < 3; i++)
		{
			GameObject* newEffect = GameObject::CreateObject("BugEffect", m_PrevEffectLayer);
			BugEffect_Com* newEffectCom = newEffect->AddComponent<BugEffect_Com>("BugEffect");

			Vector3 Pos = m_leftPos;

			if (m_Animation->GetDir() == MD_LEFT)
			{
				newEffect->GetTransform()->SetWorldRotZFromNoneAxis((25.0f + (i + 1) * 20.0f) * -1.0f);
				newEffect->GetTransform()->SetWorldPos(Pos.x + m_Scale.x * 2.0f, Pos.y, 1.0f);
			}
			else
			{
				newEffect->GetTransform()->SetWorldRotZFromNoneAxis(25.0f + (i + 1) * 20.0f);
				newEffect->GetTransform()->SetWorldPos(Pos.x - m_Scale.x * 0.5f, Pos.y, 1.0f);
			}

			SAFE_RELEASE(newEffect);
			SAFE_RELEASE(newEffectCom);
		}
		SoundManager::Get()->FindSoundEffect("BugEffect")->Play();
	}
}

void Gonner_Com::CreateBugChangeEffect(float DeltaTime)
{
	for (size_t i = 0; i < 8; i++)
	{
		GameObject* newEffect = GameObject::CreateObject("BugEffect", m_PrevEffectLayer);
		BugEffect_Com* newEffectCom = newEffect->AddComponent<BugEffect_Com>("BugEffect");

		float x = cosf(DegreeToRadian(45.0f * i));
		float y = sinf(DegreeToRadian(45.0f * i));

		newEffect->GetTransform()->SetWorldRotZ(45.0f * i);
		newEffect->GetTransform()->SetWorldPos(m_Pos.x + (x * 100.0f), m_Pos.y + (y * 100.0f), 1.0f);
		newEffect->GetTransform()->SetWorldScale(128.0f, 128.0f * 2.0f, 1.0f);


		SAFE_RELEASE(newEffect);
		SAFE_RELEASE(newEffectCom);
	}
}

void Gonner_Com::ItemUpdate(float DeltaTime)
{
	if (m_Gun != NULLPTR)
		m_Gun->GetAnimation()->SetDir(m_Animation->GetDir());

	 if(m_Heart != NULLPTR)
		m_Heart->GetAnimation()->SetDir(m_Animation->GetDir());

	if (m_Skull != NULLPTR)
		m_Skull->GetAnimation()->SetDir(m_Animation->GetDir());
}

void Gonner_Com::OutItem()
{
	if (m_GunObject != NULLPTR)
	{
		m_Gun->ClearUI();
		m_Gun->SetIsActive(false);
		m_GunObject->SetIsActive(false);

		SAFE_RELEASE(m_GunObject);
		SAFE_RELEASE(m_Gun);

		GameObject* gunItemObject = GameObject::CreateObject("GunItem", m_Layer);
		GunItem_Com* gunItemCom = gunItemObject->AddComponent<GunItem_Com>("GunItem");
		Gravity_Com* newGrivaty = gunItemObject->AddComponent<Gravity_Com>("Gravity");
		newGrivaty->SetStage(m_Stage);
		newGrivaty->SetForce((float)RandomRange(200, 500));
		gunItemCom->SetDrop(true);
		gunItemObject->GetTransform()->SetWorldPos(m_upPos.x, m_upPos.y, 1.0f);

		SAFE_RELEASE(gunItemObject);
		SAFE_RELEASE(gunItemCom);
		SAFE_RELEASE(newGrivaty);
	}

	if (m_HeartObject != NULLPTR)
	{
		m_Heart->ClearUI();
		m_Heart->SetIsActive(false);
		m_HeartObject->SetIsActive(false);

		SAFE_RELEASE(m_HeartObject);
		SAFE_RELEASE(m_Heart);

		GameObject* heartItemObject = GameObject::CreateObject("HeartItem", m_Layer);
		HeartItem_Com* heartItemCom = heartItemObject->AddComponent<HeartItem_Com>("HeartItem");
		Gravity_Com* newGrivaty = heartItemObject->AddComponent<Gravity_Com>("Gravity");
		newGrivaty->SetStage(m_Stage);
		heartItemCom->SetDrop(true);
		newGrivaty->SetForce((float)RandomRange(200, 500));
		heartItemObject->GetTransform()->SetWorldPos(m_upPos.x, m_upPos.y, 1.0f);

		SAFE_RELEASE(newGrivaty);
		SAFE_RELEASE(heartItemObject);
		SAFE_RELEASE(heartItemCom);

	}
	if (m_SkullObject != NULLPTR)
	{
		m_Skull->ClearUI();
		m_Skull->SetIsActive(false);
		m_SkullObject->SetIsActive(false);

		SAFE_RELEASE(m_Skull);
		SAFE_RELEASE(m_SkullObject);

		GameObject* LifeItemObject = GameObject::CreateObject("LifeItem", m_Layer);
		LifeItem_Com* LifeItemCom = LifeItemObject->AddComponent<LifeItem_Com>("LifeItem");
		Gravity_Com* newGrivaty = LifeItemObject->AddComponent<Gravity_Com>("Gravity");
		newGrivaty->SetStage(m_Stage);
		newGrivaty->SetForce((float)RandomRange(200, 500));
		LifeItemCom->SetDrop(true);
		LifeItemObject->GetTransform()->SetWorldPos(m_upPos.x, m_upPos.y, 1.0f);

		SAFE_RELEASE(LifeItemObject);
		SAFE_RELEASE(LifeItemCom);
		SAFE_RELEASE(newGrivaty);
	}
}

void Gonner_Com::BasicInit()
{
	m_WinSize = Device::Get()->GetWinSizeVector2();

	KeyInput::Get()->AddKey("Jump", VK_SPACE);
	KeyInput::Get()->AddKey("Attack", 'X');
	KeyInput::Get()->AddKey("Reload", 'C');

	m_Renderer = m_Object->AddComponent<Renderer_Com>("GonnerRender");
	m_Renderer->SetMesh("TextureRect");
	m_Renderer->SetRenderState(ALPHA_BLEND);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "Gonner", TEXT("Monster\\player.png"));
	m_Material->SetMaterial(Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f));

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("GonnerBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	RectColl->SetMyTypeName("Gonner");
	RectColl->SetCollsionCallback(CCT_FIRST, this, &Gonner_Com::GunItemHit);
	RectColl->SetCollsionCallback(CCT_FIRST, this, &Gonner_Com::ReloadBulletHit);
	RectColl->SetCollsionCallback(CCT_FIRST, this, &Gonner_Com::HeartItemHit);
	RectColl->SetCollsionCallback(CCT_FIRST, this, &Gonner_Com::LifeItemHit);
	RectColl->SetCollsionCallback(CCT_FIRST, this, &Gonner_Com::MonsterHitFirst);
	RectColl->SetCollsionCallback(CCT_FIRST, this, &Gonner_Com::SnakeHeadHitFirst);
	RectColl->SetCollsionCallback(CCT_END, this, &Gonner_Com::MonsterHitEnd);

	SAFE_RELEASE(RectColl);

	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Transform->SetWorldPos(500.0f, 1500.0f, 1.0f);

	m_Scale = Vector3(64.0f, 64.0f, 1.0f);
	m_ScaleHalf = m_Scale / 2.0f;

	m_BugAngle = 0.0f;
	m_ChangeTime = 0.1f;
	m_BubbleTime = 0.1f;
	m_BugEffectTime = 1.0f;
	m_isJumpAttack = false;

	m_ChangeColor[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_ChangeColor[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_ChangeColor[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);
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

	m_AniName[GS_BUGIDLE] = "BugIdle"; 
	m_AniName[GS_BUGDOWN] = "BugMove";
	m_AniName[GS_BUGJUMP] = "BugMove"; 
	m_AniName[GS_IDLE] = "Idle"; 
	m_AniName[GS_RUN] = "Run"; 
	m_AniName[GS_JUMP] = "Jump"; 
	m_AniName[GS_DOUBLEJUMP] = "Jump"; 
	m_AniName[GS_WALLSTOP] = "WallStop"; 
	m_AniName[GS_HIT] = "Knight";
	m_AniName[GS_WALLJUMP] = "Jump";

#ifdef _DEBUG
	ChangeState(GS_IDLE, m_AniName, m_Animation);
#else
	ChangeState(GS_BUGDOWN, m_AniName, m_Animation);
#endif
}
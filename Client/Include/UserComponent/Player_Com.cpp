#include "ClientHeader.h"
#include "Player_Com.h"
#include "GameObject.h"
#include "KeyInput.h"

#include "Component/ColliderRect_Com.h"
#include "Component/ColliderCircle_Com.h"
#include "Component/ColliderOBB2D_Com.h"
#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Material_Com.h"
#include "Component/TitleBar_Com.h"

#include "../UserComponent/Bullet_Com.h"
#include "../UserComponent/BulletRot_Com.h"

Player_Com::Player_Com()
	: myAnimation(NULLPTR)
{
}

Player_Com::Player_Com(const Player_Com & userCom)
	:UserComponent_Base(userCom)
{
	myAnimation = NULLPTR;
}

Player_Com::~Player_Com()
{
	SAFE_RELEASE(myAnimation);
}

bool Player_Com::Init()
{				   
	KeyInput::Get()->AddKey("S1", VK_F1);
	KeyInput::Get()->AddKey("S2", VK_F2);
	KeyInput::Get()->AddKey("S3", VK_F3);
	KeyInput::Get()->AddKey("S4", VK_F4);

	KeyInput::Get()->AddKey("ChangeAnimation", VK_SPACE);

	Renderer_Com* RenderComponent = m_Object->AddComponent<Renderer_Com>("PlayerRender");
	RenderComponent->SetMesh("TextureRect");
	RenderComponent->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(RenderComponent);

	Material_Com* MaterialComponent = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	MaterialComponent->SetDiffuseTexture(0, "Player", TEXT("Player.png"));
	MaterialComponent->SetMaterial(Vector4::White);
	SAFE_RELEASE(MaterialComponent);

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("PlayerBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(100.0f, 100.0f, 0.0f));
	RectColl->SetMyTypeName("Player");
	SAFE_RELEASE(RectColl);
	
	TitleBar_Com* TitleCom = m_Object->AddComponent<TitleBar_Com>("TitleBar");
	SAFE_RELEASE(TitleCom);

	m_Transform->SetWorldScale(300.0f, 300.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);
	m_Transform->SetWorldPos(0.0f, 0.0f, 1.0f);

	myAnimation = m_Object->AddComponent<Animation2D_Com>("PlayerAnimation");
	myAnimation->SetDir(1);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	for (int i = 0; i < 14; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 45.0f, 60.f);
		tFrame.RightBottom = Vector2(45.0f + i * 45.0f, 120.f);
		vecClipFrame.push_back(tFrame);
	}

 	myAnimation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "Player", L"Player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 21; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 45.0f, 180.0f);
		tFrame.RightBottom = Vector2(45.0f + i * 45.0f, 240.0f);
		vecClipFrame.push_back(tFrame);
	}

	myAnimation->AddClip("Attack", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "Player", L"Player.png");

	return true;
}

int Player_Com::Input(float DeltaTime)
{
	if (myAnimation == NULLPTR)
		myAnimation = m_Object->FindComponentFromType<Animation2D_Com>(CT_ANIMATION2D);

	if (KeyInput::Get()->KeyPress("MoveLeft"))
		m_Transform->RotationZ(180.0f, DeltaTime);
	else if (KeyInput::Get()->KeyPress("MoveRight"))
		m_Transform->RotationZ(-180.0f, DeltaTime);
	if (KeyInput::Get()->KeyPress("MoveUp"))
		m_Transform->Move(AXIS_Y, 1000.0f, DeltaTime);
	else if (KeyInput::Get()->KeyPress("MoveDown"))
		m_Transform->Move(AXIS_Y, -1000.0f, DeltaTime);

	return 0;
}

int Player_Com::Update(float DeltaTime)
{
	return 0;
}

int Player_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Player_Com::Collision(float DeltaTime)
{
}

void Player_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Player_Com::Render(float DeltaTime)
{
}

Player_Com * Player_Com::Clone()
{
	return new Player_Com(*this);
}


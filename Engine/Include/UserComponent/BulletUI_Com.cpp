#include "stdafx.h"
#include "BulletUI_Com.h"
#include "Gun_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

Gun_Com* BulletUI_Com::m_TargetGun = NULLPTR;
Vector3 BulletUI_Com::m_GunPos;
float BulletUI_Com::m_Range = 100.0f;
float BulletUI_Com::m_MoveSpeed = 1200.0f;

BulletUI_Com::BulletUI_Com()
{
	m_Index = 0;
}

BulletUI_Com::BulletUI_Com(const BulletUI_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BulletUI_Com::~BulletUI_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool BulletUI_Com::Init()
{
	 m_LightTimeVar = 0.0f;
	 
	 int RandNum = RandomRange(1, 3);
	 switch (RandNum)
	 {
		 case 1:
			 m_LightTime = 0.1f;
			 break;
		 case 2:
			 m_LightTime = 0.2f;
			 break;
		 case 3:
			 m_LightTime = 0.3f;
			 break;
	 }

	 m_Color[BT_ON] = Vector4::Yellow;
	 m_Color[BT_OFF] = Vector4::Gray;
	 
	Renderer_Com* BulletUIRender = m_Object->AddComponent<Renderer_Com>("BoomEffect");
	BulletUIRender->SetMesh("TextureRect");
	BulletUIRender->SetRenderState(ALPHA_BLEND);
	BulletUIRender->SetScreenRender(true);
	SAFE_RELEASE(BulletUIRender);

	m_Transform->SetWorldScale(32.0f, 32.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BulletUI", TEXT("weapons.png"));
	m_Material->SetMaterial(Vector4::Yellow);

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BulletUIAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 640.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 704.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BulletUI", A2D_ATLS, AO_LOOP, 0.5f, vecClipFrame, "BulletUI", L"weapons.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("BulletUI");

	m_StaticTime = 3.0f;
	m_StaticTimeVar = 0.0f;
	m_isMove = false;

	return true;
}

int BulletUI_Com::Input(float DeltaTime)
{
	return 0;
}

int BulletUI_Com::Update(float DeltaTime)
{
	m_GunPos = m_TargetGun->GetTransform()->GetWorldPos();

	if (m_isMove == false)
		SetPos(m_Index);

	//m_StaticTimeVar += DeltaTime;

	//if (m_StaticTimeVar >= m_StaticTime)
	//	m_isMove = true;

	//if (m_isMove == true)
	//	Move(DeltaTime);

	//switch (m_State)
	//{
	//	case BT_ON:
	//		On(DeltaTime);
	//		break;
	//	case BT_OFF:
	//		Off(DeltaTime);
	//		break;
	//}

	return 0;
}

int BulletUI_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BulletUI_Com::Collision(float DeltaTime)
{
}

void BulletUI_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BulletUI_Com::Render(float DeltaTime)
{
}

BulletUI_Com * BulletUI_Com::Clone()
{
	return new BulletUI_Com(*this);
}

void BulletUI_Com::AfterClone()
{
}

void BulletUI_Com::GrayLightChange(float DeltaTime)
{
	m_LightTimeVar += DeltaTime;

	if (m_LightTimeVar >= m_LightTime)
	{
		m_LightTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4::Yellow)
			m_Material->SetMaterial(m_Material->GetDiffuseLight() * 0.7f);
		else
			m_Material->SetMaterial(Vector4::Yellow);
	}
}
void BulletUI_Com::YellowLightChange(float DeltaTime)
{
	m_LightTimeVar += DeltaTime;

	if (m_LightTimeVar >= m_LightTime)
	{
		m_LightTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4::Gray)
			m_Material->SetMaterial(m_Material->GetDiffuseLight() * 1.3f);
		else
			m_Material->SetMaterial(Vector4::Gray);
	}
}

void BulletUI_Com::On(float DeltaTime)
{
	YellowLightChange(DeltaTime);
}

void BulletUI_Com::Off(float DeltaTime)
{
	GrayLightChange(DeltaTime);
}

void BulletUI_Com::Move(float DeltaTime)
{
}

void BulletUI_Com::SetIndex(int Index)
{
	m_Index = Index + 1;
}

void BulletUI_Com::SetPos(int Index)
{
	Vector3 CameraPos = m_Scene->GetMainCameraTransform()->GetWorldPos();
	m_CirclePos = m_GunPos;
	m_CirclePos -= CameraPos;
	m_CirclePos.z = 0.0f;

	float Angle = 20.0f * Index;
	float x = cosf(DegreeToRadian(Angle));
	float y = sinf(DegreeToRadian(Angle));

	m_GoingPos = Vector3(25.0f * Index, 80.0f, 1.0f);
	m_CirclePos = Vector3(m_CirclePos.x + (m_Range * x), m_CirclePos.y + (m_Range * y), 0.0f);
	m_Transform->SetWorldPos(m_CirclePos);
}

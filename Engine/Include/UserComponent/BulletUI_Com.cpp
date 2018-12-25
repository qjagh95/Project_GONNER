#include "stdafx.h"
#include "BulletUI_Com.h"
#include "Gun_Com.h"

#include "../Component/Animation2D_Com.h"

JEONG_USING

Gun_Com* BulletUI_Com::m_TargetGun = NULLPTR;
Vector3 BulletUI_Com::m_GunPos;
float BulletUI_Com::m_Range = 80.0f;
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
	 
	Renderer_Com* BulletUIRender = m_Object->AddComponent<Renderer_Com>("BoomEffect");
	BulletUIRender->SetMesh("TextureRect");
	BulletUIRender->SetRenderState(ALPHA_BLEND);
	BulletUIRender->SetScreenRender(true);
	SAFE_RELEASE(BulletUIRender);

	m_Transform->SetWorldScale(45.0f, 45.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BulletUI", TEXT("weapons.png"));
	m_Material->SetMaterial(Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f));

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
	m_isGoingPos = false;
	m_State = BT_ON;
	m_DirAngle = 0.0f;
	
	int RandNum2 = RandomRange(1, 4);
	switch (RandNum2)
	{
		case 1:
			m_RotSpeed = 20.0f;
			break;
		case 2:
			m_RotSpeed = 25.0f;
			break;
		case 3:
			m_RotSpeed = 30.0f;
			break;
		case 4:
			m_RotSpeed = 35.0f;
			break;
	}

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

	if (m_Index > Gun_Com::m_BulletCount)
		m_State = BT_OFF;
	else
		m_State = BT_ON;

	m_StaticTimeVar += DeltaTime;

	if (m_StaticTimeVar >= m_StaticTime)
		m_isMove = true;

	if (m_isMove == true && m_isGoingPos == false)
		TargetMove(DeltaTime);
	
	if (m_isGoingPos == true)
		RotMove(DeltaTime);

	switch (m_State)
	{
		case BT_ON:
			On(DeltaTime);
			break;
		case BT_OFF:
			Off(DeltaTime);
			break;
	}

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

		if (m_Material->GetDiffuseLight() == Vector4::Gray)
			m_Material->SetMaterial(m_Material->GetDiffuseLight() * 1.1f);
		else
			m_Material->SetMaterial(Vector4::Gray);
	}
}
void BulletUI_Com::YellowLightChange(float DeltaTime)
{
	m_LightTimeVar += DeltaTime;

	if (m_LightTimeVar >= m_LightTime)
	{
		m_LightTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f))
			m_Material->SetMaterial(Vector4(1.0f, 209.0f / 255.0f, 81.0f / 255.0f, 1.0f));
		else
			m_Material->SetMaterial(Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f));
	}

}

void BulletUI_Com::On(float DeltaTime)
{
	YellowLightChange(DeltaTime);

	if (m_isGoingPos == false)
		return;

	Vector3 Lerp = Vector3::Lerp(m_Transform->GetWorldPos(), Vector3(m_GoingPos.x, m_GoingPos.y, 1.0f), DeltaTime * 3.0f);
	m_Transform->SetWorldPos(Lerp);
}

void BulletUI_Com::Off(float DeltaTime)
{
	GrayLightChange(DeltaTime);

	if (m_isGoingPos == false)
		return;

	Vector3 Lerp = Vector3::Lerp(m_Transform->GetWorldPos(), Vector3(m_GoingPos.x, m_GoingPos.y - 30.0f, 1.0f), DeltaTime * 3.0f);
	m_Transform->SetWorldPos(Lerp);
}

void BulletUI_Com::TargetMove(float DeltaTime)
{
	Vector3 Lerp = Vector3::Lerp(m_Transform->GetWorldPos(), m_GoingPos, DeltaTime * 3.0f);
	m_Transform->SetWorldPos(Lerp);

	int intPosX;
	int intPosY;
	intPosX = (int)Lerp.x;
	intPosY = (int)Lerp.y;

	if (intPosX <= m_GoingPos.x && intPosY <= m_GoingPos.y)
		m_isGoingPos = true;
}

void BulletUI_Com::RotMove(float DeltaTime)
{
	m_DirAngle += m_RotSpeed * DeltaTime;

	Vector2 Dir;
	Dir.x = cosf((DegreeToRadian(m_DirAngle)));
	Dir.y = sinf((DegreeToRadian(m_DirAngle)));

	m_Transform->Move(Dir, m_RotSpeed, DeltaTime);
}

void BulletUI_Com::SetIndex(int Index)
{
	m_Index = Index + 1;
	
	if (m_Index <= Gun_Com::m_BulletCount)
	{
		m_State = BT_OFF;
		m_Material->SetMaterial(Vector4::Gray);
	}
	else
	{
		m_State = BT_ON;
		m_Material->SetMaterial(Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f));
	}
}

void BulletUI_Com::SetPos(int Index)
{
	Vector3 CameraPos = m_Scene->GetMainCameraTransform()->GetWorldPos();
	m_CirclePos = m_GunPos;
	m_CirclePos -= CameraPos;
	m_CirclePos.z = 0.0f;

	float Angle = -8.0f + (Index * -8.0f);
	float x = cosf(DegreeToRadian(Angle));
	float y = sinf(DegreeToRadian(Angle));

	m_GoingPos = Vector3(100.0f + (Index * 25.0f), 140.0f, 1.0f);
	m_CirclePos = Vector3(m_CirclePos.x + (m_Range * x), m_CirclePos.y + (m_Range * y), 0.0f);
	m_Transform->SetWorldPos(m_CirclePos);
}
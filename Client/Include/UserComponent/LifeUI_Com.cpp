#include "ClientHeader.h"
#include "LifeUI_Com.h"
#include "Skull_Com.h"
#include "Gun_Com.h"
#include "Gonner_Com.h"

JEONG_USING

float LifeUI_Com::m_Range = 80.0f;
float LifeUI_Com::m_MoveSpeed = 1200.0f;

LifeUI_Com::LifeUI_Com()
{
	m_Index = 0;
}

LifeUI_Com::LifeUI_Com(const LifeUI_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

LifeUI_Com::~LifeUI_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool LifeUI_Com::Init()
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

	Renderer_Com* BulletUIRender = m_Object->AddComponent<Renderer_Com>("LifeUI");
	BulletUIRender->SetMesh("TextureRect");
	BulletUIRender->SetRenderState(ALPHA_BLEND);
	BulletUIRender->SetScreenRender(true);
	SAFE_RELEASE(BulletUIRender);

	m_Transform->SetWorldScale(40.0f, 40.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "LifeUI", TEXT("Monster\\sprites.png"));
	m_Material->SetMaterial(Vector4(170.0f / 255.0f, 230.0f / 255.0f, 236.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("LifeUIAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(384.0f + i * 64.0f, 576.0f);
		tFrame.RightBottom = Vector2(384.0f + (i + 1) * 64.0f, 640.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("LifeUI", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "LifeUI", L"Monster\\sprites.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("LifeUI");

	m_StaticTime = 3.0f;
	m_StaticTimeVar = 0.0f;
	m_isMove = false;
	m_isGoingPos = false;
	m_State = LS_ON;
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

int LifeUI_Com::Input(float DeltaTime)
{
	return 0;
}

int LifeUI_Com::Update(float DeltaTime)
{
	m_TargetPos = Gonner_Com::m_GonnerPos;

	if (m_isMove == false)
		SetPos(m_Index);

	if (m_Index > Skull_Com::m_LifeCount)
		m_State = LS_OFF;
	else
		m_State = LS_ON;

	m_StaticTimeVar += DeltaTime;

	if (m_StaticTimeVar >= m_StaticTime)
		m_isMove = true;

	if (m_isMove == true && m_isGoingPos == false)
		TargetMove(DeltaTime);

	if (m_isGoingPos == true)
		RotMove(DeltaTime);

	switch (m_State)
	{
		case LS_ON:
			On(DeltaTime);
			break;
		case LS_OFF:
			Off(DeltaTime);
			break;
	}

	return 0;
}

int LifeUI_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void LifeUI_Com::Collision(float DeltaTime)
{
}

void LifeUI_Com::CollisionLateUpdate(float DeltaTime)
{
}

void LifeUI_Com::Render(float DeltaTime)
{
}

LifeUI_Com * LifeUI_Com::Clone()
{
	return new LifeUI_Com(*this);
}

void LifeUI_Com::AfterClone()
{
}

void LifeUI_Com::GrayLightChange(float DeltaTime)
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
void LifeUI_Com::LightChange(float DeltaTime)
{
	m_LightTimeVar += DeltaTime;

	if (m_LightTimeVar >= m_LightTime)
	{
		m_LightTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4(170.0f / 255.0f, 230.0f / 255.0f, 236.0f / 255.0f, 1.0f))
			m_Material->SetMaterial(Vector4(175.0f / 255.0f, 236.0f / 255.0f, 231.0f / 255.0f, 1.0f));
		else
			m_Material->SetMaterial(Vector4(170.0f / 255.0f, 230.0f / 255.0f, 236.0f / 255.0f, 1.0f));
	}

}

void LifeUI_Com::On(float DeltaTime)
{	
	LightChange(DeltaTime);

	if (m_isGoingPos == false)
		return;

	Vector3 Lerp = Vector3::Lerp(m_Transform->GetWorldPos(), Vector3(m_GoingPos.x, m_GoingPos.y, 1.0f), DeltaTime * 3.0f);
	m_Transform->SetWorldPos(Lerp);
}

void LifeUI_Com::Off(float DeltaTime)
{
	GrayLightChange(DeltaTime);
}

void LifeUI_Com::TargetMove(float DeltaTime)
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

void LifeUI_Com::RotMove(float DeltaTime)
{
	m_DirAngle += m_RotSpeed * DeltaTime;

	Vector2 Dir;
	Dir.x = cosf((DegreeToRadian(m_DirAngle)));
	Dir.y = sinf((DegreeToRadian(m_DirAngle)));

	m_Transform->Move(Dir, m_RotSpeed, DeltaTime);
}

void LifeUI_Com::SetIndex(int Index)
{
	m_Index = Index + 1;

	if (m_Index <= Skull_Com::m_LifeCount)
	{
		m_State = LS_OFF;
		m_Material->SetMaterial(Vector4::Gray);
	}
	else
	{
		m_State = LS_ON;
		m_Material->SetMaterial(Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f));
	}
}

void LifeUI_Com::SetPos(int Index)
{
	Vector3 CameraPos = m_Scene->GetMainCameraTransform()->GetWorldPos();
	m_CirclePos = m_TargetPos;
	m_CirclePos -= CameraPos;
	m_CirclePos.z = 0.0f;

	float Angle = 175.0f + (Index * -30.0f);
	float x = cosf(DegreeToRadian(Angle));
	float y = sinf(DegreeToRadian(Angle));

	m_GoingPos = Vector3(100.0f + (Index * 60.0f), 280.0f, 1.0f);
	m_CirclePos = Vector3(m_CirclePos.x + (m_Range * x), m_CirclePos.y + (m_Range * y), 0.0f);
	m_Transform->SetWorldPos(m_CirclePos);
}
#include "stdafx.h"
#include "ReloadBullet_Com.h"

#include "../Component/ColliderRect_Com.h"
#include "../Component/Animation2D_Com.h"

JEONG_USING

ReloadBullet_Com::ReloadBullet_Com()
{
	m_RectColl = NULLPTR;
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

ReloadBullet_Com::ReloadBullet_Com(const ReloadBullet_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

ReloadBullet_Com::~ReloadBullet_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_RectColl);
}

bool ReloadBullet_Com::Init()
{
	m_ChangeColorTimeVar = 0.0f;
	m_ChangeColorTime = 0.2f;
	m_MoveTime = 0.3f;
	m_MoveTimeVar = 0.0f;
	m_MoveSpeed = 800.0f;

	Renderer_Com* ReloadBulletRender = m_Object->AddComponent<Renderer_Com>("ReloadBulletRender");
	ReloadBulletRender->SetMesh("TextureRect");
	ReloadBulletRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(ReloadBulletRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f));
	m_Material->SetDiffuseTexture(0, "ReloadBullet", TEXT("Monster\\sprites.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("ReloadBulletAni");
	m_Transform->SetWorldScale(40.0f, 40.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 576.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 640.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("ReloadBullet", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "ReloadBullet", L"Monster\\sprites.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("ReloadBullet");

	m_RectColl = m_Object->AddComponent<ColliderRect_Com>("ReloadBulletBody");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(40.0f, 40.0f, 0.0f));
	m_RectColl->SetMyTypeName("ReloadBullet");
	m_RectColl->PushContinueTypeName("Bullet");
	m_RectColl->PushContinueTypeName("Monster");
	//초반 바로생성 후 나오자마자 사라지는 걸 막음.
	m_RectColl->SetIsShow(false);

	return true;
}

int ReloadBullet_Com::Input(float DeltaTime)
{
	m_TargetPos = m_Target->GetTransform()->GetWorldPos();

	return 0;
}

int ReloadBullet_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);

	m_MoveTimeVar += DeltaTime;

	if (m_MoveTimeVar >= m_MoveTime)
	{
		m_RectColl->SetIsShow(true);
		m_isRot = true;
	}

	if (m_isRot == true)
	{
		Vector3 Look = m_TargetPos - m_Transform->GetWorldPos();
		Vector3 ShotDir = m_Transform->GetWorldAxis(AXIS_Y);
		float Angle = ShotDir.GetAngle(Look);
		float Distance = m_Transform->GetWorldPos().GetDistance(m_TargetPos);

		//외적 z값이 0보다 크거나 작거나에따라서 앞뒤판단
		Vector3 Cross = ShotDir.Cross(Look);
		Cross.Nomallize();

		//스피드와 거리간의 비율을 곱해줘서 거리에따라서 더 빠르게돈다.
		m_Transform->RotationZ(Angle * Cross.z, DeltaTime * (m_MoveSpeed / Distance));
		m_Transform->Move(AXIS_Y, m_MoveSpeed, DeltaTime);
	}
	else
		m_Transform->Move(AXIS_X, m_MoveSpeed, DeltaTime);


	return 0;
}

int ReloadBullet_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void ReloadBullet_Com::Collision(float DeltaTime)
{
}

void ReloadBullet_Com::CollisionLateUpdate(float DeltaTime)
{
}

void ReloadBullet_Com::Render(float DeltaTime)
{
}

ReloadBullet_Com * ReloadBullet_Com::Clone()
{
	return new ReloadBullet_Com(*this);
}

void ReloadBullet_Com::AfterClone()
{
}

void ReloadBullet_Com::ChangeColor(float DeltaTime)
{
	m_ChangeColorTimeVar += DeltaTime;

	if (m_ChangeColorTimeVar >= m_ChangeColorTime)
	{
		m_ChangeColorTimeVar = 0.0f;

		if (m_Material->GetDiffuseLight() == Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f))
			m_Material->SetMaterial(Vector4(1.0f, 209.0f / 255.0f, 81.0f / 255.0f, 1.0f));
		else
			m_Material->SetMaterial(Vector4(1.0f, 238.0f / 255.0f, 80.0f / 255.0f, 1.0f));
	}
}

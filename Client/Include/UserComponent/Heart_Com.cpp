#include "ClientHeader.h"
#include "Heart_Com.h"
#include "Gun_Com.h"
#include "ReloadBullet_Com.h"
#include "Gonner_Com.h"

JEONG_USING

Heart_Com::Heart_Com()
{
}

Heart_Com::Heart_Com(const Heart_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Heart_Com::~Heart_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
}

bool Heart_Com::Init()
{
	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.1f;

	m_Color[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_Color[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_Color[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	Renderer_Com* HeartItemRender = m_Object->AddComponent<Renderer_Com>("HeartItemRender");
	HeartItemRender->SetMesh("TextureRect");
	HeartItemRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(HeartItemRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4::White);
	m_Material->SetDiffuseTexture(0, "HeartItem", TEXT("Monster\\player.png"));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("HeartItemAni");
	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(640.0f + i * 64.0f, 576.0f);
		tFrame.RightBottom = Vector2(640.0f + (i + 1) * 64.0f, 640.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("HeartItem", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "HeartItem", L"Monster\\player.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("HeartItem");

	return true;
}

int Heart_Com::Input(float DeltaTime)
{
	return 0;
}

int Heart_Com::Update(float DeltaTime)
{
	ChangeColor(DeltaTime);

	if (KeyInput::Get()->KeyDown("Reload"))
		CreateReloadBullet(DeltaTime);

	return 0;
}

int Heart_Com::LateUpdate(float DeltaTime)
{
	m_TargetPos = Gonner_Com::m_GonnerPos;

	switch (m_Animation->GetDir())
	{
		case MD_LEFT:
		{
			m_Object->GetTransform()->SetWorldPos(m_TargetPos.x + 8.0f, m_TargetPos.y - 5.0f, 1.0f);
			m_Animation->SetDir(MD_LEFT);
		}
		break;
		case MD_RIGHT:
		{
			m_Object->GetTransform()->SetWorldPos(m_TargetPos.x - 8.0f, m_TargetPos.y - 5.0f, 1.0f);
			m_Animation->SetDir(MD_RIGHT);
		}
		break;
	}

	return 0;
}

void Heart_Com::Collision(float DeltaTime)
{
}

void Heart_Com::CollisionLateUpdate(float DeltaTime)
{

}

void Heart_Com::Render(float DeltaTime)
{
}

Heart_Com * Heart_Com::Clone()
{
	return new Heart_Com(*this);
}

void Heart_Com::AfterClone()
{
}

void Heart_Com::ChangeColor(float DeltaTime)
{
	m_ChangeTimeVar += DeltaTime;

	if (m_ChangeTimeVar > m_ChangeTime)
	{
		m_ChangeTimeVar = 0.0f;

		int RandNum = RandomRange(1, 3);

		switch (RandNum)
		{
			case 1:
				m_Material->SetMaterial(m_Color[RandNum - 1]);
				break;
			case 2:
				m_Material->SetMaterial(m_Color[RandNum - 1]);
				break;
			case 3:
				m_Material->SetMaterial(m_Color[RandNum - 1]);
				break;
		}
	}
}

void Heart_Com::CreateReloadBullet(float DeltaTime)
{
	if (Gun_Com::m_isReloading == true)
		return;

	if (Gun_Com::m_isEquip == false)
		return;

	SoundManager::Get()->FindSoundEffect("ReloadBulletCreate")->Play();
	Layer* defaultLayer = m_Scene->FindLayer("Default");

	GameObject* newReloadBullet = GameObject::CreateObject("ReloadBullet", defaultLayer);
	ReloadBullet_Com* newReloadCom = newReloadBullet->AddComponent< ReloadBullet_Com>("ReloadBullet");
	newReloadCom->GetAnimation()->SetDir(m_Animation->GetDir());

	if (m_Animation->GetDir() == MD_LEFT)
	{
		newReloadBullet->GetTransform()->SetWorldPos(m_TargetPos.x + 30.0f, m_TargetPos.y + 20.0f, 1.0f);
		newReloadBullet->GetTransform()->SetWorldRotZ(-25.0f);
	}
	else if (m_Animation->GetDir() == MD_RIGHT)
	{
		newReloadBullet->GetTransform()->SetWorldPos(m_TargetPos.x - 30.0f, m_TargetPos.y + 20.0f, 1.0f);
		newReloadBullet->GetTransform()->SetWorldRotZ(25.0f);
	}

	SAFE_RELEASE(newReloadBullet);
	SAFE_RELEASE(newReloadCom);
	SAFE_RELEASE(defaultLayer);
}

#include "ClientHeader.h"
#include "Gun_Com.h"
#include "Bullet_Com.h"
#include "BulletUI_Com.h"
#include "Gonner_Com.h"

#include <UserComponent/ShotEffect_Com.h>

bool Gun_Com::m_isReloading = false;
bool Gun_Com::m_isEquip = false;

Gun_Com::Gun_Com()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
	m_AfterEffectLayer = NULLPTR;
	m_DefaultLayer = NULLPTR;
}

Gun_Com::Gun_Com(const Gun_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

Gun_Com::~Gun_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_AfterEffectLayer);
	Safe_Release_VecList(m_vecBulletUIObject);
	Safe_Release_VecList(m_vecBulletUI);
}

bool Gun_Com::Init()
{
	m_Color[0] = Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f);
	m_Color[1] = Vector4(78.0f / 255.0f, 197.0f / 255.0f, 152.0f / 255.0f, 1.0f);
	m_Color[2] = Vector4(80.0f / 255.0f, 187.0f / 255.0f, 166.0f / 255.0f, 1.0f);

	Renderer_Com* GunRender = m_Object->AddComponent<Renderer_Com>("GunRender");
	GunRender->SetMesh("TextureRect");
	GunRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(GunRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "Gun", TEXT("weapons.png"));
	m_Animation = m_Object->AddComponent<Animation2D_Com>("Gun");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	for (int i = 0; i < 6; i++)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 0.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 64.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("GunIdle", A2D_ATLS, AO_LOOP, 0.2f, vecClipFrame, "Gun", L"weapons.png");
	vecClipFrame.clear();

	m_AniName[GGS_IDLE] = "GunIdle";
	m_AniName[GGS_SHOT] = "GunIdle";
	m_AniName[GGS_RELOAD] = "GunIdle";

	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	m_ChangeTimeVar = 0.0f;
	m_ChangeTime = 0.3f;
	m_ReloadDelayTimeVar = 0.0f;
	m_ReloadDelayTime = 4.0f;

	ChangeState(GGS_IDLE, m_AniName, m_Animation);

	Scene* getScene = SceneManager::Get()->GetCurScene();
	m_AfterEffectLayer = getScene->FindLayer("AfterEffectLayer");
	Layer* UILayer = getScene->FindLayer("UI");
	m_DefaultLayer = getScene->FindLayerNoneCount("Default");

	SAFE_RELEASE(getScene);

	for (int i = 0; i < 20; i++)
	{
		GameObject* BulletUIObject = GameObject::CreateObject("BulletUI", UILayer);
		BulletUI_Com* newUICom = BulletUIObject->AddComponent<BulletUI_Com>("BulletUI");
		newUICom->SetIndex(i);

		m_vecBulletUIObject.push_back(BulletUIObject);
		m_vecBulletUI.push_back(newUICom);
	}

	m_ReloadTimeVar = 0.0f;
	m_ReloadTime = 0.02f;

	SAFE_RELEASE(UILayer);
	return true;
}

int Gun_Com::Input(float DeltaTime)
{

	return 0;
}

int Gun_Com::Update(float DeltaTime)
{
	Vector3 TargetPos = Gonner_Com::m_GonnerPos;

	switch (m_Animation->GetDir())
	{
		case MD_LEFT:
			m_Transform->SetWorldPos(TargetPos.x - 10.0f, TargetPos.y - 10.0f, 1.0f);
		break;
		case MD_RIGHT:
			m_Transform->SetWorldPos(TargetPos.x + 10.0f, TargetPos.y - 10.0f, 1.0f);
		break;
	}

	m_Pos = m_Transform->GetWorldPos();

	ChangeColor(DeltaTime);

	if (KeyInput::Get()->KeyDown("Reload"))
	{
		if (m_isReloading == false)
			m_isReloading = true;
	}

	DelayTime(DeltaTime);

	switch (m_State)
	{
		case GGS_IDLE:
			FS_IDLE(DeltaTime);
			break;
		case GGS_SHOT:
			FS_SHOT(DeltaTime);
			break;
		case GGS_RELOAD:
			FS_RELOAD(DeltaTime);
			break;
	}
	return 0;
}

int Gun_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Gun_Com::Collision(float DeltaTime)
{
}

void Gun_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Gun_Com::Render(float DeltaTime)
{
}

Gun_Com * Gun_Com::Clone()
{
	return new Gun_Com(*this);
}

void Gun_Com::AfterClone()
{
}

void Gun_Com::FS_IDLE(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("Attack") || KeyInput::Get()->KeyDown("Attack"))
		ChangeState(GGS_SHOT, m_AniName, m_Animation);
}

void Gun_Com::FS_SHOT(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("Attack") || KeyInput::Get()->KeyDown("Attack"))
	{
		if (m_Animation->GetFrame() == 2)
		{
			if (m_Animation->GetPrevFrame() == m_Animation->GetFrame())
				return;

			if (CountManager::Get()->m_BulletCount == 0)
				return;

			GameObject* newbulletObject = GameObject::CreateObject("Bullet", m_DefaultLayer);
			Bullet_Com* newBullet = newbulletObject->AddComponent<Bullet_Com>("Bullet");
			newbulletObject->GetTransform()->SetWorldPos(m_Pos.x, m_Pos.y, 1.0f);
			newBullet->GetAnimation()->SetDir(m_Animation->GetDir());
			newBullet->SetAfterLayer(m_AfterEffectLayer);

			//ÀÌÆåÆ®»ý¼º(Shot)
			GameObject* newShotEffectObject = GameObject::CreateObject("ShotEffect", m_AfterEffectLayer);
			ShotEffect_Com* newEffectCom = newShotEffectObject->AddComponent<ShotEffect_Com>("ShotEffect");
			newEffectCom->GetAnimation()->SetDir(m_Animation->GetDir());

			if (m_Animation->GetDir() == MD_LEFT)
			{
				newBullet->GetTransform()->SetWorldRotZFromNoneAxis(90.0f);
				newShotEffectObject->GetTransform()->SetWorldPos(m_Pos.x - 50.0f, m_Pos.y, 1.0f);
				newEffectCom->GetTransform()->SetWorldRotZFromNoneAxis(90.0f);
			}
			else
			{
				newBullet->GetTransform()->SetWorldRotZFromNoneAxis(-90.0f);
				newShotEffectObject->GetTransform()->SetWorldPos(m_Pos.x + 50.0f, m_Pos.y, 1.0f);
				newEffectCom->GetTransform()->SetWorldRotZFromNoneAxis(-90.0f);
			}

			SoundManager::Get()->FindSoundEffect("Shot")->Play();

			if (CountManager::Get()->m_BulletCount > 0)
				CountManager::Get()->m_BulletCount--;
			else
				CountManager::Get()->m_BulletCount = 0;

			SAFE_RELEASE(newbulletObject);
			SAFE_RELEASE(newBullet);
			SAFE_RELEASE(newShotEffectObject);
			SAFE_RELEASE(newEffectCom);
		}
	}

	if (KeyInput::Get()->KeyUp("Attack"))
		ChangeState(GGS_IDLE, m_AniName, m_Animation);
}

void Gun_Com::FS_RELOAD(float DeltaTime)
{
	if (CountManager::Get()->m_BulletCount == 20)
	{
		ChangeState(GGS_IDLE, m_AniName, m_Animation);
		return;
	}

	m_ReloadTimeVar += DeltaTime;

	if (m_ReloadTimeVar >= m_ReloadTime)
	{
		m_ReloadTimeVar = 0.0f;
		CountManager::Get()->m_BulletCount++;
	}

	if (CountManager::Get()->m_BulletCount >= 20)
		ChangeState(GGS_IDLE, m_AniName, m_Animation);
}

void Gun_Com::ChangeColor(float DeltaTime)
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

void Gun_Com::DelayTime(float DeltaTime)
{
	if (m_isReloading == false)
		return;

	m_ReloadDelayTimeVar += DeltaTime;

	if (m_ReloadDelayTimeVar >= m_ReloadDelayTime)
	{
		m_ReloadDelayTimeVar = 0.0f;
		m_isReloading = false;

		SoundManager::Get()->FindSoundEffect("DelayFinish")->Play();
	}
}

void Gun_Com::ClearUI()
{
	for (size_t i = 0; i < m_vecBulletUI.size(); i++)
	{
		m_vecBulletUI[i]->SetIsActive(false);
		SAFE_RELEASE(m_vecBulletUI[i]);
	}

	for (size_t i = 0; i < m_vecBulletUIObject.size(); i++)
	{
		m_vecBulletUIObject[i]->SetIsActive(false);
		SAFE_RELEASE(m_vecBulletUIObject[i]);

	}
}
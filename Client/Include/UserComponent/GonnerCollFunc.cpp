#include "ClientHeader.h"
#include "Gonner_Com.h"
#include "FragmentEffect_Com.h"
#include "BasicEffect_Com.h"

#include <UserComponent/HeartUI_Com.h>
#include <UserComponent/Skull_Com.h>

void Gonner_Com::GunItemHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "GunItemBody")
	{
		if (m_State == GS_BUGJUMP || m_State == GS_BUGIDLE || m_State == GS_BUGDOWN)
			return;

		Dest->GetGameObject()->SetIsActive(false);
		
		if (m_GunObject != NULLPTR || m_Gun != NULLPTR)
			return;

		m_GunObject = GameObject::CreateObject("GunObject", m_AfterEffectLayer);
		m_Gun = m_GunObject->AddComponent<Gun_Com>("Gun");
		m_GunObject->SetScene(m_Scene);
		m_GunObject->SetLayer(m_Layer);
		m_GunObject->GetTransform()->SetWorldRotZFromNoneAxis(-90.0f);
		Gun_Com::m_isEquip = true;

		SoundManager::Get()->FindSoundEffect("EatGun")->Play();
	}
}
void Gonner_Com::HeartItemHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "HeartItemBody")
	{
		if (m_State == GS_BUGJUMP || m_State == GS_BUGIDLE || m_State == GS_BUGDOWN)
			return;

		Dest->GetGameObject()->SetIsActive(false);

		if (m_HeartObject != NULLPTR || m_Heart != NULLPTR)
			return;
		
		Layer* prevLayer = m_Scene->FindLayer("PrevEffectLayer");
		Layer* UILayer = m_Scene->FindLayer("UI");

		m_HeartObject = GameObject::CreateObject("HeartObject", prevLayer);
		m_Heart = m_HeartObject->AddComponent<Heart_Com>("Heart");
		m_HeartObject->SetScene(m_Scene);
		m_HeartObject->SetLayer(m_Layer);

		GameObject* newHeartUI = GameObject::CreateObject("HeartUI", UILayer);
		HeartUI_Com* newUI = newHeartUI->AddComponent< HeartUI_Com>("HeartUI");
		newUI->SetTarget(m_Object);

		SAFE_RELEASE(newHeartUI);
		SAFE_RELEASE(newUI);

		SAFE_RELEASE(prevLayer);
		SAFE_RELEASE(UILayer);
		SoundManager::Get()->FindSoundEffect("ReloadBulletCreate")->Play();
	}
}

void Gonner_Com::ReloadBulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "ReloadBulletBody")
	{
		Dest->GetGameObject()->SetIsActive(false);
		SoundManager::Get()->FindSoundEffect("Reload")->Play();

		if (m_Gun == NULLPTR)
			return;

		int RandNum = RandomRange(8, 15);
		for (int i = 0; i < RandNum; i++)
		{
			GameObject* newEffect = GameObject::CreateObject("ReloadEffect", m_AfterEffectLayer);
			BasicEffect_Com* BasicEffect = newEffect->AddComponent<BasicEffect_Com>("ReloadEffect");
			BasicEffect->GetTransform()->SetWorldPos(m_Pos.x, m_Pos.y, 1.0f);
			BasicEffect->SetRandomDirection(Vector4(1.0f, 1.0f, 0.0f, 0.3f));

			SAFE_RELEASE(newEffect);
			SAFE_RELEASE(BasicEffect);
		}

		m_Gun->ChangeState(GGS_RELOAD, m_Gun->GetAniName(), m_Gun->GetAnimation());
	}
}

void Gonner_Com::LifeItemHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "LifeItemBody")
	{
		if (m_State == GS_BUGJUMP || m_State == GS_BUGIDLE || m_State == GS_BUGDOWN)
			return;

		Dest->GetGameObject()->SetIsActive(false);

		if (m_SkullObject != NULLPTR || m_Skull != NULLPTR)
			return;

		m_SkullObject = GameObject::CreateObject("Life", m_AfterEffectLayer);
		m_Skull = m_SkullObject->AddComponent< Skull_Com>("Life");
		
		SoundManager::Get()->FindSoundEffect("LifeEat")->Play();
		m_isSkullItem = true;
	}
}

void Gonner_Com::MonsterHitFirst(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MonsterBody")
	{
		if (m_State != GS_JUMP || m_State != GS_DOUBLEJUMP)
			return;

		if (m_isJumpAttack == false)
			return;

		///
	}
}
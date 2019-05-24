#include "ClientHeader.h"
#include "Gonner_Com.h"
#include "SnakeBody_Com.h"
#include "SnakeHead_Com.h"

#include <Core.h>
#include <UserComponent/Fade_Com.h>
#include <UserComponent/BasicEffect_Com.h>
#include <UserComponent/FragmentEffect_Com.h>
#include <UserComponent/HeartUI_Com.h>
#include <UserComponent/Skull_Com.h>
#include <UserComponent/LifeItem_Com.h>
#include <UserComponent/HeartItem_Com.h>

#include <UserComponent/HitEffect_Com.h>
#include <UserComponent/Monster_Base.h>

void Gonner_Com::GunItemHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "GunItemBody")
	{
		if (m_State == GS_BUGJUMP || m_State == GS_BUGIDLE || m_State == GS_BUGDOWN)
			return;

		Dest->GetGameObject()->SetIsActive(false);
		
		if (m_GunObject != NULLPTR || m_Gun != NULLPTR)
			return;

 		m_GunObject = GameObject::CreateObject("GunObject", m_AfterEffectLayer, true);
		m_Gun = m_GunObject->AddComponent<Gun_Com>("Gun");
		m_GunObject->GetTransform()->SetWorldRotZFromNoneAxis(-90.0f);
		Gun_Com::m_isEquip = true;

		SoundManager::Get()->FindSoundEffect("EatGun")->Play();
		SceneManager::Get()->AfterAccess(m_GunObject);
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

		m_HeartObject = GameObject::CreateObject("HeartObject", prevLayer, true);
		m_Heart = m_HeartObject->AddComponent<Heart_Com>("Heart");

		SAFE_RELEASE(prevLayer);
		SoundManager::Get()->FindSoundEffect("ReloadBulletCreate")->Play();
		SceneManager::Get()->AfterAccess(m_HeartObject);
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
			GameObject* newEffect = GameObject::CreateObject("ReloadEffect", m_AfterEffectLayer, true);
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

		m_SkullObject = GameObject::CreateObject("Life", m_AfterEffectLayer, true);
		m_Skull = m_SkullObject->AddComponent<Skull_Com>("Life");
		
		SoundManager::Get()->FindSoundEffect("LifeEat")->Play();
		m_isSkullItem = true;

		SceneManager::Get()->AfterAccess(m_SkullObject);
	}
}

void Gonner_Com::MonsterHitFirst(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MonsterBody")
	{
		Monster_Base* getMonster = Dest->GetGameObject()->FindComponentFromTypeNoneCount<Monster_Base>(CT_MONSTER);
		getMonster->SetIsJumpAttack(m_isJumpAttack);

		if (m_State == GS_BUGDOWN || m_State == GS_BUGIDLE || m_State == GS_BUGJUMP)
			return;

#ifdef _DEBUG
#else
		//if (m_Skull == NULLPTR)
		//{
		//	MessageBox(Core::Get()->GetHwnd(), TEXT("场"), TEXT("场"), MB_OK);
		//	return;
		//}
#endif
		if (m_isJumpAttack == true)
		{
			if (getMonster->GetState() == (GUARD_STATE)GUS_GUARD)
			{
				CountManager::Get()->m_LifeCount--;
				ChangeState(GS_BUGIDLE, m_AniName, m_Animation);
				m_BugJumpCount = 0;
				m_Camera->SetShake(10.0f, 0.2f);
				SoundManager::Get()->FindSoundEffect("ChangeStateBug")->Play();

				OutItem();
			}
			else
			{
				Layer* getLayer = SceneManager::Get()->GetCurSceneNonCount()->FindLayerNoneCount("AfterEffect");

				GameObject* newHitEffect = GameObject::CreateObject("Hit", getLayer);
				HitEffect_Com* HitEffect = newHitEffect->AddComponent<HitEffect_Com>("Hit");
				HitEffect->SetPos(Vector3(m_Pos.x, m_Pos.y + m_Scale.y * 0.5f, 1.0f), Vector4(Vector4(1.0f, 80.0f / 255.0f, 79.0f / 255.0f, 0.4f)));
				SAFE_RELEASE(newHitEffect);
				SAFE_RELEASE(HitEffect);

				SoundManager::Get()->FindSoundEffect("JumpAttack")->Play();

				m_Camera->SetShake(10.0f, 0.2f);
				getMonster->AddHp(-1);
				m_GravityCom->SetForce(600.0f);
				ChangeState(GS_JUMP, m_AniName, m_Animation);
			}
	
		}
		else if (CountManager::Get()->m_LifeCount != 0)
		{
			CountManager::Get()->m_LifeCount--;
			ChangeState(GS_BUGIDLE, m_AniName, m_Animation);
			m_BugJumpCount = 0;
			m_Camera->SetShake(10.0f, 0.3f);
			SoundManager::Get()->FindSoundEffect("ChangeStateBug")->Play();

			OutItem();
		}
#ifdef _DEBUG
#else
		//else if (CountManager::Get()->m_LifeCount == 0)
		//	MessageBox(Core::Get()->GetHwnd(), TEXT("场"), TEXT("场"), MB_OK);
#endif
	}
}

void Gonner_Com::MonsterHitDoing(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{

}
void Gonner_Com::MonsterHitEnd(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
}

void Gonner_Com::SnakeHeadHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
}
void Gonner_Com::SnakeHeadHitFirst(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "SnakeHeadBody")
	{
		SoundManager::Get()->FindSoundEffect("SnakeEat")->Play();

		GameObject* getObject = Dest->GetGameObject();
		SnakeHead_Com* getCom = getObject->FindComponentFromTypeNoneCount<SnakeHead_Com>(CT_SNAKEHEAD);
		getCom->ChangeState(1, getCom->GetAniName(), getCom->GetAnimation());

		Layer* FadeLayer = m_Scene->FindLayer("Fade");

		GameObject* newFade = GameObject::CreateObject("Fade", FadeLayer, false);
		Fade_Com* newFadeCom = newFade->AddComponent<Fade_Com>("Fade");
		newFadeCom->SetFadeColor(Vector3(0.0f, 0.0f, 0.0f), FO_IN);
		newFadeCom->SetFadeSpeed(0.6f);
		newFadeCom->Start();

		SAFE_RELEASE(FadeLayer);
	}
}
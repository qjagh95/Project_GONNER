#include "ClientHeader.h"
#include "Gonner_Com.h"

void Gonner_Com::GunItemHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "GunItemBody")
	{
		if (m_State == GS_BUGJUMP || m_State == GS_BUGIDLE || m_State == GS_BUGDOWN)
			return;

		Dest->GetGameObject()->SetIsActive(false);
		
		if (m_GunObject != NULLPTR || m_Gun != NULLPTR)
			return;

		m_GunObject = GameObject::CreateObject("GunObject");
		m_Gun = m_GunObject->AddComponent<Gun_Com>("Gun");
		m_GunObject->SetScene(m_Scene);
		m_GunObject->SetLayer(m_Layer);
		m_GunObject->GetTransform()->SetWorldRotZFromNoneAxis(-90.0f);

		SoundManager::Get()->FindSoundEffect("EatGun")->Play();
	}
}
void Gonner_Com::HeartItemHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "HeartItemBody")
	{

	}
}

void Gonner_Com::MonsterHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MonsterBody")
	{

	}
}

void Gonner_Com::ReloadBulletHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "ReloadBulletBody")
	{

	}
}
#include "ClientHeader.h"
#include "Gonner_Com.h"

void Gonner_Com::GunItemHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "GunItemBody")
	{
		if (m_State == GS_BUGJUMP || m_State == GS_BUGIDLE || m_State == GS_BUGDOWN)
			return;

		Dest->GetGameObject()->SetIsActive(false);
		
		m_GunObject = GameObject::CreateObject("GunObject");
		m_Gun = m_GunObject->AddComponent<Gun_Com>("Gun");
		m_GunObject->SetScene(m_Scene);
		m_GunObject->SetLayer(m_Layer);
		m_GunObject->GetTransform()->SetWorldRotZFromNoneAxis(-90.0f);
	}
}

#include "ClientHeader.h"
#include "Gonner_Com.h"

void Gonner_Com::GunItemHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "GunItemBody")
	{
		Dest->GetGameObject()->SetIsActive(false);
		//아이템 들기.
	}
}

#include "ClientHeader.h"
#include "CountManager.h"

#include "UserComponent/Gonner_Com.h"

SINGLETON_VAR_INIT(CountManager)

CountManager::CountManager()
{
	m_LifeCount = 5;
	m_BulletCount = 20;
}

CountManager::~CountManager()
{
}

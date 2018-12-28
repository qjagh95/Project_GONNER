#include "stdafx.h"
#include "CountManager.h"

JEONG_USING
SINGLETON_VAR_INIT(CountManager)

CountManager::CountManager()
{
	m_LifeCount = 5;
	m_BulletCount = 20;
}

CountManager::~CountManager()
{
}

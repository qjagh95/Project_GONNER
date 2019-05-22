#include "stdafx.h"
#include "StageManager.h"

JEONG_USING
SINGLETON_VAR_INIT(StageManager)

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}

void StageManager::InsertStage(Stage2D_Com* stage)
{
	if (m_StageName.empty() == true)
	{
		TrueAssert(true);
		return;
	}

	Stage2D_Com* getStage = FindCurStage();

	if (getStage != NULLPTR)
		return;

	getStage = stage;

	m_StageMap.insert(make_pair(m_StageName, getStage));
}

Stage2D_Com * StageManager::FindCurStage()
{
	unordered_map<string, Stage2D_Com*>::iterator FindIter = m_StageMap.find(m_StageName);

	if (FindIter == m_StageMap.end())
		return NULLPTR;

	return FindIter->second;
}

void StageManager::SetStageName(const string & StageName)
{
	m_StageName = StageName;
}

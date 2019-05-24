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
	Stage2D_Com* getStage = FindCurStage();

	if (getStage != NULLPTR)
		return;

	m_StageMap.insert(make_pair(stage->GetTag(), stage));
}

Stage2D_Com * StageManager::FindCurStage()
{
	unordered_map<string, Stage2D_Com*>::iterator FindIter = m_StageMap.find(GetCurStageName());

	if (FindIter == m_StageMap.end())
		return NULLPTR;

	return FindIter->second;
}

string StageManager::GetCurStageName()
{
	auto StartIter = SceneManager::Get()->GetCurSceneNonCount()->FindLayerNoneCount("Tile")->GetObjectList()->begin();
	auto EndIter = SceneManager::Get()->GetCurSceneNonCount()->FindLayerNoneCount("Tile")->GetObjectList()->end();

	for (; StartIter != EndIter; StartIter++)
	{
		Component_Base* getComponent = dynamic_cast<Component_Base*>((*StartIter)->FindComponentFromTypeNoneCount<Stage2D_Com>(CT_STAGE2D));

		if (getComponent != NULLPTR)
			return getComponent->GetTag();
	}

	return string();
}
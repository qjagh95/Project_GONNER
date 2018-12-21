#pragma once
JEONG_BEGIN

class Stage2D_Com;
class JEONG_DLL StageManager
{
public:
	void InsertStage(Stage2D_Com* stage);
	Stage2D_Com* FindCurStage();
	void SetStageName(const string& StageName);

private:
	unordered_map<string, Stage2D_Com*> m_StageMap;
	string m_StageName;

public:
	CLASS_IN_SINGLE(StageManager)
};

JEONG_END
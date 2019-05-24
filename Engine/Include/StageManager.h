#pragma once
JEONG_BEGIN

class Stage2D_Com;
class JEONG_DLL StageManager
{
public:
	void InsertStage(Stage2D_Com* stage);
	Stage2D_Com* FindCurStage();
	string GetCurStageName();

private:
	unordered_map<string, Stage2D_Com*> m_StageMap;

public:
	CLASS_IN_SINGLE(StageManager)
};

JEONG_END
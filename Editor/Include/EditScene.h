#pragma once
#include <Scene/SceneComponent.h>
#include <Component/BackColor_Com.h>
#include <Component/Stage2D_Com.h>

struct SaveData
{
	MONSTER_TYPE Type;
	Vector3 Pos;
	MOVE_DIR Dir;
};

class EditScene : public SceneComponent
{
public:
	bool Init() override;
	int Update(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;

	vector<SaveData> m_vecSaveData;
	vector<GameObject*> m_vecSaveObject;
	int m_Index;

private:
	void ToolOnActive(float DeltaTime, EditorForm* editorForm);
	void ToolOffActive(float DeltaTime);
	void ChangeTile(const Vector3& mPos, EditorForm* form, Stage2D_Com* TileStage);

private:
	BackColor_Com* m_BackColorCom;
	wstring m_Path;
	bool m_isSelect;
	bool m_isCreate;

	MainFrame* m_MainFrame;
	EditorForm*	m_EditorForm;

public:
	EditScene();
	~EditScene();
};


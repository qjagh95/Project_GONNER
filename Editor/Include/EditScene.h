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

private:
	void ToolOnActive(float DeltaTime, EditorForm* editorForm);
	void ToolOffActive(float DeltaTime, EditorForm* editorForm);

	void ChangeTile(const Vector3& mPos, EditorForm* form, Stage2D_Com* TileStage);

private:
	BackColor_Com* m_BackColorCom;
	wstring m_Path;
	vector<SaveData> m_vecSaveData;
	vector<GameObject*> m_vecSaveObject;
	bool m_isSelect;
	int m_Index;
	bool m_isCreate;

public:
	EditScene();
	~EditScene();
};


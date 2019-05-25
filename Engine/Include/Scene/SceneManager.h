#pragma once
JEONG_BEGIN

class Scene;
class Layer;
class GameObject;
class SceneComponent;
class JEONG_DLL SceneManager
{
public:
	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	int Collision(float DeltaTime);
	int CollsionLateUpdate(float DeltaTime);
	void Render(float DeltaTime);

	Scene* GetCurScene() const;
	Scene* GetCurSceneNonCount() { return m_CurScene; }
	void SetIsChange(bool isChange);
	void AddLayer(const string& TagName, int ZOrder);
	void ChangeLayerZOrder(const string& TagName, int ZOrder);
	Layer* FindLayer(const string& TagName);
	GameObject* FindObject(const string& TagName);
	void ChangeScene(const string& KeyName);
	const unordered_map<string, Scene*>* GetSceneMap() { return &m_SceneMap; }
	Scene* FindScene(const string& KeyName);
	void Access();
	void AfterAccess(GameObject* object);
	bool GetIsAccessComplected() const { return m_isAccessCompleted; }

public:
	template <typename T>
	void AddScene(const string & SceneKeyName, const string& ComponentTag)
	{
		Scene* newScene = FindScene(SceneKeyName);

		if (newScene != NULLPTR)
			return;

		newScene = new Scene();
		m_SceneMap.insert(make_pair(SceneKeyName, newScene));
		newScene->Init();
		newScene->SetTag(SceneKeyName);
		newScene->AddSceneComponent<T>(ComponentTag);

		if (m_isStart == false)
			m_CurScene = m_SceneMap.begin()->second;

		m_isStart = true;

		KeyInput::Get()->ChangeMouseScene(m_CurScene);
		
		m_vecTemp.push_back(newScene);
	}

private:
	template <typename T>
	bool AddSceneComponent(const string& SceneKeyName, const string& ComponentTag)
	{
		Scene* getScene = FindScene(SceneKeyName);

		if (getScene == NULLPTR)
		{
			TrueAssert(true);
			return false;
		}

		return getScene->AddSceneComponent<T>(ComponentTag);
	}

	void AfterInit();

private:
	unordered_map<string, Scene*> m_SceneMap;
	vector<Scene*> m_vecTemp;
	Scene* m_CurScene;

	bool m_isChange;
	bool m_isStart;
	bool m_isAccessCompleted;

public:
	CLASS_IN_SINGLE(SceneManager)
};

JEONG_END
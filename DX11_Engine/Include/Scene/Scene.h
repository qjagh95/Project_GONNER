#pragma once
#include "../RefCount.h"
JEONG_BEGIN

class Layer;
class SceneComponent;
class GameObject;
class Camera_Com;
class Transform_Com;
class JEONG_DLL Scene : public RefCount
{
public:
	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void CollisionLateUpdate(float DeltaTime);
	void Render(float DeltaTime);

	void AddLayer(const string& TagName, int ZOrder);
	void ChangeLayerZOrder(const string& TagName, int ZOrder);
	void SortLayer();
	void SetEnableLayer(const string& TagName, bool isShow);
	void SetLayerDie(const string& TagName, bool isActive);
	Layer* FindLayer(const string& TagName);
	Layer* FindLayerNoneCount(const string& TagName);
	GameObject* FindObject(const string& TagName);
	list<Layer*>* GetLayerList() { return &m_LayerList; }

	template<typename T>
	bool AddSceneComponent(const string& TagName)
	{
		T* newCom = new T();

		newCom->SetTag(TagName);
		newCom->m_Scene = this;

		if (newCom->Init() == false)
		{
			SAFE_RELEASE(newCom);
			return false;
		}

		m_SceneComponent = newCom;
		return true;
	}

	GameObject* CreateCamera(const string& TagName, const Vector3& Pos, CAMERA_TYPE eType, float Width, float Height, float ViewAngle, float Near, float Far);
	void ChangeCamera(const string& TagName);

	GameObject* GetMainCameraObject() const { return m_MainCameraObject; }
	Transform_Com* GetMainCameraTransform() const { return m_MainCameraTransform; }
	Camera_Com* GetMainCamera() const { return m_MainCamera; }

	GameObject* GetUICameraObject() const { return m_UICameraObject; }
	Transform_Com* GetUICameraTransform() const { return m_UICameraTransform; }
	Camera_Com* GetUICamera() const { return m_UICamera; }

	void CreateWave(const Vector3& Pos, float LiveTime, float Range);
	SceneComponent* GetSceneComponent() const { return m_SceneComponent; }

private:
	class GameObject* FindCamera(const string& TagName);
	void UpdateWaveCBuffer(float DeltaTime);
	void AfterInit();

private:
	list<Layer*> m_LayerList;
	SceneComponent* m_SceneComponent;

	unordered_map<string, GameObject*> m_CameraMap;
	Camera_Com* m_MainCamera;
	Transform_Com* m_MainCameraTransform;
	GameObject* m_MainCameraObject;

	Camera_Com* m_UICamera;
	Transform_Com* m_UICameraTransform;
	GameObject* m_UICameraObject;

	WaveCBuffer m_WaveCBuffer;
	Vector2 m_WinSize;

private:
	Scene();
public:
	~Scene();

public:
	static bool SortLayerFunc(const Layer* Src, const Layer* Dest);
	friend class SceneManager;
};

JEONG_END
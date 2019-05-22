#include "stdafx.h"
#include "GameObject.h"
#include "CollsionManager.h"
#include "ObjectManager.h"

#include "Scene/Layer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Animation2D_Com.h"
#include "Component/UIBase_Com.h"
#include "Component/TitleBar_Com.h"
#include "Component/Text_Com.h"
#include "Component/Tile2D_Com.h"
#include "Component/TileImage_Com.h"
#include "Component/Stage2D_Com.h"
#include "Component/BackColor_Com.h"
#include "Component/Gravity_Com.h"
#include "Component/Number_Com.h"
#include "Component/ColliderCircle_Com.h"
#include "Component/ColliderRect_Com.h"
#include "Component/ColliderPixel_Com.h"
#include "Component/ColliderPoint_Com.h"
#include "Component/ColliderOBB2D_Com.h"

JEONG_USING

unordered_map<string, GameObject*> GameObject::m_ProtoTypeMap;

GameObject::GameObject()
	:m_Scene(NULLPTR), m_Layer(NULLPTR), m_Transform(NULLPTR), m_Parent(NULLPTR)
{
	SetTag("GameObject");
}

GameObject::GameObject(const GameObject& copyObject)
{
	*this = copyObject;

	ReferanceCount = 1;

	m_Transform = copyObject.m_Transform->Clone();
	m_Transform->m_Transform = m_Transform;

	m_ComponentList.clear();
	m_FindComList.clear();

	list<Component_Base*>::const_iterator StartIter = copyObject.m_ComponentList.begin();
	list<Component_Base*>::const_iterator EndIter = copyObject.m_ComponentList.end();

	for (; StartIter != EndIter ; StartIter++)
	{
		Component_Base* newComponent = (*StartIter)->Clone();
		newComponent->m_Object = this;
		newComponent->m_Transform = m_Transform;

		m_ComponentList.push_back(newComponent);
	}

	Renderer_Com* getRender = FindComponentFromType<Renderer_Com>(CT_RENDER);

	if(getRender != NULLPTR)
	{
		getRender->CheckComponent();

		SAFE_RELEASE(getRender);
	}

	m_ChildList.clear();

	list<GameObject*>::iterator StartIter1 = m_ChildList.begin();
	list<GameObject*>::iterator EndIter1 = m_ChildList.end();

	for (; StartIter1 != EndIter1; StartIter1++)
	{
		GameObject* child = (*StartIter1)->Clone();
		child->m_Parent = this;
		child->m_Transform->SetParentFlag(TPF_POS | TPF_ROT);

		m_ChildList.push_back(child);
	}
}

GameObject::~GameObject()
{
	Safe_Release_VecList(m_ChildList);
	SAFE_RELEASE(m_Transform);
	Safe_Release_VecList(m_FindComList);
	Safe_Release_VecList(m_ComponentList);
}

bool GameObject::Init()
{
	m_Transform = new Transform_Com();
	m_Transform->Init();

	m_Transform->m_Transform = m_Transform;

	return true;
}

int GameObject::Input(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
			if (pRenderer != NULLPTR)
			{
				pRenderer->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(pRenderer);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Input(DeltaTime);
		StartIter++;
	}

	return 0;
}

int GameObject::Update(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
			if (pRenderer != NULLPTR)
			{
				pRenderer->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(pRenderer);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Update(DeltaTime);
		StartIter++;
	}

	//내꺼 Transform업데이트를 한다
	m_Transform->Update(DeltaTime);

	//자식이 있다면 자식트랜스폼에 부모의 정보가 저장된 행렬과 자식의 Transform정보를 곱하여
	//자식의 Parent행렬에 넣어준다.
	list<GameObject*>::iterator StartIter1 = m_ChildList.begin();
	list<GameObject*>::iterator EndIter1 = m_ChildList.end();

	for (; StartIter1 != EndIter1; StartIter1++)
	{
		Matrix S = m_Transform->GetWorldScaleMatrix() * m_Transform->GetParentScale();
		Matrix R = m_Transform->GetWorldRotMatrix() * m_Transform->GetParentRot();
		Matrix T = m_Transform->GetWorldPosMatrix() * m_Transform->GetParentPos();

		(*StartIter1)->GetTransform()->SetParentScale(S);
		(*StartIter1)->GetTransform()->SetParentRot(R);
		(*StartIter1)->GetTransform()->SetParentPos(T);
		(*StartIter1)->GetTransform()->SetIsUpdate(true);
	}

	return 0;
}

int GameObject::LateUpdate(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			Renderer_Com* pRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
			if (pRenderer != NULLPTR)
			{
				pRenderer->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(pRenderer);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}
		(*StartIter)->LateUpdate(DeltaTime);
		StartIter++;
	}

	m_Transform->LateUpdate(DeltaTime);

	list<GameObject*>::iterator StartIter1 = m_ChildList.begin();
	list<GameObject*>::iterator EndIter1 = m_ChildList.end();

	for (; StartIter1 != EndIter1; StartIter1++)
	{
		Matrix S = m_Transform->GetWorldScaleMatrix() * m_Transform->GetParentScale();
		Matrix R = m_Transform->GetWorldRotMatrix() * m_Transform->GetParentRot();
		Matrix T = m_Transform->GetWorldPosMatrix() * m_Transform->GetParentPos();

		(*StartIter1)->GetTransform()->SetParentScale(S);
		(*StartIter1)->GetTransform()->SetParentRot(R);
		(*StartIter1)->GetTransform()->SetParentPos(T);
		(*StartIter1)->GetTransform()->SetIsUpdate(true);
	}

	return 0;
}

void GameObject::Collision(float DeltaTime)
{
	//충돌체 추가한다.
	CollsionManager::Get()->AddCollsion(this);
}

void GameObject::CollisionLateUpdate(float DeltaTime)
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		Renderer_Com* getRenderer = FindComponentFromType<Renderer_Com>(CT_RENDER);
		if (getRenderer != NULLPTR)
		{
			getRenderer->DeleteComponentCBuffer(*StartIter);
			SAFE_RELEASE(getRenderer);
		}

		if ((*StartIter)->GetIsActive() == false)
		{
			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}
		(*StartIter)->CollisionLateUpdate(DeltaTime);
		StartIter++;
	}

}

void GameObject::Render(float DeltaTime)
{
	m_Transform->Render(DeltaTime);

	Renderer_Com* getRender = FindComponentFromType<Renderer_Com>(CT_RENDER);
	
	if (getRender != NULLPTR)
	{
		if (getRender->GetIsActive() == false)
		{
			getRender->Release();
			m_ComponentList.remove(getRender);
		}
		else if (getRender->GetIsShow() == true)
		{
			getRender->Render(DeltaTime);
		}

		SAFE_RELEASE(getRender);
	}

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetIsActive() == false)
		{
			if (getRender != NULLPTR)
			{
				getRender->DeleteComponentCBuffer(*StartIter);
				SAFE_RELEASE(getRender);
			}

			SAFE_RELEASE((*StartIter));
			StartIter = m_ComponentList.erase(StartIter);
			continue;
		}
		else if ((*StartIter)->GetIsShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Render(DeltaTime);
		StartIter++;
	}
}

GameObject * GameObject::Clone()
{
	return new GameObject(*this);
}

void GameObject::AfterClone()
{
	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (;StartIter != EndIter; StartIter++)
		(*StartIter)->AfterClone();

}

void GameObject::SetScene(Scene * scene)
{
	m_Scene = scene;
	m_Transform->m_Scene = scene;

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (;StartIter != EndIter; StartIter++)
		(*StartIter)->m_Scene = scene;
}

void GameObject::SetLayer(Layer * layer)
{
	m_Layer = layer;
	m_LayerName = layer->GetTag();
	m_LayerZOrder = layer->GetZOrder();

	m_Transform->m_Layer = layer;

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (;StartIter != EndIter; StartIter++)
		(*StartIter)->m_Layer = layer;
}

GameObject * GameObject::CreateObject(const string & TagName, Layer * layer, bool isStaticObject)
{
	//TODO
	GameObject*	newObject = new GameObject;

	newObject->SetTag(TagName);

	if (isStaticObject)
		newObject->IamNotDestroy();

	if (newObject->Init() == false)
	{
		SAFE_RELEASE(newObject);
		return NULLPTR;
	}

	if (layer != NULLPTR)
		layer->AddObject(newObject);

	return newObject;
}

const list<Component_Base*>* GameObject::GetComponentList() const
{
	return &m_ComponentList;
}

bool GameObject::CheckComponentType(COMPONENT_TYPE eType)
{
	list<Component_Base*>::const_iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::const_iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetComType() == eType)
			return true;
	}
	return false;
}

Component_Base * GameObject::AddComponent(Component_Base * component)
{
	component->m_Scene = m_Scene;
	component->m_Layer = m_Layer;
	component->m_Transform = m_Transform;
	component->m_Object = this;
	component->AddRefCount();

	m_ComponentList.push_back(component);

	Renderer_Com* pRender = FindComponentFromType<Renderer_Com>(CT_RENDER);

	if (pRender != NULLPTR)
	{
		pRender->CheckComponent();
		SAFE_RELEASE(pRender);
	}

	return component;
}

GameObject * GameObject::CreateProtoType(const string & TagName)
{
	//TODO
	Scene* getScene = NULLPTR;
	getScene = SceneManager::Get()->GetCurScene();

	GameObject* newProtoType = FindProtoType(TagName);
	
	if (newProtoType != NULLPTR)
		return NULLPTR;

	unordered_map<string, GameObject*>::iterator FindIter = m_ProtoTypeMap.find(TagName);

	if (FindIter != m_ProtoTypeMap.end())
		return FindIter->second;

	newProtoType = new GameObject();
	newProtoType->SetTag(TagName);

	if (newProtoType->Init() == false)
	{
		SAFE_RELEASE(newProtoType);
		return NULLPTR;
	}

	newProtoType->AddRefCount();
	m_ProtoTypeMap.insert(make_pair(TagName, newProtoType));

	return newProtoType;
}

GameObject * GameObject::CreateClone(const string & TagName, Layer * layer)
{
	//TODO
	Scene* getScene = NULLPTR;
	getScene = SceneManager::Get()->GetCurScene();

	GameObject* newCloneObject = FindProtoType(TagName);
	SAFE_RELEASE(getScene);

	if (newCloneObject == NULLPTR)
		return NULLPTR;

	GameObject*	pClone = newCloneObject->Clone();
	pClone->SetTag(TagName);
	pClone->AfterClone();

	if (layer != NULLPTR)
		layer->AddObject(pClone);

	return pClone;
}

void GameObject::DestroyProtoType(const string& TagName)
{
	unordered_map<string, GameObject*>::iterator FindIter = m_ProtoTypeMap.find(TagName);

	if (FindIter == m_ProtoTypeMap.end())
		return;

	m_ProtoTypeMap.erase(TagName);
}

void GameObject::DestroyProtoType()
{
	Safe_Release_Map(m_ProtoTypeMap);
	m_ProtoTypeMap.clear();
}

GameObject * GameObject::FindProtoType(const string& TagName)
{
 	unordered_map<string, GameObject*>::iterator FindIter = m_ProtoTypeMap.find(TagName);
	
	if (FindIter == m_ProtoTypeMap.end())
		return NULLPTR;

	return FindIter->second;
}

GameObject * GameObject::FindObject(const string & TagName)
{
	return SceneManager::Get()->FindObject(TagName);
}

void GameObject::AddChild(GameObject * Child)
{
	Child->m_Parent = this;

	Child->m_Transform->SetParentFlag(TPF_ROT | TPF_POS);
	Child->AddRefCount();

	m_ChildList.push_back(Child);
	m_Layer->AddObject(Child);
}

void GameObject::AddChild(GameObject * child, Scene * scene)
{
	child->m_Parent = this;

	child->m_Transform->SetParentFlag(TPF_ROT | TPF_POS);
	child->AddRefCount();

	m_ChildList.push_back(child);
	m_Layer->AddObject(child, scene);
}

void GameObject::AddChild(GameObject * child, Scene * scene, Layer * layer)
{
	child->m_Parent = this;

	child->m_Transform->SetParentFlag(TPF_ROT | TPF_POS);
	child->AddRefCount();

	m_ChildList.push_back(child);
	m_Layer->AddObject(child, scene, layer);
}

void GameObject::Save(BineryWrite & Writer)
{
	Writer.WriteData(m_ComponentList.size());

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		Writer.WriteData((*StartIter)->GetComType());
		Writer.WriteData((*StartIter)->GetTag());

		if ((*StartIter)->GetComType() == CT_COLLIDER)
			Writer.WriteData(((Collider_Com*)(*StartIter))->GetCollType());

		(*StartIter)->Save(Writer);
	}
}

void GameObject::Load(BineryRead & Reader)
{
	size_t getSize;
	Reader.ReadData(getSize);

	for (size_t i = 0; i < getSize; i++)
	{
		COMPONENT_TYPE getType;
		string getTag;
		Reader.ReadData((size_t&)getType);
		Reader.ReadData(getTag);

		switch (getType)
		{
			case CT_TRANSFORM:
			{
				Transform_Com* newTrans = AddComponent<Transform_Com>(getTag);
				newTrans->Load(Reader);
			}
				break;
			case CT_RENDER:
			{
				Renderer_Com* newRender = AddComponent<Renderer_Com>(getTag);
				newRender->Load(Reader);
			}
				break;
			case CT_MATERIAL:
			{
				Material_Com* newMater = AddComponent<Material_Com>(getTag);
				newMater->Load(Reader);
			}
				break;
			case CT_ANIMATION2D:
			{
				Animation2D_Com* newAni = AddComponent<Animation2D_Com>(getTag);
				newAni->Load(Reader);
			}
				break;
			case CT_COLLIDER:
			{
				COLLIDER_TYPE getColType;
				Reader.ReadData((int&)getColType);
				
				switch (getColType)
				{
					case CT_RECT:
					{
						ColliderRect_Com* getRect = AddComponent<ColliderRect_Com>(getTag);
						getRect->Load(Reader);
					}
						break;
					case CT_POINT:
					{
						ColliderPoint_Com* getPoint = AddComponent<ColliderPoint_Com>(getTag);
						getPoint->Load(Reader);
					}
						break;
					case CT_CIRCLE:
					{
						ColliderCircle_Com* getCircle = AddComponent<ColliderCircle_Com>(getTag);
						getCircle->Load(Reader);
					}
						break;
					case CT_OBB2D:
					{
						ColliderOBB2D_Com* getOBB2D = AddComponent<ColliderOBB2D_Com>(getTag);
						getOBB2D->Load(Reader);
					}
						break;
					case CT_PIXEL:
					{
						ColliderPixel_Com* getPixel = AddComponent<ColliderPixel_Com>(getTag);
						getPixel->Load(Reader);
					}
						break;
				}
			}
				break;
			case CT_TITLEBAR:
			{
				TitleBar_Com* newTitle = AddComponent<TitleBar_Com>(getTag);
				newTitle->Load(Reader);
			}
				break;
			case CT_TEXT:
			{
				Text_Com* newText = AddComponent<Text_Com>(getTag);
				newText->Load(Reader);
			}
				break;
			case CT_TILE2D:
			{
				Tile2D_Com* newTile = AddComponent<Tile2D_Com>(getTag);
				newTile->Load(Reader);
			}
				break;
			case CT_TILEIMAGE:
			{
				TileImage_Com* newTileImage = AddComponent<TileImage_Com>(getTag);
				newTileImage->Load(Reader);
			}
				break;
			case CT_STAGE2D:
			{
				Stage2D_Com* newStage = AddComponent<Stage2D_Com>(getTag);
				newStage->Load(Reader);
			}
				break;
			case CT_BACKCOLOR:
			{
				BackColor_Com* newBackColor = AddComponent<BackColor_Com>(getTag);
				newBackColor->Load(Reader);
			}
				break;
			case CT_GARVITY:
			{
				Gravity_Com* newGravity = AddComponent<Gravity_Com>(getTag);
				newGravity->Load(Reader);
			}
				break;
			case CT_NUMBER:
			{
				Number_Com* newNumber = AddComponent<Number_Com>(getTag);
				newNumber->Load(Reader);
			}
				break;
		}
	}
}

void GameObject::IamNotDestroy()
{
	ObjectManager::Get()->PushDontDestoryObject(this);
}

const list<Component_Base*>* GameObject::FindComponentFromTag(const string& TagName)
{
	Safe_Release_VecList(m_FindComList);
	m_FindComList.clear();

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter ; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->AddRefCount();
			m_FindComList.push_back(*StartIter);
		}
	}
	return &m_FindComList;
}

const list<Component_Base*>* GameObject::FindComponentFromType(COMPONENT_TYPE type)
{
	Safe_Release_VecList(m_FindComList);
	m_FindComList.clear();

	list<Component_Base*>::iterator StartIter = m_ComponentList.begin();
	list<Component_Base*>::iterator EndIter = m_ComponentList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetComType() == type)
		{
			(*StartIter)->AddRefCount();
			m_FindComList.push_back(*StartIter);
		}
	}
	return &m_FindComList;
}

void GameObject::SetTransform(Transform_Com* transform)
{
	m_Transform = transform;
}
void GameObject::SetRotation(const Vector3& vecRot)
{
	m_Transform->Rotation(vecRot);	
}

void GameObject::SetRotationX(float RotX)
{
	m_Transform->SetWorldRotX(RotX);
}

void GameObject::SetRotationY(float RotY)
{
	m_Transform->SetWorldRotY(RotY);
}

void GameObject::SetRotationZ(float RotZ)
{
	m_Transform->SetWorldRotZ(RotZ);
}

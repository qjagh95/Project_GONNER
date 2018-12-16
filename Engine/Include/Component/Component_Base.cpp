#include "stdafx.h"
#include "Component_Base.h"

#include "../Scene/Scene.h"
#include "../Scene/Layer.h"
#include "../GameObject.h"

#include "Transform_Com.h"

JEONG_USING

JEONG::Component_Base::Component_Base()
	:m_Scene(NULLPTR), m_Layer(NULLPTR), m_Object(NULLPTR), m_Transform(NULLPTR), m_ComType(CT_NONE)
{
	m_isUserComponent = false;
}

JEONG::Component_Base::Component_Base(const Component_Base & copyObject)
{
	*this = copyObject;
	ReferanceCount = 1;
}

JEONG::Component_Base::~Component_Base()
{
}

int JEONG::Component_Base::Input(float DeltaTime)
{
	return 0;
}

int JEONG::Component_Base::Update(float DeltaTime)
{
	return 0;
}

int JEONG::Component_Base::LateUpdate(float DeltaTime)
{
	return 0;
}

void JEONG::Component_Base::Collision(float DeltaTime)
{
}

void JEONG::Component_Base::CollisionLateUpdate(float DeltaTime)
{
}

void JEONG::Component_Base::Render(float DeltaTime)
{
}

void JEONG::Component_Base::Save(BineryWrite & Writer)
{
}

void JEONG::Component_Base::Load(BineryRead & Reader)
{	
}

const list<JEONG::Component_Base*>* JEONG::Component_Base::FindComponentFromTag(const string& TagName)
{
	return m_Object->FindComponentFromTag(TagName);
}

const list<JEONG::Component_Base*>* JEONG::Component_Base::FindComponentFromType(COMPONENT_TYPE type)
{
	return m_Object->FindComponentFromType(type);
}

JEONG::GameObject * JEONG::Component_Base::GetGameObject() const
{
	return m_Object;
}

JEONG::Transform_Com * JEONG::Component_Base::GetTransform() const
{
	return m_Transform;
}

bool JEONG::Component_Base::CheckComponentFromType(COMPONENT_TYPE eType)
{
	return m_Object->CheckComponentType(eType);
}

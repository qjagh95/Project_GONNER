#include "stdafx.h"
#include "EditorMonster_Base.h"

#include "../Component/Animation2D_Com.h"
#include "../Component/ColliderRect_Com.h"

JEONG_USING

GameObject* EditorMonster_Base::m_SelectObject = NULLPTR;

EditorMonster_Base::EditorMonster_Base()
{
	m_Material = NULLPTR;
	m_Animation = NULLPTR;
	m_RectColl = NULLPTR;

	m_Index = 0;
	m_ComType = CT_EDITOR;
}

EditorMonster_Base::EditorMonster_Base(const EditorMonster_Base & CopyData)
	:UserComponent_Base(CopyData)
{
}

EditorMonster_Base::~EditorMonster_Base()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_RectColl);
}

bool EditorMonster_Base::Init()
{
	Renderer_Com* EditorRender = m_Object->AddComponent<Renderer_Com>("EditorRenderRender");
	EditorRender->SetMesh("TextureRect");
	EditorRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(EditorRender);

	m_RectColl = m_Object->AddComponent<ColliderRect_Com>("MonsterBody");
	m_RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(64.0f, 64.0f, 0.0f));
	m_RectColl->SetCollsionCallback(CCT_DOING, this, &EditorMonster_Base::MouseHit);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4::White);
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);

	return true;
}

int EditorMonster_Base::Input(float DeltaTime)
{
	return 0;
}

int EditorMonster_Base::Update(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("LButton"))
	{
		if (m_SelectObject == NULLPTR)
			return 0;

		Vector3 mPos = KeyInput::Get()->GetMouseObject()->GetTransform()->GetWorldPos();
		Vector3 cPos = m_Scene->GetMainCameraTransform()->GetWorldPos();

		mPos += cPos;

		m_SelectObject->GetTransform()->SetWorldPos(mPos);
	}

	if (KeyInput::Get()->KeyUp("LButton"))
		m_SelectObject = NULLPTR;

	return 0;
}

int EditorMonster_Base::LateUpdate(float DeltaTime)
{
	return 0;
}

void EditorMonster_Base::Collision(float DeltaTime)
{
}

void EditorMonster_Base::CollisionLateUpdate(float DeltaTime)
{
}

void EditorMonster_Base::Render(float DeltaTime)
{
}

EditorMonster_Base * EditorMonster_Base::Clone()
{
	return new EditorMonster_Base(*this);
}

void EditorMonster_Base::AfterClone()
{
}

void EditorMonster_Base::MouseHit(Collider_Com * Src, Collider_Com * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MouseWorld")
	{
		if (KeyInput::Get()->KeyDown("LButton"))
		{
			if (m_SelectObject != NULLPTR)
				return;

			m_SelectObject = m_Object;
		}

		if (KeyInput::Get()->KeyDown("RButton"))
		{
			SetIsActive(false);
			m_Object->SetIsActive(false);
		}

		if (KeyInput::Get()->KeyPress("RButton"))
		{
			SetIsActive(false);
			m_Object->SetIsActive(false);
		}

	}
}

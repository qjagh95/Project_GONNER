#include "ClientHeader.h"
#include "SnakeHead_Com.h"

#include <Component/Animation2D_Com.h>
#include <Component/ColliderRect_Com.h>

SnakeHead_Com::SnakeHead_Com()
{
	m_Animation = NULLPTR;
	m_Material = NULLPTR;
}

SnakeHead_Com::SnakeHead_Com(const SnakeHead_Com & CopyData)
{
}

SnakeHead_Com::~SnakeHead_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool SnakeHead_Com::Init()
{
	Renderer_Com* SnakeHeadRender = m_Object->AddComponent<Renderer_Com>("SnakeHead");
	SnakeHeadRender->SetMesh("TextureRect");
	SnakeHeadRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(SnakeHeadRender);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetMaterial(Vector4::White);
	m_Material->SetDiffuseTexture(0, "SnakeHead", TEXT("Monster\\player.png"));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("SnakeHeadAni");
	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 6; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 320.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Idle", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "SnakeHead", L"Monster\\player.png");
	vecClipFrame.clear();

	for (int i = 0; i < 13; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 128.0f, 320.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 128.0f, 384.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("Eat", A2D_ATLS, AO_LOOP, 0.4f, vecClipFrame, "SnakeHead", L"Monster\\player.png");
	vecClipFrame.clear();


	m_Animation->ChangeClip("Idle");

	ColliderRect_Com* RectColl = m_Object->AddComponent<ColliderRect_Com>("LifeItemBody");
	RectColl->SetInfo(Vector3(0.0f, 0.0f, 0.0f), Vector3(128.0f, 128.0f, 0.0f));
	SAFE_RELEASE(RectColl);

	return true;
}

int SnakeHead_Com::Input(float DeltaTime)
{
	return 0;
}

int SnakeHead_Com::Update(float DeltaTime)
{
	return 0;
}

int SnakeHead_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void SnakeHead_Com::Collision(float DeltaTime)
{
}

void SnakeHead_Com::CollisionLateUpdate(float DeltaTime)
{
}

void SnakeHead_Com::Render(float DeltaTime)
{
}

SnakeHead_Com * SnakeHead_Com::Clone()
{
	return new SnakeHead_Com(*this);
}

void SnakeHead_Com::AfterClone()
{
}

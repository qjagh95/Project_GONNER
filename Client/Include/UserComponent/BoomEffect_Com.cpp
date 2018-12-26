#include "ClientHeader.h"
#include "BoomEffect_Com.h"

BoomEffect_Com::BoomEffect_Com()
{
}

BoomEffect_Com::BoomEffect_Com(const BoomEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BoomEffect_Com::~BoomEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool BoomEffect_Com::Init()
{
	Renderer_Com* BoomEffectRender = m_Object->AddComponent<Renderer_Com>("BoomEffect");
	BoomEffectRender->SetMesh("TextureRect");
	BoomEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BoomEffectRender);

	m_Transform->SetWorldScale(64.0f, 64.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BoomEffect", TEXT("Monster\\sprites.png"));
	m_Material->SetMaterial(Vector4::Yellow);

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BoomEffectAni");

	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 7; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 64.0f, 128.0f);
		tFrame.RightBottom = Vector2(0.0f + (i + 1) * 64.0f, 192.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BoomEffect", A2D_ATLS, AO_ONCE_STOP, 0.3f, vecClipFrame, "BoomEffect", L"Monster\\sprites.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("BoomEffect");
	return true;
}

int BoomEffect_Com::Input(float DeltaTime)
{
	if (m_Animation->GetIsEnd() == true)
	{
		SetIsActive(false);
		m_Object->SetIsActive(false);
	}

	return 0;
}

int BoomEffect_Com::Update(float DeltaTime)
{
	return 0;
}

int BoomEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BoomEffect_Com::Collision(float DeltaTime)
{
}

void BoomEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BoomEffect_Com::Render(float DeltaTime)
{
}

BoomEffect_Com * BoomEffect_Com::Clone()
{
	return new BoomEffect_Com(*this);
}

void BoomEffect_Com::AfterClone()
{
}

#include "ClientHeader.h"
#include "BugEffect_Com.h"

BugEffect_Com::BugEffect_Com()
{
}

BugEffect_Com::BugEffect_Com(const BugEffect_Com & CopyData)
	:UserComponent_Base(CopyData)
{
}

BugEffect_Com::~BugEffect_Com()
{
	SAFE_RELEASE(m_Animation);
	SAFE_RELEASE(m_Material);
}

bool BugEffect_Com::Init()
{
	m_Alpha = 1.0f;

	Renderer_Com* BugEffectRender = m_Object->AddComponent<Renderer_Com>("BugEffect");
	BugEffectRender->SetMesh("TextureRect");
	BugEffectRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(BugEffectRender);

	m_Transform->SetWorldScale(128.0f, 128.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	m_Material->SetDiffuseTexture(0, "BugEffect", TEXT("Monster\\bloodParticles.png"));
	m_Material->SetMaterial(Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, 1.0f));

	m_Animation = m_Object->AddComponent<Animation2D_Com>("BugEffectAni");
	
	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};
	for (int i = 0; i < 8; ++i)
	{
		tFrame.LeftTop = Vector2(1024.0f + i * 128.0f, 1536.0f);
		tFrame.RightBottom = Vector2(1024.0f + (i + 1) * 128.0f, 1664.0f);
		vecClipFrame.push_back(tFrame);
	}

	m_Animation->AddClip("BugEffect", A2D_ATLS, AO_ONCE_STOP, 0.7f, vecClipFrame, "BugEffect", L"Monster\\bloodParticles.png");
	vecClipFrame.clear();

	m_Animation->ChangeClip("BugEffect");

	return true;
}

int BugEffect_Com::Input(float DeltaTime)
{
	return 0;
}

int BugEffect_Com::Update(float DeltaTime)
{
	m_Alpha -= DeltaTime;

	m_Material->SetMaterial(Vector4(83.0f / 255.0f, 170.0f / 255.0f, 185.0f / 255.0f, m_Alpha));

	if (m_Alpha <= 0.0f)
	{
		m_Object->SetIsActive(false);
		SetIsActive(false);
	}

	return 0;
}

int BugEffect_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void BugEffect_Com::Collision(float DeltaTime)
{
}

void BugEffect_Com::CollisionLateUpdate(float DeltaTime)
{
}

void BugEffect_Com::Render(float DeltaTime)
{
}

BugEffect_Com * BugEffect_Com::Clone()
{
	return new BugEffect_Com(*this);
}

void BugEffect_Com::AfterClone()
{
}

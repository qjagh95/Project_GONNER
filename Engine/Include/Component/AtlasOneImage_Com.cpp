#include "stdafx.h"
#include "AtlasOneImage_Com.h"

#include "../Resource/Texture.h"

JEONG_USING

AtlasOneImage_Com::AtlasOneImage_Com()
{
}


AtlasOneImage_Com::AtlasOneImage_Com(const AtlasOneImage_Com & CopyData)
	:Component_Base(CopyData)
{
}

AtlasOneImage_Com::~AtlasOneImage_Com()
{
}

bool AtlasOneImage_Com::Init()
{
	Renderer_Com* OneImageRender = m_Object->AddComponent<Renderer_Com>("LogoRender");
	OneImageRender->SetMesh("TextureRect");
	OneImageRender->SetRenderState(ALPHA_BLEND);
	//OneImageRender->SetShader(ATLASONE_SHADER);
	OneImageRender->SetScreenRender(true);
	OneImageRender->CreateRendererCBuffer("AtlasOneCBuffer", sizeof(AtlasOneCBuffer));

	SAFE_RELEASE(OneImageRender);
	return true;
}

int AtlasOneImage_Com::Input(float DeltaTime)
{
	return 0;
}

int AtlasOneImage_Com::Update(float DeltaTime)
{
	return 0;
}

int AtlasOneImage_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void AtlasOneImage_Com::Collision(float DeltaTime)
{
}

void AtlasOneImage_Com::CollisionLateUpdate(float DeltaTime)
{
}

void AtlasOneImage_Com::Render(float DeltaTime)
{
}

AtlasOneImage_Com * AtlasOneImage_Com::Clone()
{
	return new AtlasOneImage_Com(*this);
}

void AtlasOneImage_Com::AfterClone()
{
}

void AtlasOneImage_Com::SetAtlas(const string & FileName, const Vector4& CutRect)
{
	Material_Com* OneImageMat = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	OneImageMat->SetDiffuseTexture(0, FileName, CA2W(FileName.c_str()));

	Texture* newTex = ResourceManager::Get()->FindTexture(FileName);
	
	Vector2 ImageSize;
	ImageSize.x = (float)newTex->GetWidth();
	ImageSize.y = (float)newTex->GetHeight();

	m_CBuffer.LeftTopUV.x = CutRect.x / ImageSize.x;
	m_CBuffer.LeftTopUV.y = CutRect.y / ImageSize.y;
	m_CBuffer.RightBottomUV.x = CutRect.z / ImageSize.x;
	m_CBuffer.RightBottomUV.y = CutRect.w / ImageSize.y;

	SAFE_RELEASE(newTex);
	SAFE_RELEASE(OneImageMat);
}

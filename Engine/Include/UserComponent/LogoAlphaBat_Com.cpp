#include "stdafx.h"
#include "LogoAlphaBat_Com.h"

JEONG_USING

LogoAlphaBat_Com::LogoAlphaBat_Com()
	:m_ChangeTime(0.15f), m_TimeVar(0.0f), m_isReturn(false), m_AlphaAngle(0.0f), m_Count(0)
{
}

LogoAlphaBat_Com::LogoAlphaBat_Com(const LogoAlphaBat_Com & CopyData)
	:UserComponent_Base(CopyData)
{

}

LogoAlphaBat_Com::~LogoAlphaBat_Com()
{
}

bool LogoAlphaBat_Com::Init()
{
	Renderer_Com* AlphabatRender = m_Object->AddComponent<Renderer_Com>("AlphabatRender");
	AlphabatRender->SetMesh("TextureRect");
	AlphabatRender->SetRenderState(ALPHA_BLEND);
	AlphabatRender->SetShader(ALPHABAT_SHADER);
	AlphabatRender->SetScreenRender(true);
	AlphabatRender->CreateRendererCBuffer("AlphaBatCBuffer", sizeof(AlphaBatCBuffer));
	SAFE_RELEASE(AlphabatRender);

	m_Transform->SetWorldScale(150.0f, 300.0f, 1.0f);
	m_CBuffer.Light = Vector4::White;


	return true;
}

int LogoAlphaBat_Com::Input(float DeltaTime)
{
	return 0;
}

int LogoAlphaBat_Com::Update(float DeltaTime)
{
	m_TimeVar += DeltaTime;

	if (m_TimeVar > m_ChangeTime)
	{
		Material_Com* getMat = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);

		m_TimeVar = 0.0f;

		int Ran = rand() % 3;

		switch (Ran)
		{
			case 0:
				m_CBuffer.Light = Vector4(76.0f / 255.0f, 181.0f / 255.0f, 147.0f / 255.0f, 255.0f / 255.0f);
				break;
			case 1:
				m_CBuffer.Light = Vector4(76.0f / 255.0f, 159.0f / 255.0f, 170.0f / 255.0f, 255.0f / 255.0f);
				break;
			case 2:
				m_CBuffer.Light = Vector4(76.0f / 255.0f, 168.0f / 255.0f, 160.0f / 255.0f, 255.0f / 255.0f);
				break;
		}

		SAFE_RELEASE(getMat);
	}

	if (m_Transform->GetWorldRotationZ() <= -2.0f)
	{
		m_isReturn = true;
	}
	else if (m_Transform->GetWorldRotationZ() >= 2.0f)
	{
		m_isReturn = false;
		m_Count++;
	}

	if (m_isReturn == true)
		m_Transform->RotationZ(20.0f, DeltaTime);
	else
		m_Transform->RotationZ(20.0f, -DeltaTime);

	if (m_Count >= 5)
	{
		m_AlphaAngle += 0.4f * DeltaTime;

		m_CBuffer.RangeX = m_AlphaAngle;
		m_CBuffer.RangeY = m_AlphaAngle;
	}

	return 0;
}

int LogoAlphaBat_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void LogoAlphaBat_Com::Collision(float DeltaTime)
{
}

void LogoAlphaBat_Com::CollisionLateUpdate(float DeltaTime)
{
}

void LogoAlphaBat_Com::Render(float DeltaTime)
{
	Renderer_Com* getRender = m_Object->FindComponentFromType< Renderer_Com>(CT_RENDER);

	getRender->UpdateRendererCBuffer("AlphaBatCBuffer", &m_CBuffer, sizeof(AlphaBatCBuffer));

	SAFE_RELEASE(getRender);
}

LogoAlphaBat_Com * LogoAlphaBat_Com::Clone()
{
	return new LogoAlphaBat_Com(*this);
}

void LogoAlphaBat_Com::AfterClone()
{
}

void LogoAlphaBat_Com::SetLogoAlphaBat(LOGO_ALPHABAT Data)
{
	Material_Com* getMat = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	getMat->SetDiffuseTexture(1, "CircleAlpha", TEXT("CircleAlphaMap.png"));

	switch (Data)
	{
		case LA_A:
			getMat->SetDiffuseTextureFromFullPath(0 ,"AlphaBatA", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 5));
			break;
		case LA_R:
			getMat->SetDiffuseTextureFromFullPath(0, "AlphaBatR", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 6));
			break;
		case LA_T:
			getMat->SetDiffuseTextureFromFullPath(0, "AlphaBatT", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 7));
			break;
		case LA_I:
			getMat->SetDiffuseTextureFromFullPath(0, "AlphaBatI", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 1));
			break;
		case LA_N:
			getMat->SetDiffuseTextureFromFullPath(0, "AlphaBatN", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 2));
			break;
		case LA_H:
			getMat->SetDiffuseTextureFromFullPath(0, "AlphaBatH", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 3));
			break;
		case LA_E:
			getMat->SetDiffuseTextureFromFullPath(0, "AlphaBatE", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 4));
			break;
		case LA_SPACAL:
			getMat->SetDiffuseTextureFromFullPath(0, "AlphaBatS", ExcelManager::Get()->ReadStringData("LogoFileName", 0, 0));
			break;
	}

	SAFE_RELEASE(getMat);
}

void LogoAlphaBat_Com::SetAlphaBatColor(const Vector4 & Color)
{
	Material_Com* getMat = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	getMat->SetMaterial(Color);
	SAFE_RELEASE(getMat);
}

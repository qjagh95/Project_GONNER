#include "stdafx.h"
#include "Number_Com.h"

JEONG_USING

Number_Com::Number_Com()
{
	m_Number = 0;
}

Number_Com::~Number_Com()
{
}

Number_Com::Number_Com(const Number_Com & number)
	:Component_Base(number)
{
}

bool Number_Com::Init()
{
	m_Number = 1;

	Renderer_Com* pRenderer = m_Object->AddComponent<Renderer_Com>("NumberRenderer");
	pRenderer->SetMesh("TextureRect");
	pRenderer->SetRenderState(ALPHA_BLEND);
	pRenderer->SetScreenRender(true);
	SAFE_RELEASE(pRenderer);

	Material_Com* pMaterial = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	pMaterial->SetMaterial(Vector4::White);

	SAFE_RELEASE(pMaterial);

	m_Transform->SetWorldScale(49.0f, 54.0f, 0.f);

	return true;
}

int Number_Com::Input(float DeltaTime)
{
	return 0;
}

int Number_Com::Update(float DeltaTime)
{
	return 0;
}

int Number_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

Number_Com * Number_Com::Clone()
{
	return new Number_Com(*this);
}

void Number_Com::SetNumber(int Number)
{
 	m_Number = Number;
	Material_Com* getMaterial = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);

	string TagName = "Number" + to_string(Number);
	wstring FileName = L"Number\\default-" + to_wstring(Number) + L".png";

	getMaterial->SetDiffuseTexture(0, TagName, FileName.c_str());
	SAFE_RELEASE(getMaterial);
	
	m_Transform->SetWorldScale(49.0f, 54.0f, 0.0f);
}

void Number_Com::SetNumberPos(const Vector3& Pos)
{
	m_Transform->SetWorldPos(Pos);
}

void Number_Com::SetNumberPivot(const Vector3& Pivot)
{
	m_Transform->SetWorldPivot(Pivot);
}
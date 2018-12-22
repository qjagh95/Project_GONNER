#include "stdafx.h"
#include "TileImage_Com.h"

JEONG_USING

bool JEONG::TileImage_Com::m_isEditorMode = false;

JEONG::TileImage_Com::TileImage_Com()
{
	m_ComType = CT_TILEIMAGE;
	m_Material = NULLPTR;
	m_Renderer = NULLPTR;
	m_NearObject = NULLPTR;
	m_NearMaterial = NULLPTR;

	m_ColorChangeTime = 0.0f;
	m_ColorChangeTimeVar = 0.0f;
	m_InputDistance = 0.0f;
}

JEONG::TileImage_Com::TileImage_Com(const TileImage_Com & CopyData)
	:Component_Base(CopyData)
{
}

JEONG::TileImage_Com::~TileImage_Com()
{
	SAFE_RELEASE(m_Material);
	SAFE_RELEASE(m_Renderer);
}

bool JEONG::TileImage_Com::Init()
{
	m_Renderer = m_Object->AddComponent<Renderer_Com>("TileImageRender");
	m_Renderer->SetMesh("TextureRect");
	m_Renderer->SetRenderState(ALPHA_BLEND);
	m_Renderer->SetShader(TILEIMAGE_SHADER);
	m_Renderer->CreateRendererCBuffer("TileImageCBuffer", sizeof(TileImageCBuffer));

	m_Material = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);

	m_Distance = 350.0f;
	m_Transform->SetWorldPivot(0.0f, -0.5f, 0.0f);
	
	if(m_isEditorMode == false)
		m_Transform->SetWorldScale(Vector3(0.0f, 0.0f, 1.0f));
	else
		m_Transform->SetWorldScale(Vector3(128.0f, 128.0f, 1.0f));

	m_ScaleVar = Vector3(128.0f, 128.0f, 1.0f);

	int RanNum = RandomRange(1, 4);

	switch (RanNum)
	{
		case 1:
			m_ColorChangeTime = 0.2f;
			break;
		case 2:
			m_ColorChangeTime = 0.3f;
			break;
		case 3:
			m_ColorChangeTime = 0.4f;
			break;
		case 4:
			m_ColorChangeTime = 0.5f;
			break;
	}

	m_CBuffer.Light = Vector4::White;
	m_CBuffer.ColorPercent = Vector4::White;
	return true;
}

int JEONG::TileImage_Com::Input(float DeltaTime)
{
	return 0;
}

int JEONG::TileImage_Com::Update(float DeltaTime)
{
	if (m_NearMaterial != NULLPTR)
	{
		if(m_NearMaterial->GetMateralEmpty() == false)
			m_Material->SetMaterial(m_NearMaterial->GetDiffuseLight());
	}

	m_ColorChangeTimeVar += DeltaTime;

	if (m_ColorChangeTimeVar >= m_ColorChangeTime)
	{
		m_ColorChangeTimeVar = 0.0f;

		if (m_CBuffer.Light == Vector4::One)
			m_CBuffer.Light = Vector4(1.1f, 1.1f, 1.1f, 1.1f);
		else
			m_CBuffer.Light = Vector4::One;
	}
	
	if (m_isEditorMode == false)
	{
		if (m_isMove == true)
		{
			Vector2 Scale = Vector2(m_Object->GetTransform()->GetWorldScale().x, m_Object->GetTransform()->GetWorldScale().y);
			m_Object->GetTransform()->SetWorldPivot(0.0f, -0.5f, 0.0f);

			if (Scale.x <= m_ScaleVar.x && Scale.y <= m_ScaleVar.y)
				m_Object->GetTransform()->AddScaleXY(500.0f, DeltaTime);
		}
		else
		{
			Vector2 Scale = Vector2(m_Object->GetTransform()->GetWorldScale().x, m_Object->GetTransform()->GetWorldScale().y);

			if (Scale.x > 0.0f && Scale.y > 0.0f)
			{
				m_Object->GetTransform()->SetWorldPivot(0.0f, -0.4f, 0.0f);
				m_Object->GetTransform()->AddScaleXY(-500.0f, DeltaTime);
			}
			else
				m_Object->GetTransform()->SetWorldScale(Vector3(0.0f, 0.0f, 1.0f));
		}
	}
	
	return 0;
}

int JEONG::TileImage_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void JEONG::TileImage_Com::Collision(float DeltaTime)
{
}

void JEONG::TileImage_Com::CollisionLateUpdate(float DeltaTime)
{
}

void JEONG::TileImage_Com::Render(float DeltaTime)
{
 	m_Renderer->UpdateRendererCBuffer("TileImageCBuffer", &m_CBuffer, sizeof(TileImageCBuffer));
}

JEONG::TileImage_Com * JEONG::TileImage_Com::Clone()
{
	return new JEONG::TileImage_Com(*this);
}

void JEONG::TileImage_Com::AfterClone()
{
}

void JEONG::TileImage_Com::Save(BineryWrite & Writer)
{
	Component_Base::Save(Writer);

	Writer.WriteData(m_Distance);
	Writer.WriteData(m_Transform->GetWorldPos());
	Writer.WriteData(m_Transform->GetWorldScale());
}

void JEONG::TileImage_Com::Load(BineryRead & Reader)
{
	Component_Base::Load(Reader);

	Reader.ReadData(m_Distance);

	Vector3 Pos;
	Vector3 Scale;

	Reader.ReadData(Pos);
	Reader.ReadData(Scale);

	m_Transform->SetWorldPos(Pos);
}

void JEONG::TileImage_Com::SetTexture(const string& KeyName, wchar_t* FileName, const string & PathKey)
{
	Material_Com* getMaterial = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	getMaterial->SetDiffuseTexture(0, KeyName, FileName);
	
	SAFE_RELEASE(getMaterial);
}

void JEONG::TileImage_Com::SetDiffuseColor(const Vector4 & Color)
{
	Material_Com* getMaterial = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	getMaterial->SetMaterial(Color);

	SAFE_RELEASE(getMaterial);
}

void JEONG::TileImage_Com::SetPercentColor(const Vector4 & Color)
{
	m_CBuffer.ColorPercent = Color;
}

void JEONG::TileImage_Com::SetNearObject(GameObject * NearObject, float Distance)
{
	m_InputDistance = Distance;

	if (m_InputDistance > m_Distance)
	{
		m_isMove = false;
		return;
	}
	else
	{
		m_isMove = true;

		if (m_isEditorMode == true)
			return;
		
		if (NearObject != NULLPTR)
		{
			m_NearObject = NearObject;
			m_NearMaterial = m_NearObject->FindComponentFromTypeNoneCount<Material_Com>(CT_MATERIAL);
		}
	}
}


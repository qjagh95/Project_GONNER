#include "stdafx.h"
#include "Tile2D_Com.h"
#include "TileImage_Com.h"

#include "../Resource/Mesh.h"
#include "../Render/Shader.h"

JEONG_USING

Tile2D_Com::Tile2D_Com()
	:m_Shader(NULLPTR), m_Mesh(NULLPTR), m_Layout(NULLPTR), m_TileImage(NULLPTR), m_TileImageObject(NULLPTR),
	m_Dir(0)
{
	m_ComType = CT_STAGE2D;
	SetTag("Stage2D");
	m_isLine = true;
}

Tile2D_Com::Tile2D_Com(const Tile2D_Com& CopyData)
	:Component_Base(CopyData)
{
	*this = CopyData;
}

Tile2D_Com::~Tile2D_Com()
{
	SAFE_RELEASE(m_Mesh);
	SAFE_RELEASE(m_Shader);
	SAFE_RELEASE(m_TileImage);
	SAFE_RELEASE(m_TileImageObject);

	Safe_Release_VecList(m_vecTileImage);
}

bool Tile2D_Com::Init()
{
	m_TileOption = T2D_NORMAL;

	m_Mesh = ResourceManager::Get()->FindMesh("ColliderRect");
	m_Shader = ShaderManager::Get()->FindShader(COLLIDER_SHADER);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_vecTileImage.resize(3);

	return true;
}

int Tile2D_Com::Input(float DeltaTime)
{
	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//{
	//	m_vecTileImage[i]->Input(DeltaTime);
	//}

	return 0;
}

int Tile2D_Com::Update(float DeltaTime)
{
	if (m_TileImageObject != NULLPTR)
		m_TileImageObject->Update(DeltaTime);

	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//{
	//	m_vecTileImage[i]->Update(DeltaTime);
	//}

	return 0;
}

int Tile2D_Com::LateUpdate(float DeltaTime)
{
	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//{
	//	m_vecTileImage[i]->LateUpdate(DeltaTime);
	//}
	return 0;
}

void Tile2D_Com::Collision(float DeltaTime)
{
	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//{
	//	m_vecTileImage[i]->Collision(DeltaTime);
	//}
}

void Tile2D_Com::CollisionLateUpdate(float DeltaTime)
{

	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//{
	//	m_vecTileImage[i]->CollisionLateUpdate(DeltaTime);
	//}
}

void Tile2D_Com::Render(float DeltaTime)
{
	if (m_TileImageObject != NULLPTR)
		m_TileImageObject->Render(DeltaTime);

	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//{
	//	m_vecTileImage[i]->Render(DeltaTime);
	//}

	if (m_isLine == false)
		return;

	TransformCBuffer tCBuffer = {};
	Camera_Com*	pMainCamera = m_Scene->GetMainCamera();

	tCBuffer.World = m_Transform->GetWorldMatrix();
	tCBuffer.View = pMainCamera->GetViewMatrix();
	tCBuffer.Projection = pMainCamera->GetProjection();
	tCBuffer.WV = tCBuffer.World * tCBuffer.View;
	tCBuffer.WVP = tCBuffer.WV * tCBuffer.Projection;
	tCBuffer.Pivot = Vector3::Zero;
	tCBuffer.Lenth = m_Mesh->GetLenth();

	tCBuffer.World.Transpose();
	tCBuffer.View.Transpose();
	tCBuffer.Projection.Transpose();
	tCBuffer.WV.Transpose();
	tCBuffer.WVP.Transpose();

	ShaderManager::Get()->UpdateCBuffer("Transform", &tCBuffer);

	Vector4	LineColor;
	switch (m_TileOption)
	{
		case T2D_NORMAL:
			LineColor = Vector4::Green;
			break;
		case T2D_NOMOVE:
			LineColor = Vector4::Red;
			break;
	}

	m_Shader->SetShader();
	{
		Device::Get()->GetContext()->IASetInputLayout(m_Layout);
		ShaderManager::Get()->UpdateCBuffer("Collider", &LineColor);
	}
	m_Mesh->Render();
}

Tile2D_Com * Tile2D_Com::Clone()
{
	return new Tile2D_Com(*this);
}

void Tile2D_Com::AfterClone()
{
}

void Tile2D_Com::Save(BineryWrite & Writer)
{
	Component_Base::Save(Writer);

	Writer.WriteData((int)m_TileType);
	Writer.WriteData((int)m_TileOption);
	Writer.WriteData(m_ImageFileName);
	Writer.WriteData(m_Dir);
	
	if (m_TileImage != NULLPTR)
		m_TileImage->Save(Writer);

	//Writer.WriteData(m_vecTileImage.size());

	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//	m_vecTileImage[i]->Save(Writer);

}

void Tile2D_Com::Load(BineryRead & Reader)
{
	Component_Base::Load(Reader);

	Reader.ReadData((int&)m_TileType);
	Reader.ReadData((int&)m_TileOption);

	SetTileType(m_TileType);
	switch (m_TileType)
	{
		case STT_TILE:
		{
			switch (m_TileOption)
			{
				case T2D_NORMAL:
					m_Mesh = ResourceManager::Get()->FindMesh("ColliderRect");
					break;
				case T2D_NOMOVE:
					m_Mesh = ResourceManager::Get()->FindMesh("TileNoMove");
					break;
			}
		}
		break;
		case STT_ISO:
		{
			switch (m_TileOption)
			{
				case T2D_NORMAL:
					m_Mesh = ResourceManager::Get()->FindMesh("IsoTileNomal");
					break;
				case T2D_NOMOVE:
					m_Mesh = ResourceManager::Get()->FindMesh("IsoTileNomove");
					break;
			}
		}
		break;
	}

	Reader.ReadData(m_ImageFileName);
	Reader.ReadData(m_Dir);

	SetMainTileImage(m_ImageFileName, m_Dir);

	if(m_TileImage != NULLPTR)
		m_TileImage->Load(Reader);

	//size_t SubImageSize;
	//Reader.ReadData(SubImageSize);

	//for (size_t i = 0; i < SubImageSize; i++)
	//{
	//	
	//}
}

void Tile2D_Com::SetTileType(STAGE2D_TILE_TYPE type)
{
	m_TileType = type;
	
	SAFE_RELEASE(m_Mesh);
	SAFE_RELEASE(m_Shader);

	switch (type)
	{
		case STT_TILE:
			m_Mesh = ResourceManager::Get()->FindMesh("ColliderRect");
			break;
		case STT_ISO:
			m_Mesh = ResourceManager::Get()->FindMesh("IsoTileNomal");
			break;
	}

	m_Shader = ShaderManager::Get()->FindShader(TILE_SHADER);
	m_Layout = ShaderManager::Get()->FindInputLayOut(POS_LAYOUT);
}

void Tile2D_Com::SetMesh(const string & KeyName)
{
	SAFE_RELEASE(m_Mesh);

	m_Mesh = ResourceManager::Get()->FindMesh(KeyName);
}

void Tile2D_Com::SetWorldPos(const Vector3 & Pos)
{
	m_Transform->SetWorldPos(Pos);
	m_TileImage->GetTransform()->SetWorldPos(Pos);

	//for (size_t i = 0; i < m_vecTileImage.size(); i++)
	//	m_vecTileImage[i]->GetTransform()->SetWorldPos(Pos);
}

void Tile2D_Com::SetMainTileImage(const string& FileName, int Dir)
{
	m_Dir = Dir;
	m_ImageFileName = FileName;

	if (FileName.empty() == true)
	{
		if (m_TileImage != NULLPTR && m_TileImageObject != NULLPTR)
		{
			m_TileImage->SetIsActive(false);
			m_TileImageObject->SetIsActive(false);
		}
		
		SAFE_RELEASE(m_TileImage);
		SAFE_RELEASE(m_TileImageObject);
		return;
	}

	SAFE_RELEASE(m_TileImage);
	SAFE_RELEASE(m_TileImageObject);

	m_TileImageObject = GameObject::CreateObject("TileImageObject");
	m_TileImage = m_TileImageObject->AddComponent<TileImage_Com>("TileImage");
	m_TileImageObject->SetScene(m_Scene);
	m_TileImageObject->SetLayer(m_Layer);

	m_TileImage->SetTexture(FileName, CA2W(FileName.c_str()));

	Vector3 TilePos = m_Transform->GetWorldPos();
	Vector3 TileScale = m_Transform->GetWorldScale();

	m_TileImageObject->GetTransform()->SetWorldPos(TilePos);

	switch (Dir)
	{
		case 90:
			m_TileImageObject->GetTransform()->SetWorldRotZ(-90.0f);
			m_TileImageObject->GetTransform()->SetWorldPos(TilePos.x, TilePos.y + TileScale.y, 0.0f);
			m_TileImage->SetDistance(300.0f);
			break;
		case -90:
			m_TileImageObject->GetTransform()->SetWorldRotZ(90.0f);
			m_TileImageObject->GetTransform()->SetWorldPos(TilePos.x + TileScale.x, TilePos.y, 0.0f);
			m_TileImage->SetDistance(200.0f);
			break;
		case 180:
			m_TileImageObject->GetTransform()->SetWorldRotZ(180.0f);
			m_TileImageObject->GetTransform()->SetWorldPos(TilePos.x + TileScale.x, TilePos.y + TileScale.y, 0.0f);
			m_TileImage->SetDistance(100.0f);
			break;
	}
}

void Tile2D_Com::SetSubTileImage(size_t ImageCount)
{
	string Path = PathManager::Get()->FindPathMultiByte(TEXTURE_PATH);
	Path += m_ImageFileName;

	for (size_t i = 0; i < ImageCount; i++)
	{
		GameObject* newImageObject = GameObject::CreateObject("TileImageObject");
		TileImage_Com* newImage = newImageObject->AddComponent<TileImage_Com>("TileImage");
		newImageObject->SetScene(m_Scene);
		newImageObject->SetLayer(m_Layer);

		Vector3 TilePos = m_Transform->GetWorldPos();
		Vector3 TileScale = m_Transform->GetWorldScale();

		newImage->SetTexture(m_ImageFileName, CA2W(Path.c_str()));

		float RandomAngle = (float)(RandomRange(-45, 45));

		switch (m_Dir)
		{
			case 0:
			{
				Vector3 rRange = Vector3(TilePos.x, (float)RandomRange((int)TilePos.y, (int)(TilePos.y - TileScale.y)), 0.0f);

				newImageObject->GetTransform()->SetWorldPos(TilePos.x, TilePos.y + TileScale.y, 0.0f);
				newImageObject->GetTransform()->SetWorldRotZ(RandomAngle);
			}
				break;
			case 90:
			{
				//Vector3 rRange = Vector3((float)RandomRange((int)TilePos.x, (int)(TilePos.x - TileScale.x)), TilePos.y + TileScale.y, 0.0f);

				//newImageObject->GetTransform()->SetWorldRotZ(-90.0f + RandomAngle);
				//newImageObject->GetTransform()->SetWorldPos(TilePos.x, TilePos.y + TileScale.y, 0.0f);

				//m_TileImage->SetDistance(300.0f);
			}
				break;
			case -90:
			{
				//Vector3 rRange = Vector3((float)RandomRange((int)(TilePos.x + TileScale.x), (int)(TilePos.x - TileScale.x)), TilePos.y + TileScale.y, 0.0f);

				//newImageObject->GetTransform()->SetWorldRotZ(90.0f + RandomAngle);
				//newImageObject->GetTransform()->SetWorldPos(TilePos.x + TileScale.x, TilePos.y, 0.0f);

				//m_TileImage->SetDistance(200.0f);
			}
				break;
			case 180:
			{
				//Vector3 rRange = Vector3(TilePos.x + TileScale.x, (float)RandomRange((int)TilePos.y, (int)(TilePos.y + TileScale.y)), 0.0f);

				//newImageObject->GetTransform()->SetWorldRotZ(180.0f + RandomAngle);
				//newImageObject->GetTransform()->SetWorldPos(TilePos.x + TileScale.x, TilePos.y + TileScale.y, 0.0f);

				//m_TileImage->SetDistance(100.0f);
			}
				break;
		}

		m_vecTileImage.push_back(newImage);
		SAFE_RELEASE(newImageObject);
	}
}
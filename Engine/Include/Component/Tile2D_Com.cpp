#include "stdafx.h"
#include "Tile2D_Com.h"
#include "TileImage_Com.h"

#include "../Resource/Mesh.h"
#include "../Render/Shader.h"

JEONG_USING

Tile2D_Com::Tile2D_Com()
{
	m_ComType = CT_STAGE2D;
	SetTag("Stage2D");
	m_isLine = true;
	m_TileOption = {};
	m_TileType = {};
	m_Shader = NULLPTR;
	m_Mesh = NULLPTR;
	m_Layout = NULLPTR;
	m_TileImageObject = NULLPTR;
	m_TileImage = NULLPTR;
	m_NearObject = NULLPTR;
	m_NearMaterial = NULLPTR;
	m_DefaultLayer = NULLPTR;
	m_Dir = 1;
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
	SAFE_RELEASE(m_DefaultLayer);

	Safe_Release_VecList(m_vecTileImage);
	Safe_Release_VecList(m_vecImage);
}

bool Tile2D_Com::Init()
{
	m_TileOption = T2D_NORMAL;

	m_Mesh = ResourceManager::Get()->FindMesh("ColliderRect");
	m_Shader = ShaderManager::Get()->FindShader(COLLIDER_SHADER);

	m_Transform->SetWorldPivot(0.5f, 0.5f, 0.0f);
	m_vecTileImage.reserve(4);

	m_DefaultLayer = m_Scene->FindLayer("Default");

	return true;
}

int Tile2D_Com::Input(float DeltaTime)
{
	if (m_NearObject != NULLPTR && m_NearObject->GetIsActive() == false)
		m_NearObject = NULLPTR;

	return 0;
}

int Tile2D_Com::Update(float DeltaTime)
{
	if (m_NearObject != NULLPTR && m_NearObject->GetIsActive() == false)
		m_NearObject = NULLPTR;

	if (m_TileImageObject != NULLPTR)
	{
		m_TileImageObject->Update(DeltaTime);

		for (size_t i = 0; i < m_vecTileImage.size(); i++)
			m_vecTileImage[i]->Update(DeltaTime);
	}
	return 0;
}

int Tile2D_Com::LateUpdate(float DeltaTime)
{

	return 0;
}

void Tile2D_Com::Collision(float DeltaTime)
{
}

void Tile2D_Com::CollisionLateUpdate(float DeltaTime)
{
	if (m_NearObject != NULLPTR && m_NearObject->GetIsActive() == false)
		m_NearObject = NULLPTR;
}

void Tile2D_Com::Render(float DeltaTime)
{
	if (m_NearObject != NULLPTR && m_NearObject->GetIsActive() == false)
		m_NearObject = NULLPTR;

	if (m_TileImageObject != NULLPTR)
	{
		float SrcDist = 0.0f;
		float DestDist = 0.0f;

		//가까운놈 탐색한다.
		list<GameObject*>::const_iterator StartIter = m_DefaultLayer->m_ObjectList.begin();
		list<GameObject*>::const_iterator EndIter = m_DefaultLayer->m_ObjectList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			if (m_NearObject == NULLPTR)
				m_NearObject = *StartIter;

			//(야매코드)
			//Near가 삭제된 오브젝트를 가르키고 있을 수 있기때문에 쓰레기값 예외처리
			if(m_NearObject->GetComponentSize() >= 20)
				m_NearObject = *StartIter;

			Vector3 src = m_NearObject->GetTransform()->GetWorldPos();
			Vector3 dest = (*StartIter)->GetTransform()->GetWorldPos();

			SrcDist = src.GetDistance(m_TileImageObject->GetTransform()->GetWorldPos());
			DestDist = dest.GetDistance(m_TileImageObject->GetTransform()->GetWorldPos());

			if (SrcDist >= DestDist)
				m_NearObject = *StartIter;

			m_TileImage->SetNearObject(m_NearObject, SrcDist);
		}

		m_TileImageObject->Render(DeltaTime);

		for (size_t i = 0; i < m_vecTileImage.size(); i++)
		{
			m_vecImage[i]->SetNearObject(m_NearObject, SrcDist);
			m_vecTileImage[i]->Render(DeltaTime);
		}
	}

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

	Writer.WriteData(m_vecImage.empty());

	if (m_vecImage.empty() == true)
		return;

	Writer.WriteData(m_vecImage.size());

	for (size_t i = 0; i < m_vecImage.size(); i++)
		m_vecImage[i]->Save(Writer);
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

	bool Temp;
	Reader.ReadData(Temp);

	if (Temp == true)
		return;

	size_t SubImageSize = 0;
	Reader.ReadData(SubImageSize);

	SetSubTileImage(m_ImageFileName ,SubImageSize);

	for (size_t i = 0; i < SubImageSize; i++)
		m_vecImage[i]->Load(Reader);
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
}

void Tile2D_Com::SetMainTileImage(const string& FileName, int Dir)
{
	m_Dir = Dir;
	m_ImageFileName = FileName;

	if (m_ImageFileName.empty() == true)
	{
		m_TileImage = NULLPTR;
		m_TileImageObject = NULLPTR;
		return;
	}

	SAFE_RELEASE(m_TileImage);
	SAFE_RELEASE(m_TileImageObject);

	m_TileImageObject = GameObject::CreateObject("TileImageObject");
	m_TileImage = m_TileImageObject->AddComponent<TileImage_Com>("TileImage");
	m_TileImageObject->SetScene(m_Scene);
	m_TileImageObject->SetLayer(m_Layer);

	m_TileImage->SetTexture(FileName, CA2W(FileName.c_str()));
	m_TileImage->SetDiffuseColor(Vector4::White);
	Vector3 TilePos = m_Transform->GetWorldPos();
	Vector3 TileScale = m_Transform->GetWorldScale();

	m_TileImageObject->GetTransform()->SetWorldPos(TilePos);
	m_TileImage->SetSavePos(TilePos);
	m_TileImage->SetDistance(500.0f);

	switch (Dir)
	{
		case 90:
			m_TileImageObject->GetTransform()->SetWorldPos(TilePos.x, TilePos.y + TileScale.y, 0.0f);
			m_TileImageObject->GetTransform()->SetWorldRotZ(-90.0f);
			break;
		case -90:
			m_TileImageObject->GetTransform()->SetWorldPos(TilePos.x + TileScale.x, TilePos.y, 0.0f);
			m_TileImageObject->GetTransform()->SetWorldRotZ(90.0f);
			break;
		case 180:
			m_TileImageObject->GetTransform()->SetWorldPos(TilePos.x + TileScale.x, TilePos.y + TileScale.y, 0.0f);
			m_TileImageObject->GetTransform()->SetWorldRotZ(180.0f);
			break;
	}
}

void Tile2D_Com::SetSubTileImage(const string& FileName, size_t ImageCount)
{
	if (m_TileImage == NULLPTR || m_ImageFileName.empty() == true)
		return;

	if (FileName != m_ImageFileName)
		m_ImageFileName = FileName;

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

		newImage->SetDiffuseColor(m_TileImage->GetMaterial()->GetDiffuseLight());
		newImage->SetTexture(m_ImageFileName, CA2W(Path.c_str()));

		switch (i)
		{
			case 0:
				newImage->SetDistance(350.0f);
				newImage->SetPercentColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
				break;
			case 1:
				newImage->SetDistance(250.0f);
				newImage->SetPercentColor(Vector4(0.5f, 0.5f, 0.5f, 1.0f));
				break;
			case 2:
				newImage->SetDistance(200.0f);
				newImage->SetPercentColor(Vector4(0.4f, 0.4f, 0.4f, 1.0f));
				break;
			case 3:
				newImage->SetDistance(150.0f);
				newImage->SetPercentColor(Vector4(0.3f, 0.3f, 0.3f, 1.0f));
				break;
		}

		float RandomAngle = (float)(RandomRange(-20, 20));

		switch (m_Dir)
		{
			case 0:
			{
				Vector3 rRange = Vector3(TilePos.x, (float)RandomRange((int)(TilePos.y - TileScale.y + 50.0f), (int)TilePos.y), 0.0f);

				newImageObject->GetTransform()->SetWorldPos(TilePos.x, rRange.y, 0.0f);
				newImageObject->GetTransform()->SetWorldRotZ(RandomAngle);
				newImage->SetSavePos(rRange);
			}
				break;
			case 90:
			{
				Vector3 rRange = Vector3((float)RandomRange((int)TilePos.x, (int)(TilePos.x - (TileScale.x / 2.0f))), TilePos.y + TileScale.y, 0.0f);
				
				newImageObject->GetTransform()->SetWorldRotZ(-90.0f + RandomAngle);
				newImageObject->GetTransform()->SetWorldPos(rRange.x , TilePos.y + TileScale.y , 0.0f);

				newImage->SetSavePos(rRange);
			}
				break;
			case -90:
			{
				int RandomPos = RandomRange(0, (int)TileScale.x);

				newImageObject->GetTransform()->SetWorldRotZ(90.0f + RandomAngle);
				newImageObject->GetTransform()->SetWorldPos(TilePos.x + RandomPos, TilePos.y, 0.0f);

				newImage->SetSavePos(newImageObject->GetTransform()->GetWorldPos());
			}
				break;
			case 180:
			{
				int RandomPosX = RandomRange(0, (int)TileScale.x);
				int RandomPosY = RandomRange((int)TileScale.y, (int)TileScale.y * 2);

				newImageObject->GetTransform()->SetWorldRotZ(180.0f + RandomAngle);
				newImageObject->GetTransform()->SetWorldPos(TilePos.x + RandomPosX, TilePos.y + RandomPosY, 0.0f);

				newImage->SetSavePos(newImageObject->GetTransform()->GetWorldPos());
			}
				break;
		}

		m_vecTileImage.push_back(newImageObject);
		m_vecImage.push_back(newImage);
	}
}

GameObject * Tile2D_Com::GetSubTileImageObject(size_t index) const
{
	if (m_vecTileImage.empty())
		return NULLPTR;

	return m_vecTileImage[index];
}

void Tile2D_Com::ClearSubImage()
{
	for (size_t i = 0; i < m_vecTileImage.size(); i++)
		m_vecTileImage[i]->SetIsActive(false);
	
	for (size_t i = 0; i < m_vecImage.size(); i++)
		m_vecImage[i]->SetIsActive(false);

	Safe_Release_VecList(m_vecImage);
	Safe_Release_VecList(m_vecTileImage);

	m_vecImage.clear();
	m_vecTileImage.clear();

	m_ImageFileName.clear();
}

void Tile2D_Com::ClearMainImage()
{
	if (m_TileImage != NULLPTR && m_TileImageObject != NULLPTR)
	{
		m_TileImage->SetIsActive(false);
		m_TileImageObject->SetIsActive(false);
	}

	SAFE_RELEASE(m_TileImage);
	SAFE_RELEASE(m_TileImageObject);
}

void Tile2D_Com::ClearNearObject()
{
	m_NearObject = NULLPTR;
}

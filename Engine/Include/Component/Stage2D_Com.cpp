#include "stdafx.h"
#include "Stage2D_Com.h"
#include "Tile2D_Com.h"

JEONG_USING

JEONG::Stage2D_Com::Stage2D_Com()
	:m_vecTile2DCom(NULLPTR), m_vecTileObject(NULLPTR),
	m_TileObjectCapacity(10), m_TileObjectSize(0),m_Tile2DComCapacity(10), m_Tile2DComSize(0)
{
	m_ComType = CT_TILE2D;
	SetTag("Stage2D");
	m_isLineOn = true;
}

JEONG::Stage2D_Com::Stage2D_Com(const Stage2D_Com& CopyData)
	:Component_Base(CopyData)
{
	*this = CopyData;
}

JEONG::Stage2D_Com::~Stage2D_Com()
{
	for (size_t i = 0; i < m_Tile2DComSize; i++)
		SAFE_RELEASE(m_vecTileObject[i]);
	for (size_t i = 0; i < m_Tile2DComSize; i++)
		SAFE_RELEASE(m_vecTile2DCom[i]);

	SAFE_DELETE_ARRARY(m_vecTile2DCom);
	SAFE_DELETE_ARRARY(m_vecTileObject);
}

bool JEONG::Stage2D_Com::Init()
{
	return true;
}

int JEONG::Stage2D_Com::Input(float DeltaTime)
{
	return 0;
}

int JEONG::Stage2D_Com::Update(float DeltaTime)
{
	Transform_Com* pMainCameraTr = m_Scene->GetMainCameraTransform();
	Vector3	CameraPos = pMainCameraTr->GetWorldPos();
	Vector3	EndPos;
	EndPos.x = CameraPos.x + Device::Get()->GetWinSize().Width;
	EndPos.y = CameraPos.y + Device::Get()->GetWinSize().Height;

	switch (m_TileType)
	{
		case STT_TILE:
		{
			CameraPos -= m_StartPos;
			CameraPos /= m_TileScale;

			EndPos /= m_TileScale;

			m_StartX = (int)CameraPos.x;
			m_StartY = (int)CameraPos.y;

			m_EndX = (int)EndPos.x + 1;
			m_EndY = (int)EndPos.y + 1;

			//m_StartX = m_StartX < 0 ? 0 : m_TileCountX - 1;
			//m_StartY = m_StartY < 0 ? 0 : m_TileCountY - 1;
			//m_EndX = m_EndX < 0 ? 0 : m_TileCountX - 1;
			//m_EndY = m_EndY < 0 ? 0 : m_TileCountY - 1;

			if (m_StartX < 0)
				m_StartX = 0;

			else if (m_StartX >= m_TileCountX)
				m_StartX = m_TileCountX;

			if (m_StartY < 0)
				m_StartY = 0;

			else if (m_StartY >= m_TileCountY)
				m_StartY = m_TileCountY;

			if (m_EndX < 0)
				m_EndX = 0;

			else if (m_EndX >= m_TileCountX)
				m_EndX = m_TileCountX;

			if (m_EndY < 0)
				m_EndY = 0;

			else if (m_EndY >= m_TileCountY)
				m_EndY = m_TileCountY;
		}
			break;
		case STT_ISO:
		{
			Vector2 LBIndex = GetIsoTileIndexVec(CameraPos);
			Vector2 LTIndex = GetIsoTileIndexVec(Vector3(CameraPos.x, EndPos.y, 0.0f));
			Vector2 RBIndex = GetIsoTileIndexVec(Vector3(EndPos.x, CameraPos.y, 0.0f));
			Vector2 RTIndex = GetIsoTileIndexVec(EndPos);

			m_StartX = clamp((int)LBIndex.x, 0, m_TileCountX);
			m_EndX = clamp((int)RTIndex.x, 0, m_TileCountX);
			m_StartY = clamp((int)RBIndex.y, 0, m_TileCountY);
			m_EndY = clamp((int)LTIndex.y, 0, m_TileCountY);
		}
			break;
	}

	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			int Index = y * m_TileCountX + x;
			m_vecTileObject[Index]->Update(DeltaTime);
		}
	}

	return 0;
}

int JEONG::Stage2D_Com::LateUpdate(float DeltaTime)
{
	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			int Index = y * m_TileCountX + x;
			m_vecTileObject[Index]->LateUpdate(DeltaTime);
		}
	}

	return 0;
}

void JEONG::Stage2D_Com::Collision(float DeltaTime)
{
}

void JEONG::Stage2D_Com::CollisionLateUpdate(float DeltaTime)
{
}

void JEONG::Stage2D_Com::Render(float DeltaTime)
{
	for (int y = m_StartY; y < m_EndY; ++y)
	{
		for (int x = m_StartX; x < m_EndX; ++x)
		{
			int Index = y * m_TileCountX + x;
			m_vecTileObject[Index]->Render(DeltaTime);
		}
	}
}

JEONG::Stage2D_Com * Stage2D_Com::Clone()
{
	return new Stage2D_Com(*this);
}

void JEONG::Stage2D_Com::AfterClone()
{
}

void JEONG::Stage2D_Com::Save(BineryWrite & Writer)
{
	Component_Base::Save(Writer);
	
	Writer.WriteData(m_TileCountX);
	Writer.WriteData(m_TileCountY);

	Writer.WriteData(m_TileScale);
	Writer.WriteData(m_StartPos);

	Writer.WriteData((int&)m_TileType);

	for (size_t i = 0; i < m_Tile2DComSize; ++i)
	{
		// Ÿ���� ũ��� ��ġ�� �����Ѵ�.
		Vector3	vScale = m_vecTile2DCom[i]->GetTransform()->GetWorldScale();
		Vector3	vPos = m_vecTile2DCom[i]->GetTransform()->GetWorldPos();

		Writer.WriteData(vScale);
		Writer.WriteData(vPos);

		m_vecTile2DCom[i]->Save(Writer);
	}
}

void JEONG::Stage2D_Com::Load(BineryRead & Reader)
{
	Component_Base::Load(Reader);

	Reader.ReadData(m_TileCountX);
	Reader.ReadData(m_TileCountY);

	Reader.ReadData(m_TileScale);
	Reader.ReadData(m_StartPos);

	Reader.ReadData((int&)m_TileType);

	m_Tile2DComCapacity = m_TileCountX * m_TileCountY;
	m_TileObjectCapacity = m_TileCountX * m_TileCountY;
	m_TileObjectSize = 0;
	m_Tile2DComSize = 0;

	m_vecTileObject = new GameObject*[m_TileObjectCapacity];
	m_vecTile2DCom = new Tile2D_Com*[m_Tile2DComCapacity];

	for (size_t y = 0; y < m_TileCountY; ++y)
	{
		for (size_t x = 0; x < m_TileCountX; x++)
		{
			size_t Index = y * m_TileCountX + x;

			GameObject*	newTileObject = GameObject::CreateObject("TileObject");
			newTileObject->SetScene(m_Scene);
			newTileObject->SetLayer(m_Layer);

			Transform_Com*	TileTransform = newTileObject->GetTransform();

			Vector3	vScale;
			Vector3	vPos;

			Reader.ReadData(vScale);
			Reader.ReadData(vPos);

			TileTransform->SetWorldScale(vScale);
			TileTransform->SetWorldPos(vPos);

			Tile2D_Com*	newTileCom = newTileObject->AddComponent<Tile2D_Com>("Tile");
			newTileCom->Load(Reader);

			m_vecTileObject[Index] = newTileObject;
			m_vecTile2DCom[Index] = newTileCom;

			m_TileObjectSize++;
			m_Tile2DComSize++;
		}
	}
}

int JEONG::Stage2D_Com::GetTileIndex(const Vector3 & Pos)
{
	switch (m_TileType)
	{
		case STT_TILE:
			return GetRectTileIndex(Pos);
			break;
		case STT_ISO:
			return GetIsoTileIndex(Pos);
			break;
	}
	return -1;
}

void JEONG::Stage2D_Com::CreateTileMap(int TileCountX, int TileCountY, const Vector3& StartPos, const Vector3& TileScale, STAGE2D_TILE_TYPE tileType, const string& KeyName, const TCHAR* FileName, const string& PathKey)
{
	m_StartPos = StartPos;
	m_TileCountX = TileCountX;
	m_TileCountY = TileCountY;

	m_TileObjectCapacity = TileCountX * TileCountY;
	m_Tile2DComCapacity = TileCountX * TileCountY;

	m_vecTileObject = new GameObject*[m_TileObjectCapacity];
	m_vecTile2DCom = new Tile2D_Com*[m_Tile2DComCapacity];

	m_TileScale = TileScale;
	m_TileType = tileType;

	//ȭ�� ��üũ��� �ø���.
	Vector3 SumScale;
	SumScale.x = TileScale.x * TileCountX;
	SumScale.y = TileScale.y * TileCountY;
	SumScale.z = 1.0f;

	m_Transform->SetWorldPos(StartPos);

	switch (tileType)
	{
		case STT_TILE:
			CreateTile(StartPos, TileScale, KeyName, FileName, PathKey);
			break;
		case STT_ISO:
			CreateIsoTile(StartPos, TileScale, KeyName, FileName, PathKey);
			break;
	}

}

void JEONG::Stage2D_Com::ClearImage()
{
	ClearMainImage();
	ClearSubImage();
}

void JEONG::Stage2D_Com::ClearSubImage()
{
	for (size_t i = 0; i < m_Tile2DComSize; i++)
		m_vecTile2DCom[i]->ClearSubImage();
}

void JEONG::Stage2D_Com::ClearMainImage()
{
	for (size_t i = 0; i < m_Tile2DComSize; i++)
		m_vecTile2DCom[i]->ClearMainImage();
}

void JEONG::Stage2D_Com::CreateTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName, const TCHAR* FileName, const string& PathKey)
{
	for (int y = 0; y < m_TileCountY; ++y)
	{
		for (int x = 0; x < m_TileCountX; ++x)
		{
			//�ε�������
			int	Index = y * m_TileCountX + x;

			GameObject*	newTileObject = GameObject::CreateObject("TileObject");
			newTileObject->SetScene(m_Scene);
			newTileObject->SetLayer(m_Layer);

			Tile2D_Com*	pTile = newTileObject->AddComponent<Tile2D_Com>("Tile");
			pTile->SetTileType(STT_TILE);
			pTile->SetLineOn(m_isLineOn);
			pTile->SetMesh("ColliderRect");

			Transform_Com*	pTransform = newTileObject->GetTransform();
			pTransform->SetWorldScale(TileScale);

			Vector3	vPos = StartPos + TileScale * Vector3((float)x, (float)y, 1.0f);
			pTransform->SetWorldPos(vPos);

			if (FileName != NULLPTR)
			{
				Renderer_Com* pRenderer = newTileObject->AddComponent<Renderer_Com>("Renderer");
				pRenderer->SetMesh("TextureRect");
				pRenderer->SetRenderState(ALPHA_BLEND);
				SAFE_RELEASE(pRenderer);

				Material_Com* pMaterial = newTileObject->AddComponent<Material_Com>("Material");
				pMaterial->SetDiffuseTexture(0, KeyName, FileName, PathKey);
				SAFE_RELEASE(pMaterial);
			}

			m_vecTileObject[Index] = newTileObject;
			m_vecTile2DCom[Index] = pTile;

			if (m_TileObjectSize == m_TileObjectCapacity)
			{
				m_TileObjectCapacity *= 2;

				GameObject** newObject = new GameObject*[m_TileObjectCapacity];
				memcpy(newObject, m_vecTileObject, sizeof(m_vecTileObject) * m_TileObjectSize);
				SAFE_DELETE(m_vecTileObject);
				m_vecTileObject = newObject;
			}

			if (m_Tile2DComSize == m_Tile2DComCapacity)
			{
				m_Tile2DComCapacity *= 2;

				Tile2D_Com** newTile = new Tile2D_Com*[m_Tile2DComCapacity];
				memcpy(newTile, m_vecTile2DCom, sizeof(m_vecTile2DCom) * m_Tile2DComSize);
				SAFE_DELETE(m_vecTile2DCom);
				m_vecTile2DCom = newTile;
			}

			m_TileObjectSize++;
			m_Tile2DComSize++;
		}//for(x)
	}//for(y)
}

void JEONG::Stage2D_Com::CreateIsoTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName , const TCHAR* FileName, const string& PathKey)
{
	Vector3 sPos;
	sPos.x = (m_TileCountX * TileScale.x) * 0.5f;

	for (int y = 0; y < m_TileCountY; y++)
	{
		for (int x = 0; x < m_TileCountX; x++)
		{
			int Index = y * m_TileCountX + x;
			
			GameObject* newTileObject = GameObject::CreateObject("IsoTileObject");
			newTileObject->SetScene(m_Scene);
			newTileObject->SetLayer(m_Layer);

			Tile2D_Com*	pTile = newTileObject->AddComponent<Tile2D_Com>("IsoTile");
			pTile->SetTileType(STT_ISO);
			pTile->SetMesh("IsoTileNomal");
			pTile->SetLineOn(m_isLineOn);

			Transform_Com* pTransform = newTileObject->GetTransform();
			pTransform->SetWorldScale(TileScale);

			Vector3 tPos;
			tPos.x = sPos.x + (TileScale.x * 0.5f) * (x - y);
			tPos.y = sPos.y + (TileScale.y * 0.5f) * (x + y);

			//��ü�������� �߾ӿ������� �����Ѵ�.
			//x���� �����Ҷ� y�൵ �����ؾ���.

			//y���� �����Ҷ� x���� �پ������.

			pTransform->SetWorldPos(tPos);

			if (FileName != NULLPTR)
			{
				Renderer_Com* pRenderer = newTileObject->AddComponent<Renderer_Com>("Renderer");
				pRenderer->SetMesh("TextureRect");
				pRenderer->SetRenderState(ALPHA_BLEND);
				SAFE_RELEASE(pRenderer);

				Material_Com* pMaterial = newTileObject->AddComponent<Material_Com>("Material");
				pMaterial->SetDiffuseTexture(0, KeyName, FileName, PathKey);
				SAFE_RELEASE(pMaterial);
			}

			m_vecTile2DCom[Index] = pTile;
			m_vecTileObject[Index] = newTileObject;

			if (m_TileObjectSize == m_TileObjectCapacity)
			{
				m_TileObjectCapacity *= 2;

				GameObject** newObject = new GameObject*[m_TileObjectCapacity];
				memcpy(newObject, m_vecTileObject, sizeof(m_vecTileObject) * m_TileObjectSize);
				SAFE_DELETE(m_vecTileObject);
				m_vecTileObject = newObject;
			}

			if (m_Tile2DComSize == m_Tile2DComCapacity)
			{
				m_Tile2DComCapacity *= 2;

				Tile2D_Com** newTile = new Tile2D_Com*[m_Tile2DComCapacity];
				memcpy(newTile, m_vecTile2DCom, sizeof(m_vecTile2DCom) * m_Tile2DComSize);
				SAFE_DELETE(m_vecTile2DCom);
				m_vecTile2DCom = newTile;
			}

			m_Tile2DComSize++;
			m_TileObjectSize++;

		}//for(x)
	}//for(y)
}

void JEONG::Stage2D_Com::SetTileOption(const Vector3& Pos, TILE2D_OPTION option)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1 || Index > m_TileCountX * m_TileCountY)
		return;

	if(m_vecTile2DCom[Index] != NULLPTR)
		m_vecTile2DCom[Index]->SetTileOption(option);
}

void JEONG::Stage2D_Com::SetLineOn(bool Value)
{
	m_isLineOn = Value;

	for (size_t i = 0; i < m_Tile2DComSize; i++)
		m_vecTile2DCom[i]->SetLineOn(m_isLineOn);
}

int JEONG::Stage2D_Com::GetRectTileIndex(const Vector3 & Pos)
{
	//�簢Ÿ�� �ε��� ���ϱ�. Pos / Size �� ���� int�� ����ȯ
	int	x = (int)((Pos.x - m_StartPos.x) / m_TileScale.x);

	if (x < 0 || x >= m_TileCountX)
		return -1;

	int	y = (int)((Pos.y - m_StartPos.y) / m_TileScale.y);

	if (y < 0 || y >= m_TileCountY)
		return -1;

	return y * m_TileCountX + x;
}

int JEONG::Stage2D_Com::GetIsoTileIndex(const Vector3 & Pos)
{
	Vector3 sPos;
	sPos.y = (m_TileCountY * m_TileScale.y) * 0.5f;
	sPos.x = (m_TileCountX * m_TileScale.x) * 0.5f;

	float dY = Pos.y - (Pos.x * 0.5f);
	float dX = Pos.y + (Pos.x * 0.5f);

	int XIndex = (int)((dX - sPos.y) / m_TileScale.y);
	int YIndex = (int)((dY + sPos.y) / m_TileScale.y);

	return YIndex * m_TileCountX + XIndex;
}

Vector2 JEONG::Stage2D_Com::GetIsoTileIndexVec(const Vector3 & Pos)
{
	Vector3 sPos;
	sPos.x = (m_TileCountX * m_TileScale.x) * 0.5f;
	sPos.y = (m_TileCountY * m_TileScale.y) * 0.5f;

								//Scale.x / Scale.y = ����(�ϴ� ������)
	float dX = Pos.y + (Pos.x * 0.5f);
	float dY = Pos.y - (Pos.x * 0.5f);

	int XIndex = (int)((dX - sPos.y) / m_TileScale.y);
	int YIndex = (int)((dY + sPos.y) / m_TileScale.y);
	
	return Vector2((float)XIndex, (float)YIndex);
}

void JEONG::Stage2D_Com::SetNoMoveMesh(const Vector3 & Pos, STAGE2D_TILE_TYPE TileType)
{
	JEONG::Tile2D_Com* getTile = GetTile2D(Pos);

	switch (TileType)
	{
		case STT_TILE:
		{
			if (getTile != NULLPTR)
				getTile->SetMesh("TileNoMove");
		}
			break;
		case STT_ISO:
		{
			if (getTile != NULLPTR)
				getTile->SetMesh("IsoTileNomove");
		}
			break;
	}
}

void JEONG::Stage2D_Com::SetMoveMesh(const Vector3 & Pos, STAGE2D_TILE_TYPE TileType)
{
	JEONG::Tile2D_Com* getTile = GetTile2D(Pos);

	switch (TileType)
	{
		case STT_TILE:
		{
			if (getTile != NULLPTR)
				getTile->SetMesh("ColliderRect");
		}
		break;
		case STT_ISO:
		{
			if (getTile != NULLPTR)
				getTile->SetMesh("IsoTileNomal");
		}
		break;
	}
}

JEONG::Tile2D_Com * JEONG::Stage2D_Com::GetTile2D(const Vector3 & Pos)
{		
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return NULLPTR;

	return m_vecTile2DCom[Index];
}

JEONG::Tile2D_Com * JEONG::Stage2D_Com::GetTile2D(float X, float Y, float Z)
{
	int Index = GetTileIndex(Vector3(X, Y, Z));

	if (Index == -1)
		return NULLPTR;

	return m_vecTile2DCom[Index];
}

void JEONG::Stage2D_Com::SetMainTileImage(const Vector3 & Pos, const string & FileName, int Dir)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	//�ѹ��� ����.
	if (m_vecTile2DCom[Index]->GetImageFileName() == FileName && m_vecTile2DCom[Index]->GetDir() == Dir)
		return;

	m_vecTile2DCom[Index]->SetMainTileImage(FileName, Dir);
}

void JEONG::Stage2D_Com::SetSubTileImage(const Vector3 & Pos, const string & FileName, size_t ImageCount, int Dir)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	if (m_vecTile2DCom[Index]->GetSubTileImageObject(0) != NULLPTR)
		return;

	m_vecTile2DCom[Index]->SetSubTileImage(ImageCount);
}

void JEONG::Stage2D_Com::SetRotation(const Vector3& Pos, float Angle)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile2DCom[Index]->GetTransform()->SetWorldRotZ(Angle);
}

void JEONG::Stage2D_Com::ClearImage(const Vector3& Pos)
{
	ClearMainImage(Pos);
	ClearSubImage(Pos);
}

void JEONG::Stage2D_Com::ClearMainImage(const Vector3& Pos)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile2DCom[Index]->ClearMainImage();
}

void JEONG::Stage2D_Com::ClearSubImage(const Vector3& Pos)
{
	int Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile2DCom[Index]->ClearSubImage();
}
#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class Material_Com;
class Renderer_Com;
class GameObject;
class JEONG_DLL TileImage_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	TileImage_Com* Clone() override;
	void AfterClone() override;
	void Save(BineryWrite& Writer) override;
	void Load(BineryRead& Reader) override;

	void SetTexture(const string& KeyName, wchar_t* FileName, const string& PathKey = TEXTURE_PATH);
	void SetDiffuseColor(const Vector4& Color);
	void SetDistance(float Distance) { m_Distance = Distance; }
	float GetDistance() const { return m_Distance; }
	void SetSavePos(const Vector3& Pos) { m_SavePos = Pos; }
	bool GetIsMove() const { return m_isMove; }
	void SetIsMove(bool Value) { m_isMove = Value; }

	Material_Com* GetMaterial() const { return m_Material; }
	Renderer_Com* GetRenderer() const { return m_Renderer; }
	void SetPercentColor(const Vector4& Color);

	void SetNearObject(GameObject* NearObject, float Distance);


private:
	float m_Distance;
	Vector3 m_SavePos;
	Vector3 m_ScaleVar;
	bool m_isMove;
	float m_InputDistance;

	float m_ColorChangeTime;
	float m_ColorChangeTimeVar;
	Material_Com* m_Material;
	Renderer_Com* m_Renderer;
	TileImageCBuffer m_CBuffer;

	GameObject* m_NearObject;
	Material_Com* m_NearMaterial;

protected:
	TileImage_Com();
	TileImage_Com(const TileImage_Com& CopyData);
	~TileImage_Com();

public:
	friend class GameObject;
};

JEONG_END


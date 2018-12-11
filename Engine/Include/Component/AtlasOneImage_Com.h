#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class JEONG_DLL AtlasOneImage_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	AtlasOneImage_Com* Clone() override;
	void AfterClone() override;

	void SetAtlas(const string& FileName, const Vector4& CutRect);

private:
	//AtlasOneCBuffer m_CBuffer;

protected:
	AtlasOneImage_Com();
	AtlasOneImage_Com(const AtlasOneImage_Com& CopyData);
	~AtlasOneImage_Com();

public:
	friend class GameObject;
};

JEONG_END


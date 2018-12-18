#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class JEONG_DLL Number_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	Number_Com* Clone() override;

	void SetNumber(int Number);
	void SetNumberPos(const Vector3& Pos);
	void SetNumberPivot(const Vector3& Pivot);

private:
	int m_Number;

private:
	Number_Com();
	Number_Com(const Number_Com& number);
	~Number_Com();

public:
	friend class GameObject;
};

JEONG_END
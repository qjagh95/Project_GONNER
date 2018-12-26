#pragma once
#include <UserComponent/UserComponent_Base.h>

JEONG_USING

class LogoAlphaBat_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	LogoAlphaBat_Com* Clone() override;
	void AfterClone() override;

	void SetLogoAlphaBat(LOGO_ALPHABAT Data);
	void SetAlphaBatColor(const Vector4& Color);

private:
	float m_ChangeTime;
	float m_TimeVar;
	AlphaBatCBuffer m_CBuffer;
	bool m_isReturn;
	int m_Count;
	float m_AlphaAngle;

protected:
	LogoAlphaBat_Com();
	LogoAlphaBat_Com(const LogoAlphaBat_Com& CopyData);
	~LogoAlphaBat_Com();

public:
	friend class GameObject;
};


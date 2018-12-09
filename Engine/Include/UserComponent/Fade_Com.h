#pragma once
#include "UserComponent_Base.h"

JEONG_BEGIN

class JEONG_DLL Fade_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Fade_Com* Clone() override;
	void AfterClone() override;

	void Start();
	void SetFadeColor(const Vector3& Color, FADE_OPTION Option);
	void SetFadeSpeed(float Speed) { m_CBuffer.Speed = Speed; }
	bool GetIsOver() const { return m_isOver; }
	bool GetIsInOut() const { return m_isInOut; }

private:
	void FadeIn(float DeltaTime);
	void FadeOut(float DeltaTime);
	void FadeInOut(float DeltaTime);

private:
	bool m_isStart;
	bool m_isOver;
	bool m_isInOut;
	FadeCBuffer m_CBuffer;

	FADE_OPTION m_Option;

protected:
	Fade_Com();
	Fade_Com(const Fade_Com& CopyData);
	~Fade_Com();

public:
	friend class GameObject;
};

JEONG_END


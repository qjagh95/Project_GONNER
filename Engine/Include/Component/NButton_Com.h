#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class ColliderRect_Com;
class JEONG_DLL NButton_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	NButton_Com* Clone() override;
	void AfterClone() override;

	void Disable();
	void SetNormal();
	void SetStateColor(BUTTON_STATE eState, const Vector4& Color);
	void SetStateColor(BUTTON_STATE eState, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void MouseHit(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);
	void MouseOut(Collider_Com* Src, Collider_Com* Dest, float DeltaTime);

	void SetCallBack(void*(pFunc)(float)) { m_ButtonCallBack = bind(pFunc, placeholders::_1); }
	void SetCallBack(function<void(float)> pFunc) { m_ButtonCallBack = pFunc; }
	template<typename T>
	void SetCallBack(void(T::*pFunc)(float), T* Object)
	{
		m_ButtonCallBack = bind(pFunc, Object, placeholders::_1);
	}

	void SetSaveScale(const Vector3& Scale) { m_SaveScale = Scale; }

	void SetTexture(const string& KeyName, const TCHAR* FileName);
	void ActiveFunction(float DeltaTime);
	void LightOn();
	void LightOff();

protected:
	BUTTON_STATE m_ButtonState;
	function<void(float)> m_ButtonCallBack;
	Vector4 m_ButtonColor[BS_MAX];
	ButtonCBuffer m_ButtonCBuffer;
	ColliderRect_Com* m_RectColl;
	Vector3 m_SaveScale;

	bool m_isMouse;

protected:
	NButton_Com();
	NButton_Com(const NButton_Com& CopyData);
	 ~NButton_Com();

public:
	friend class GameObject;
};

JEONG_END


#pragma once

JEONG_BEGIN

class Number_Com;
class JEONG_DLL NumberManager
{
public:
	void SetNumber(int Number);
	void AddNumber();
	void ClearNumber();
	void SetScene(class Scene* pCurScene);

private:
	vector<Number_Com*> m_vecNumber;
	vector<GameObject*> m_vecNumberObject;
	vector<int> m_vecNumberValue;

	int  m_Number;
	bool m_isChangeNumber;
	int  m_DigitCount;

public:
	bool Init();
	void Input(float DeltaTime);
	void ClearVecNumber();

public:
	CLASS_IN_SINGLE(NumberManager)
};

JEONG_END
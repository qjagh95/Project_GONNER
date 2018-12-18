#include "stdafx.h"
#include "NumberManager.h"
#include "Component/Number_Com.h"

JEONG_USING

SINGLETON_VAR_INIT(NumberManager)

JEONG::NumberManager::NumberManager()
{
}

JEONG::NumberManager::~NumberManager()
{
	for (size_t i = 0; i < m_vecNumber.size(); ++i)
		SAFE_RELEASE(m_vecNumber[i]);

	for (size_t i = 0; i < m_vecNumberObject.size(); ++i)
		SAFE_RELEASE(m_vecNumberObject[i]);

	m_vecNumber.clear();
}

bool JEONG::NumberManager::Init()
{
	Scene* getScene = SceneManager::Get()->GetCurScene();
	Layer* fadeLayer = getScene->FindLayer("Fade");

	m_isChangeNumber = false;

	for (int i = 0; i < 5; ++i)
	{
		GameObject* newObject = GameObject::CreateObject("Number", fadeLayer);
		newObject->SetIsShow(false);
		Number_Com* newNumber = newObject->AddComponent<Number_Com>("NumberCom");
		newNumber->SetNumberPos(Vector3(i * 49.0f + 300.0f, 300.0f, 0.0f));
	
		m_vecNumber.push_back(newNumber);
		m_vecNumberObject.push_back(newObject);
	}

	m_DigitCount = 0;

	SAFE_RELEASE(getScene);
	SAFE_RELEASE(fadeLayer);

	return true;
}

void JEONG::NumberManager::Input(float DeltaTime)
{
	if (m_isChangeNumber == true)
	{
		int DigitCount = 0;
		m_vecNumberValue.clear();

		int Number = m_Number;

		while (Number > 0)
		{
			int	Result = Number % 10;
			Number /= 10;

			m_vecNumberValue.push_back(Result);
			DigitCount++;
		}
		if (m_DigitCount < DigitCount)
		{
			for (int i = m_DigitCount; i < DigitCount; ++i)
			{
				if (i >= m_vecNumber.size())
					return;

				GameObject* getObject = m_vecNumber[i]->GetGameObject();
				getObject->SetIsShow(true);
			}
		}
		else if (m_DigitCount > DigitCount)
		{
			for (int i = DigitCount; i < m_vecNumber.size(); ++i)
			{
				if (i >= m_vecNumber.size())
					return;

				GameObject* getObject = m_vecNumber[i]->GetGameObject();
				getObject->SetIsShow(false);
			}
		}
		m_DigitCount = DigitCount;

		int Count = 0;
		for (int i = m_DigitCount - 1; i >= 0; --i)
		{
			m_vecNumber[Count]->SetNumber(m_vecNumberValue[i]);
			Count++;
		}
		m_isChangeNumber = false;
	}
}

void JEONG::NumberManager::ClearVecNumber()
{
	for (size_t i = 0; i < m_vecNumber.size(); ++i)
		SAFE_RELEASE(m_vecNumber[i]);

	m_vecNumber.clear();
}

void JEONG::NumberManager::SetNumber(int Number)
{
	m_vecNumberValue.clear();
	m_isChangeNumber = true;
	m_Number = Number;
}

void JEONG::NumberManager::AddNumber()
{
	m_isChangeNumber = true;
	m_Number++;
}

void JEONG::NumberManager::ClearNumber()
{
	m_isChangeNumber = true;
	m_Number = 0;
}

void JEONG::NumberManager::SetScene(Scene * pCurScene)
{
	if (m_vecNumberObject[0] == NULLPTR)
		return;

	Layer* getLayer = pCurScene->FindLayer("UI");

	for (size_t i = 0; i < m_vecNumberObject.size();++i)
		getLayer->AddObject(m_vecNumberObject[i]);

	SAFE_RELEASE(getLayer);
}


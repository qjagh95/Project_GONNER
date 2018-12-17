//#pragma once
//
//JEONG_BEGIN
//
//class CNumber;
//class JEONG_DLL UIManager
//{
//private:
//	static UIManager* m_pInst;
//public:
//	static UIManager* GetInst()
//	{
//		if (m_pInst == nullptr)
//			m_pInst = new UIManager;
//
//		return m_pInst;
//	}
//	
//	static void DestroyInst()
//	{
//		SAFE_DELETE(m_pInst);
//	}
//private:
//	vector<CNumber*> m_vecNumber;
//	vector<int> m_vecNumberValue;
//
//	int  m_iNumber;
//	bool m_bChangeNumber;
//	int  m_iDigitCount;
//
//public:
//	void SetNumber(int _iNumber)
//	{
//		m_vecNumberValue.clear();
//		m_bChangeNumber = true;
//		m_iNumber = _iNumber;
//	}
//
//	void AddNumber()
//	{
//		m_bChangeNumber = true;
//		++m_iNumber;
//	}
//
//	void ClearNumber()
//	{
//		m_bChangeNumber = true;
//		m_iNumber = 0;
//	}
//
//public:
//	bool Init();
//	void Input(float _fTime);
//	void ClearVecNumber();
//
//private:
//	UIManager();
//	~UIManager();
//};
//
//JEONG_END
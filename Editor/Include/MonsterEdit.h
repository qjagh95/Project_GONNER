#pragma once
// MonsterEdit 대화 상자

class EditScene;
class MonsterEdit : public CDialogEx
{
	DECLARE_DYNAMIC(MonsterEdit)

public:
	MonsterEdit(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MonsterEdit();

	void SetForm(EditorForm* form) { m_EditorForm = form; }
	EditorForm* m_EditorForm;

	MONSTER_TYPE m_CurType;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOBTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_MonsterList;
	CComboBox m_MobListCombo;
	MONSTER_TYPE m_CurMobType;
	BOOL m_isLeft;
	float m_CurPosX;
	float m_CurPosY;
	float m_SelectPosX;
	float m_SelectPosY;
	EditScene* m_EditScene;
	wstring m_TexturePath;
	int m_ListIndex;

	void ReDrawWindow();
	afx_msg void OnBnClickedClose();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit5();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton4();

	afx_msg void OnBnClickedMonload();
};

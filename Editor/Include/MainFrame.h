
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

class EditorView;
class EditorForm;

class MainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	EditorView* GetEditorView() const { return m_EditorView; }
	EditorForm* GetEditorForm() const { return m_EditorForm; }

	CSplitterWnd m_SplitWindow;

	MainFrame* GetMainframe() { return this; }
// �����Դϴ�.
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  
	//���������� (�������Ұ� ���������� ����)

	EditorView* m_EditorView;
	EditorForm* m_EditorForm;


// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};



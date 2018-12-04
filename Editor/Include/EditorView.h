
// EditorView.h : EditorView Ŭ������ �������̽�
//

#pragma once

#include "EditorDoc.h"

class EditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	EditorView();
	DECLARE_DYNCREATE(EditorView)

// Ư���Դϴ�.
public:
	EditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~EditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // EditorView.cpp�� ����� ����
inline EditorDoc* EditorView::GetDocument() const
   { return reinterpret_cast<EditorDoc*>(m_pDocument); }
#endif



// EditorView.cpp : EditorView Ŭ������ ����
//

#include "EditorHeader.h"
#include "EditScene.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Editor.h"
#endif

#include "EditorDoc.h"
#include "EditorView.h"
#include "EditorForm.h"
#include <Component/FreeCamera_Com.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//EditorView

IMPLEMENT_DYNCREATE(EditorView, CView)

BEGIN_MESSAGE_MAP(EditorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

//EditorView ����/�Ҹ�

EditorView::EditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

EditorView::~EditorView()
{
}

BOOL EditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}


void EditorView::OnDraw(CDC* /*pDC*/)
{
	EditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
		return;
}

BOOL EditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void EditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void EditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// EditorView ����

#ifdef _DEBUG
void EditorView::AssertValid() const
{
	CView::AssertValid();
}

void EditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

EditorDoc* EditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(EditorDoc)));
	return (EditorDoc*)m_pDocument;
}
#endif //_DEBUG

//TODO
// EditorView �޽��� ó����
void EditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

BOOL EditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	MainFrame* mainFrame = (MainFrame*)AfxGetMainWnd();
	EditorForm*	editorForm = mainFrame->GetEditorForm();
	
	Scene* getScene = SceneManager::Get()->GetCurScene();
	Camera_Com* getCamera = getScene->GetMainCamera();

	if (KeyInput::Get()->KeyPress("Shift"))
	{
		if (zDelta <= 0) //�� �ٿ�
		{
			getCamera->AddZoom(-50.0f);
		}
		else //�پ�
		{
			getCamera->AddZoom(50.0f);
		}
	}

	SAFE_RELEASE(getScene);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

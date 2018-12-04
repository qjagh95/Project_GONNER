// MainFrm.cpp : MainFrame Ŭ������ ����
//

#include "EditorHeader.h"
#include "Editor.h"
#include "EditorView.h"
#include "EditorForm.h"

#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

MainFrame::MainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

MainFrame::~MainFrame()
{
}

//�������������� ��ó�� ��������� ������ �Լ�
int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	//���������� ����ũ��
	cs.cx = 1800;
	cs.cy = 720;

	return TRUE;
}

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

//TODO
BOOL MainFrame::DestroyWindow()
{
	return CFrameWnd::DestroyWindow();
}


BOOL MainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//â�� �����Ѵ�.
	//�θ�, ���θ ���θ?
	m_SplitWindow.CreateStatic(this, 1, 2);

	//���ҵ� �� â�� ���ϴ� �����츦 �����Ѵ�.
	m_SplitWindow.CreateView(0, 0, RUNTIME_CLASS(EditorView), CSize(1280, 720), pContext);
	m_SplitWindow.CreateView(0, 1, RUNTIME_CLASS(EditorForm), CSize(520, 720), pContext);
	
	//�����츦 ������ �Լ�.
	m_EditorView = (EditorView*)m_SplitWindow.GetPane(0, 0);
	m_EditorForm = (EditorForm*)m_SplitWindow.GetPane(0, 1);

	return TRUE;
}
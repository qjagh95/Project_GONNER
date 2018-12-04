
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

//�� Ŭ�������� Window�� ����.

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

	Vector3 CameraNormal = Vector3::Nomallize(getCamera->GetTransform()->GetWorldPos());
	Vector3 MouseNormal = Vector3::Nomallize(KeyInput::Get()->GetMouseWorldPos());

	Vector3 CameraPos = getCamera->GetTransform()->GetWorldPos();
	Vector3 MousePos = KeyInput::Get()->GetMouseWorldPos();

	if (KeyInput::Get()->KeyPress("Shift"))
	{
		if (zDelta <= 0) //�� �ٿ�
		{
			if (Vector3::CameraZoom.x <= 0.0f && Vector3::CameraZoom.y <= 0.0f)
				editorForm->AddWorkText("Error! 0%���Ϸ� ���� �� �����ϴ�");
			else
			{
				getCamera->GetTransform()->Move(Vector3(Device::Get()->GetWinSize().Width * -0.1f, Device::Get()->GetWinSize().Height * -0.1f, 0.0f));
				editorForm->AddWorkText("20% ����...");
			}
		
			Vector3::AddCameraZoom(Vector3(-0.2f, -0.2f, 0.0f));
		}
		else //�پ�
		{
			if ((Vector3::CameraZoom.x >= 1.0f && Vector3::CameraZoom.y >= 1.0f) && (Vector3::CameraZoom.x < 5.0f && Vector3::CameraZoom.y < 5.0f))
			{
				editorForm->AddWorkText("20% ����...");
				getCamera->GetTransform()->Move(Vector3(Device::Get()->GetWinSize().Width * 0.1f, Device::Get()->GetWinSize().Height * 0.1f, 0.0f));
			}
			if(Vector3::CameraZoom.x >= 5.0f && Vector3::CameraZoom.y >= 5.0f)
				editorForm->AddWorkText("Error! 500% �̻����� �ø� �� �����ϴ�.");

			Vector3::AddCameraZoom(Vector3(0.2f, 0.2f, 0.0f));
		}
	}

	SAFE_RELEASE(getScene);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

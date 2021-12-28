
// ImageViewerView.cpp : CImageViewerView Ŭ������ ����
//

#include "stdafx.h"
#include "ImageViewer.h"

#include "ImageViewerDoc.h"
#include "ImageViewerView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageViewerView

IMPLEMENT_DYNCREATE(CImageViewerView, CView)

BEGIN_MESSAGE_MAP(CImageViewerView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageViewerView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CImageViewerView ����/�Ҹ�

CImageViewerView::CImageViewerView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageViewerView::~CImageViewerView()
{
}

BOOL CImageViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageViewerView �׸���

void CImageViewerView::OnDraw(CDC* /*pDC*/)
{
	CImageViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CImageViewerView �μ�


void CImageViewerView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CImageViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CImageViewerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageViewerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CImageViewerView ����

#ifdef _DEBUG
void CImageViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CImageViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageViewerDoc* CImageViewerView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageViewerDoc)));
	return (CImageViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageViewerView �޽��� ó����

void CImageViewerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//if(!::IsWindow(m_treeview.GetSafeHwnd()))
	//{
	//	CRect rect;
	//	GetClientRect(&rect); 
	//	//m_treeview.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0,0,300,rect.Height()), this, 1000);  //101020
 //		m_treeview.SetRootDirectory(L""); 
	//}

	//if(!::IsWindow(m_listview.GetSafeHwnd()))
	//{
	//	CRect rect;
	//	GetClientRect(&rect); 
	//	//m_listview.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT , CRect(300,0,rect.Width(),rect.Height()), this, 2000);  //101020
	//}
}
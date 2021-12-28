
// ImageViewerView.cpp : CImageViewerView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageViewerView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CImageViewerView 생성/소멸

CImageViewerView::CImageViewerView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageViewerView::~CImageViewerView()
{
}

BOOL CImageViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageViewerView 그리기

void CImageViewerView::OnDraw(CDC* /*pDC*/)
{
	CImageViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CImageViewerView 인쇄


void CImageViewerView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CImageViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CImageViewerView 진단

#ifdef _DEBUG
void CImageViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CImageViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageViewerDoc* CImageViewerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageViewerDoc)));
	return (CImageViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageViewerView 메시지 처리기

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
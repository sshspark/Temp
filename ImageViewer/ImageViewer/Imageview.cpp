// Imageview.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "Imageview.h"
#include "MainFrm.h"


// CImageview

IMPLEMENT_DYNCREATE(CImageview, CScrollView)

CImageview::CImageview()
{
	m_nZoom = 0;
	m_pImage = 0;
	m_bMaximize = FALSE;
}

CImageview::~CImageview()
{
}


BEGIN_MESSAGE_MAP(CImageview, CScrollView)
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_LEFT_ROTATE, &CImageview::OnLeftRotate)
	ON_COMMAND(ID_MENU_RIGHT_ROTATE, &CImageview::OnRightRotate)
END_MESSAGE_MAP()


// CImageview 그리기입니다.

void CImageview::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CImageview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: 여기에 그리기 코드를 추가합니다.

	
	CRect _rt;

	GetClientRect(&_rt);

	if(m_pImage)
	{
		if(m_bMaximize)
		{
			CRect rt;

			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetClientRect(&rt);

			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.SetColumnInfo(0, rt.Width(), 0);		
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter2.SetRowInfo(0, 0, 0);
			
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.RecalcLayout() ;
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter2.RecalcLayout();
	
			int rx = (rt.Width() - m_pImage->GetWidth()) / 2;
			int ry = (rt.Height() - m_pImage->GetHeight()) / 2;

			if(m_nZoom >= 1)
			{
				m_pImage->Draw(pDC->m_hDC, rx - m_nZoom / 2, ry - m_nZoom / 2, m_pImage->GetWidth() + m_nZoom, m_pImage->GetHeight() + m_nZoom);
			}
			else
			{
				m_pImage->Draw(pDC->m_hDC, rx + m_nZoom / 2, ry + m_nZoom / 2, m_pImage->GetWidth() - (-m_nZoom), m_pImage->GetHeight() - (-m_nZoom));
			}	
		}
		else
		{
			CRect rt;	
			
			pDC->SetStretchBltMode(COLORONCOLOR);
			m_pImage->Draw(pDC->m_hDC, _rt);

			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetClientRect(&rt);

			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.SetColumnInfo(0, rt.Width() / 3, 10);	
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter2.SetRowInfo(0, rt.Height() /2, 10);

			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.RecalcLayout();
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter2.RecalcLayout();	
		

		}
	}

}


// CImageview 진단입니다.

#ifdef _DEBUG
void CImageview::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CImageview::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CImageview 메시지 처리기입니다.

void CImageview::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	CScrollView::OnNcLButtonDblClk(nHitTest, point);
}

BOOL CImageview::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_nZoom += zDelta;

	if(m_nZoom < -1000)
		m_nZoom = -1000;

	if(m_nZoom > 1000)
		m_nZoom = 1000;

	Invalidate();

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}
void CImageview::UpdateImage(CString strPathName)
{	

	bool bLoad;
	m_pImage = new CxImage;

	CT2A ascii(strPathName);

	TRACE(_T("FILE NAME : %S \n"),ascii.m_psz);
	bLoad = m_pImage->Load(ascii.m_psz, CxImage::FindType(ascii.m_psz));
	
	if(bLoad) Invalidate();
}


void CImageview::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(!m_bMaximize) m_bMaximize = TRUE;
	else m_bMaximize = FALSE;

	Invalidate();

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CImageview::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;

	menu.CreatePopupMenu();

	
	menu.AppendMenu(MF_STRING, ID_MENU_LEFT_ROTATE, _T("왼쪽 회전"));
	menu.AppendMenu(MF_STRING, ID_MENU_RIGHT_ROTATE, _T("오른쪽 회전"));

	menu.TrackPopupMenu(TPM_LEFTALIGN,
			    point.x,
			    point.y,
			    AfxGetMainWnd());


}
void CImageview::OnLeftRotate()
{
	if(m_pImage)	
	{
		m_pImage->RotateLeft();
		Invalidate();
	}
}
void CImageview::OnRightRotate()
{
	if(m_pImage)	
	{	
		m_pImage->RotateRight();
		Invalidate();
	}
}

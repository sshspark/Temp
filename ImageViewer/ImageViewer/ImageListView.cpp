// ImageListView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageListView.h"
#include "Imageview.h"
#include "Mainfrm.h"


// ImageListView

IMPLEMENT_DYNCREATE(CImageListView, CListView)

CImageListView::CImageListView()
{
	m_pList = NULL;
}

CImageListView::~CImageListView()
{
}

BEGIN_MESSAGE_MAP(CImageListView, CListView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CImageListView::OnLvnItemchanged)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGING, &CImageListView::OnLvnItemchanging)
	ON_NOTIFY(HDN_ITEMCLICKA, 0, &CImageListView::OnHdnItemclick)
	ON_NOTIFY(HDN_ITEMCLICKW, 0, &CImageListView::OnHdnItemclick)
END_MESSAGE_MAP()


// ImageListView 진단입니다.

#ifdef _DEBUG
void CImageListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CImageListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG

void CImageListView::InitHeader()
{
	LV_COLUMN col;
	CString strHeader;

	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	for(int i=0; i< 4; i++)
	{
		strHeader = cListHeader[i];
		col.fmt = (strHeader.Compare(L"크기") == 0 ? LVCFMT_RIGHT:LVCFMT_LEFT);
		col.cx = nHeaderWidth[i];
		col.pszText = (LPWSTR)(LPCWSTR)strHeader;
		col.iSubItem = i;
		GetListCtrl().InsertColumn(i, &col);
	}
	
	CHeaderCtrl* pH = (CHeaderCtrl*)GetDlgItem(0);
	pH->ModifyStyle(0, HDS_HOTTRACK);
}

void CImageListView::UpdateList()
{
	CString strFileSize;
	CString strLastWriteTime;
	int			i = 0;
	POSITION	pos;
	LIST_VIEW*	pListView;
    LVITEM item = { 0 } ;

    item.mask = LVIF_TEXT;
    item.iItem = 0;
	
	for(pos = m_pList->GetHeadPosition();pos != NULL;i++)
	{
		pListView = (LIST_VIEW*)m_pList->GetNext(pos);

		GetListCtrl().InsertItem(&item);

		GetListCtrl().SetItemText(0, 0, (LPTSTR)(LPCTSTR)pListView->strName);

		strFileSize.Format(L"%dKB", pListView->dwFileSize);
		GetListCtrl().SetItemText(0, 1, strFileSize);

		strLastWriteTime.Format(L"%d-%d-%d %d:%d", 
			pListView->tLastWriteTime.GetYear(), pListView->tLastWriteTime.GetMonth(),
			pListView->tLastWriteTime.GetDay(), pListView->tLastWriteTime.GetHour(), 
			pListView->tLastWriteTime.GetMinute());

		GetListCtrl().SetItemText(0, 2, strLastWriteTime);

	} 
}

// ImageListView 메시지 처리기입니다.

void CImageListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	InitHeader();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
void CImageListView::UpdateFileName(CString strName)
{
	
	CFileFind finder;

	CString strPath;
	CString strExt;
	CString str;
	CString strFileName;
	CTime time;

	CListCtrl& listctrl = GetListCtrl();
	
	str.Format(_T("%s\\*.*"),strName);
	BOOL bWorking = finder.FindFile(str);

	LIST_VIEW* pListView;


	if(m_pList != NULL)
	{
		ListInitAll();
	}
	m_pList = new CObList;
	
	listctrl.DeleteAllItems();


	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(!finder.IsDots() && !finder.IsDirectory())
		{
			strPath = finder.GetFileName();

			AfxExtractSubString(strExt,strPath,1,'.');

			if(strExt.CompareNoCase(_T("jpg"))==0 ||
				strExt.CompareNoCase(_T("bmp"))==0 ||
				strExt.CompareNoCase(_T("gif"))==0 ||
				strExt.CompareNoCase(_T("png"))==0)
			{
				pListView = new LIST_VIEW;
				InitListViewStruct(pListView);

				pListView->strPath = finder.GetFilePath();
				pListView->strName = finder.GetFileName();
				pListView->dwFileSize = finder.GetLength() / 1024;
				finder.GetLastWriteTime(time);
				pListView->tLastWriteTime = time;

				TRACE(_T("%s\n"),(LPCTSTR)finder.GetFileName());

				

				m_pList->AddTail((CObject*)pListView);
			}
		}
	}
	UpdateList();

}

void CImageListView::InitListViewStruct(LIST_VIEW *pListView)
{
	pListView->strName = "";
	pListView->strPath = "";
	pListView->bIsDirectory = TRUE;
	pListView->strKind = "파일 폴더";
	pListView->tCreateTime = 0;
	pListView->tLastAccessTime = 0;
	pListView->tLastWriteTime = 0;
	pListView->bIsHidden = FALSE;
	pListView->bIsArchived = FALSE;
	pListView->bIsSystem = FALSE; 
}



void CImageListView::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}

void CImageListView::ListInitAll()
{
	LIST_VIEW*	pListView;
	
	POSITION pos = m_pList->GetHeadPosition();
	
	while(pos)
	{
		pListView = (LIST_VIEW*)m_pList->GetNext(pos);			
		delete	pListView;
	}
	
	m_pList->RemoveAll();
	delete	m_pList;
	m_pList = NULL;
}

void CImageListView::OnLvnItemchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	POSITION	pos = m_pList->GetHeadPosition();
	LIST_VIEW*	pListView = 0;

	int nSelectedItem = 0;

	CString strPath;

	nSelectedItem = pNMListView->iItem;
	strPath = GetListCtrl().GetItemText(nSelectedItem, 0);

	while(pos)
	{
		pListView = (LIST_VIEW*)m_pList->GetNext(pos);
		if(pListView->strName == strPath)
		{
			break;
		}
	}
	if(pListView)
	{
		CImageview *pView2 = (CImageview*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter2.GetPane(1, 0);
		pView2->UpdateImage(pListView->strPath);
	}
	*pResult = 0;
}

void CImageListView::OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

  //   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;

	 //
	 //int nColumn = pNMListView->iItem;

	 //for(int i=0; i< GetListCtrl().GetItemCount(); i++)
	 //{
		//GetListCtrl().SetItemData(i,i);
	 //}

	 //m_bAscending = !m_bAscending;

	 //SORTPARAM sortparams;
	 //sortparams.pList = &GetListCtrl();
	 //sortparams.nSortColumn = nColumn;
	 //sortparams.bSortDirect = m_bAscending;

	 //GetListCtrl().SortItems(&CompareFunc,(LPARAM)&sortparams);

	*pResult = 0;
}

static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam)
 {
	 CListCtrl *pList = ((SORTPARAM*)lParam)->pList;
	 int nSortColumn = ((SORTPARAM*)lParam)->nSortColumn;
	 bool bSortDirect = ((SORTPARAM*)lParam)->bSortDirect;

	 LVFINDINFO info1, info2;

	 info1.flags = LVFI_PARAM;
	 info1.lParam = lParam1;

	 info2.flags = LVFI_PARAM;
	 info2.lParam = lParam1;

	 int nrow1 = pList->FindItem(&info1,-1);
	 int nrow2 = pList->FindItem(&info2,-1);

	 CString strItem1 = pList->GetItemText(nrow1,nSortColumn);
	 CString strItem2 = pList->GetItemText(nrow1,nSortColumn);

	 CT2A ascii(strItem1);

	 CT2A ascii2(strItem2);

	 return bSortDirect?strcmp(ascii.m_psz,ascii2.m_psz):-strcmp(ascii.m_psz,ascii2.m_psz);
 }
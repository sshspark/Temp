#pragma once


// ImageListView 뷰입니다.

static char* cListHeader[3]={"이름", "크기", "수정 날짜"};
const int nHeaderWidth[3]=  {200,	  100,	  150};


class CImageListView : public CListView
{
	DECLARE_DYNCREATE(CImageListView)

public:
	CImageListView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CImageListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	
	CObList* m_pList;
	BOOL m_bAscending;

	void UpdateList();
	void InitListViewStruct(LIST_VIEW *pListView);
	void UpdateFileName(CString strName);
	void InitHeader();
	void ListInitAll();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam);

	virtual void OnInitialUpdate();
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchanging(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult);


};
struct SORTPARAM
{
	int nSortColumn;
	bool bSortDirect;
	CListCtrl *pList;
};
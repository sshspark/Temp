#pragma once


// ImageListView ���Դϴ�.

static char* cListHeader[3]={"�̸�", "ũ��", "���� ��¥"};
const int nHeaderWidth[3]=  {200,	  100,	  150};


class CImageListView : public CListView
{
	DECLARE_DYNCREATE(CImageListView)

public:
	CImageListView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
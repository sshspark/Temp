#pragma once

#include <set>
#include <vector>
#include "ImageViewer.h"
#include "ImageListView.h"
// CImageTreeView ∫‰¿‘¥œ¥Ÿ.

class CImageTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CImageTreeView)

public:
	CImageTreeView();           
	virtual ~CImageTreeView();

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
	BOOL CreateSystemImageList(CImageList *pImageList, CString rootDir, BOOL bLargeIcon);
	BOOL SetRootDirectory(CString rootDir);
	BOOL ShowDrives(HTREEITEM hParentItem);
	BOOL GetChildNodeName(HTREEITEM hNode, std::set<CString> *dest);
	BOOL GetAllChildNode(HTREEITEM hNode, std::vector<HTREEITEM>* dest);

	CString GetFullNodeName(HTREEITEM hNode);
	CString GetSelectedItemFullName(int index);

	CImageList			m_smallImageList; 
	CImageList			m_largeImageList; 

	CImageListView	m_listview;
private:
	BOOL ShowDirectoryInTree(HTREEITEM hParentItem);
public:
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();
	afx_msg void OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
};



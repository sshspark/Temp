
// ImageViewerView.h : CImageViewerView Ŭ������ �������̽�
//

#pragma once

#include "ImageTreeView.h"
#include "ImageListView.h"
#include "ImageViewer.h"
#include "ImageViewerDoc.h"

class CImageViewerView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageViewerView();
	DECLARE_DYNCREATE(CImageViewerView)

// Ư���Դϴ�.
public:
	CImageViewerDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void UpdateList(CString strName);
	void InitListViewStruct(LIST_VIEW *pListView);

	CImageTreeView	m_treeview; 
	CImageListView	m_listview; 

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CImageViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // ImageViewerView.cpp�� ����� ����
inline CImageViewerDoc* CImageViewerView::GetDocument() const
   { return reinterpret_cast<CImageViewerDoc*>(m_pDocument); }
#endif


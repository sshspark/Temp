#pragma once

#define ID_MENU_LEFT_ROTATE 2000
#define ID_MENU_RIGHT_ROTATE 2001

#include "xImage.h"
// CImageview ���Դϴ�.

class CImageview : public CScrollView
{
	DECLARE_DYNCREATE(CImageview)

protected:
	CImageview();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CImageview();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLeftRotate();
	afx_msg void OnRightRotate();

public:
	CxImage *m_pImage;

	BOOL m_bMaximize;
	BOOL m_nZoom;
	
	void UpdateImage(CString strPathName);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};



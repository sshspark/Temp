
// ImageViewerDoc.cpp : CImageViewerDoc Ŭ������ ����
//

#include "stdafx.h"
#include "ImageViewer.h"

#include "ImageViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageViewerDoc

IMPLEMENT_DYNCREATE(CImageViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageViewerDoc, CDocument)
END_MESSAGE_MAP()


// CImageViewerDoc ����/�Ҹ�

CImageViewerDoc::CImageViewerDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageViewerDoc::~CImageViewerDoc()
{
}

BOOL CImageViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImageViewerDoc serialization

void CImageViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CImageViewerDoc ����

#ifdef _DEBUG
void CImageViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageViewerDoc ���

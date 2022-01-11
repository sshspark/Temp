
// ImageViewerDoc.cpp : CImageViewerDoc 클래스의 구현
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


// CImageViewerDoc 생성/소멸

CImageViewerDoc::CImageViewerDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageViewerDoc::~CImageViewerDoc()
{
}

BOOL CImageViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageViewerDoc serialization

void CImageViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CImageViewerDoc 진단

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


// CImageViewerDoc 명령

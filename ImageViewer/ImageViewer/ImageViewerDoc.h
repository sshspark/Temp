
// ImageViewerDoc.h : CImageViewerDoc Ŭ������ �������̽�
//


#pragma once


class CImageViewerDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageViewerDoc();
	DECLARE_DYNCREATE(CImageViewerDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CImageViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};



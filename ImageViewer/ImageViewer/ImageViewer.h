
// ImageViewer.h : ImageViewer ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CImageViewerApp:
// �� Ŭ������ ������ ���ؼ��� ImageViewer.cpp�� �����Ͻʽÿ�.
//

typedef	struct _LIST_VIEW
{
	CString		strName;			// �̸�
	CString		strPath;			// ���
	BOOL		bIsDirectory;		// ���丮
	DWORD		dwFileSize;			// ���� ũ��
	CString		strKind;			// ���� ����
	CTime		tCreateTime;		// ���� ��¥
	CTime		tLastAccessTime;	// ����� ��¥
	CTime		tLastWriteTime;		// �ٲ� ��¥
	BOOL		bIsHidden;			// hidden ����
	BOOL		bIsArchived;		// ��� ����
	BOOL		bIsSystem;			// �ý��� ����
	int			Image;

}LIST_VIEW;

class CImageViewerApp : public CWinAppEx
{
public:
	CImageViewerApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageViewerApp theApp;

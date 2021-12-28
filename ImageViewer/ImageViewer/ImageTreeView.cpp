// ImageTreeView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommonTool.h"
#include "ImageViewer.h"
#include "ImageViewerView.h"
#include "ImageTreeView.h"
#include "MainFrm.h"


// CImageTreeView

IMPLEMENT_DYNCREATE(CImageTreeView, CTreeView)

CImageTreeView::CImageTreeView()
{

}

CImageTreeView::~CImageTreeView()
{
}

BEGIN_MESSAGE_MAP(CImageTreeView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CImageTreeView::OnTvnItemexpanded)
	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CImageTreeView::OnTvnItemChanged)
END_MESSAGE_MAP()


// CImageTreeView 진단입니다.

#ifdef _DEBUG
void CImageTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CImageTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG



BOOL CImageTreeView::CreateSystemImageList(CImageList *pImageList, CString rootDir, BOOL bLargeIcon)
{
	ASSERT(pImageList  != NULL);

	pImageList->Detach(); 
	pImageList->DeleteImageList();
	
	SHFILEINFO sfi = { 0 }; 
	
	CImageList *pSysImageList = NULL; 
	
	if(bLargeIcon == TRUE)
	{
		pImageList->Attach((HIMAGELIST)SHGetFileInfo(_T("C:\\"), 0, &sfi, sizeof(sfi), SHGFI_LARGEICON | SHGFI_SYSICONINDEX));
	}
	else{
		pImageList->Attach((HIMAGELIST)SHGetFileInfo(_T("C:\\"), 0, &sfi, sizeof(sfi), SHGFI_SMALLICON | SHGFI_SYSICONINDEX));
	}
	return true; 
}

BOOL CImageTreeView::SetRootDirectory(CString rootDir)
{
	CTreeCtrl&	treectrl = GetTreeCtrl();
	
	treectrl.DeleteAllItems(); 

	CreateSystemImageList(&m_smallImageList, rootDir, FALSE); 
	CreateSystemImageList(&m_largeImageList, rootDir, TRUE); 

	GetTreeCtrl().SetImageList(&m_smallImageList, TVSIL_NORMAL); 

	UINT nFlags = SHGFI_DISPLAYNAME | SHGFI_TYPENAME | SHGFI_SYSICONINDEX; 

	SHFILEINFO sfi = { 0 }; 

	if(rootDir == "")
	{
		int sysIconIndex = -1; 

		CString strlabel = GetDesktopLabel(&sysIconIndex); 
		HTREEITEM hRoot = treectrl.InsertItem(strlabel, sysIconIndex,sysIconIndex, TVI_ROOT); 

		strlabel = GetMyDocumentLabel(&sysIconIndex); 
		HTREEITEM hItem = treectrl.InsertItem(strlabel, sysIconIndex,sysIconIndex, hRoot); 

		TCHAR desktop_path[MAX_PATH] = _T(""); 

		SHGetSpecialFolderPath(NULL,desktop_path,CSIDL_DESKTOPDIRECTORY,0);

		CString subfolder; 

		if(GetFirstSubfolderName(desktop_path,&subfolder) == TRUE)
		{
			CString strFirstSubfolder; 
			strFirstSubfolder.Format(_T("%s\\%s"),desktop_path, subfolder); 
			SHGetFileInfo(strFirstSubfolder, 0, &sfi, sizeof(sfi), nFlags); 
			treectrl.InsertItem(subfolder, sfi.iIcon, sfi.iIcon, hItem); 
		}

		strlabel = GetMyComputerLabel(&sysIconIndex); 
		hItem = treectrl.InsertItem(strlabel, sysIconIndex,sysIconIndex, hRoot);
		ShowDrives(hItem); 

	}
	else
	{
		SHGetFileInfo(rootDir, 0, &sfi, sizeof(sfi), nFlags); 

		HTREEITEM hRoot = treectrl.InsertItem(rootDir, sfi.iIcon, sfi.iIcon, TVI_ROOT); 

		ShowDirectoryInTree(hRoot); 

		treectrl.SelectItem(hRoot); 
		treectrl.Expand(treectrl.GetRootItem(),TVE_TOGGLE); 
	}
	return true; 
}

BOOL CImageTreeView::ShowDirectoryInTree(HTREEITEM hParentItem)
{
	CTreeCtrl&	treectrl = GetTreeCtrl();

	CString fullRootPath = GetFullNodeName(hParentItem); 
	std::set<CString> ChildNodeName; 
	// Get all child nodes attached to [hParentItem]. 
	GetChildNodeName(hParentItem, &ChildNodeName); 

	if(fullRootPath == "My Computer")
	{
		ShowDrives(hParentItem); 
		return true;
	}

	std::vector<CString> vNodeNamelist; 
	std::vector<bool> vIsNodeDirectory; 
	WIN32_FIND_DATA fd = { 0 }; 
	HANDLE hSearch = NULL; 
	BOOL bFinish = false; 
	if(fullRootPath[1] == ':' && fullRootPath.GetLength() == 3)
	{
		fullRootPath = fullRootPath.Left(2); 
	}

	hSearch = FindFirstFile(fullRootPath  + "\\*.*", &fd); 
	while(!bFinish)
	{
		if(ChildNodeName.count(fd.cFileName) == 1)
		{
			bFinish = !FindNextFile(hSearch, &fd); 
			continue; 
		}

		bool IsCurNodeDir = false;

		if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if( (_tcslen(fd.cFileName) == 1 && fd.cFileName[0] == '.') ||
				(_tcslen(fd.cFileName) == 2 && fd.cFileName[0] == '.' && fd.cFileName[1] == '.') ||
				(PathIsSystemFolder(fullRootPath+"\\"+fd.cFileName, NULL) == TRUE)
				)
			{
				bFinish = !FindNextFile(hSearch, &fd); 
				continue; 
			}
			IsCurNodeDir = true; 
		}

		vNodeNamelist.push_back(fd.cFileName);
		vIsNodeDirectory.push_back(IsCurNodeDir); 
		bFinish = !FindNextFile(hSearch, &fd); 
	}
	FindClose(hSearch); 

	UINT nFlags = SHGFI_DISPLAYNAME | SHGFI_TYPENAME | SHGFI_SYSICONINDEX; 
	SHFILEINFO sfi = { 0 }; 


	int i = 0; 
	for(i = 0; i<vNodeNamelist.size() ; i++)
	{
		if(vIsNodeDirectory[i] == true)
		{
			CString path = fullRootPath + "\\" + vNodeNamelist[i];
			SHGetFileInfo(path, 0, &sfi, sizeof(sfi), nFlags); 
			HTREEITEM hItem = treectrl.InsertItem(vNodeNamelist[i], sfi.iIcon, sfi.iIcon, hParentItem); 
		}
	}

	std::vector<HTREEITEM> vAllChildNode; 
	GetAllChildNode(hParentItem, &vAllChildNode); 

	std::vector<HTREEITEM>::iterator pos = vAllChildNode.begin(); 

	for(; pos != vAllChildNode.end(); pos++)
	{
		CString strfullChildPath = GetFullNodeName(*pos); 
		CString subfolder; 

		if(GetFirstSubfolderName(strfullChildPath,&subfolder) == TRUE)
		{
			std::set<CString> strAllGrandChildName; 
			GetChildNodeName(*pos, &strAllGrandChildName); 
			if(strAllGrandChildName.count(subfolder) == 0)
			{
				SHGetFileInfo(strfullChildPath+"\\"+subfolder, 0, &sfi, sizeof(sfi), nFlags); 
				treectrl.InsertItem(subfolder, sfi.iIcon, sfi.iIcon, *pos); 
			}
		}
	}

	return true; 
}
CString CImageTreeView::GetFullNodeName(HTREEITEM hNode)
{
	
	CString path("");
	CString myDocumentLabel = GetMyDocumentLabel(NULL); 
	CString myComputerLabel = GetMyComputerLabel(NULL); 
	CString desktopLabel = GetDesktopLabel(NULL); 


	HTREEITEM hRoot = GetTreeCtrl().GetRootItem();

	if(hNode == hRoot)
	{
		TCHAR path[MAX_PATH] = _T(""); 
		SHGetSpecialFolderPath(NULL,path,CSIDL_DESKTOPDIRECTORY,0);
		return path; 
	}

	if(hRoot == GetTreeCtrl().GetParentItem(hNode))
	{
		CString currentItemText = GetTreeCtrl().GetItemText(hNode); 

		if(currentItemText == myDocumentLabel)
		{
			TCHAR path[MAX_PATH] = _T(""); 
			SHGetSpecialFolderPath(NULL,path,CSIDL_PERSONAL,0);
			return path; 
		}

		if(currentItemText == myComputerLabel)
		{
			return _T("My Computer"); 
		}
 
		TCHAR path[MAX_PATH] = _T(""); 

		SHGetSpecialFolderPath(NULL,path,CSIDL_DESKTOPDIRECTORY,0);

		CString fullPath(path); 

		fullPath += (_T("\\") + currentItemText); 

		return fullPath;
	}


	while(hNode != NULL)
	{
		CString itemText = GetTreeCtrl().GetItemText(hNode); 

		if(itemText == myComputerLabel || itemText == desktopLabel || itemText == myDocumentLabel)
		{
			if(itemText == myComputerLabel)
			{
				CString drive = _T("");
				CString folder = _T("");

				if(path.Find('\\') != -1)
				{
					drive = path[path.Find('\\')-3];//
					drive += _T(":\\"); 

					folder = path.Right(path.GetLength() - path.Find('\\')-1); 
				}
				else
				{
					drive = path[path.GetLength()-3];
					drive += _T(":\\"); 
				}


				if(folder != _T(""))
				{
					path = drive + folder; 
				}
				else
				{
					path = drive; 
				}
			}
			else if(itemText == desktopLabel)
			{
				TCHAR desktop_path[MAX_PATH] = _T(""); 
				CString temp_path;

				SHGetSpecialFolderPath(NULL,desktop_path,CSIDL_DESKTOPDIRECTORY,0);

				temp_path.Format(_T("%s\\%s"),desktop_path, path); 

				path = temp_path; 
			}
			else if(itemText == myDocumentLabel)
			{
				TCHAR myDocument_path[MAX_PATH] = _T(""); 
				CString temp_path;

				SHGetSpecialFolderPath(NULL,myDocument_path,CSIDL_PERSONAL,0);

				temp_path.Format(_T("%s\\%s"),myDocument_path, path); 

				path = temp_path; 
			}

			break;
		}

		if(path.IsEmpty())
			path = GetTreeCtrl().GetItemText(hNode);
		else
		{
			CString prePath(path);
			path = GetTreeCtrl().GetItemText(hNode);

			if(path[path.GetLength()-1] == '\\')
				path += prePath;
			else
				path += _T("\\") + prePath;
		}

		hNode = GetTreeCtrl().GetParentItem(hNode);
	
	}

	return path; 
}
BOOL CImageTreeView::ShowDrives(HTREEITEM hParentItem)
{
	CTreeCtrl&	treectrl = GetTreeCtrl();

	std::set<CString> child_node_name; 

	GetChildNodeName(hParentItem, &child_node_name); 

	DWORD logicalDrives = GetLogicalDrives(); 

	unsigned int i = 64; 
	do{
		i++; 
		if((logicalDrives & 1) != 0)
		{
			CString strDrive = _T(""); 
			UINT driveType = GetDriveType(strDrive); 

			strDrive.Format(_T("%c:\\"),i); 

			SHFILEINFO sfi = { 0 }; 

			SHGetFileInfo(strDrive, 0, &sfi, sizeof(sfi), SHGFI_DISPLAYNAME | SHGFI_SYSICONINDEX); 

			if(child_node_name.count(sfi.szDisplayName) == 0)
			{
				HTREEITEM hItem = treectrl.InsertItem(sfi.szDisplayName, sfi.iIcon, sfi.iIcon, hParentItem); 

				CString subfolder; 

				if(GetFirstSubfolderName(strDrive,&subfolder) == TRUE)
				{
					SHGetFileInfo(strDrive+subfolder, 0, &sfi, sizeof(sfi), SHGFI_DISPLAYNAME | SHGFI_SYSICONINDEX); 
					treectrl.InsertItem(subfolder, sfi.iIcon, sfi.iIcon, hItem); 
				}
			}
		}
	}while((logicalDrives >>= 1) != 0);

	return true; 
}
BOOL CImageTreeView::GetChildNodeName(HTREEITEM hNode, std::set<CString> *dest)
{

	if(GetTreeCtrl().ItemHasChildren(hNode) == false) return true; 

	std::vector<HTREEITEM> vAllChildNode; 

	GetAllChildNode(hNode, &vAllChildNode); 

	std::vector<HTREEITEM>::iterator pos = vAllChildNode.begin(); 

	for(; pos != vAllChildNode.end(); pos++){
		CString itemText = GetTreeCtrl().GetItemText(*pos); 
		dest->insert(itemText); 	
	}

	return true; 
}
BOOL CImageTreeView::GetAllChildNode(HTREEITEM hNode, std::vector<HTREEITEM>* dest)
{
	HTREEITEM hNextItem = NULL; 
	HTREEITEM hChildItem = GetTreeCtrl().GetChildItem(hNode); 

	while(hChildItem != NULL)
	{
		hNextItem = GetTreeCtrl().GetNextItem(hChildItem, TVGN_NEXT); 
		dest->push_back(hChildItem); 
		hChildItem = hNextItem; 
	}

	return true; 
}

// CImageTreeView 메시지 처리기입니다.

void CImageTreeView::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM hCurItem = pNMTreeView->itemNew.hItem;
	ShowDirectoryInTree(hCurItem); 

	*pResult = 0;
}

void CImageTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	long style = GetWindowLong(this->GetSafeHwnd(),GWL_STYLE) | TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS | TVS_LINESATROOT | TVS_TRACKSELECT;
	
	SetWindowLong(this->GetSafeHwnd(),GWL_STYLE,style);

	SetRootDirectory(L"");

}

void CImageTreeView::OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
	HTREEITEM hNode;

	CString strName;

	hNode = GetTreeCtrl().GetSelectedItem();
	strName = GetFullNodeName(hNode);

	CImageListView *pView = (CImageListView*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.GetPane(0, 1);
	pView->UpdateFileName(strName);

	*pResult = 0;
}

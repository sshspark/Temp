#include "stdafx.h"
#include "util.h"
#include "CommonTool.h"


#include <fstream>
#include <algorithm>


CString GetMyDocumentLabel(int *sysIconIndex)
{
	LPMALLOC pMalloc; 
	SHGetMalloc(&pMalloc); 
	SHFILEINFO sfi = { 0 }; 
	LPITEMIDLIST pidl; 

	SHGetSpecialFolderLocation(NULL,CSIDL_PERSONAL, &pidl); 
	SHGetFileInfo((LPCWSTR)pidl, 0, &sfi, sizeof(sfi), SHGFI_DISPLAYNAME | SHGFI_SYSICONINDEX | SHGFI_PIDL); 

	pMalloc->Free(pidl); 
	pMalloc->Release(); 

	if(sysIconIndex != NULL){
		*sysIconIndex = sfi.iIcon; 
	}
	return sfi.szDisplayName; 
}
CString GetMyComputerLabel(int *sysIconIndex)
{
	LPMALLOC pMalloc; 
	SHGetMalloc(&pMalloc); 
	SHFILEINFO sfi = { 0 }; 
	LPITEMIDLIST pidl; 

	SHGetSpecialFolderLocation(NULL,CSIDL_DRIVES, &pidl); 
	SHGetFileInfo((LPCWSTR)pidl, 0, &sfi, sizeof(sfi), SHGFI_DISPLAYNAME | SHGFI_SYSICONINDEX | SHGFI_PIDL); 

	pMalloc->Free(pidl); 
	pMalloc->Release(); 

	if(sysIconIndex != NULL){
		*sysIconIndex = sfi.iIcon; 
	}
	return sfi.szDisplayName; 
}
CString GetDesktopLabel(int *sysIconIndex)
{
	TCHAR path[MAX_PATH] = L""; 
	LPMALLOC pMalloc; 
	SHGetMalloc(&pMalloc); 
	SHFILEINFO sfi = { 0 }; 
	LPITEMIDLIST pidl; 

	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl); 
	SHGetFileInfo((LPCWSTR)pidl, 0, &sfi, sizeof(sfi), SHGFI_DISPLAYNAME | SHGFI_SYSICONINDEX | SHGFI_PIDL); 

	pMalloc->Free(pidl);
	pMalloc->Release(); 

	if(sysIconIndex != NULL){
		*sysIconIndex = sfi.iIcon; 
	}
	return sfi.szDisplayName; 

}
BOOL GetFirstSubfolderName(CString fullPath, CString* subfolder)
{
	if(PathIsDirectory(fullPath) == FALSE){
		return false; 
	}

	WIN32_FIND_DATA fd = { 0 }; 

	HANDLE hSearch = NULL; 
	BOOL bFinish = false; 
	BOOL has_subfolder = false; 

	if(fullPath[1] == ':' && fullPath.GetLength() == 3)
	{
		fullPath = fullPath.Left(2); 
	}

	hSearch = FindFirstFile(fullPath  + "\\*.*", &fd); 
	while(!bFinish)
	{
		if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if( (_tcslen(fd.cFileName) == 1 && fd.cFileName[0] == '.') ||
				(_tcslen(fd.cFileName) == 2 && fd.cFileName[0] == '.' && fd.cFileName[1] == '.') ||
				(PathIsSystemFolder(fullPath+"\\"+fd.cFileName,0) == TRUE))
			{
				bFinish = !FindNextFile(hSearch, &fd); 
				continue;
			}
				*subfolder = fd.cFileName; 
				FindClose(hSearch); 
				return true; 
		}
		bFinish = !FindNextFile(hSearch, &fd); 
	}
	FindClose(hSearch); 


	return false; 
}

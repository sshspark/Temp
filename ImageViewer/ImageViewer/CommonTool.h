#include <shlwapi.h>
#include <shlobj.h>


#include <set>
#include <vector>
#include <string>

#include <conio.h>


CString GetMyDocumentLabel(int *sysIconIndex);
CString GetMyComputerLabel(int *sysIconIndex);
CString GetDesktopLabel(int *sysIconIndex); 

BOOL GetFirstSubfolderName(CString fullPath, CString* subfolder); 


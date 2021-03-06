#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commctrl.h>

#include <WindowsX.h> //Dùng để ánh xạ các message vào các hàm xử lí tương ứng
#include <Dbt.h> //Chứa các hằng số sự kiện của thông điệp WM_DEVICECHANGE

#include "resource.h"

#include "CDrive.h"
#include "CTreeView.h"
#include "CListView.h"
#include "CStatus.h"
#include "DList.h"	
#include "CAddress.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

/*****************************************************************************************/
//Các khai báo hàm
ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);
void OnSize(HWND hwnd, UINT state, int cx, int cy);

void DoSizeTreeView();
/*****************************************************************************************/
//Các biến toàn cục
HINSTANCE g_hInst;
HWND g_hWnd;

CDrive *g_Drive;
CTreeView *g_TreeView;
RECT g_TreeViewRect;
CListView *g_ListView;
CStatus *g_Status;
DList *g_History;
CAddress *g_Address;

BOOL g_bStarted = FALSE; //Báo hiệu đã khởi tạo xong các điều khiển tránh lỗi trong sự kiện WM_SIZE
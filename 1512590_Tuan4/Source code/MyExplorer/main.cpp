#include "main.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
		return false;

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
		if (!IsDialogMessage(g_hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}//if

		return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX	wc;

	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON4));
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = _T("MyApp");
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance;
	g_hWnd = CreateWindowEx(0, _T("MyApp"), _T("My Explorer"), 
		WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_MAXIMIZE,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, hInstance, NULL);

	if (!g_hWnd)
		return false;

	ShowWindow(g_hWnd, SW_MAXIMIZE);
	UpdateWindow(g_hWnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}
/*****************************************************************************************/

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
 	//Lấy các kích thước của cửa sổ hiện hành
	RECT main; 
	GetWindowRect(hwnd, &main);

	g_Address = new CAddress;
	g_Address->Create(hwnd, IDC_ADDRESS, g_hInst);



	g_Status = new CStatus;
	g_Status->Create(hwnd, IDC_STATUSBAR, g_hInst);

	g_History = new DList;

	g_Drive = new CDrive;
	g_Drive->GetSystemDrives();

	g_TreeView = new CTreeView;
	g_TreeView->Create(hwnd, IDC_TREEVIEW, g_hInst, main.right/3, main.bottom);
	g_TreeView->LoadMyComputer(g_Drive);
	g_TreeView->GetFocus();
	g_TreeView->Expand(g_TreeView->GetCurSel());
	
	g_ListView = new CListView;
	g_ListView->Create(hwnd, IDC_LISTVIEW, g_hInst, (main.right - main.left) * 2 / 3 + 1, main.bottom, main.right / 3);
	g_ListView->LoadMyComputer(g_Drive);
	g_ListView->ChangeViewOption(LVS_REPORT);
	g_Status = new CStatus;
	g_Status->Create(hwnd, IDC_STATUSBAR, g_hInst);
	g_ListView->LoadChild(g_TreeView->GetCurPath(), g_Drive);

	g_History->InsertAfterCur(g_ListView->GetCurParentPath());
	

	//ShowWindow(g_TreeView->GetHandle(), SW_HIDE);
	//ShowWindow(g_ListView->GetHandle(), SW_HIDE);

	//Đã khởi tạo xong ứng dụng
	g_bStarted = TRUE;

	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_FILE_EXIT:
		DestroyWindow(hwnd);
		break;

	case ID_FILE_SELECTALL:
		g_ListView->SelectAll();
		break;

	case IDM_HELP_ABOUT:
		MessageBox(NULL, _T("MyExplorer\n"), _T("About"), MB_OK);
		break;

	case ID_HELP_HELP:
		MessageBox(NULL, _T("Try MyExplorer yourself! ^_^"), _T("Help"), MB_OK);
		break;

	case ID_VIEW_ICONS:
		g_ListView->ChangeViewOption(LVS_ICON);
		break;

	case ID_VIEW_SMALLICONS:
		g_ListView->ChangeViewOption(LVS_SMALLICON);
		break;

	case ID_VIEW_LIST1:
		g_ListView->ChangeViewOption(LVS_LIST);
		break;

	case ID_VIEW_DETAILS1:
		g_ListView->ChangeViewOption(LVS_REPORT);
		break;
	}
}

void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	g_TreeView->Size(cy);
	GetWindowRect(g_TreeView->GetHandle(), &g_TreeViewRect); //Cap nhat lai cho TreeView


	g_ListView->Size();
	g_Status->Size();
	
	SendMessage(g_Address->GetHandle(), TB_AUTOSIZE, 0, (LPARAM) 0);
	g_Address->Size();
}

LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm)
{
	int nCurSelIndex; 
	LPNMTOOLBAR lpnmToolBar = (LPNMTOOLBAR) pnm;

	if (g_bStarted) //Để tránh vòng lặp lẩn quẩn T_T
	{
		LPNMTREEVIEW lpnmTree = (LPNMTREEVIEW) pnm;
		
		switch (pnm->code)
		{
		case TVN_ITEMEXPANDING:
			g_TreeView->PreloadExpanding(lpnmTree->itemOld.hItem, lpnmTree->itemNew.hItem);
			break;
		//------------------------------------------------------------------------------
		case TVN_SELCHANGED:
			g_TreeView->Expand(g_TreeView->GetCurSel());
			g_ListView->DeleteAll(); //Xóa sạch List View để nạp cái mới
			g_ListView->LoadChild(g_TreeView->GetCurPath(), g_Drive);
			g_History->InsertAfterCur(g_TreeView->GetCurPath());

			break;
		//------------------------------------------------------------------------------
		case NM_CLICK:
			if (pnm->hwndFrom == g_ListView->GetHandle())
			{
				nCurSelIndex = ListView_GetNextItem(g_ListView->GetHandle(), -1, LVNI_FOCUSED);
				if (nCurSelIndex != -1)
					g_ListView->DisplayInfoCurSel();

			}
			break;
			
				
		 //case NM_CLICK:
		//------------------------------------------------------------------------------
		case NM_DBLCLK:
			if (pnm->hwndFrom == g_ListView->GetHandle())
				g_ListView->LoadCurSel();
			break;
		//------------------------------------------------------------------------------
		case NM_CUSTOMDRAW: //Ve lai cua so con
			if (pnm->hwndFrom == g_TreeView->GetHandle())
				DoSizeTreeView();
			break; 
		//------------------------------------------------------------------------------
		}
	}

	return 0;
}

void DoSizeTreeView()
{
	RECT newTreeRC;
	GetClientRect(g_TreeView->GetHandle(), &newTreeRC);

	if (newTreeRC.right != g_TreeViewRect.right)
	{
		g_ListView->Size();
		g_TreeViewRect = newTreeRC;
	}
}
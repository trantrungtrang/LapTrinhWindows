// QuickLaunch.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuickLaunch.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_QUICKLAUNCH, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUICKLAUNCH));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUICKLAUNCH));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszClassName = L"QuickLaunch";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	main = CreateWindowEx(0, L"QuickLaunch", L"QuickLaunch", WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU,
		500, 200, 400, 300, NULL, NULL, hInstance, NULL);
	if (!main)
		return FALSE;
	ShowWindow(main, 0);
	UpdateWindow(main);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	POINT pCursor;
	HMENU NotifyMenu;
	switch (message)
	{
	case WM_CREATE:

		LoadNIcon(hWnd);
		hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyHookProc, hInstHook, 0);
		searchBox = CreateWindowEx(0, L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_AUTOHSCROLL, 50, 30, 300, 30, hWnd, (HMENU)IDCB_SEARCH, hInst, NULL);

		LoadFile(L"C:\\Program Files (x86)");
		LoadData();
		LoadSearchBox();
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case 202:


			DialogBox(hInst, MAKEINTRESOURCE(IDD_BIEUDO), NULL, VeBieuDo);
			break;
		case IDM_EXIT:
		{
			int mess = MessageBox(hWnd, L"Bạn muốn thoát QuickLaunch ?", L"CẢNH BÁO", MB_YESNO | MB_ICONQUESTION);
			switch (mess) {
			case IDYES:
				PostQuitMessage(0);
				break;
			case IDNO:
				//ShowWindow(main, SW_SHOW);
				break;
			}
			break;
		}
		case 203: //open
			ShowWindow(main, SW_SHOW);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDCB_SEARCH: // combobox text changed event
			if (wmEvent == CBN_EDITUPDATE)
				LoadSearchBox();
			break;

		}
		break;
	case WM_DESTROY:
		SaveData();
		PostQuitMessage(0);
		break;
	case 201:
		switch (lParam)
		{
		case WM_LBUTTONUP:
			if (0 == state)
			{
				state = 1;
				ShowWindow(main, SW_SHOW);
				SetFocus(searchBox);
			}
			else
			{
				state = 0;
				ShowWindow(main, SW_HIDE);
			}
			break;
		case WM_RBUTTONUP:
			NotifyMenu = CreatePopupMenu();

			AppendMenu(NotifyMenu, MF_STRING, 204, L"Scan to build database");
			AppendMenu(NotifyMenu, MF_STRING, 202, L"View statitistics");
			AppendMenu(NotifyMenu, MF_SEPARATOR, 0, 0);
			AppendMenu(NotifyMenu, MF_STRING, IDM_ABOUT, L"About");
			AppendMenu(NotifyMenu, MF_STRING, 203, L"Open");
			AppendMenu(NotifyMenu, MF_STRING, IDM_EXIT, L"Exit");

			GetCursorPos(&pCursor);
			SetForegroundWindow(hWnd);
			TrackPopupMenu(NotifyMenu, TPM_RIGHTBUTTON, pCursor.x, pCursor.y, 0, hWnd, NULL);
			PostMessage(hWnd, WM_NULL, 0, 0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	if ((GetAsyncKeyState(VK_SPACE) & 0x0001) && (GetAsyncKeyState(VK_LCONTROL) & (0x8000)) && 0 == k)
	{
		k = 1;
		if (0 == state)
		{
			state = 1;
			ShowWindow(main, SW_SHOW);
			SetFocus(searchBox);
			return TRUE;
		}
		else
		{
			state = 0;
			ShowWindow(main, SW_HIDE);
			return TRUE;
		}
	}
	else
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x0001)
		{
			if (1 == state)
			{
				Excute();
				state = 0;
				ShowWindow(main, SW_HIDE);
			}
		}
		else
		{
			k = 0;
			return CallNextHookEx(hHook, nCode, wParam, lParam);
		}
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void LoadNIcon(HWND hwnd)//load notify icon
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	//nid.uCallbackMessage = APPWM_ICONNOTIFY;
	nid.uCallbackMessage = 201;

	wcscpy_s(nid.szTip, L"Quick Launch");
	nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));
	Shell_NotifyIcon(NIM_ADD, &nid);
}

void LoadFile(wstring path)
{
	WIN32_FIND_DATAW data;
	//find folder
	wstring tempPath = path + L"\\*.*";

	HANDLE findFile = FindFirstFile(tempPath.c_str(), &data);
	if (findFile == (HANDLE)-1)
		return;
	do
	{
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && wcscmp(data.cFileName, L".") != 0 && wcscmp(data.cFileName, L"..") != 0)
		{
			wstring folderPath = path + L"\\" + data.cFileName;
			LoadFile(folderPath);
		}
	} while (FindNextFile(findFile, &data));

	// find *.exe
	wstring exePath = path + L"\\*.exe";
	findFile = FindFirstFile(exePath.c_str(), &data);
	if (findFile == (HANDLE)-1)
		return;
	do
	{
		if (wcscmp(data.cFileName, L"") != 0)
		{
			CApp *temp;
			wstring fullPath = path + L"\\" + data.cFileName;
			temp = new CApp(data.cFileName, (WCHAR*)fullPath.c_str(), 0);
			app.push_back(temp);
		}
	} while (FindNextFile(findFile, &data));
}

void ClearItem()// clear item of the searchbox
{
	int count = SendMessage(searchBox, CB_GETCOUNT, 0, 0);
	for (int i = count - 1; i >= 0; i--)
	{
		SendMessage(searchBox, CB_DELETESTRING, i, 0);
	}
}

void LoadSearchBox() //load the search everytime the box text changed
{
	currentSearch.clear();
	WCHAR fileName[500];
	GetWindowText(searchBox, fileName, 500);
	wstring search = fileName;
	transform(search.begin(), search.end(), search.begin(), tolower);
	ClearItem();

	//load app into tempApp -- tempApp is a temp list for search
	for (int i = 0; i < app.size(); i++)
	{
		wstring temp = app[i]->GetName();
		transform(temp.begin(), temp.end(), temp.begin(), tolower);
		if (temp.find(search) != -1)
		{
			CApp *tempApp = new CApp(app[i]->GetName(), app[i]->GetPath(), 0);
			currentSearch.push_back(tempApp);
		}
	}


	//load tempApp into searchBox
	for (int i = 0; i < currentSearch.size() && i < 10; i++)
		ComboBox_AddString(searchBox, currentSearch[i]->GetName());
	if (state == 1)
		ComboBox_ShowDropdown(searchBox, TRUE);
}

void Excute() // excute the program
{
	WCHAR fileName[500];
	GetWindowText(searchBox, fileName, 500);
	wstring file = fileName;
	if (file == L"")
		return;
	for (int i = 0; i < app.size(); i++)
	{
		if (file == app[i]->GetName())
		{
			app[i]->IncSeq();
			app[i]->Execute();
			sort(app.begin(), app.end(), moreSeq());

		}
	}
}

int CountData()
{
	int count = 0;
	for (int i = 0; i < app.size(); i++)
	{
		if (app[i]->GetSeq() > 0)
			count++;
		else
			break;
	}
	return count;
}

void SaveData()
{
	int count = CountData();

	WCHAR *path = new WCHAR[MAX_PATH];
	WCHAR *buff = new WCHAR[MAX_PATH];
	swprintf(buff, MAX_PATH, L"%d", count);

	GetCurrentDirectory(MAX_PATH, path);
	wcscat_s(path, MAX_PATH, L"\\data.ini");
	WritePrivateProfileString(L"data", L"count", buff, path);

	for (int i = 0; i < count; i++)
	{
		WCHAR *seq = new WCHAR[MAX_PATH];
		swprintf(buff, MAX_PATH, L"%d", i);
		swprintf(seq, MAX_PATH, L"%d", app[i]->GetSeq());
		WritePrivateProfileString(buff, L"Name", app[i]->GetName(), path);
		WritePrivateProfileString(buff, L"Seq", seq, path);
	}
}

void LoadData()
{
	WCHAR *path = new WCHAR[MAX_PATH];
	WCHAR *buff = new WCHAR[MAX_PATH];
	int count;

	//get path
	GetCurrentDirectory(MAX_PATH, path);
	wcscat_s(path, MAX_PATH, L"\\data.ini");

	//get count
	GetPrivateProfileString(L"data", L"count", L"0", buff, MAX_PATH, path);
	count = _wtoi(buff);

	//update seq
	for (int i = 0; i < count; i++)
	{
		WCHAR *seq = new WCHAR[MAX_PATH];
		WCHAR *name = new WCHAR[MAX_PATH];
		swprintf(buff, MAX_PATH, L"%d", i);
		GetPrivateProfileString(buff, L"Name", L"Unknown", name, MAX_PATH, path);
		GetPrivateProfileString(buff, L"Seq", L"0", seq, MAX_PATH, path);
		for (int i = 0; i < app.size(); i++)
		{
			if (wcscmp(app[i]->GetName(), name) == 0)
			{
				app[i]->SetSeq(_wtoi(seq));
			}
		}
	}
	sort(app.begin(), app.end(), moreSeq());
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


struct DataLink
{
	wstring filename;
	wstring filepath;
	int solansudung = 0;
};
vector<DataLink> list;
vector<DataLink> vectorlistbox;
INT_PTR CALLBACK VeBieuDo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	int wmId, wmEvent;
	HBRUSH hbrush;

	switch (message)
	{
	case WM_INITDIALOG:	//WM_CREATE:
		return (INT_PTR)TRUE;
	case WM_CTLCOLORDLG:
		return (INT_PTR)(HBRUSH)CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			EndDialog(hWnd, 0);
		}
		break;
	//case WM_PAINT:
	//{
	//	//0 0 0 3 0 5 1
	//	//3 5 1
	//	vector<DataLink> dscanve;
	//	int tongsolansudung = 0;
	//	for (int i = 0; i < list.size(); i++)
	//	{
	//		if (list[i].solansudung != 0)
	//		{
	//			dscanve.push_back(list[i]);
	//			tongsolansudung += list[i].solansudung;
	//		}
	//	}
	//	vector<float>phantran;
	//	for (int i = 0; i < dscanve.size(); i++)
	//	{
	//		phantran.push_back(((float)dscanve[i].solansudung / tongsolansudung) * 360);
	//	}


	//	HDC hdc = GetDC(hWnd);
	//	Graphics *graphic = new Graphics(hdc);
	//	Brush* brush[6];
	//	for (int i = 0; i < 6; i++)
	//		brush[i] = new SolidBrush(Color(255, 255 - i * 40, i * 40, i * 40));

	//	int len = phantran.size();
	//	int bd = 0, docanve = 0;
	//	for (int i = 0; i < phantran.size(); i++)
	//	{
	//		docanve = phantran[i];
	//		graphic->FillPie(brush[i], Rect(0, 0, 300, 300), bd, docanve);
	//		bd += docanve;
	//	}

	//	break;
	//}
	//
	}
	return (INT_PTR)FALSE;
}

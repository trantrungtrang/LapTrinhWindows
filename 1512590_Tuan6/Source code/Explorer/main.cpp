#include "HoTro.h"
int with=200;
POINT bd;
HWND sbar;
bool kt;
WCHAR *confi;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	hins = hInstance;
	WCHAR buffer[1000];
	GetCurrentDirectory(1000, buffer);
	confi = new WCHAR[wcslen(buffer) + 15];
	wsprintf(confi, L"%s\\config.ini", buffer);

	MyRegisterClass(hInstance);
	
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	WCHAR tam[10];
	int x, y, w, h;
	GetPrivateProfileString(L"hwnd", L"left", L"200", tam, 10, confi);
	x = _wtoi(tam);
	GetPrivateProfileString(L"hwnd", L"top", L"200", tam, 10, confi);
	y = _wtoi(tam);
	GetPrivateProfileString(L"hwnd", L"right", L"800", tam, 10, confi);
	w = _wtoi(tam) - x;
	GetPrivateProfileString(L"hwnd", L"bottom", L"650", tam, 10, confi);
	h = _wtoi(tam) - y;
	GetPrivateProfileString(L"treeview", L"dodai", L"200", tam, 10, confi);
	with = _wtoi(tam);
	hWnd = CreateWindow(L"MyClass", L"File ex", WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hInstance, NULL);
	if (!hWnd)		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	iconthispc = ExtractIcon(hInstance, L"%SystemRoot%\\system32\\shell32.dll", 17 * 4 - 1);
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = iconthispc;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"MyClass";
	wcex.hIconSm = iconthispc;
	return 	RegisterClassEx(&wcex);
}
void Track(HWND hw)
{
	TRACKMOUSEEVENT a;
	a.cbSize = sizeof(TRACKMOUSEEVENT);
	a.dwFlags = TME_HOVER | TME_LEAVE;
	a.dwHoverTime = 1;
	a.hwndTrack = hw;
	TrackMouseEvent(&a);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT mes, WPARAM wparam, LPARAM lparam)
{
	RECT rect;
	int kichthuoc,vt;
	NMHDR *nmh;
	LVITEM lvi;
	LPNMTREEVIEW pnmtv;
	HTREEITEM htvitem;
	INITCOMMONCONTROLSEX icex;
	static bool xSizing = false; 
	static HDC hdc;
	static POINT bd;
	static bool track = false;
	POINT vtc;
	static int dodaitv = 200;
	static int chimang[3] = { 300, 700, -1 };
	switch (mes)
	{
	case WM_LBUTTONUP:
	{
						 ReleaseCapture();
						 kt = false;
						 break;
	}
	case WM_LBUTTONDOWN:
	{
						   bd.x = LOWORD(lparam);
						   bd.y = HIWORD(lparam);
						   if (bd.x >= with && bd.x <= with + 5)
						   {
							   kt = true;
							   SetCapture(hwnd);
							   SetCursor(LoadCursor(NULL, IDC_SIZEWE));
						   }
						   break;
	}
	case WM_MOUSEMOVE:
	{
						 GetClientRect(hwnd, &rect);
						 int x, y;
						 x = LOWORD(lparam);
						 y = HIWORD(lparam);
						 if (x >= with && x <= with + 5)
							 SetCursor(LoadCursor(NULL, IDC_SIZEWE));
						 if (kt == true)
						 {
							 with = with + x - bd.x;
							 MoveWindow(tv.GetHWND(), 0, 45, with, rect.bottom - 45 - 35, 1);
							 MoveWindow(lv.GetHWND(), with + 5, 45, rect.right - with - 10, rect.bottom - 45 - 35, 1);
							 MoveWindow(hstatic, 70, 10, rect.right - 70, 30, TRUE);
							 bd.x = x; bd.y = y;
						 }
						 break;
	}
	case WM_NOTIFY:
		nmh = (LPNMHDR)lparam;
		switch (nmh->code)
		{
		case NM_CLICK:
			switch (nmh->idFrom)
			{
			case ID_LIST:
				vt = SendMessage(lv.GetHWND(), LVM_GETNEXTITEM, -1, LVNI_SELECTED);
				if (vt == -1)
					break;
				loai = true;
				lvi.iItem = vt;
				ListView_GetItem(lv.GetHWND(), (LVITEM*)&lvi);
				chuoi = (WCHAR*)lvi.lParam;
				TheThienTrenStastus(chuoi);
				break;
			}
			break;
		case NM_DBLCLK:
			switch (nmh->idFrom)
			{
			case ID_LIST:
				vt = SendMessage(lv.GetHWND(), LVM_GETNEXTITEM, -1, LVNI_SELECTED);
				if (vt == -1)
					break;
				loai = true;
				lvi.iItem = vt;
				ListView_GetItem(lv.GetHWND(), (LVITEM*)&lvi);
				chuoi = (WCHAR*)lvi.lParam;
				lv.ChayThuMucHoacChuongTrinh(chuoi, loai);
				loai = false;
				break;
			}
			break;
		case TVN_ITEMEXPANDED:
			pnmtv = (LPNMTREEVIEW)lparam;
			tv.TacDong(pnmtv->itemNew.hItem);
			break;
		case TVN_SELCHANGED:
			tv.MoRa();
			chuoi = tv.LayDuongDan(tv.LayItemTacDong());
			lv.ChayThuMucHoacChuongTrinh(chuoi, loai);
			break;
		}
		break;
	case WM_COMMAND:
		if (LOWORD(wparam) == ID_BUTTON)
		{
			if (wcscmp(chuoi, L"This PC"))
				chuoi = XacDinhChuoiCha(chuoi);
			lv.ChayThuMucHoacChuongTrinh(chuoi, loai);
		}
		break;
	case WM_CREATE:
		icex.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&icex);
		odia.LayODiaTuSystem();
		chuoi = L"This PC";
		GetClientRect(hwnd, &rect);
		tv.Create(hwnd);
		lv.Create(hwnd);
		button = CreateWindow(WC_BUTTON, L"<---", WS_CHILD | WS_VISIBLE | WS_DISABLED, 10, 10, 40, 40, hwnd, (HMENU)ID_BUTTON, hins, NULL);
		hstatic = CreateWindow(WC_STATIC, L"This PC", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTERIMAGE, 0, 0, 0, 0, hwnd, (HMENU)ID_BUTTON, hins, NULL);
		sbar = CreateWindow(STATUSCLASSNAME, L"", WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, hwnd, (HMENU)ID_BUTTON, hins, NULL);
		SendMessage(sbar, SB_SETMINHEIGHT, 35, 0);
		SendMessage(sbar, SB_SETPARTS, 3, (LPARAM)&chimang);
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &rect);
		MoveWindow(tv.GetHWND(), 0, 45, with, rect.bottom - 35 - 45, 1);
		MoveWindow(lv.GetHWND(), with + 5, 45, rect.right - with - 10, rect.bottom - 35 - 45, 1);
		MoveWindow(sbar, 0, rect.bottom - 35, rect.right, 35, 1);
		MoveWindow(hstatic, 70, 10, rect.right - 70, 30, TRUE);
		SendMessage(sbar, SB_SETMINHEIGHT, 35, 0);
		break;
	case WM_DESTROY:
	{
					   WCHAR tam[10];
					   GetWindowRect(hWnd, &rect);
					   WritePrivateProfileString(L"hwnd", L"left", _itow(rect.left, tam, 10), confi);
					   WritePrivateProfileString(L"hwnd", L"top", _itow(rect.top, tam, 10), confi);
					   WritePrivateProfileString(L"hwnd", L"right", _itow(rect.right, tam, 10), confi);
					   WritePrivateProfileString(L"hwnd", L"bottom", _itow(rect.bottom, tam, 10), confi);
					   WritePrivateProfileString(L"treeview", L"dodai", _itow(with, tam, 10), confi);
					   PostQuitMessage(0);
	}
		break;
	}
	return DefWindowProc(hwnd, mes, wparam, lparam);
}
void TheThienTrenStastus(WCHAR* chuoi)
{
	if (wcslen(chuoi) == 2)
	{
		long long tamp = 0;
		SHGetDiskFreeSpaceEx(chuoi, NULL, (PULARGE_INTEGER)&tamp,NULL);
		SendMessage(sbar, WM_SETTEXT, 0, (LPARAM)chuoi);
		SendMessage(sbar, WM_SETTEXT, 1, (LPARAM)Convert(tamp));
	}
	else
	{
		WIN32_FIND_DATA fd;
		FindFirstFile(chuoi, &fd);
		SendMessage(sbar, WM_SETTEXT, 0, (LPARAM)fd.cFileName);
		if (fd.nFileSizeLow != 0)
			SendMessage(sbar, WM_SETTEXT, 1, (LPARAM)Convert(fd.nFileSizeLow));
		else
			SendMessage(sbar, WM_SETTEXT, 1, (LPARAM)L"");
	}
}




// 1512590.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512590.h"
#include <windowsx.h>
#include <string>
#include <fstream>
#include <vector>
#include"QuanLyChiTieu.h"
#include <codecvt>
using namespace std;
#define MAX_LOADSTRING 100

extern  TCHAR loaiChiTieu[6][100] = {  L"Ăn uống", L"Di chuyển",L"Dịch vụ", L"Nhà cửa", L"Nhu yếu phẩm", L"Xe cộ"  };
int val[6];
vector<QuanLyChiTieu> QLCT;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK XuLyDialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID DocFile(HWND);
VOID GhiFile();

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
	LoadStringW(hInstance, IDC_MY1512590, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1512590));

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
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1512590));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY1512590);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
		memset(val, 0, sizeof(val));
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, XuLyDialog);
		GhiFile();
		DestroyWindow(hWnd);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK XuLyDialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	TCHAR temp1[MAX_LOADSTRING];
	TCHAR temp2[MAX_LOADSTRING];

	switch (message)
	{
	case WM_INITDIALOG:	//WM_CREATE:
		for (int i = 0; i < 6; ++i)
		{
			SendMessage(GetDlgItem(hwnd, IDC_COMBO_LOAICHITIEU), CB_ADDSTRING, NULL, (LPARAM)loaiChiTieu[i]);

		}
		SendMessage(GetDlgItem(hwnd, IDC_COMBO_LOAICHITIEU), CB_SETCURSEL, NULL, 0);
		DocFile(hwnd);
		return (INT_PTR)TRUE;
	case WM_PAINT:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDTHOAT:
		{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_EDIT_NOIDUNG: 
		case IDC_EDIT_SOTIEN:
			if (Edit_GetTextLength(GetDlgItem(hwnd, IDC_EDIT_NOIDUNG)) && Edit_GetTextLength(GetDlgItem(hwnd, IDC_EDIT_SOTIEN)))
				EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_THEM), true);
			else
				EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_THEM), false);
			return (INT_PTR)TRUE;
		case IDC_BUTTON_THEM:
			int cursel = SendMessage(GetDlgItem(hwnd, IDC_COMBO_LOAICHITIEU), CB_GETCURSEL, NULL, NULL);
			Edit_GetText(GetDlgItem(hwnd, IDC_EDIT_SOTIEN), temp1, MAX_LOADSTRING);
			Edit_GetText(GetDlgItem(hwnd, IDC_EDIT_NOIDUNG), temp2, MAX_LOADSTRING);
			QuanLyChiTieu ChiTieu(loaiChiTieu[cursel], temp2, temp1);
			QLCT.push_back(ChiTieu);
			ChiTieu.ThemVaoDanhSach(GetDlgItem(hwnd, IDC_LIST_DANHSACHCHITIEU));
			for (int i = cursel; i < 6; ++i)
				val[i] += _wtoi(temp1);
			SetDlgItemInt(hwnd, IDC_EDIT_TONGCONG , val[5], false);

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

VOID DocFile(HWND hDlg)
{
	wifstream is("data.txt");

	wstring str;
	is.imbue(locale(is.getloc(), new codecvt_utf8_utf16<TCHAR>));
	while (is.good())
	{
		getline(is, str);
		QuanLyChiTieu ct = QuanLyChiTieu(str.c_str());
		int sel;
		for (sel = 0; sel < 6; ++sel)
		{
			if (!wcscmp(ct.Loai, loaiChiTieu[sel]))
				break;
		}
		for (; sel < 6; ++sel)
			val[sel] += _wtoi(ct.Tien);
		QLCT.push_back(ct);
		ct.ThemVaoDanhSach(GetDlgItem(hDlg, IDC_LIST_DANHSACHCHITIEU));
	}
	SetDlgItemInt(hDlg, IDC_EDIT_TONGCONG, val[5], false);

}

VOID GhiFile()
{
	if (QLCT.empty()) {
		return;

	}

	wofstream os("data.txt");

	if (!os.good())
		return;

	os.imbue(locale(os.getloc(), new codecvt_utf8_utf16<TCHAR>));

	QLCT[0].Ghi(os) ;
	for (int i = 1; i < QLCT.size(); ++i)
	{
		os << endl;
		QLCT[i].Ghi(os);
	}
}


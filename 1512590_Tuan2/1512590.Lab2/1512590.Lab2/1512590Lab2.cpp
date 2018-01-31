// 1512590Lab2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512590Lab2.h"
#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
int WINAPI MessageBox(_In_opt_ HWND hWnd,_In_opt_ LPCTSTR lpText,_In_opt_ LPCTSTR lpCaption,_In_ UINT uType);

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_1512590LAB2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_1512590LAB2));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(238, 238, 238));
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_1512590LAB2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

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

//khác
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, L"Bảng Tư Vấn Mua iPad", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);		
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Message handler for about box.

#define CreateTextBox(text, left, top, width, height, ID) 

HWND tienNhat;
HWND tienSingapore;
HWND ketQua;
HWND so1VND;
HWND so2VND;
HWND JPYtoVND;
HWND SGDtoVND;
unsigned long int soTien1;
unsigned long int soTien2;
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
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	HWND hwnd = CreateWindowEx(0, L"BUTTON", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 400, 100, 40, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"BUTTON", L"JPY to VND: ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 300, 100, 40, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"BUTTON", L"SGD to VND", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 200, 100, 40, hWnd, (HMENU)IDC_BUTTON3, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Giá tiền Singapore:", WS_CHILD | WS_VISIBLE | SS_CENTER, 200, 200, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Giá tiền Nhật:", WS_CHILD | WS_VISIBLE | SS_CENTER, 200, 300, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"JPY", WS_CHILD | WS_VISIBLE | SS_CENTER, 455, 310, 25, 15, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"VND", WS_CHILD | WS_VISIBLE | SS_CENTER, 750, 310, 25, 15, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"VND", WS_CHILD | WS_VISIBLE | SS_CENTER, 750, 210, 25, 15, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"SGD", WS_CHILD | WS_VISIBLE | SS_CENTER, 455, 210, 25, 15, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"CHƯƠNG TRÌNH TƯ VẪN MUA IPAD ", WS_CHILD | WS_VISIBLE | SS_CENTER, 400, 100, 200, 40, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	tienNhat = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE  | WS_BORDER| SS_CENTER | ES_NUMBER, 350, 300, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(tienNhat, WM_SETFONT, WPARAM(hFont), TRUE);

	JPYtoVND = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER| SS_CENTER | ES_NUMBER, 630, 300, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(JPYtoVND, WM_SETFONT, WPARAM(hFont), TRUE);

	SGDtoVND = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER| SS_CENTER | ES_NUMBER, 630, 200, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(SGDtoVND, WM_SETFONT, WPARAM(hFont), TRUE);

	tienSingapore = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | ES_NUMBER, 350, 200, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(tienSingapore, 0, WPARAM(hFont), TRUE);

	//hwnd = CreateWindowEx(0, L"STATIC", L"Lời khuyên:", WS_CHILD | WS_VISIBLE | SS_LEFT, 200, 400, 100, 40, hWnd, NULL, hInst, NULL);
	//SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	ketQua = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_BORDER| SS_CENTER | ES_NUMBER, 350, 400, 400, 50, hWnd, NULL, hInst, NULL);
	SendMessage(ketQua, WM_SETFONT, WPARAM(hFont), TRUE);

	return true;
}
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	WCHAR* buffer1 = NULL;
	WCHAR* buffer2 = NULL;
	WCHAR* bufferKQ = NULL;
	WCHAR* bufferKQJPStoVND = NULL;
	WCHAR* bufferKQSGDtoVND = NULL;
	int size1;
	int size2;
	int sizeKQ;
	int sizeKQJPStoVND;
	int sizeKQSGDtoVND;

	unsigned long int so1JPY;
	unsigned long int so2SGD;

	size1 = GetWindowTextLength(tienNhat);
	size2 = GetWindowTextLength(tienSingapore);

	buffer1 = new WCHAR[size1 + 1];
	buffer2 = new WCHAR[size2 + 1];

	GetWindowText(tienNhat, buffer1, size1 + 1);
	GetWindowText(tienSingapore, buffer2, size2 + 1);

	so1JPY = _wtoi(buffer1);
	so2SGD = _wtoi(buffer2);

	soTien1 = so1JPY * 204;
	soTien2 = so2SGD * 16885;
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case IDM_Window:
		//
		DialogBox(hInst, MAKEINTRESOURCE(IDD_1512590LAB2_DIALOG), hWnd, About);

		break;
	case IDC_BUTTON1:
		bufferKQ = new WCHAR[255];

		if (soTien1 < soTien2) {
			wsprintf(bufferKQ, L"Nên Mua iPad Nhật với giá: %d JPY (Lưu ý: Chương trình chỉ tính toán số nguyên!)", so1JPY);
			int msgboxID = MessageBox(NULL,(LPCWSTR)L"NÊN MUA IPAD NHẬT VÌ NÓ RẺ HƠN",(LPCWSTR)L"Thông Báo",NULL);
			
		}
		else if (soTien1 > soTien2) {
			wsprintf(bufferKQ, L"Nên Mua iPad Sin với giá: %d SGD (Lưu ý: Chương trình chỉ tính toán số nguyên!)", so2SGD);
			int msgboxID = MessageBox(NULL,(LPCWSTR)L"NÊN MUA IPAD SINGAPORE VÌ NÓ RẺ HƠN",(LPCWSTR)L"Thông Báo",NULL);
		}
		else if (soTien1 == soTien2) {
			wsprintf(bufferKQ, L"Mua loại nào cũng được. Vì hai iPad cùng giá tiền");
			int msgboxID = MessageBox(NULL, (LPCWSTR)L"MUA LOẠI NÀO CŨNG ĐƯỢC. VÌ CHÚNG CÙNG GIÁ", (LPCWSTR)L"Thông Báo", NULL);
		}
		SetWindowText(ketQua, bufferKQ);
		break;
	case IDC_BUTTON2:
		bufferKQJPStoVND = new WCHAR[255];
		wsprintf(bufferKQJPStoVND,L"%d", soTien1);
		SetWindowText(JPYtoVND, bufferKQJPStoVND);
		break;
	case IDC_BUTTON3:
		bufferKQSGDtoVND = new WCHAR[255];
		wsprintf(bufferKQSGDtoVND, L"%d", soTien2);
		SetWindowText(SGDtoVND, bufferKQSGDtoVND);
		break;
	}


	if (!buffer1)
		delete[] buffer1;
	if (!buffer2)
		delete[] buffer2;
	if (!bufferKQ)
		delete[] bufferKQ;
	if (!bufferKQJPStoVND)
		delete[] bufferKQJPStoVND;
	if (!bufferKQSGDtoVND)
		delete[] bufferKQSGDtoVND;
}


void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

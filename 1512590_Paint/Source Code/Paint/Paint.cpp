// paint.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "paint.h"
using namespace std;

#define MAX_LOADSTRING 100
#define LINE 0
#define RECTANGLE 1
#define ELLIPSE 2

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;

class CShape
{
protected:
	POINT lefttop;
	POINT rightbottom;
public:
	virtual void Draw(HDC hdc) = 0;
	virtual CShape* Create() = 0;
	virtual void SetData(int a, int b, int c, int d) = 0;
	CShape(){}
	~CShape(){}
};

class CLine : public CShape
{
public:
	CLine(){}
	void CLine::Draw(HDC hdc)
	{
		MoveToEx(hdc, lefttop.x, lefttop.y, NULL);
		LineTo(hdc, rightbottom.x, rightbottom.y);
	}
	CShape* CLine::Create()
	{
		return new CLine;
	}

	void CLine::SetData(int a, int b, int c, int d)
	{
		lefttop.x = a;
		lefttop.y = b;
		rightbottom.x = c;
		rightbottom.y = d;
	
	}
	~CLine(){}
};

class CRectangle : public CShape
{
public:
	CRectangle(){}
	void CRectangle::Draw(HDC hdc)
	{
		Rectangle(hdc, lefttop.x, lefttop.y, rightbottom.x, rightbottom.y);

	}
	CShape* CRectangle::Create()
	{
		return new CRectangle;
	}

	void CRectangle::SetData(int a, int b, int c, int d)
	{
		lefttop.x = a;
		lefttop.y = b;
		rightbottom.x = c;
		rightbottom.y = d;
	}
	~CRectangle(){}
};


class CEllipse : public CShape
{
public:
	CEllipse() {}
	void CEllipse::Draw(HDC hdc)
	{
		Ellipse(hdc, lefttop.x, lefttop.y, rightbottom.x, rightbottom.y);
	}
	CShape* CEllipse::Create() { return new CEllipse; }

	void CEllipse::SetData(int a, int b, int c, int d)
	{
		lefttop.x = a;
		lefttop.y = b;
		rightbottom.x = c;
		rightbottom.y = d;

	}
	~CEllipse(){}
};

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
bool isDrawing;
POINT pCurrent, pEnd;
int iChoose ;		
vector<CShape*> gShapes;
vector<CShape*> gPrototypes;
HMENU hMenu;
RECT rect;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
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
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_PAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
void SquaresCircle()
{
	if (abs(pCurrent.x - pEnd.x) > abs(pCurrent.y - pEnd.y))
	{
		if (pCurrent.x > pEnd.x)
			pEnd.x = pCurrent.x - abs(pCurrent.y - pEnd.y);
		else
			pEnd.x = pCurrent.x + abs(pCurrent.y - pEnd.y);
	}
	else
	{
		if (pCurrent.y > pEnd.y)
			pEnd.y = pCurrent.y - abs(pCurrent.x - pEnd.x);
		else
			pEnd.y = pCurrent.y + abs(pCurrent.x - pEnd.x);
	}
}


BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct) {
	hMenu = GetMenu(hWnd);
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); //them
	CheckMenuItem(hMenu, ID_DRAW_LINE, MF_CHECKED);		//chon LINE lam mac dinh
	gPrototypes.push_back(new CLine); //tạo ra 1 mau LINE
	return true;
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify) {
	hMenu = GetMenu(hWnd);
	switch (id)
	{
	case ID_DRAW_LINE:
	{
		iChoose = 0;
		CheckMenuItem(hMenu, ID_DRAW_LINE, MF_CHECKED);		// tick o LINE
		CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_UNCHECKED);
		break;
	}
	case ID_DRAW_RECTANGLE:
	{
		iChoose = 1;
		CheckMenuItem(hMenu, ID_DRAW_LINE, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_CHECKED);  // tick o rectangle
		CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_UNCHECKED);
		break;
	}
	case ID_DRAW_ELLIPSE:
	{
		iChoose = 2;
		CheckMenuItem(hMenu, ID_DRAW_LINE, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_CHECKED);  //tick o ellipse
		break;
	}
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	}
}

void OnButtonDown(HWND hwnd, int dc, int x, int y, LPARAM lParam)
{
	if (!isDrawing)
	{
		isDrawing = TRUE;
		pCurrent.x = x;
		pCurrent.y = y;
	}
}

void OnButtonUp(HWND hWnd, int x, int y, LPARAM lParam)
{
	pEnd.x = x;
	pEnd.y = y;
	if (iChoose == LINE)
	{
		CLine* line = new CLine;

		line->SetData(pCurrent.x, pCurrent.y, pEnd.x, pEnd.y);
		gShapes.push_back(line);
	}
	else if (iChoose == RECTANGLE)
	{
		if (lParam & MK_SHIFT)		
			SquaresCircle();
		CRectangle* rect = new CRectangle;
		rect->SetData(pCurrent.x, pCurrent.y, pEnd.x, pEnd.y);
		gShapes.push_back(rect);
	}
	else
	{
		if (lParam & MK_SHIFT)		
			SquaresCircle();
		CEllipse* ellipse = new CEllipse;
		ellipse->SetData(pCurrent.x, pCurrent.y, pEnd.x, pEnd.y);
		gShapes.push_back(ellipse);
	}

	isDrawing = FALSE;
	InvalidateRect(hWnd, NULL, FALSE);
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);   //chuan bi cua so de ve
	Graphics* graphics = new Graphics(hdc);

	HBRUSH hbr = GetStockBrush(NULL_BRUSH);
	GetClientRect(hWnd, &rect);
	HDC vHdc = CreateCompatibleDC(hdc);
	HBITMAP vBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	SelectObject(vHdc, vBitmap);
	FillRect(vHdc, &rect, HBRUSH(RGB(255, 255, 255)));//tao 1 vung trang moi de ve tiep ma k de len cac hinh da ve truoc do
	SelectObject(vHdc, hbr); // doi tuong moi luc nay se thay the doi tuong cu
							 //SelectObject(vHdc, CreatePen(0,1,RGB(0,0,0)));


	for (int i = 0; i < gShapes.size(); i++)
		gShapes[i]->Draw(vHdc);
	graphics->DrawLines;

	if (isDrawing) {
		if (iChoose == LINE)
		{
			MoveToEx(vHdc, pCurrent.x, pCurrent.y, NULL);
			LineTo(vHdc, pEnd.x, pEnd.y);
		}
		else if (iChoose == RECTANGLE)
		{
			Rectangle(vHdc, pCurrent.x, pCurrent.y, pEnd.x, pEnd.y);
		}
		else
		{
			Ellipse(vHdc, pCurrent.x, pCurrent.y, pEnd.x, pEnd.y);
		}
	}
	//BOOL BitBlt(_In_ HDC   hdcDest,_In_ int   nXDest,_In_ int   nYDest,_In_ int   nWidth,_In_ int   nHeight,_In_ HDC   hdcSrc,_In_ int   nXSrc,_In_ int   nYSrc,_In_ DWORD dwRop);
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, vHdc, 0, 0, SRCCOPY);
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnButtonUp);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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




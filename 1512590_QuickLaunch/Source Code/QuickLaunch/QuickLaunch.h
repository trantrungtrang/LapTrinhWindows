#pragma once

#include "resource.h"
#include <string>
#include <iostream>
using namespace std;
#include <windowsx.h>
#define MAX_LOADSTRING 100

#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
//Windows Aero theme
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Global Variables:
HINSTANCE hInst, hInstHook, hInstIcon;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND main, searchBox;
NOTIFYICONDATA nid = {};
HHOOK hHook;
int k = 0, state = 0;
vector<CApp*> app;
vector<CApp*> currentSearch;
struct moreSeq
{
	inline bool operator() (CApp *app1, CApp *app2)
	{
		return (app1->GetSeq() > app2->GetSeq());
	}
};
												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK VeBieuDo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam);
void LoadNIcon(HWND hwnd);
void LoadFile(wstring path);
void LoadSearchBox();
void Excute();
void ClearItem();
void LoadData();
void SaveData();
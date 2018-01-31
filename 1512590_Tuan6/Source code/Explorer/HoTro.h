#pragma once
#define ID_TREE   1000
#define ID_LIST   1001
#define ID_BUTTON 1002
#define ID_STATUSBAR 1003

#include <Windows.h>
#include <CommCtrl.h>
#include <Shellapi.h>
#include <Shobjidl.h>
#include <Shlobj.h>
#include <time.h>
#include "Tree.h"
#include "List.h"
#include "Disk.h"
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"Shlwapi.lib")
#pragma comment (lib,"Shell32.lib")

ATOM MyRegisterClass(HINSTANCE);
WCHAR* Convert(long long nSize);
void TheThienTrenStastus(WCHAR* chuoi);
WCHAR* ChuyenNgay(WIN32_FIND_DATA fd);
BOOL InitInstance(HINSTANCE, int);
WCHAR* LayKieuLoai(WIN32_FIND_DATA fd);
LPWSTR XacDinhChuoiCha(LPWSTR con);
void LayIconAnhTren(WCHAR * duongdan);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

extern HINSTANCE hins;
extern HWND hWnd;
extern HWND button;
extern HWND hstatic;
extern LPWSTR chuoi;
extern HICON lui;
extern HICON iconthispc;
extern int  with;
extern WCHAR *confi;
extern int loai;
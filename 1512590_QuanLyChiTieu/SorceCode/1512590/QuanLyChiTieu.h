#pragma once
#include "stdafx.h"
#include "1512590.h"
#include <windowsx.h>
#include <string>
#include <fstream>
#include <vector>
#include<sstream>
#define MAX 1000
using namespace std;
class QuanLyChiTieu
{

public:
	TCHAR Loai[MAX];
	TCHAR NoiDung[MAX];
	TCHAR Tien[MAX];
	TCHAR loaiChiTieu[6][100] = { L"Ăn uống", L"Di chuyển",L"Dịch vụ", L"Nhà cửa", L"Nhu yếu phẩm", L"Xe cộ" };
	QuanLyChiTieu(TCHAR*, TCHAR*, TCHAR*);
	QuanLyChiTieu(const TCHAR*);
	void ThemVaoDanhSach(HWND);
	void Ghi(wofstream &);
	~QuanLyChiTieu();
};


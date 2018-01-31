#include "stdafx.h"
#include "QuanLyChiTieu.h"


QuanLyChiTieu::QuanLyChiTieu(TCHAR* loai, TCHAR* noidung, TCHAR* tien)
{
	memcpy(Loai, loai, sizeof(Loai));
	memcpy(NoiDung, noidung, sizeof(NoiDung));
	memcpy(Tien, tien, sizeof(Tien));
}

QuanLyChiTieu::QuanLyChiTieu(const TCHAR* line)
{
	TCHAR temp[MAX];
	wstringstream str;   //dung th vien <sstream>
	str.clear();
	str << line;
	str.getline(temp, MAX, L'\t');
	wcscpy(Loai, loaiChiTieu[_wtoi(temp)]);
	str.getline(temp, MAX, L'\t');
	wcscpy(NoiDung, temp);
	str.getline(temp, MAX);
	wcscpy(Tien, temp);
}

void QuanLyChiTieu::ThemVaoDanhSach(HWND hwnd)
{
	wstring temp;
	temp += wstring(Loai) + wstring(L", ") + wstring(NoiDung) + wstring(L", ") + wstring(Tien);
	SendMessage(hwnd, LB_ADDSTRING, NULL, (LPARAM)temp.c_str());
}

void QuanLyChiTieu::Ghi(wofstream &os)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (!wcscmp(Loai, loaiChiTieu[i]))
			break;
	}
	TCHAR str[MAX];
	_swprintf(str, L"%d\t%s\t%s", i, NoiDung, Tien);
	os << str;
}



QuanLyChiTieu::~QuanLyChiTieu()
{
}

#include "HoTro.h"

WCHAR* Convert(long long nSize)
{
	int nType = 0;
	while (nSize >= 1048576) //
	{
		nSize /= 1024;
		++nType;
	}
	long long nRight;
	if (nSize >= 1024)
	{
		nRight = nSize % 1024;
		while (nRight > 99)
			nRight /= 10;
		nSize /= 1024;
		++nType;
	}
	else
		nRight = 0;
	WCHAR *buffer = new WCHAR[11];
	_itow_s(nSize, buffer, 11, 10);
	if (nRight != 0 && nType > 1)
	{
		wcscat(buffer, L".");
		WCHAR *right = new WCHAR[3];
		_itow_s(nRight, right, 3, 10);
		wcscat(buffer, right);
	}
	if (buffer[0] == L'0')
		return L"";
	switch (nType)
	{
	case 0://Bytes
		wcscat(buffer, L" bytes");
		break;
	case 1:
		wcscat(buffer, L" KB");
		break;
	case 2:
		wcscat(buffer, L" MB");
		break;
	case 3:
		wcscat(buffer, L" GB");
		break;
	case 4:
		wcscat(buffer, L" TB");
		break;
	}
	return buffer;
}

WCHAR* ChuyenNgay(WIN32_FIND_DATA fd)
{
	FILETIME ft = fd.ftLastWriteTime;
	ULARGE_INTEGER ull;
	ull.LowPart = ft.dwLowDateTime;
	ull.HighPart = ft.dwHighDateTime;
	time_t t = ull.QuadPart / 10000000ULL - 11644473600ULL;
	tm *ltm = localtime(&t);
	WCHAR *tam = new WCHAR[20];
	wsprintf(tam, L"%d-%d-%d %d:%d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year, ltm->tm_hour, ltm->tm_min);
	return tam;
}
WCHAR* LayKieuLoai(WIN32_FIND_DATA fd)
{
	if (fd.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)
		return  L"File Folder";
	int vt = wcsrchr(fd.cFileName, L'.') - fd.cFileName;
	int len = wcslen(fd.cFileName);
	if (vt < 0 || vt >= len) //Nếu không tìm thấy
		return L"";
	WCHAR *duoi = new WCHAR[len - vt + 1];
	for (int i = 0; i < len - vt; i++)
		duoi[i] = fd.cFileName[vt + i];
	duoi[len - vt] = 0;
	if (!wcsicmp(duoi, L".htm") || !wcsicmp(duoi, L".html"))
		return L"Web page";
	WCHAR pszOut[256];
	HKEY hKey;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 256;
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, duoi, 0, KEY_READ, &hKey))
	{
		RegCloseKey(hKey);
		return L"";
	}
	if (RegQueryValueEx(hKey, NULL, NULL, &dwType, (PBYTE)pszOut, &dwSize))
	{
		RegCloseKey(hKey);
		return L"";
	}
	RegCloseKey(hKey);
	WCHAR *pszPath = new WCHAR[1000];
	dwSize = 1000;
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, pszOut, 0, KEY_READ, &hKey))
	{
		RegCloseKey(hKey);
		return L"";
	}

	if (RegQueryValueEx(hKey, NULL, NULL, &dwType, (PBYTE)pszPath, &dwSize))
	{
		RegCloseKey(hKey);
		return L"";
	}
	RegCloseKey(hKey);
	return pszPath;
}
LPWSTR XacDinhChuoiCha(LPWSTR con)
{
	int len = wcslen(con);
	if (len < 3)
		return L"This PC";
	else
	{
		len = wcsrchr(con, L'\\') - con;
		con[len] = 0;
	}
	return con;
}
void LayIconAnhTren(WCHAR * duongdan)
{
	HICON hicon;
	if (!wcscmp(duongdan, L"This PC"))
	{
		SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 17 * 4 - 1));
		return;
	}
	WORD a = 0;
	int len = wcslen(duongdan);
	if (len == 2)
	{
		SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)ExtractAssociatedIcon(hins, duongdan, &a));
		return;
	}
	WCHAR * link = new WCHAR[1000];
	wcscpy(link, duongdan);
	link[len] = 0;
	int vt = wcsrchr(link, L'.') - link;
	if (vt < 0 || vt >= len)
	{
		SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)ExtractAssociatedIcon(hins, duongdan, &a));
		return;
	}
	WCHAR *duoi = new WCHAR[len - vt + 1];
	for (int i = 0; i < len - vt; i++)
		duoi[i] = link[vt + i];
	duoi[len - vt] = 0;
	if (!wcsicmp(duoi, L".htm") || !wcsicmp(duoi, L".html"))
	{
		SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 55 * 4));
		return;
	}
	SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)ExtractAssociatedIconW(hins, link, &a));

}
HWND hWnd;
HWND button;
HWND hstatic;
HINSTANCE hins;
Disk odia;
Tree tv;
List lv;
LPWSTR chuoi;
HICON lui;
HICON iconthispc;
int loai = 0;
#include "Disk.h"


OCung::OCung()
{
	cung = new WCHAR[3];
	cung[0] = 0;
	cung[1] = L':';
	cung[2] = 0;
	free = 0;
	total = 0;
	loai = new WCHAR[15];
}
void OCung::ThemVao(WCHAR ten)
{
	cung[0] = ten;
	Type();
	Size();
}
OCung::~OCung()
{
	delete[] cung;
	delete[] loai;
}
void OCung::Type()
{
	int kieu = GetDriveType(cung);
	switch (kieu)
	{
	case DRIVE_UNKNOWN:
	case DRIVE_NO_ROOT_DIR:
		wcscpy(loai, L"Khong biet");
		break;
	case DRIVE_REMOVABLE:
		wcscpy(loai, L"Removable Disk");
		break;
	case DRIVE_FIXED:
		wcscpy(loai, L"Local Disk");
		break;
	case DRIVE_REMOTE:
		wcscpy(loai, L"Remote Drive");
		break;
	case DRIVE_CDROM:
		wcscpy(loai, L"CD Drive");
		break;
	case DRIVE_RAMDISK:
		wcscpy(loai, L"Ram Disk");
		break;
	}
}
void OCung::Size()
{
	WCHAR a[4];
	wsprintf(a, L"%s", cung);
	SHGetDiskFreeSpaceEx(a, NULL, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);
}
Disk::Disk()
{
	dem = 0;
}
void Disk::LayODiaTuSystem()
{
	WCHAR s[26 * 4 + 1];
	GetLogicalDriveStrings(26 * 4 + 1, s);
	if (wcslen(s) == 0)
	{
		MessageBox(hWnd, L"Khong tim thay o dia nao", L"Error", MB_OK | MB_ICONERROR);
		DestroyWindow(hWnd);
		return;
	}
	for (int i = 0; s[i] != 0; i = i + 4)
		this->ocung[dem++].ThemVao(s[i]);
}
Disk::~Disk()
{
}

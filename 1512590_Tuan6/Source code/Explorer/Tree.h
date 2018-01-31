#pragma once
#include "HoTro.h"
class Tree
{
	HWND hTree;
	HTREEITEM pc;
	HIMAGELIST hil;
public:
	friend class Disk;
	friend class List;
	friend class OCung;
	Tree();
	void Create(HWND);
	void ResizeWindow(int, int, int, int);
	void TaoPC();
	HTREEITEM ThemItem(WCHAR *,WCHAR*,HTREEITEM);
	void TaiItemTuFolderVaoTree(WCHAR*, HTREEITEM);
	bool KiemTraCoCon(WCHAR *, HTREEITEM);
	void ThemODiaVaoPC();
	HWND GetHWND();
	void TacDong(HTREEITEM);
	WCHAR * LayDuongDan(HTREEITEM);
	void MoRa();
	HTREEITEM LayItemTacDong();
	int LayIconAnh(WCHAR*);
	~Tree();
};
extern Tree tv;

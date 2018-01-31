#pragma once
#include "HoTro.h"
class List
{
	HWND hList;
	bool cot;
	HIMAGELIST hil;
public:
	friend class Disk;
	friend class OCung;
	friend class Tree;
	List();
	void Create(HWND);
	void TaoCotThuMuc();
	void ResizeWindow(int,int,int,int);
	void TaoCotOCung();
	void TaiPCVaoList();
	void TaiDiskVaoList(int);
	void ThemItemVaoList(WCHAR*, WIN32_FIND_DATA);
	void HienThiList(WCHAR*);
	void ChayThuMucHoacChuongTrinh(WCHAR *,bool);
	HWND GetHWND();
	int LayIconAnh(WCHAR *);
	~List();
};
extern List lv;
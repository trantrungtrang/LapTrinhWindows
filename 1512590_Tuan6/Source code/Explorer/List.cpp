#include "List.h"



List::List()
{
	cot = true;
}
List::~List()
{
}

void List::Create(HWND cha)
{

	this->hList = CreateWindowEx(0, WC_LISTVIEW, L"ListView", WS_CHILD | LVS_EDITLABELS | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_ICON, 0,0,0,0, cha, (HMENU)ID_LIST, hins, NULL);
	ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT);
	this->hil = ImageList_Create(32, 32, ILC_COLOR32 | ILC_MASK, 0, 0);
	ImageList_AddIcon(this->hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 3));
	ListView_SetImageList(this->hList,this->hil,LVSIL_SMALL);
	this->TaoCotOCung();
	this->TaiPCVaoList();
}
void List::TaoCotThuMuc()
{
	LVCOLUMN cot;
	cot.cx = 250;
	cot.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	cot.fmt = LVCFMT_LEFT;
	cot.pszText = L"Name";
	ListView_InsertColumn(this->hList, 0, &cot);
	cot.cx = 170;
	cot.pszText = L"Date modified";
	ListView_InsertColumn(this->hList, 1, &cot);
	cot.cx = 120;
	cot.pszText = L"Type";
	ListView_InsertColumn(this->hList, 2, &cot);
	cot.cx = 100;
	cot.pszText = L"Size";
	ListView_InsertColumn(this->hList, 3, &cot);
}
int List::LayIconAnh(WCHAR * duongdan)
{

	WORD a = 0;
	int len = wcslen(duongdan);
	if (len == 2)
		return ImageList_AddIcon(hil, ExtractAssociatedIconW(hins, duongdan, &a));
	WCHAR * link = new WCHAR[1000];
	wcscpy(link, duongdan);
	link[len] = 0;
	int vt = wcsrchr(link, L'.') - link;
	if (vt < 0 || vt >= len)
		return 0;
	WCHAR *duoi = new WCHAR[len - vt + 1];
	for (int i = 0; i < len - vt; i++)
		duoi[i] = link[vt + i];
	duoi[len - vt] = 0;
	if (!wcsicmp(duoi, L".htm") || !wcsicmp(duoi, L".html"))
		return ImageList_AddIcon(hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 55 * 4));
	return ImageList_AddIcon(hil, ExtractAssociatedIconW(hins, link, &a));
}
void List::TaoCotOCung()
{
	LVCOLUMN cot;
	cot.cx = 250;
	cot.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT | LVCF_SUBITEM;;
	cot.fmt = LVCFMT_LEFT;
	cot.pszText = L"Name";
	ListView_InsertColumn(this->hList, 0, &cot);
	cot.cx = 170;
	cot.pszText = L"Type";
	ListView_InsertColumn(this->hList, 1, &cot);
	cot.cx = 120;
	cot.pszText = L"Total Size";
	ListView_InsertColumn(this->hList, 2, &cot);
	cot.cx = 100;
	cot.pszText = L"Free Space";
	ListView_InsertColumn(this->hList, 3, &cot);
}
void List::ResizeWindow(int x, int y, int w, int h)
{
	MoveWindow(this->hList, x, y, w, h, TRUE);
}
HWND List::GetHWND()
{
	return hList;
}
void List::TaiDiskVaoList(int sttdong)
{
	LVITEM m;
	m.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM|LVIF_GROUPID;
	m.iSubItem = 0;
	m.pszText = odia.ocung[sttdong].cung;
	m.iImage = LayIconAnh(odia.ocung[sttdong].cung);
	m.lParam = (LPARAM)odia.ocung[sttdong].cung;
	m.cchTextMax = 2;
	m.iGroupId = 0;
	m.iItem = sttdong;
	ListView_InsertItem(this->hList, &m);
	ListView_SetItemText(this->hList, sttdong, 1, odia.ocung[sttdong].loai);
	ListView_SetItemText(this->hList, sttdong, 2, Convert(odia.ocung[sttdong].total));
	ListView_SetItemText(this->hList, sttdong, 3, Convert(odia.ocung[sttdong].free));
}
void List::TaiPCVaoList()
{
	for (int i = 0; i < odia.dem; i++)
		TaiDiskVaoList(i);
}
void List::HienThiList(WCHAR *parent)
{
	
	if (cot == true)
	{
		cot = false;
		for (int i = 0; i < 4; i++)
			ListView_DeleteColumn(this->hList, 0);
		TaoCotThuMuc();
	}
	LPSHELLFOLDER folderdechua = NULL;
	LPENUMIDLIST thangdautien = NULL;
	LPITEMIDLIST itemdata = NULL;
	WIN32_FIND_DATA fd;
	LPITEMIDLIST itembandau = ILCreateFromPath(parent);
	SHBindToObject(NULL, itembandau, NULL, IID_IShellFolder, (void**)&folderdechua);
	folderdechua->EnumObjects(NULL, SHCONTF_FOLDERS|SHCONTF_NONFOLDERS, &thangdautien);
	while (thangdautien->Next(1, &itemdata, NULL) == S_OK)
	{
		SHGetDataFromIDList(folderdechua, itemdata, SHGDFIL_FINDDATA, &fd, sizeof(WIN32_FIND_DATA));
		WCHAR *child = new WCHAR[wcslen(parent) + wcslen(fd.cFileName) + 2];
		wsprintf(child, L"%s\\%s", parent, fd.cFileName);
		ThemItemVaoList(child, fd);
	}
}

void List::ThemItemVaoList(WCHAR* link, WIN32_FIND_DATA da)
{
	LVITEM m;
	m.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	m.iSubItem = 0;
	m.pszText = da.cFileName;
	WORD a;
	m.iImage = ImageList_AddIcon(this->hil, ExtractAssociatedIcon(hins,link,&a));
	m.iImage = LayIconAnh(link);
	m.lParam = (LPARAM)link;
	m.cchTextMax = 100;
	m.iItem = 0;
	ListView_InsertItem(this->hList, &m);
	ListView_SetItemText(hList, 0, 1, ChuyenNgay(da));
	ListView_SetItemText(hList, 0, 2, LayKieuLoai(da));
	ListView_SetItemText(hList, 0, 3, Convert(da.nFileSizeLow));
}
void List::ChayThuMucHoacChuongTrinh(WCHAR * link,bool loai)
{
	if (!wcscmp(link, L"This PC"))
	{
		EnableWindow(button, FALSE);
		SetWindowText(hstatic, L"This PC");
		ListView_DeleteAllItems(this->hList);
		this->cot = true;
		for (int i = 0; i < 4; i++)
			ListView_DeleteColumn(this->hList,0);
		TaoCotOCung();
		TaiPCVaoList();
		SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)iconthispc);
		return; 
	}
	WIN32_FIND_DATA fd;
	GetFileAttributesEx(link, GetFileExInfoStandard, &fd);
	if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (IsWindowEnabled(button)==false)
			EnableWindow(button, TRUE);
		SetWindowText(hstatic, link);
		ListView_DeleteAllItems(this->hList);
		HienThiList(link);
		LayIconAnhTren(link);
	}
	else
		ShellExecute(0, L"open", link, 0,0, 1);
}

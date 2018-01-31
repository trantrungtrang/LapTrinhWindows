#include "Tree.h"


Tree::Tree()
{
}
Tree::~Tree()
{
}

void Tree::Create(HWND cha)
{
	hTree = CreateWindow(WC_TREEVIEW, L"", WS_BORDER|WS_VISIBLE | WS_CHILD  | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, 0, 0, 0,0, cha, (HMENU)ID_TREE, hins, NULL);
	this->hil = ImageList_Create(16, 16, ILC_COLOR16 | ILC_MASK, 0, 0);
	ImageList_AddIcon(this->hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 3));
	ImageList_AddIcon(this->hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 68*4));
	SendMessage(hTree, TVM_SETIMAGELIST, 0, (LPARAM)hil);
	TaoPC();
	ThemODiaVaoPC();
}
void Tree::ResizeWindow(int x, int y, int w, int h)
{
	MoveWindow(this->hTree, x, y, w, h, TRUE);
}
HWND Tree::GetHWND()
{
		
	return hTree;
}
void Tree::TaoPC()
{
	WCHAR *s = new WCHAR[8];
	wcscpy(s, L"This PC");
	TVINSERTSTRUCT tv;
	tv.hInsertAfter = TVI_FIRST;
	tv.item.cchTextMax = 8;
	tv.item.iImage = 1;
	tv.item.iSelectedImage = 1;
	tv.item.lParam = (LPARAM)s;
	tv.item.pszText = s;
	tv.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tv.hParent = TVI_ROOT;
	pc= (HTREEITEM)SendMessage(hTree, TVM_INSERTITEM, 0, (LPARAM)&tv);
}

HTREEITEM Tree::ThemItem(WCHAR *link, WCHAR* s, HTREEITEM cha)
{
	int icon = LayIconAnh(link);
	TVINSERTSTRUCT tv;
	tv.hInsertAfter = cha;
	tv.item.cchTextMax = 255;
	tv.item.iImage = icon;
	tv.item.iSelectedImage = icon;
	tv.item.lParam = (LPARAM)link;
	tv.item.pszText = s;
	tv.item.mask = TVIF_TEXT| TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tv.hParent = cha;
	return (HTREEITEM)SendMessage(this->hTree, TVM_INSERTITEM, 0, (LPARAM)&tv);
}
void Tree::ThemODiaVaoPC()
{
	for (int i = 0; i < odia.dem; i++)
	{
		HTREEITEM drive=ThemItem(odia.ocung[i].cung, odia.ocung[i].cung, pc);
		KiemTraCoCon(odia.ocung[i].cung, drive);
	}
}
void Tree::TaiItemTuFolderVaoTree(WCHAR* parent, HTREEITEM cha)
{
	LPSHELLFOLDER folderdechua = NULL;
	LPENUMIDLIST thangdautien = NULL;
	LPITEMIDLIST itemdata = NULL;
	WIN32_FIND_DATA fd;
	LPITEMIDLIST itembandau = ILCreateFromPath(parent);
	SHBindToObject(NULL, itembandau, NULL, IID_IShellFolder, (void**)&folderdechua);

	folderdechua->EnumObjects(NULL, SHCONTF_FOLDERS, &thangdautien);

	while (thangdautien->Next(1, &itemdata, NULL) == S_OK)
	{
		SHGetDataFromIDList(folderdechua, itemdata, SHGDFIL_FINDDATA, &fd, sizeof(WIN32_FIND_DATA));
		WCHAR *child = new WCHAR[wcslen(parent) + wcslen(fd.cFileName) + 2];
		wsprintf(child, L"%s\\%s", parent, fd.cFileName);
		HTREEITEM con = ThemItem(child, fd.cFileName, cha);
		KiemTraCoCon(child, con);
	}

}
bool Tree::KiemTraCoCon(WCHAR *parent, HTREEITEM cha)
{
	WIN32_FIND_DATA fd;
	WCHAR folder[MAX_PATH];
	wsprintf(folder, L"%s\\*.*", parent);
	HANDLE hFind = FindFirstFile(folder, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)==false)
			{
				if (wcscmp(fd.cFileName, L".") && wcscmp(fd.cFileName, L".."))
				{
					WCHAR *child = new WCHAR[8];
					wcscpy(child, L"ItemCon");
					ThemItem(child, fd.cFileName,cha);
					return true;
				}
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
	return false;
}
WCHAR* Tree::LayDuongDan(HTREEITEM itemcanlay)
{
	TVITEMEX tv;
	tv.mask = TVIF_PARAM;
	tv.hItem = itemcanlay;
	TreeView_GetItem(this->hTree, &tv);
	return (WCHAR*)tv.lParam;
}
void Tree::TacDong(HTREEITEM itemnew)
{
	if (itemnew == this->pc)
		return;
	HTREEITEM con = TreeView_GetChild(this->hTree,itemnew);
	WCHAR *link = LayDuongDan(con);
	if (!wcscmp(link, L"ItemCon"))
	{
		TreeView_DeleteItem(this->hTree,con);
		TaiItemTuFolderVaoTree(LayDuongDan(itemnew), itemnew);
	}
}
void Tree::MoRa()
{
	HTREEITEM h = this->LayItemTacDong();
	TreeView_Expand(this->hTree, h, TVE_EXPAND);
}
HTREEITEM Tree::LayItemTacDong()
{
	return TreeView_GetNextItem(this->hTree, NULL, TVGN_CARET);
}
int Tree::LayIconAnh(WCHAR * link)
{
	WORD a = 0;
	int len = wcslen(link);
	if (len == 2)
		return ImageList_AddIcon(this -> hil, ExtractAssociatedIconW(hins, link, &a));
	return 0;

}
#ifndef DLIST_H
#define DLIST_H

#include "DNode.h"

class DList //Lớp danh sách liên kết kép để lưu vết đường dẫn
{
private:
	DNode *m_pHead;
	DNode *m_pTail;
	DNode *m_pCur;

public:
	DList();
	~DList();
	bool   IsEmpty();
	DNode* GetNode(LPCTSTR path);

	DNode* GetCur();

	void InsertAfterCur(LPCWSTR path);
	void GoBack();
	void GoForward();
};

#endif
#pragma once
#include "HoTro.h"
class OCung
{
	WCHAR *cung;
	long long  free;
	long long total;
	WCHAR* loai;
public:
	friend class Disk;
	friend class List;
	friend class Tree;
	OCung();
	~OCung();
	void ThemVao(WCHAR);
	void Type();
	void Size();
};

class Disk
{
	OCung ocung[26];
	int dem;
public:
	friend class OCung;
	friend class List;
	friend class Tree;
	Disk();
	void LayODiaTuSystem();
	~Disk();
};
extern Disk odia;
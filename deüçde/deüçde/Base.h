#include "stdafx.h"
#include "Menu.h"
#pragma once

class cBase
{

public:
	FILE *LOG;
	char dllpath[255];
	char logfile[255];
	DWORD CSH;
	HANDLE hProcces;

	struct sscreen
	{
		int height;
		int width;
	}screen;

	char* GetFile(char *file);
	void  WriteFile(FILE *file,const char *fmt, ...);

};
extern cBase Base;
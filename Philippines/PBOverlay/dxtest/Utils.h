#pragma once
#include "stdafx.h"

struct UtilsT
{
	DWORD PID;
	inline bool IsHandleValid(HANDLE h);
	inline BOOL ProperlyCloseHandle(HANDLE h);
	BOOL GetPID(const wchar_t * lpwstrProcessName, DWORD* pid);
	DWORD EnumRegions(HANDLE hProcess, DWORD ADR_CHARACTERPOINTER, DWORD falseBase = NULL);

	struct sinfo
	{
		int main;
	}info;

	struct sd3d
	{
		int main;
		int crosshair;
		int wallhack;
		int chams;
		int chamsa;
		int chamsb;
		int nofog;
		int nosmoke;
	}d3d;

	struct sesp
	{
		int health;
		int line;
		int distance;
	}esp;
};

extern UtilsT* Utils;

#pragma once
#include "stdafx.h"

struct GarenaT
{
private:
	void * d3d9SwapChain[20];
public:
	DWORD dwBase;
	DWORD dwBaseArray[3];

	DWORD dwGetRealBase()
	{
		DWORD Real;
		for (int i = 0; i < 3; i++)
		{
			if (dwBaseArray[i])
				Real = dwBaseArray[i];
		}
		return Real;
	}
	unsigned __stdcall InstallHook(LPVOID param);
};

extern GarenaT * Garena;
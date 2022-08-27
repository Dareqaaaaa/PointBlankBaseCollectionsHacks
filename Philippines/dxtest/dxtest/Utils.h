#pragma once
#include "stdafx.h"

struct PModule
{
	DWORD dwBase;
	DWORD dwSize;
};

struct UtilsT
{
private:
	HANDLE _process;
	DWORD pID;
public:
	PModule modBase;
	PModule modi3SceneDx;
	PModule modi3GfxDx;
private:
	PModule GetModule(const char* moduleName);
	PModule GetBaseAddress();
public:
	bool Attach(const char* pName, DWORD rights);
	PModule* GetClientModule();
public:
	template <class T>
	T Read(DWORD addr) {
		T _read;
		ReadProcessMemory(_process, (LPVOID)addr, &_read, sizeof(T), NULL);
		return _read;
	}
	template <class T>
	void Write(DWORD addr, T val) {
		WriteProcessMemory(_process, (LPVOID)addr, &val, sizeof(T), NULL);
	}

	template <class T>
	void Read(DWORD addr, T read, size_t _size = sizeof(T)) {
		ReadProcessMemory(_process, (LPVOID)addr, read, _size, NULL);
	}

	void ReadString(DWORD addr, size_t nSize, char buffer[]) {
		ReadProcessMemory(_process, (LPVOID)addr, buffer, nSize, NULL);
	}

	std::string ReadString(DWORD addr)
	{
		char _read[260];
		ReadProcessMemory(_process, (LPVOID)addr, &_read, sizeof(_read), NULL);
		return _read;
	}
public:
	struct sinfo
	{
		int main;
	}info;

	struct sd3d
	{
		int main;
		int crosshair;
	}d3d;

	struct smemory
	{
		int main;
		int fastreload;
		int fastswitch;
		int fastrespawn;
		int nofalldamage;
		int speedrun;
		int norecoil;
	}memory;

	struct sesp
	{
		int main;
		int bone;
		int box;
		int line;
		int distance;
		int hp;
	}esp;
};

extern UtilsT* Utils;

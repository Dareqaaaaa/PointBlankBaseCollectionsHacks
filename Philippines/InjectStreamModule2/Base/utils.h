#pragma once

struct PModule
{
	DWORD dwBase;
	DWORD dwSize;
};

class utils
{
public:
	utils();
	~utils();

	PModule modBase;
	PModule modi3SceneDx;
	PModule modi3GfxDx;
	PModule modi3FrameworkDx;
	PModule modi3MathDx;
	PModule modD3DX43;
	PModule modKernel32;
	PModule modCheatBlocker;

	HANDLE hCreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID);
	BOOL hGetThreadContext(HANDLE hThread, LPCONTEXT lpContext);
	BOOL hSetThreadContext(HANDLE hThread, const LPCONTEXT lpContext);
	PVOID hAddVectoredExceptionHandler(ULONG First, PVECTORED_EXCEPTION_HANDLER Handler);
	HANDLE hOpenThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId);
	DWORD hSuspendThread(HANDLE hThread);
	DWORD hResumeThread(HANDLE hThread);
	BOOL hCloseHandle(HANDLE hObject);
	BOOL hThread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
	BOOL hThread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte);

	DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget);
	DWORD FindPatternArray(DWORD start, DWORD size, const char* mask, int count, ...);
	DWORD FindPatternD3D9(DWORD dwStartAddress, DWORD dwSize, BYTE *bMask, char * szMask, int codeOffset, BOOL extract);
	void HideModule(HINSTANCE hModule);
	BOOL GetSwapChainAddress(void ** pTable, size_t Size);
	DWORD GetCirticalSectionAddress();
	BOOL CheckWindowsVersion(DWORD dwMajorVersion, DWORD dwMinorVersion, DWORD dwProductType);
	PModule* GetClientModule();

	struct sd3d
	{
		int main;
		int crosshair;
	}d3d;
	struct sesp
	{
		int main;
		int team;
		int bone;
		int box;
		int distace;
		int line;
		int name;
		int health;
		int healthbar;
	}esp;

	struct smemory
	{
		int main;
		int fastshot;
		int fastreloadknife;
		int rapidfire;
		int fastreload;
		int fastrespawn;
		int fastswitch;
		int nofalldamage;
		int speedhack;
		int norecoil;
		int unliammo;
		int accuracy;
		int respawnindeath;
		int fastbomb;
		int antikick;
		int unlockroom;
	}memory;

	struct stelebomb
	{
		int main;
		int draw;
	}telebomb;

	struct saimbot
	{
		int main;
		int smooth;
		int fov;
		int draw;
		int key;
		int target;
	}aimbot;

	struct saimbullet
	{
		int main;
		int target;
		int draw;
		int autoshot;
	}aimbullet;

	struct smenu
	{
		int main;
		int panickey;
		int closemenu;
	}menu;
private:
	//kernel
	typedef HANDLE(__stdcall* oCreateToolhelp32Snapshot)(DWORD dwFlags, DWORD th32ProcessID);
	typedef BOOL(__stdcall* oGetThreadContext)(HANDLE hThread, LPCONTEXT lpContext);
	typedef BOOL(__stdcall* oSetThreadContext)(HANDLE hThread, const LPCONTEXT lpContext);
	typedef PVOID (__stdcall* oAddVectoredExceptionHandler)(ULONG First, PVECTORED_EXCEPTION_HANDLER Handler);
	typedef HANDLE (__stdcall* oOpenThread)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId);

	typedef DWORD(__stdcall* oSuspendThread)(HANDLE hThread);
	typedef DWORD(__stdcall* oResumeThread)(HANDLE hThread);
	typedef BOOL (__stdcall* oCloseHandle)(HANDLE hObject);

	typedef BOOL(__stdcall* oThread32First)(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
	typedef BOOL(__stdcall* oThread32Next)(HANDLE hSnapshot, LPTHREADENTRY32 lpte);

	typedef HRESULT(__stdcall* oD3DXCreateLine)(LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE *ppLine);
	typedef HRESULT(__stdcall* oD3DXCreateFont)(IDirect3DDevice9 *pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCTSTR pFacename, LPD3DXFONT *ppFont);
	typedef D3DXVECTOR3*(__stdcall * oD3DXVec3Project)(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DVIEWPORT9 *pViewport, CONST D3DXMATRIX *pProjection, CONST D3DXMATRIX *pView, CONST D3DXMATRIX *pWorld);

	DWORD FindPattern(DWORD start, DWORD size, const char* sig, const char* mask);
	bool DataCompare(const BYTE* pData, const BYTE* pMask, const char* pszMask);
	PModule GetModule(char* moduleName);
	PModule GetBaseAddress();
};
extern utils pUtils;

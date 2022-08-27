#include "StdAfx.h"
#include "function.h"
#include "menu.h"
#include "utils.h"
#include "Xor.h"

function pFunction;
int BulletEnable, AutoShotEnable, AntiKickEnable, UnlockRoomEnable, SpeedHackEnable;
float fX, fY, fZ;
float fSpeed = 10.0f;
DWORD dwTempEcx, dwTempEbx, dwJump;
DWORD dwDisableCallBypass, dwDisableCallHelper, dwAntiKick, dwUnlockRoom;
DWORD dwDisableCallBypass_jmp, dwDisableCallHelper_jmp, dwAntiKick_jmp, dwUnlockRoom_jmp, dwSpeedHack_jmp;

function::function()
{
}

function::~function()
{
}

#pragma region Class
class i3CollideeLine
{
private:
	typedef i3CollideeLine* (__stdcall * tgetHandler)();
public:
	D3DXVECTOR3 vTemp;
	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vDir;
public:
	static i3CollideeLine* Singleton()
	{
		tgetHandler getHandler = (tgetHandler)((DWORD)GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?new_object_fun@i3CollideeLine@@SAPAV1@XZ*/XorStr<0xD5, 42, 0xC3DBDC62>("\xEA\xB8\xB2\xAF\x86\xB5\xB9\xB6\xB8\xBD\xAB\xBF\x87\x97\x8D\xA4\x8C\xD5\xA4\x87\x85\x86\x82\x88\x88\x8B\xA3\x99\x9F\x97\xB3\xB4\xA6\xB7\xA7\xB9\xAF\xCB\xBB\xA4\xA7" + 0xC3DBDC62).s));
		return (i3CollideeLine*)(getHandler());
	}
};

class i3PhysixHitResult
{
public:
	char _0x0000[28];
	D3DXVECTOR3 FinalPos;
	float Distance;
};

class dwPhtsX {
public:
	void* i3PhysixContext;
};

class i3RenderContext
{
public:
	static i3RenderContext * GetRenderContext()
	{
		return (i3RenderContext *)(*(DWORD*)(GetProcAddress((HMODULE)pUtils.modi3GfxDx.dwBase, /*?g_pRenderContext@@3PAVi3RenderContext@@A*/XorStr<0xB8, 42, 0xC8ED595D>("\x87\xDE\xE5\xCB\xEE\xD8\xD0\xDB\xA5\xB3\x81\xAC\xAA\xB1\xA3\xBF\xBC\x89\x8A\xF8\x9C\x8C\x98\xA6\xE3\x83\xB7\xBD\xB0\xB0\xA4\x94\xB7\xB7\xAE\xBE\xA4\xA9\x9E\x9F\xA1" + 0xC8ED595D).s)));
	}

	D3DXMATRIX* GetProjectMatrix()
	{
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress((HMODULE)pUtils.modi3GfxDx.dwBase, /*?GetProjectMatrix@i3RenderContext@@QAEPATMATRIX@@XZ*/XorStr<0x27, 52, 0xF8A010B3>("\x18\x6F\x4C\x5E\x7B\x5E\x42\x44\x4A\x53\x45\x7F\x52\x40\x47\x5F\x4F\x78\x50\x09\x69\x59\x53\x5A\x5A\x32\x02\x2D\x2D\x30\x20\x3E\x33\x08\x09\x1B\x0A\x09\x1D\x0F\x1B\x1D\x10\x06\x01\x1D\x0D\x16\x17\x00\x03" + 0xF8A010B3).s)))(this);
	}
	D3DXMATRIX* GetWorldMatrix() {
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress((HMODULE)pUtils.modi3GfxDx.dwBase, /*?GetWorldMatrix@i3RenderContext@@QAEPATMATRIX@@XZ*/XorStr<0xD8, 50, 0x5EABD911>("\xE7\x9E\xBF\xAF\x8B\xB2\xAC\xB3\x84\xAC\x83\x97\x96\x8C\x9E\xA7\x81\xDA\xB8\x8E\x82\x89\x8B\x9D\xB3\x9E\x9C\x87\x91\x8D\x82\xB7\xB8\xA8\xBB\xBE\xAC\xBC\xAA\xB2\x41\x55\x50\x4A\x5C\x45\x46\x5F\x52" + 0x5EABD911).s)))(this);
	}
	D3DXMATRIX* GetViewMatrix() {
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress((HMODULE)pUtils.modi3GfxDx.dwBase, /*?GetViewMatrix@i3RenderContext@@QAEPATMATRIX@@XZ*/XorStr<0xA3, 49, 0xF6D3D3AA>("\x9C\xE3\xC0\xD2\xF1\xC1\xCC\xDD\xE6\xCD\xD9\xDC\xC6\xC8\xF1\xDB\x80\xE6\xD0\xD8\xD3\xDD\xCB\xF9\xD4\xD2\xC9\xDB\xC7\xB4\x81\x82\x92\x85\x80\x96\x86\x9C\x84\x8B\x9F\x9E\x84\x96\x8F\x90\x89\x88" + 0xF6D3D3AA).s)))(this);
	}
};

class i3SceneObject
{
private:
	typedef D3DXMATRIX * (__thiscall * oFindCacheMatrixByName)(i3SceneObject *, const char *);
	typedef int(__thiscall * oFindBoneIndexByName)(i3SceneObject *, const char *);
public:
	int FindBoneIndexByName(const char * bonename) {
		static const oFindBoneIndexByName pFineBoneIndexByName = (oFindBoneIndexByName)GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?FindBoneIndexByName@i3SceneObject@@QBEHPBD@Z*/XorStr<0xB3, 46, 0x965DB1D9>("\x8C\xF2\xDC\xD8\xD3\xFA\xD6\xD4\xDE\xF5\xD3\xDA\xDA\xB8\x83\xBB\x8D\xA5\xA8\xA3\x87\xA1\xFA\x99\xA8\xA9\xA3\xAB\x80\xB2\xBB\xB7\xB0\xA0\x95\x96\x86\x9A\x9C\x92\x8B\x9E\x99\x9E\x85" + 0x965DB1D9).s);
		return pFineBoneIndexByName(this, bonename);
	}
	D3DXMATRIX * FindCacheMatrixByName(const char * bonename) {
		static const oFindCacheMatrixByName pFindCacheMatrixByName = (oFindCacheMatrixByName)GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?FindCacheMatrixByName@i3SceneObject@@QBEPATMATRIX@@PBD@Z*/XorStr<0xEA, 58, 0xFB82033F>("\xD5\xAD\x85\x83\x8A\xAC\x91\x92\x9A\x96\xB9\x94\x82\x85\x91\x81\xB8\x82\xB2\x9C\x93\x9A\x40\x68\x31\x50\x67\x60\x68\x62\x47\x6B\x60\x6E\x6F\x79\x4E\x4F\x41\x53\x57\x43\x55\x41\x5B\x56\x4C\x4B\x53\x43\x5C\x5D\x4E\x5D\x64\x61\x78" + 0xFB82033F).s);
		return (D3DXMATRIX *)pFindCacheMatrixByName(this, bonename);
	}
};

class i3GameNode
{
private:
	typedef i3GameNode * (__thiscall  * oGetFirstChild)(i3GameNode *);
public:

	i3GameNode * getFirstChild(void) {
		static const oGetFirstChild pGetFirstChild = (oGetFirstChild)GetProcAddress((HMODULE)pUtils.modi3FrameworkDx.dwBase, /*?getFirstChild@i3GameNode@@QAEPAV1@XZ*/XorStr<0x86, 38, 0x32DCFC4A>("\xB9\xE0\xED\xFD\xCC\xE2\xFE\xFE\xFA\xCC\xF8\xF8\xFE\xF7\xD4\xFC\xA5\xD0\xF9\xF4\xFF\xD5\xF3\xF9\xFB\xDF\xE0\xF0\xE3\xE6\xF4\xE4\xF0\x96\xE8\xF1\xF0" + 0x32DCFC4A).s);
		return (i3GameNode *)pGetFirstChild(this);
	}
};

class i3GameObj
{
private:
	typedef i3SceneObject * (__thiscall * oGetSceneObject)(i3GameObj *);
	typedef D3DXVECTOR3 * (__thiscall * oGetPos)(i3GameObj *);
	typedef int(__thiscall * oGetCurHP)(i3GameObj *);
	typedef void(__thiscall * oSetCharaWeaponSet)(i3GameObj *, DWORD, DWORD);
public:
	i3SceneObject * getSceneObject(void) {
		static const oGetSceneObject pGetSceneObject = (oGetSceneObject)GetProcAddress((HMODULE)pUtils.modi3FrameworkDx.dwBase, /*?getSceneObject@i3GameObj@@QBEPAVi3SceneObject@@XZ*/XorStr<0x20, 51, 0x21681C6B>("\x1F\x46\x47\x57\x77\x46\x43\x49\x4D\x66\x48\x41\x49\x4E\x5A\x6F\x59\x02\x75\x52\x59\x50\x79\x55\x52\x79\x7A\x6A\x7E\x78\x6E\x7E\x16\x28\x71\x10\x27\x20\x28\x22\x07\x2B\x20\x2E\x2F\x39\x0E\x0F\x08\x0B" + 0x21681C6B).s);
		return (i3SceneObject *)pGetSceneObject(this);
	}

	D3DXVECTOR3 * getPos(void) {
		static const oGetPos pGetPos = (oGetPos)GetProcAddress((HMODULE)pUtils.modi3FrameworkDx.dwBase, /*?GetPos@i3GameObj@@QAEPATVEC3D@@XZ*/XorStr<0x95, 35, 0xA85CE5B3>("\xAA\xD1\xF2\xEC\xC9\xF5\xE8\xDC\xF4\xAD\xD8\xC1\xCC\xC7\xEC\xC6\xCF\xE6\xE7\xF9\xE8\xEF\xFB\xED\xF9\xF8\xEA\xF3\x82\xF6\xF3\xF4\xED\xEC" + 0xA85CE5B3).s);
		return (D3DXVECTOR3 *)pGetPos(this);
	}

	int getCurHP(DWORD dwGetCurHP) {
		static const oGetCurHP pGetCurHP = (oGetCurHP)dwGetCurHP;
		return (int)pGetCurHP(this);
	}

	void setCharaWeaponSet(DWORD dwSetCharaWep, DWORD dwWeaponID, DWORD dwSlotID)
	{
		static const oSetCharaWeaponSet pSetCharaWeaponSet = (oSetCharaWeaponSet)dwSetCharaWep;
		pSetCharaWeaponSet(this, dwWeaponID, dwSlotID);
	}
};


const char * bones[22] =
{
	"Neck",			//0
	"Head",			//1
	"Spine1",		//2
	"Pelvis",		//3
	"L Clavicle",	//4
	"R Clavicle",	//5
	"L UpperArm",	//6
	"L Forearm",	//7
	"L Hand",		//8
	"L Thumb1",		//9
	"R UpperArm",	//10
	"R Forearm",	//11
	"R Hand",		//12
	"R Thumb1",		//13
	"L Thigh",		//14
	"L Calf",		//15
	"L Foot",		//16
	"L Toe",		//17
	"R Thigh",		//18
	"R Calf",		//19
	"R Foot",		//20
	"R Toe"			//21
};
#pragma endregion

void function::Init()
{
	pUtils.GetClientModule();
	Beep(100, 100);

	//Bypass
	KERNEL_GETLASTERROR = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*x?x????x????xxxxxx?x*/XorStr<0x6C, 21, 0x2392B8C5>("\x14\x52\x16\x50\x4F\x4E\x4D\x0B\x4B\x4A\x49\x48\x00\x01\x02\x03\x04\x05\x41\x07" + 0x2392B8C5).s, 20, 0x6A, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x7D, 0x08, 0x85, 0xFF, 0x75, 0x00, 0xFF);
	KERNEL_GETLASTERROR = KERNEL_GETLASTERROR + 0x7F;

	ANTI_CHEAT = pUtils.FindPatternArray(pUtils.modCheatBlocker.dwBase, pUtils.modCheatBlocker.dwSize, /*xxx????x????xxx*/XorStr<0x0A, 16, 0x1B5E119A>("\x72\x73\x74\x32\x31\x30\x2F\x69\x2D\x2C\x2B\x2A\x6E\x6F\x60" + 0x1B5E119A).s, 15, 0x6A, 0x10, 0x68, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x7D, 0x08);
	ANTI_CHEAT_PUSH = *(DWORD*)(ANTI_CHEAT + 3);
	
	ADR_GAMECONTEXT = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*x????xx????xx????*/XorStr<0x2C, 18, 0x9144BC75>("\x54\x12\x11\x10\x0F\x49\x4A\x0C\x0B\x0A\x09\x4F\x40\x06\x05\x04\x03" + 0x9144BC75).s, 17, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xB0, 0x00, 0x00, 0x00, 0x00);
	ADR_GAMECONTEXT = *(DWORD*)(ADR_GAMECONTEXT + 1);

	OFS_TEAM = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xx????xxxxxx????*/XorStr<0x77, 17, 0x1E975BA1>("\x0F\x00\x46\x45\x44\x43\x05\x06\x07\xF8\xF9\xFA\xBC\xBB\xBA\xB9" + 0x1E975BA1).s, 16, 0x8B, 0x80, 0x00, 0x00, 0x00, 0x00, 0x75, 0x14, 0x50, 0x8B, 0xCE, 0xE8, 0x00, 0x00, 0x00, 0x00);
	OFS_TEAM = *(DWORD*)(OFS_TEAM + 2);

	OFS_TICKET = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxx????xxxxxxxxxx*/XorStr<0x1D, 18, 0xCD7D25CF>("\x65\x66\x67\x1F\x1E\x1D\x1C\x5C\x5D\x5E\x5F\x50\x51\x52\x53\x54\x55" + 0xCD7D25CF).s, 17, 0xD9, 0x84, 0x81, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xF4, 0x64, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00);
	OFS_TICKET = *(DWORD*)(OFS_TICKET + 3);

	OFS_TICKETSIZE = 0x48; // imul    eax, edi, 48h "Search OFS_TICKET"

	OFS_GAMEINFOSIZE = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, "xx????x????xxxxx", 16, 0x69, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC1, 0x8B, 0x4D, 0xF4);
	OFS_GAMEINFOSIZE = *(DWORD*)(OFS_GAMEINFOSIZE + 2);

	OFS_GAMEINFOOFFSET = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, "xx????x????xxxxx", 16, 0x69, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC1, 0x8B, 0x4D, 0xF4);
	OFS_GAMEINFOOFFSET = *(DWORD*)(OFS_GAMEINFOOFFSET + 7);

	ADR_CHARACTERPOINTER = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xx????xx????*/XorStr<0x3C, 13, 0x0ACDD11A>("\x44\x45\x01\x00\x7F\x7E\x3A\x3B\x7B\x7A\x79\x78" + 0x0ACDD11A).s, 12, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xB0, 0x00, 0x00, 0x00, 0x00);
	ADR_CHARACTERPOINTER = *(DWORD*)(ADR_CHARACTERPOINTER + 2);

	OFS_CHARACTERSIZE = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxxxxxx?xx????*/XorStr<0x98, 18, 0x6EAEA0AE>("\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xD8\xD9\x9D\xDB\xDC\x9A\x99\x98\x97" + 0x6EAEA0AE).s, 17, 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08, 0x83, 0xF8, 0x0F, 0x77, 0x00, 0x69, 0xC0, 0x00, 0x00, 0x00, 0x00);
	OFS_CHARACTERSIZE = *(DWORD*)(OFS_CHARACTERSIZE + 13);

	ADR_PLAYERPOINTER = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xx????xxxxxx*/XorStr<0x88, 13, 0xDFDC62A9>("\xF0\xF1\xB5\xB4\xB3\xB2\xF6\xF7\xE8\xE9\xEA\xEB" + 0xDFDC62A9).s, 12, 0x39, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x75, 0x10, 0x6A, 0x01, 0x8B, 0xCE);
	ADR_PLAYERPOINTER = *(DWORD*)(ADR_PLAYERPOINTER + 2);

	ADR_ROOMPOINTER = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxx????*/XorStr<0x01, 11, 0xFB07D44E>("\x79\x7A\x7B\x7C\x7D\x7E\x38\x37\x36\x35" + 0xFB07D44E).s, 10, 0xF6, 0xC4, 0x44, 0x7A, 0x26, 0xA1, 0x00, 0x00, 0x00, 0x00);
	ADR_ROOMPOINTER = *(DWORD*)(ADR_ROOMPOINTER + 12);

	OFS_FASTSHOT = 0x120;

	//Aimbot
	End = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxx????xxxx????*/XorStr<0x6C, 18, 0x75B11803>("\x14\x15\x16\x17\x08\x4E\x4D\x4C\x4B\x0D\x0E\x0F\x00\x46\x45\x44\x43" + 0x75B11803).s, 17, 0xFF, 0x75, 0x08, 0x8D, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xCF, 0xFF, 0x15, 0x00, 0x00, 0x00, 0x00);
	SetEnd = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xx????xx????x????xx*/XorStr<0x3A, 20, 0x20273F8B>("\x42\x43\x03\x02\x01\x00\x38\x39\x7D\x7C\x7B\x7A\x3E\x78\x77\x76\x75\x33\x34" + 0x20273F8B).s, 19, 0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x8E, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x84, 0xC0);
	SetEnd = *(DWORD*)(SetEnd + 2);

	//OPK
	SetPos = (DWORD)GetProcAddress((HMODULE)pUtils.modi3FrameworkDx.dwBase, /*?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z*/XorStr<0x3B, 36, 0x5785F49B>("\x04\x6F\x58\x4A\x6F\x2F\x32\x02\x2A\x77\x02\x27\x2A\x2D\x06\x28\x21\x0C\x0D\x1F\x0E\x15\x09\x02\x12\x00\x03\x13\x14\x6B\x1D\x1A\x1B\x1C\x07" + 0x5785F49B).s);
	
	GetButtonState = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xx????xx????xxxxxx*/XorStr<0xF2, 19, 0x8A84CAD7>("\x8A\x8B\xCB\xCA\xC9\xC8\x80\x81\xC5\xC4\xC3\xC2\x86\x87\x78\x79\x7A\x7B" + 0x8A84CAD7).s, 18, 0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x55, 0xE8, 0x3B, 0x84, 0x0A);
	GetButtonState = *(DWORD*)(GetButtonState + 2);

	ADR_NoRecoil1 = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxxxxxxxxxxxx*/XorStr<0x26, 17, 0xF9590D42>("\x5E\x5F\x50\x51\x52\x53\x54\x55\x56\x57\x48\x49\x4A\x4B\x4C\x4D" + 0xF9590D42).s, 16, 0x68, 0xEE, 0x00, 0x00, 0x00, 0x8D, 0x46, 0x10, 0x50, 0xFF, 0x76, 0x04, 0x6A, 0x00, 0x6A, 0x01);
	ADR_NoRecoil1 = (ADR_NoRecoil1 + 0x13);

	ADR_NoRecoil2 = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxxxxxxxxxxxx*/XorStr<0x26, 17, 0xF9590D42>("\x5E\x5F\x50\x51\x52\x53\x54\x55\x56\x57\x48\x49\x4A\x4B\x4C\x4D" + 0xF9590D42).s, 16, 0x68, 0xF1, 0x00, 0x00, 0x00, 0x8D, 0x46, 0x10, 0x50, 0xFF, 0x76, 0x04, 0x6A, 0x00, 0x6A, 0x01);
	ADR_NoRecoil2 = (ADR_NoRecoil2 + 0x13);

	ASM_UNLIAMMO = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxx????xxxxxx*/XorStr<0x37, 16, 0x9B605D74>("\x4F\x40\x41\x42\x43\x03\x02\x01\x00\x38\x39\x3A\x3B\x3C\x3D" + 0x9B605D74).s, 15, 0x50, 0x8B, 0xCB, 0xFF, 0x96, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x03, 0x8B, 0xCB, 0x6A, 0x00);

	ASM_AMMORELOAD = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xx????xxxxxxxxxx*/XorStr<0x16, 17, 0x639BD20F>("\x6E\x6F\x27\x26\x25\x24\x64\x65\x66\x67\x58\x59\x5A\x5B\x5C\x5D" + 0x639BD20F).s, 16, 0xDD, 0x05, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xF8, 0xCD, 0xCC, 0xCC, 0x3D, 0x0F, 0xB7, 0x02);
	ASM_AMMORELOAD = *(DWORD*)(ASM_AMMORELOAD + 2);

	ASM_ACCURACY = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxx??xxxxx*/XorStr<0xD9, 13, 0xE997959C>("\xA1\xA2\xA3\xA4\xA5\xE1\xE0\x98\x99\x9A\x9B\x9C" + 0xE997959C).s, 12, 0xF0, 0x3F, 0x43, 0x4D, 0x65, 0x00, 0x00, 0x61, 0x67, 0x65, 0x42, 0x6F);

	ASM_RESPAWNINDEATH = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxx????xxxxx*/XorStr<0x2E, 15, 0x93B93A7E>("\x56\x57\x48\x49\x4A\x0C\x0B\x0A\x09\x4F\x40\x41\x42\x43" + 0x93B93A7E).s, 14, 0x75, 0x07, 0xC7, 0x45, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xD9, 0x46, 0x04, 0x8B, 0xCF);

	ASM_FASTBOMB = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxxxx*/XorStr<0x98, 9, 0xF74C001E>("\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7" + 0xF74C001E).s, 8, 0xD9, 0x45, 0xFC, 0xD9, 0xEE, 0xDB, 0xF1, 0x5E);

	ASM_GETCURHP = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxx????x????xx????x*/XorStr<0xB9, 20, 0xEC6F5240>("\xC1\xC2\xC3\x83\x82\x81\x80\xB8\xFE\xFD\xFC\xFB\xBD\xBE\xF8\xF7\xF6\xF5\xB3" + 0xEC6F5240).s, 19, 0x5F, 0xC3, 0xB8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x56);
	ASM_GETCURHP = (ASM_GETCURHP + 2);

	ASM_ANTIKICK = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxxxxxxxxxxxxxxxx*/XorStr<0x6D, 21, 0xBF926A9D>("\x15\x16\x17\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x00\x01\x02\x03\x04\x05\x06\x07\xF8" + 0xBF926A9D).s, 20, 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08, 0x56, 0x8B, 0xF1, 0x85, 0xC0, 0x78, 0x15, 0x0F, 0x9F, 0xC0, 0x0F, 0xB6, 0xC0, 0x50);

	ASM_UNLOCKROOM = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxx????x????xxx*/XorStr<0xC1, 19, 0x6AF7E2E1>("\xB9\xBA\xBB\xBC\xBD\xBE\xF8\xF7\xF6\xF5\xB3\xF3\xF2\xF1\xF0\xA8\xA9\xAA" + 0x6AF7E2E1).s, 18, 0x33, 0xC0, 0x50, 0x50, 0x50, 0x68, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E, 0x8B, 0xE5);

	ASM_GHOSTMODE = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xx????xxxxxx*/XorStr<0x33, 13, 0xDD79C43C>("\x4B\x4C\x0A\x09\x08\x07\x41\x42\x43\x44\x45\x46" + 0xDD79C43C).s, 12, 0xDC, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x89, 0x45, 0xD8, 0x8B, 0x43, 0x04);
	ASM_GHOSTMODE = *(DWORD*)(ASM_GHOSTMODE + 2);

	ASM_SPEEDHACK = pUtils.FindPatternArray(pUtils.modBase.dwBase, pUtils.modBase.dwSize, /*xxxxxxxxxxxxxxxx*/XorStr<0x07, 17, 0x5B5E6656>("\x7F\x70\x71\x72\x73\x74\x75\x76\x77\x68\x69\x6A\x6B\x6C\x6D\x6E" + 0x5B5E6656).s, 16, 0x8B, 0x4D, 0xF4, 0xD9, 0x45, 0x08, 0x5F, 0x5E, 0x5B, 0x64, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00);

#pragma region isVisible address & offsets
	ADR_VIEWER = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?g_pPhysixCtx@@3PAVi3PhysixContext@@A*/XorStr<0x36, 38, 0x0BEC649D>("\x09\x50\x67\x49\x6A\x53\x45\x4E\x57\x47\x03\x35\x3A\x03\x04\x76\x16\x06\x1E\x20\x79\x1B\x24\x34\x3D\x26\x28\x12\x3D\x3D\x20\x30\x2E\x23\x18\x19\x1B" + 0x0BEC649D).s));
	ASM_SETSTART = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xB1, 43, 0x36F71E14>("\x8E\xE1\xD6\xC0\xE6\xC2\xD6\xCA\xCD\xFA\xD2\x8F\xFE\xD1\xD3\xAC\xA8\xA6\xA6\xA1\x89\xAF\xA9\xAD\x89\x8A\x9A\x8D\x88\x96\x9F\x91\x85\x84\x96\x97\xE6\x92\x97\x98\x99\x80" + 0x36F71E14).s));
	ASM_SETEND = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xA9, 41, 0xF4168FAB>("\x96\xF9\xCE\xD8\xE8\xC0\xCB\xF0\xD8\x81\xF0\xDB\xD9\xDA\xDE\xDC\xDC\xDF\xF7\xD5\xD3\xDB\xFF\x80\x90\x83\x86\x9C\x95\x87\x93\x9E\x8C\x89\xF8\x88\x8D\x8E\x8F\x8A" + 0xF4168FAB).s));
	ASM_INITIALIZE = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*??0i3CollideeLine@@QAE@XZ*/XorStr<0x18, 26, 0xA4894190>("\x27\x26\x2A\x72\x2F\x5E\x71\x73\x4C\x48\x46\x46\x41\x69\x4F\x49\x4D\x69\x6A\x7A\x6D\x68\x6E\x77\x6A" + 0xA4894190).s));
	ASM_RAYCLASS = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z*/XorStr<0x6B, 85, 0xED6B6ACB>("\x54\x3E\x0C\x17\x0C\x11\x02\x06\x30\x18\x1A\x05\x12\x0B\x0D\x3A\x12\x4F\x2D\x16\x06\xF3\xE8\xFA\xC0\xEB\xEB\xF2\xE2\xF0\xFD\xCA\xCB\xDD\xCC\xCB\xDF\xD1\xC4\xDB\xA0\xCB\xC5\xDE\xCE\xCB\xD0\xC2\xC4\xD4\xD4\xCA\xC0\xF2\xE4\xF1\xF6\xE8\xF1\xE6\xE7\xF8\xE8\xFC\xC2\x9F\xEE\xC1\xC3\xDC\xD8\xD6\xD6\xD1\xF9\xDF\xD9\xDD\xF9\xFA\xF3\xF5\xFD\xE4" + 0xED6B6ACB).s));
#pragma endregion
}

void function::CallInit(LPDIRECT3DDEVICE9 pDevice)
{
	auto pLocalPlayer = *(DWORD*)(ADR_PLAYERPOINTER);
	if (!pLocalPlayer) return;

	auto pGameContext = *(DWORD*)(ADR_GAMECONTEXT);
	if (!pGameContext) return;

	auto pCharaManager = *(DWORD*)(ADR_CHARACTERPOINTER);
	if (!pCharaManager) return;

	auto pRenderContext = (DWORD)i3RenderContext::GetRenderContext();
	if (!pRenderContext) return;

	int iMyIndex = GetMyIndex(pGameContext);

	auto pLocal = GetPlayerByIndex(pCharaManager, iMyIndex);
	if (!pLocal) return;

	CallEsp(pDevice, pCharaManager, pLocal, pRenderContext, iMyIndex);
	CallAimBullet(pDevice, pCharaManager, pGameContext, pRenderContext, iMyIndex);
	CallAimbot(pDevice, pCharaManager, pRenderContext, iMyIndex);
}

void function::CallEsp(LPDIRECT3DDEVICE9 pDevice, DWORD pCharaManager, DWORD pLocal, DWORD pRenderContext, int iMyIndex)
{
	for (int i = 0; i < 16; i++)
	{
		if (iMyIndex == i)
			continue;

		auto pPlayer = GetPlayerByIndex(pCharaManager, i);
		if (!pPlayer) continue;

		D3DXVECTOR3 vMe, vEnemy, vEnemyFoot;
		GetBoneMatrix(pLocal, vMe, bones[1]);
		GetBoneMatrix(pPlayer, vEnemy, bones[1]);
		GetBoneMatrix(pPlayer, vEnemyFoot, bones[16]);

		if (pUtils.esp.team) {
			if (iMyIndex % 2 == i % 2)
				continue;
		}
		else if (pUtils.esp.team == 2) {
			if (iMyIndex % 2 != i % 2)
				continue;;
		}

		bool bIsAlive = isAlive(pCharaManager, i);
		if (!bIsAlive)
			continue;

		bool bIsVisible = isVisible(pCharaManager, iMyIndex, i, vMe, vEnemy);
		DWORD EspColor = (iMyIndex % 2 != i % 2) ? (bIsVisible) ? D3DCOLOR_ARGB(255, 000, 255, 000) : D3DCOLOR_ARGB(255, 255, 000, 000) : D3DCOLOR_ARGB(255, 000, 000, 255);

		D3DXVECTOR3 vScreenHead, vScreenFoot;
		if (WorldToScreen(pDevice, pRenderContext, vEnemy, vScreenHead))
		{
			if (pUtils.esp.bone)
			{
				//Body
				DrawBoneLine(pPlayer, pRenderContext, bones[0], bones[1], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[1], bones[2], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[2], bones[3], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[0], bones[4], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[0], bones[5], EspColor, pDevice);
				//Left Arm
				DrawBoneLine(pPlayer, pRenderContext, bones[4], bones[6], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[6], bones[7], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[7], bones[8], EspColor, pDevice);
				//DrawBoneLine(index, bones[8], bones[9], Color, pDevice);
				//Right Arm
				DrawBoneLine(pPlayer, pRenderContext, bones[5], bones[10], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[10], bones[11], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[11], bones[12], EspColor, pDevice);
				//DrawBoneLine(index, bones[12], bones[13], Color, pDevice);
				//Left Foot
				DrawBoneLine(pPlayer, pRenderContext, bones[3], bones[14], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[14], bones[15], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[15], bones[16], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[16], bones[17], EspColor, pDevice);
				//Right Foot
				DrawBoneLine(pPlayer, pRenderContext, bones[3], bones[18], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[18], bones[19], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[19], bones[20], EspColor, pDevice);
				DrawBoneLine(pPlayer, pRenderContext, bones[20], bones[21], EspColor, pDevice);
			}

			if (pUtils.esp.line)
				pMenu.DrawLine(pDevice, pMenu.Viewport.Width / 2, pMenu.Viewport.Height, (int)vScreenHead.x, (int)vScreenHead.y, 1.0f, EspColor);

			if (pUtils.esp.name)
				DrawPlayerName(i, vScreenHead.x, vScreenHead.y - 20);

			if (WorldToScreen(pDevice, pRenderContext, vEnemyFoot, vScreenFoot))
			{
				if (pUtils.esp.distace)
				{
					int distance = CalcDistance(vMe, vEnemy);
					pMenu.sWriteText(vScreenFoot.x - 10, vScreenFoot.y + 10, D3DCOLOR_ARGB(255, 255, 255, 255), /*[%d] M*/XorStr<0x69, 7, 0x5797F54B>("\x32\x4F\x0F\x31\x4D\x23" + 0x5797F54B).s, distance);
				}

				if (pUtils.esp.health)
				{
					int Health =GetHealth(pPlayer, i);
					pMenu.sWriteText(vScreenFoot.x - 10, vScreenFoot.y + 20, D3DCOLOR_ARGB(255, 255, 255, 255), /*[%d]*/XorStr<0xA6, 5, 0xE1CE8CCD>("\xFD\x82\xCC\xF4" + 0xE1CE8CCD).s, Health);
				}

				if (pUtils.esp.healthbar)
				{
					int Health = GetHealth(pPlayer, i);
					float Red = 255 - (Health*2.55);
					float Green = Health * 2.55;
					pMenu.DrawBorder(pDevice, vScreenFoot.x - 41, vScreenFoot.y + 31, 102, 10, 2, D3DCOLOR_ARGB(255, 20, 20, 20));
					pMenu.DrawBox(pDevice, vScreenFoot.x - 40, vScreenFoot.y + 30, Health, 8, 2, D3DCOLOR_ARGB(255, (int)Red, (int)Green, 255), D3DCOLOR_ARGB(255, 20, 20, 20));
				
				}

				if (pUtils.esp.box)
				{
					D3DXVECTOR3 Box = vScreenHead - vScreenFoot;

					if (Box.y < 0)
						Box.y *= -1;

					int BoxWidth = (int)Box.y / 2;
					int DrawX = (int)vScreenHead.x - (BoxWidth / 2);
					int DrawY = (int)vScreenHead.y;

					pMenu.DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 2, EspColor);
					pMenu.DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 1, 0xFF000000);
				}
			}
		}
	}
}

void function::CallAimBullet(LPDIRECT3DDEVICE9 pDevice, DWORD pCharaManager, DWORD pGameContext, DWORD pRenderContext, int iMyIndex)
{
	const char * boneTarget = (pUtils.aimbullet.target == 1) ? bones[0] : (pUtils.aimbullet.target == 2) ? bones[2] : bones[0];

	int Target = -1;
	int dwCurrentWeaponIndex = *(DWORD*)(pGameContext + OFS_GAMEINFOOFFSET + (iMyIndex * OFS_GAMEINFOSIZE) + 0x94);
	if (dwCurrentWeaponIndex > 407000)
	{
		if (pUtils.telebomb.main)
			Target = GetTarget(pCharaManager, iMyIndex, false);
	}else if(pUtils.aimbullet.main)
		Target = GetTarget(pCharaManager, iMyIndex);

	if (Target != -1)
	{
		auto pPlayer = GetPlayerByIndex(pCharaManager, Target);
		D3DXVECTOR3 OnWorld, OnScreen;
		if (GetBoneMatrix(pPlayer, OnWorld, boneTarget))
		{
			fX = OnWorld.x;
			fY = OnWorld.y + 0.1f;
			fZ = OnWorld.z;
			BulletEnable = true;
			if (WorldToScreen(pDevice, pRenderContext, OnWorld, OnScreen))
			{
				if (pUtils.aimbullet.draw || pUtils.telebomb.draw)
					pMenu.cWriteText(OnScreen.x, OnScreen.y - 30, D3DCOLOR_ARGB(255, 255, 000, 000), /*Target*/XorStr<0x4E, 7, 0x4F6DE48B>("\x1A\x2E\x22\x36\x37\x27" + 0x4F6DE48B).s);
			}
		}
		else BulletEnable = false;
	}
	else BulletEnable = false;

	if (pUtils.aimbullet.autoshot)
		AutoShotEnable = BulletEnable;
	else
		AutoShotEnable = 0;
}

void function::CallAimbot(LPDIRECT3DDEVICE9 pDevice, DWORD pCharaManager, DWORD pRenderContext, int iMyIndex)
{
	if (!pUtils.aimbot.main) return;

	float ScreenCoordX = pMenu.Viewport.Width / 2;
	float ScreenCoordY = pMenu.Viewport.Height / 2;

	float aimsmooth = 0.4f;
	if (pUtils.aimbot.smooth) aimsmooth = (float)(pUtils.aimbot.smooth * aimsmooth);

	float aimfov = 10.f;
	if (pUtils.aimbot.fov) aimfov = (float)(pUtils.aimbot.fov * aimfov);

	float radiusx = aimfov * (ScreenCoordX / 100);
	float radiusy = aimfov * (ScreenCoordY / 100);

	const char * boneTarget = (pUtils.aimbot.target == 1) ? bones[0] : (pUtils.aimbot.target == 2) ? bones[2] : bones[0];

	int Target = GetTarget(pCharaManager, iMyIndex);
	if (Target != -1)
	{
		auto pPlayer = GetPlayerByIndex(pCharaManager, Target);
		D3DXVECTOR3 OnWorld, OnScreen;
		if (GetBoneMatrix(pPlayer, OnWorld, boneTarget))
		{
			if (WorldToScreen(pDevice, pRenderContext, OnWorld, OnScreen))
			{
				if (OnScreen.x >= ScreenCoordX - radiusx && OnScreen.x <= ScreenCoordX + radiusx && OnScreen.y >= ScreenCoordY - radiusy && OnScreen.y <= ScreenCoordY + radiusy)
				{
					double DistX = OnScreen.x - ScreenCoordX;
					double DistY = OnScreen.y - ScreenCoordY;

					DistX = (int)floorf((float(DistX) / 2.0f) + 0.5f);
					DistY = (int)floorf((float(DistY) / 2.0f) + 0.5f);

					if (pUtils.aimbot.draw)
						pMenu.cWriteText(OnScreen.x, OnScreen.y - 20, D3DCOLOR_ARGB(255, 255, 000, 000), /*Target*/XorStr<0x4E, 7, 0x4F6DE48B>("\x1A\x2E\x22\x36\x37\x27" + 0x4F6DE48B).s);

					if (pUtils.aimbot.key == 0)
					{
						if (GetAsyncKeyState(VK_SHIFT))
							mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
					}
					else if (pUtils.aimbot.key == 1)
					{
						if (GetAsyncKeyState(VK_LBUTTON))
							mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
					}
					else {
						mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
					}
				}
			}
		}
	}
}

_declspec(naked)void i3GetButtonState()
{
	__asm
	{
		cmp [AutoShotEnable], 0
		jz Skip
		mov eax, 1
		retn 
	Skip:
		mov eax, [ecx + 0x1C]
		retn
	}
}

_declspec(naked)void i3End()
{
	__asm
	{
		cmp [BulletEnable], 0
		jz Skip
		mov [dwTempEcx], ecx;
		mov [dwTempEbx], ebx;
		mov ecx, [ebp + 0x0C];
		mov ebx, [fX];
		mov [ecx], ebx;
		mov ebx, [fY];
		mov [ecx + 0x04], ebx;
		mov ebx, [fZ];
		mov [ecx + 0x08], ebx;
		mov ecx, [dwTempEcx];
		mov ebx, [dwTempEbx];
	Skip:
		push dword ptr[ebp + 0x8]
		lea edi, [esi + 0x48C]
		jmp	dwJump
	}
}

_declspec(naked)void i3CollideSetEnd()
{
	_asm
	{
		cmp[BulletEnable], 0;
		je Skip;
		mov eax, [esp + 4];
		mov[eax], edx;
		mov edx, [fX];
		mov[eax + 0], edx;
		mov edx, [fY];
		mov[eax + 4], edx;
		mov edx, [fZ];
		mov[eax + 8], edx;
		mov edx, [ecx + 8];
	Skip:
		jmp Original;
		nop;
	Original:
		mov eax, [esp + 4];
		fld dword ptr[eax];
		fstp dword ptr[ecx + 0x18];
		fld dword ptr[eax + 0x04];
		fstp dword ptr[ecx + 0x1C];
		fld dword ptr[eax + 0x08];
		fstp dword ptr[ecx + 0x20];
		fld dword ptr[ecx + 0x18];
		fsub dword ptr[ecx + 0x0C];
		fstp dword ptr[ecx + 0x24];
		fld dword ptr[ecx + 0x1C];
		fsub dword ptr[ecx + 0x10];
		fstp dword ptr[ecx + 0x28];
		fld dword ptr[ecx + 0x20];
		fsub dword ptr[ecx + 0x14];
		fstp dword ptr[ecx + 0x2C];
		ret 4;
	}
}

_declspec(naked)void asm_SpeedHack()
{
	__asm
	{
		cmp[SpeedHackEnable], 0
		jz Skip
		mov ecx, [ebp - 0x0C]
		fld dword ptr[fSpeed]
		jmp dwSpeedHack_jmp
		Skip :
		mov ecx, [ebp - 0x0C]
		fld dword ptr[ebp + 0x8]
		jmp dwSpeedHack_jmp
	}
}

_declspec(naked)void asm_AntiKick()
{
	__asm
	{
		cmp[AntiKickEnable], 0
		jz Skip
		retn 8
		mov ebp, esp
		mov eax, [ebp + 8]
		jmp dwAntiKick_jmp
	Skip:
		push ebp
		mov ebp, esp
		mov eax, [ebp + 8]
		jmp dwAntiKick_jmp
	}
}

_declspec(naked)void asm_UnlockRoom()
{
	__asm
	{
		xor     eax, eax
		push    eax
		lea     eax, [UnlockRoomEnable]
		push    eax
		jmp     dwUnlockRoom_jmp
	}
}

DWORD dwAntiCheat_jmp, dwAntiCheat_push;
_declspec(naked)void asm_AntiCheat()
{
	__asm
	{
		xor eax, eax
		retn
		push dwAntiCheat_push
		jmp dwAntiCheat_jmp
	}
}

DWORD dwPerformanceCounter_jmp;
_declspec(naked)void asm_PerformanceCounter()
{
	__asm
	{
		xor eax, eax
		ret 0x4
		mov ebp, esp
		push ecx
		push ecx
		jmp dwPerformanceCounter_jmp
	}
}

void function::HookBypass(DWORD pParam)
{
	dwAntiCheat_push = ANTI_CHEAT_PUSH;
	dwAntiCheat_jmp = ANTI_CHEAT + 7;
	DetourFunction((PBYTE)(ANTI_CHEAT), (PBYTE)asm_AntiCheat);

	Sleep(50);
	DWORD dwRtlQueryPerformanceCounter = (DWORD)(GetProcAddress(GetModuleHandle("ntdll.dll"), "RtlQueryPerformanceCounter")) + 2;
	dwPerformanceCounter_jmp = dwRtlQueryPerformanceCounter + 5;
	DetourFunction((PBYTE)(dwRtlQueryPerformanceCounter), (PBYTE)asm_PerformanceCounter);
	Sleep(2000);

	Write((void*)(KERNEL_GETLASTERROR), (void*)"\xC3", 1);
	Sleep(200);
}

void function::CallMemory(DWORD pParam)
{
	HookBypass(pParam);
	Sleep(700);

	pUtils.MakePTR((PBYTE)(SetEnd), (DWORD)i3CollideSetEnd);
	pUtils.MakePTR((PBYTE)(GetButtonState), (DWORD)i3GetButtonState);

	dwJump = End + 9;
	DetourFunction((PBYTE)(End), (PBYTE)i3End);

	dwSpeedHack_jmp = ASM_SPEEDHACK + 6;
	DetourFunction((PBYTE)(ASM_SPEEDHACK), (PBYTE)asm_SpeedHack);

	//dwAntiKick_jmp = ASM_ANTIKICK + 6;
	//DetourFunction((PBYTE)(ASM_ANTIKICK), (PBYTE)asm_AntiKick);

	dwUnlockRoom_jmp = ASM_UNLOCKROOM + 5;
	DetourFunction((PBYTE)(ASM_UNLOCKROOM), (PBYTE)asm_UnlockRoom);


	DWORD On = 0x3F4CE1C6, Off = 0x00000000;
	DWORD dwFastSwitch = (0xC + OFS_TICKET);
	DWORD dwFastReload = (0x10 + OFS_TICKET);
	DWORD dwSpeedRun = (0x24 + OFS_TICKET);
	DWORD dwFastRespawn = (0x30 + OFS_TICKET);
	DWORD dwNoFallDmage = (0x34 + OFS_TICKET);

	while (true)
	{
		auto pLocalPlayer = *(DWORD*)(ADR_PLAYERPOINTER);
		auto pGameContext = *(DWORD*)(ADR_GAMECONTEXT);

		//AntiKickEnable = pUtils.memory.antikick;
		UnlockRoomEnable = pUtils.memory.unlockroom;

		if (pUtils.memory.antikick)
		{
			Write((void*)(ASM_ANTIKICK), (void*)"\xC2\x08\x00", 3);
		}
		else {
			Write((void*)(ASM_ANTIKICK), (void*)"\x55\x8B\xEC", 3);
		}

		if (pUtils.memory.speedhack && pLocalPlayer)
		{
			SpeedHackEnable = 1;
			fSpeed = 7.0f + (pUtils.memory.speedhack * 0.5f);
		}
		else {
			fSpeed = 7.0f;
			SpeedHackEnable = 0;
		}

		if (pUtils.memory.norecoil && pLocalPlayer)
		{
			Write((void*)(ADR_NoRecoil1), (void*)"\xFF\x75\x00", 3);
			Write((void*)(ADR_NoRecoil2), (void*)"\xFF\x75\x04", 3);
		}
		else {
			Write((void*)(ADR_NoRecoil1), (void*)"\xFF\x75\x08", 3);
			Write((void*)(ADR_NoRecoil2), (void*)"\xFF\x75\x08", 3);
		}

		if (pUtils.memory.accuracy && pLocalPlayer)
			Write((void*)(ASM_ACCURACY), (void*)"\xFF", 1);
		else
			Write((void*)(ASM_ACCURACY), (void*)"\xF0", 1);

		if (pUtils.memory.unliammo && pLocalPlayer)
			Write((void*)(ASM_UNLIAMMO), (void*)"\x51", 1);
		else
			Write((void*)(ASM_UNLIAMMO), (void*)"\x50", 1);

		if (pUtils.memory.respawnindeath && pLocalPlayer)
		{
			auto pCharaManager = *(DWORD*)(ADR_CHARACTERPOINTER);
			int iMyIndex = GetMyIndex(pGameContext);
			if (!isAlive(pCharaManager, iMyIndex))
				Write((void*)(ASM_RESPAWNINDEATH), (void*)"\x75\x0A", 2);
			else
				Write((void*)(ASM_RESPAWNINDEATH), (void*)"\x75\x07", 2);
		}
		else
			Write((void*)(ASM_RESPAWNINDEATH), (void*)"\x75\x07", 2);

		if (pUtils.memory.fastbomb && pLocalPlayer) {
			Write((void*)(ASM_FASTBOMB), (void*)"\xD9\x45\xFF", 3);
			Write((void*)(ASM_FASTBOMB + 8), (void*)"\xF3\x0F\x10\x45\xFC", 5);
		}
		else {
			Write((void*)(ASM_FASTBOMB), (void*)"\xD9\x45\xFC", 3);
			Write((void*)(ASM_FASTBOMB + 8), (void*)"\xF3\x0F\x10\x4D\xFC", 5);
		}

		if (pLocalPlayer)
		{
			if (pUtils.memory.fastshot)
				*(DWORD*)(pLocalPlayer + OFS_FASTSHOT) = 0;

			if (pUtils.memory.fastreloadknife)
				*(BYTE*)(*(DWORD*)(*(DWORD*)(pLocalPlayer + 0x2C) + 0x2C) + 0x6B) = 66;

			if (pUtils.memory.rapidfire)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
					*(BYTE*)(*(DWORD*)(*(DWORD*)(pLocalPlayer + 0x2C) + 0x2C) + 0x5C) = 3;
			}
		}
		if (pGameContext)
		{
			int iMyIndex = GetMyIndex(pGameContext);
			if (pUtils.memory.fastreload)
			{
				if (*(DWORD*)(pGameContext + dwFastReload + iMyIndex * OFS_TICKETSIZE) != On ||
					*(DWORD*)(pGameContext + dwFastReload + iMyIndex * OFS_TICKETSIZE) == On)
				{
					*(DWORD*)(pGameContext + dwFastReload + iMyIndex * OFS_TICKETSIZE) = On;
				}
			}
			else {
				if (*(DWORD*)(pGameContext + dwFastReload + iMyIndex * OFS_TICKETSIZE) == On)
					*(DWORD*)(pGameContext + dwFastReload + iMyIndex * OFS_TICKETSIZE) = Off;
			}
			if (pUtils.memory.fastswitch)
			{
				if (*(DWORD*)(pGameContext + dwFastSwitch + iMyIndex * OFS_TICKETSIZE) != On ||
					*(DWORD*)(pGameContext + dwFastSwitch + iMyIndex * OFS_TICKETSIZE) == On)
				{
					*(DWORD*)(pGameContext + dwFastSwitch + iMyIndex * OFS_TICKETSIZE) = On;
				}
			}
			else {
				if (*(DWORD*)(pGameContext + dwFastSwitch + iMyIndex * OFS_TICKETSIZE) == On)
					*(DWORD*)(pGameContext + dwFastSwitch + iMyIndex * OFS_TICKETSIZE) = Off;
			}

			if (pUtils.memory.fastrespawn)
			{
				if (*(DWORD*)(pGameContext + dwFastRespawn + iMyIndex * OFS_TICKETSIZE) != On ||
					*(DWORD*)(pGameContext + dwFastRespawn + iMyIndex * OFS_TICKETSIZE) == On)
				{
					*(DWORD*)(pGameContext + dwFastRespawn + iMyIndex * OFS_TICKETSIZE) = On;
				}
			}
			else {
				if (*(DWORD*)(pGameContext + dwFastRespawn + iMyIndex * OFS_TICKETSIZE) == On)
					*(DWORD*)(pGameContext + dwFastRespawn + iMyIndex * OFS_TICKETSIZE) = Off;
			}

			if (pUtils.memory.nofalldamage)
			{
				if (*(DWORD*)(pGameContext + dwNoFallDmage + iMyIndex * OFS_TICKETSIZE) != 0x454CE1C6 ||
					*(DWORD*)(pGameContext + dwNoFallDmage + iMyIndex * OFS_TICKETSIZE) == 0x454CE1C6)
				{
					*(DWORD*)(pGameContext + dwNoFallDmage + iMyIndex * OFS_TICKETSIZE) = 0x454CE1C6;
				}
			}
			else {
				if (*(DWORD*)(pGameContext + dwNoFallDmage + iMyIndex * OFS_TICKETSIZE) == 0x454CE1C6)
					*(DWORD*)(pGameContext + dwNoFallDmage + iMyIndex * OFS_TICKETSIZE) = 0xB7A7C5AC;
			}

			if (pUtils.memory.speedhack)
			{
				if (*(DWORD*)(pGameContext + dwSpeedRun + iMyIndex * OFS_TICKETSIZE) != 0x3EBAD1C6 ||
					*(DWORD*)(pGameContext + dwSpeedRun + iMyIndex * OFS_TICKETSIZE) == 0x3EBAD1C6)
				{
					*(DWORD*)(pGameContext + dwSpeedRun + iMyIndex * OFS_TICKETSIZE) = 0x3EBAD1C6;
				}
			}
			else {
				if (*(DWORD*)(pGameContext + dwSpeedRun + iMyIndex * OFS_TICKETSIZE) == 0x3EBAD1C6)
					*(DWORD*)(pGameContext + dwSpeedRun + iMyIndex * OFS_TICKETSIZE) = 0;
			}
		}
		Sleep(200);
	}
}

void function::DrawBoneLine(DWORD pPlayer, DWORD pRenderContext, const char * Start, const char * End, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vStart, vEnd;
	D3DXVECTOR3 vvStart, vvEnd;
	GetBoneMatrix(pPlayer, vStart, Start);
	GetBoneMatrix(pPlayer, vEnd, End);
	if (WorldToScreen(pDevice, pRenderContext, vStart, vvStart))
	{
		if (WorldToScreen(pDevice, pRenderContext, vEnd, vvEnd))
		{
			pMenu.DrawLine(pDevice, vvStart.x, vvStart.y, vvEnd.x, vvEnd.y, 1, Color);
		}
	}
}

bool function::GetBoneMatrix(DWORD pPlayer, D3DXVECTOR3 &Out, const char * bonename)
{
	__try
	{
		auto i3GameObjpPlayer = (i3GameObj *)pPlayer;
		if (!i3GameObjpPlayer) return false;

		auto pSceneObject = i3GameObjpPlayer->getSceneObject();
		if (!pSceneObject) return false;

		auto pFindBoneIndexByName = pSceneObject->FindBoneIndexByName(bonename);
		if (!pFindBoneIndexByName) return false;

		auto pFindCacheMatrixByName = pSceneObject->FindCacheMatrixByName(bonename);
		if (!pFindCacheMatrixByName) return false;

		Out.x = pFindCacheMatrixByName->_41;
		Out.y = pFindCacheMatrixByName->_42;
		Out.z = pFindCacheMatrixByName->_43;

		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

void function::DrawPlayerName(int index, int x, int y)
{
	DWORD PlayerData;
	wchar_t Name[32];
	__try
	{
		ReadProcessMemory(GetCurrentProcess(), (LPVOID)(ADR_GAMECONTEXT), &PlayerData, sizeof(DWORD), 0);
		ReadProcessMemory(GetCurrentProcess(), (LPVOID)(PlayerData + (index * 0x4) + (OFS_TEAM + 0x8)), &PlayerData, sizeof(DWORD), 0);
		ReadProcessMemory(GetCurrentProcess(), (LPVOID)(PlayerData + 0x8), &Name, sizeof(Name), 0);
		pMenu.sWriteText(x, y, D3DCOLOR_ARGB(255, 000, 255, 000), "%ls", Name);
	}
	__except (TRUE) { return; }
}

bool function::isAlive(DWORD pCharaManager, int index)
{
	auto pState = (*(DWORD*)(pCharaManager + 0x18 + OFS_CHARACTERSIZE * index));
	if (pState == 2)
		return true;
	return false;
}

bool function::isVisible(DWORD pCharaManager, int iMyIndex, int index, D3DXVECTOR3 vMe, D3DXVECTOR3 vEnemy)
{
	if (index == -1)
		return false;
	dwPhtsX *pViewer = (dwPhtsX*)ADR_VIEWER;
	DWORD dwSetStart = ASM_SETSTART;
	DWORD dwSetEnd = ASM_SETEND;
	DWORD dwInitialize = ASM_INITIALIZE;
	DWORD dwReyClass = ASM_RAYCLASS;
	i3CollideeLine Line;
	i3CollideeLine* cLine;
	void *PhysX = pViewer->i3PhysixContext;
	cLine = &Line;;
	DWORD dwPhysix;
	Line.vStart.y += 0.1f;
	float distance = CalcDistance(vEnemy, vMe);

	_asm
	{
		mov ecx, [cLine];
		call[dwInitialize];
		lea edx, vMe;
		push edx;
		mov ecx, [cLine];
		call[dwSetStart];
		lea eax, vEnemy;
		push eax;
		mov ecx, [cLine];
		call[dwSetEnd];
		push - 1;
		push 0;
		push[cLine];
		mov ecx, [PhysX];
		call dword ptr ds : [dwReyClass];
		mov[dwPhysix], eax;
	}
	i3PhysixHitResult *pX = (i3PhysixHitResult*)dwPhysix;

	if (pX == 0)
		return false;
	if (pX->Distance < distance)
		return false;

	return true;
}

bool function::WorldToScreen(LPDIRECT3DDEVICE9 pDevice, DWORD pRenderContext, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
{
	__try
	{
		auto Render = (i3RenderContext*)pRenderContext;
		D3DXVECTOR3 vScreen;
		D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);

		pMenu.Viewport.X = pMenu.Viewport.Y = 0;
		pMenu.Viewport.MinZ = 0;
		pMenu.Viewport.MaxZ = 1;
		D3DXVec3Project(&vScreen, &PlayerPos, &pMenu.Viewport, Render->GetProjectMatrix(), Render->GetViewMatrix(), Render->GetWorldMatrix());

		if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < pMenu.Viewport.Width && vScreen.y < pMenu.Viewport.Height)
		{
			PlayerScaled.x = vScreen.x;
			PlayerScaled.y = vScreen.y;
			PlayerScaled.z = vScreen.z;
			return true;
		}
		return false;
	}
	__except (TRUE) { return false; }
}

int function::GetTarget(DWORD pCharaManager, int iMyIndex, bool bVisisble)
{
	int Result = -1;
	float fMaxDistance = 100.0f;
	D3DXVECTOR3 vMe, vEnemy;
	for (int index = 0; index < 16; index++)
	{
		if (iMyIndex == index)
			continue;

		if (iMyIndex % 2 == index % 2)
			continue;

		if (!isAlive(pCharaManager, index))
			continue;

		auto pLocal = GetPlayerByIndex(pCharaManager, iMyIndex);
		auto pPlayer = GetPlayerByIndex(pCharaManager, index);
		GetBoneMatrix(pLocal, vMe, bones[1]);
		GetBoneMatrix(pPlayer, vEnemy, bones[1]);
		if (bVisisble)
		{
			if (!isVisible(pCharaManager, iMyIndex, index, vMe, vEnemy))
				continue;
		}

		float fDistance = CalcDistance(vMe, vEnemy);
		if (fDistance < fMaxDistance)
		{
			fMaxDistance = fDistance;
			Result = index;
		}
	}
	return Result;
}

int function::GetPlayerByIndex(DWORD pCharaManager, int index)
{
	auto pPlayer = *(DWORD*)(pCharaManager + 0x14 + (OFS_CHARACTERSIZE * index));
	if (!pPlayer) return NULL;
	return pPlayer;
}

int function::GetHealth(DWORD pPlayer, int index)
{
	auto ppPlayer = (i3GameObj*)pPlayer;
	return ppPlayer->getCurHP(ASM_GETCURHP);
}

int function::GetMyIndex(DWORD pGameContext)
{
	return *(BYTE*)(pGameContext + OFS_TEAM);
}

void function::Write(void *adress, void *bytes, int size)
{
	DWORD dwProtect;
	VirtualProtect((void*)adress, size, PAGE_EXECUTE_READWRITE, &dwProtect);
	memcpy((void *)adress, (PBYTE)bytes, size);
	VirtualProtect((void*)adress, size, dwProtect, &dwProtect);
}

float function::CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}

#include "StdAfx.h"
#include "function.h"
#include "menu.h"
#include "utils.h"
#include "Xor.h"

function pFunction;

function::function()
{
}


function::~function()
{
}

#pragma region Class
class i3CollideeLine
{
public:
	D3DXVECTOR3 vTemp;
	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vDir;
public:
	static i3CollideeLine* Singleton()
	{
		typedef i3CollideeLine* (__stdcall * tgetHandler)();
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
public:
	i3SceneObject * getSceneObject(void) {
		static const oGetSceneObject pGetSceneObject = (oGetSceneObject)GetProcAddress((HMODULE)pUtils.modi3FrameworkDx.dwBase, /*?getSceneObject@i3GameObj@@QBEPAVi3SceneObject@@XZ*/XorStr<0x20, 51, 0x21681C6B>("\x1F\x46\x47\x57\x77\x46\x43\x49\x4D\x66\x48\x41\x49\x4E\x5A\x6F\x59\x02\x75\x52\x59\x50\x79\x55\x52\x79\x7A\x6A\x7E\x78\x6E\x7E\x16\x28\x71\x10\x27\x20\x28\x22\x07\x2B\x20\x2E\x2F\x39\x0E\x0F\x08\x0B" + 0x21681C6B).s);
		return (i3SceneObject *)pGetSceneObject(this);
	}
	D3DXVECTOR3 * getPos(void) {
		static const oGetPos pGetPos = (oGetPos)GetProcAddress((HMODULE)pUtils.modi3FrameworkDx.dwBase, /*?GetPos@i3GameObj@@QAEPATVEC3D@@XZ*/XorStr<0x95, 35, 0xA85CE5B3>("\xAA\xD1\xF2\xEC\xC9\xF5\xE8\xDC\xF4\xAD\xD8\xC1\xCC\xC7\xEC\xC6\xCF\xE6\xE7\xF9\xE8\xEF\xFB\xED\xF9\xF8\xEA\xF3\x82\xF6\xF3\xF4\xED\xEC" + 0xA85CE5B3).s);
		return (D3DXVECTOR3 *)pGetPos(this);
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

	ADR_GAMECONTEXT = 0x9B08D4;
	OFS_TEAM = 0x171B4; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

	OFS_TICKET = 0x1722C; //D9 84 81 ?? ?? ?? ?? 8B 4D F4 64 89 0D 00 00 00 00 //float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum
	OFS_TICKETSIZE = 0x48; // imul    eax, edi, 48h "Search OFS_TICKET"

	ADR_CHARACTERPOINTER = 0x9B0DF0; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
	OFS_CHARACTERSIZE = 0x114; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 13 //IMUL EAX,EAX,10C

	ADR_PLAYERPOINTER = 0x9B9EB8; //39 3D ?? ?? ?? ?? 75 10 6A 01 8B CE
	OFS_FASTSHOT = 0x120;

	//Aimbot
	CollideeLine = 0x48C; // pEnd != nullptr || PointBlank.exe || LEA EDI,DWORD PTR DS:[ESI+48C]
	CollideeLineEnd = 0x18; //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z || i3ScenceDx.dll || 
	CollideeLineStart = 0x0C; //?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z || i3ScenceDx.dll || 
	VEC3DSetEnd = (DWORD)GetProcAddress((HMODULE)pUtils.modi3MathDx.dwBase, /*??4VEC3D@@QAEAAT0@ABT0@@Z*/XorStr<0x96, 26, 0x3117822B>("\xA9\xA8\xAC\xCF\xDF\xD8\xAF\xD9\xDE\xDF\xF1\xE0\xE7\xE2\xE5\xF1\x96\xE7\xE9\xEB\xFE\x9B\xEC\xED\xF4" + 0x3117822B).s); //??4VEC3D@@QAEAAT0@ABT0@@Z || i3MathDx.dll

	//OPK
	SetPos = (DWORD)GetProcAddress((HMODULE)pUtils.modi3FrameworkDx.dwBase, /*?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z*/XorStr<0x3B, 36, 0x5785F49B>("\x04\x6F\x58\x4A\x6F\x2F\x32\x02\x2A\x77\x02\x27\x2A\x2D\x06\x28\x21\x0C\x0D\x1F\x0E\x15\x09\x02\x12\x00\x03\x13\x14\x6B\x1D\x1A\x1B\x1C\x07" + 0x5785F49B).s); //?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z || i3FrameworkDx.dll

	ADR_NoRecoil1 = 0xF48F5; //55 8B EC 51 51 53 57 8B F9 8D 5F 28 8B CB E8 ?? ?? ?? ??
	ADR_NoRecoil2 = 0xF49B8; //55 8B EC 51 51 53 57 8B F9 8D 5F 28 8B CB E8 ?? ?? ?? ??
}

void function::CallEsp(LPDIRECT3DDEVICE9 pDevice)
{
	auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
	if (!pLocal) return;

	for (int i = 0; i < 16; i++)
	{
		if (isAlive(i) && GetMyIndex() != i)
		{

			DWORD EspColor = (GetMyIndex() % 2 != i % 2) ? (isVisible(i)) ? D3DCOLOR_ARGB(255, 000, 255, 000) : D3DCOLOR_ARGB(255, 255, 000, 000) : D3DCOLOR_ARGB(255, 000, 000, 255);
			//Head
			D3DXVECTOR3 vWorldHead, vScreenHead;
			if (GetBoneMatrix(vWorldHead, bones[1], i))
			{
				if (WorldToScreen(pDevice, vWorldHead, vScreenHead))
				{
					if (pUtils.esp.bone)
					{
						//Body
						DrawBoneLine(i, bones[0], bones[1], EspColor, pDevice);
						DrawBoneLine(i, bones[1], bones[2], EspColor, pDevice);
						DrawBoneLine(i, bones[2], bones[3], EspColor, pDevice);
						DrawBoneLine(i, bones[0], bones[4], EspColor, pDevice);
						DrawBoneLine(i, bones[0], bones[5], EspColor, pDevice);
						//Left Arm
						DrawBoneLine(i, bones[4], bones[6], EspColor, pDevice);
						DrawBoneLine(i, bones[6], bones[7], EspColor, pDevice);
						DrawBoneLine(i, bones[7], bones[8], EspColor, pDevice);
						//DrawBoneLine(index, bones[8], bones[9], Color, pDevice);
						//Right Arm
						DrawBoneLine(i, bones[5], bones[10], EspColor, pDevice);
						DrawBoneLine(i, bones[10], bones[11], EspColor, pDevice);
						DrawBoneLine(i, bones[11], bones[12], EspColor, pDevice);
						//DrawBoneLine(index, bones[12], bones[13], Color, pDevice);
						//Left Foot
						DrawBoneLine(i, bones[3], bones[14], EspColor, pDevice);
						DrawBoneLine(i, bones[14], bones[15], EspColor, pDevice);
						DrawBoneLine(i, bones[15], bones[16], EspColor, pDevice);
						DrawBoneLine(i, bones[16], bones[17], EspColor, pDevice);
						//Right Foot
						DrawBoneLine(i, bones[3], bones[18], EspColor, pDevice);
						DrawBoneLine(i, bones[18], bones[19], EspColor, pDevice);
						DrawBoneLine(i, bones[19], bones[20], EspColor, pDevice);
						DrawBoneLine(i, bones[20], bones[21], EspColor, pDevice);
					}

					if(pUtils.esp.line)
						pMenu.DrawLine(pDevice, pMenu.Viewport.Width / 2, pMenu.Viewport.Height, (int)vScreenHead.x, (int)vScreenHead.y, 1.0f, EspColor);
				}

				//Foot
				D3DXVECTOR3 vWorlFoot, vScreenFoot;
				if (GetBoneMatrix(vWorlFoot, bones[16], i))
				{
					if (WorldToScreen(pDevice, vWorlFoot, vScreenFoot))
					{
						if (pUtils.esp.distace)
						{
							D3DXVECTOR3 vMyHead;
							if (GetBoneMatrix(vMyHead, bones[1], GetMyIndex()))
							{
								int distance = CalcDistance(vMyHead, vWorldHead);
								char buff[20];
								sprintf_s(buff, "[%d] M", distance);
								pMenu.cWriteText(vScreenFoot.x - 10, vScreenFoot.y + 10, D3DCOLOR_ARGB(255, 255, 255, 255), buff);
							}
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
	}
}

void function::CallAimBullet(LPDIRECT3DDEVICE9 pDevice)
{
	auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
	if (!pLocal || !pUtils.aimbullet.main)
	{
		BulletEnable = false;
		return;
	}

	const char * boneTarget = (pUtils.aimbullet.target == 1) ? bones[0] : (pUtils.aimbullet.target == 2) ? bones[2] : bones[0];

	int Target = GetTarget();
	if (Target != -1)
	{
		D3DXVECTOR3 OnWorld, OnScreen;
		if (GetBoneMatrix(OnWorld, boneTarget, Target))
		{
			BulletEnable = true;
			fX = OnWorld.x;
			fY = OnWorld.y + 0.1f;
			fZ = OnWorld.z;

			if (WorldToScreen(pDevice, OnWorld, OnScreen))
			{
				if (pUtils.aimbullet.draw)
					pMenu.cWriteText(OnScreen.x, OnScreen.y, D3DCOLOR_ARGB(255, 255, 000, 000), "Target");
			}
		}
		else BulletEnable = false;
	}
	else BulletEnable = false;
}

void function::CallAimbot(LPDIRECT3DDEVICE9 pDevice)
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

	auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
	if (!pLocal) return;

	const char * boneTarget = (pUtils.aimbot.target == 1) ? bones[0] : (pUtils.aimbot.target == 2) ? bones[2] : bones[0];

	int Target = GetTarget();
	if (Target != -1)
	{
		D3DXVECTOR3 OnWorld, OnScreen;
		if (GetBoneMatrix(OnWorld, boneTarget, Target))
		{
			if (WorldToScreen(pDevice, OnWorld, OnScreen))
			{
				if (OnScreen.x >= ScreenCoordX - radiusx && OnScreen.x <= ScreenCoordX + radiusx && OnScreen.y >= ScreenCoordY - radiusy && OnScreen.y <= ScreenCoordY + radiusy)
				{

					if (pUtils.aimbot.draw)
						pMenu.WriteText(OnScreen.x, OnScreen.y, D3DCOLOR_ARGB(255, 255, 000, 000), "Target");

					double DistX = OnScreen.x - ScreenCoordX;
					double DistY = OnScreen.y - ScreenCoordY;

					DistX = (int)floorf((float(DistX) / 2.0f) + 0.5f);
					DistY = (int)floorf((float(DistY) / 2.0f) + 0.5f);

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

_declspec(naked)void hkVectorSetEnd()
{
	static DWORD dwAddy;
	static float tfX, tfY, tfZ;
	static bool isSetEnd, AimBullet;
	_asm
	{
		push    ebp
		mov     ebp, esp
		mov     eax, [ebp + 8]
		mov[dwAddy], ecx
		pushad
	}

	pFunction.dwSetEndCheck = dwAddy;
	tfX = pFunction.fX;
	tfY = pFunction.fY;
	tfZ = pFunction.fZ;
	AimBullet = pFunction.BulletEnable;

	pFunction.AimCheck(isSetEnd);

	if (isSetEnd && AimBullet)
	{
		_asm
		{
			popad
			fld     dword ptr[tfX]
			fstp    dword ptr[ecx]
			fld     dword ptr[tfY]
			fstp    dword ptr[ecx + 4]
			fld     dword ptr[tfZ]
			mov     eax, ecx
			fstp    dword ptr[ecx + 8]
		}
	}
	else
	{
		_asm
		{
			popad
			fld     dword ptr[eax]
			fstp    dword ptr[ecx]
			fld     dword ptr[eax + 4]
			fstp    dword ptr[ecx + 4]
			fld     dword ptr[eax + 8]
			mov     eax, ecx
			fstp    dword ptr[ecx + 8]
		}
	}

	_asm
	{
		pop     ebp
		retn    4
	}
}

void function::CallMemory()
{
	DWORD dwHook = (DWORD)pUtils.modi3MathDx.dwBase + 0x41C0;
	pUtils.DetourCreate((PBYTE)dwHook, (PBYTE)hkVectorSetEnd, 5);

	while (true)
	{
		auto pGame = *(DWORD*)(pUtils.modBase.dwBase + ADR_PLAYERPOINTER);
		if (pGame)
		{
			DWORD On = 0x3F4CE1C6, Off = 0x00000000;

			if (pUtils.memory.norecoil)
			{
				*(BYTE*)(pUtils.modBase.dwBase + ADR_NoRecoil1 + 0x2) = 0x0;
				*(BYTE*)(pUtils.modBase.dwBase + ADR_NoRecoil2 + 0x2) = 0x4;
			}
			else {
				*(BYTE*)(pUtils.modBase.dwBase + ADR_NoRecoil1 + 0x2) = 0x8;
				*(BYTE*)(pUtils.modBase.dwBase + ADR_NoRecoil2 + 0x2) = 0x8;
			}

			if (pUtils.memory.fastshot)
				*(DWORD*)(pGame + OFS_FASTSHOT) = 0;


			if (pUtils.memory.fastreloadknife)
				*(BYTE*)(*(DWORD*)(*(DWORD*)(pGame + 0x2C) + 0x2C) + 0x6B) = 66;

			if (pUtils.memory.rapidfire)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
					*(BYTE*)(*(DWORD*)(*(DWORD*)(pGame + 0x2C) + 0x2C) + 0x5C) = 3;
			}

			auto pBattle = *(DWORD*)(pUtils.modBase.dwBase + ADR_GAMECONTEXT);
			if (pBattle)
			{
				DWORD dwFastSwitch = (0xC + OFS_TICKET);
				DWORD dwFastReload = (0x10 + OFS_TICKET);
				DWORD dwSpeedRun = (0x24 + OFS_TICKET);
				DWORD dwFastRespawn = (0x30 + OFS_TICKET);
				DWORD dwNoFallDmage = (0x34 + OFS_TICKET);

				if (pUtils.memory.fastreload)
				{
					if (*(DWORD*)(pBattle + dwFastReload + GetMyIndex() * OFS_TICKETSIZE) != On ||
						*(DWORD*)(pBattle + dwFastReload + GetMyIndex() * OFS_TICKETSIZE) == On)
					{
						*(DWORD*)(pBattle + dwFastReload + GetMyIndex() * OFS_TICKETSIZE) = On;
					}
				}
				else {
					if (*(DWORD*)(pBattle + dwFastReload + GetMyIndex() * OFS_TICKETSIZE) == On)
						*(DWORD*)(pBattle + dwFastReload + GetMyIndex() * OFS_TICKETSIZE) = Off;
				}
				if (pUtils.memory.fastswitch)
				{
					if (*(DWORD*)(pBattle + dwFastSwitch + GetMyIndex() * OFS_TICKETSIZE) != On ||
						*(DWORD*)(pBattle + dwFastSwitch + GetMyIndex() * OFS_TICKETSIZE) == On)
					{
						*(DWORD*)(pBattle + dwFastSwitch + GetMyIndex() * OFS_TICKETSIZE) = On;
					}
				}
				else {
					if (*(DWORD*)(pBattle + dwFastSwitch + GetMyIndex() * OFS_TICKETSIZE) == On)
						*(DWORD*)(pBattle + dwFastSwitch + GetMyIndex() * OFS_TICKETSIZE) = Off;
				}

				if (pUtils.memory.fastrespawn)
				{
					if (*(DWORD*)(pBattle + dwFastRespawn + GetMyIndex() * OFS_TICKETSIZE) != On ||
						*(DWORD*)(pBattle + dwFastRespawn + GetMyIndex() * OFS_TICKETSIZE) == On)
					{
						*(DWORD*)(pBattle + dwFastRespawn + GetMyIndex() * OFS_TICKETSIZE) = On;
					}
				}
				else {
					if (*(DWORD*)(pBattle + dwFastRespawn + GetMyIndex() * OFS_TICKETSIZE) == On)
						*(DWORD*)(pBattle + dwFastRespawn + GetMyIndex() * OFS_TICKETSIZE) = Off;
				}

				if (pUtils.memory.nofalldamage)
				{
					if (*(DWORD*)(pBattle + dwNoFallDmage + GetMyIndex() * OFS_TICKETSIZE) != 0x454CE1C6 ||
						*(DWORD*)(pBattle + dwNoFallDmage + GetMyIndex() * OFS_TICKETSIZE) == 0x454CE1C6)
					{
						*(DWORD*)(pBattle + dwNoFallDmage + GetMyIndex() * OFS_TICKETSIZE) = 0x454CE1C6;
					}
				}
				else {
					if (*(DWORD*)(pBattle + dwNoFallDmage + GetMyIndex() * OFS_TICKETSIZE) == 0x454CE1C6)
						*(DWORD*)(pBattle + dwNoFallDmage + GetMyIndex() * OFS_TICKETSIZE) = 0xB7A7C5AC;
				}

				if (pUtils.memory.speedhack)
				{
					if (*(DWORD*)(pBattle + dwSpeedRun + GetMyIndex() * OFS_TICKETSIZE) != 0x3EBAD1C6 ||
						*(DWORD*)(pBattle + dwSpeedRun + GetMyIndex() * OFS_TICKETSIZE) == 0x3EBAD1C6)
					{
						*(DWORD*)(pBattle + dwSpeedRun + GetMyIndex() * OFS_TICKETSIZE) = 0x3EBAD1C6;
					}
				}
				else {
					if (*(DWORD*)(pBattle + dwSpeedRun + GetMyIndex() * OFS_TICKETSIZE) == 0x3EBAD1C6)
						*(DWORD*)(pBattle + dwSpeedRun + GetMyIndex() * OFS_TICKETSIZE) = 0;
				}
			}
		}
		Sleep(100);
	}
}

void function::AimCheck(bool &isTrue)
{
	isTrue = false;
	if (dwSetEndCheck)
	{
		auto pPlayer = (i3GameNode *)GetPlayerByIndex(GetMyIndex());
		if (pPlayer)
		{
			auto FirstChild = pPlayer->getFirstChild() + CollideeLine;
			if (FirstChild)
			{
				auto dwSetEnd = (DWORD)FirstChild + CollideeLineEnd;
				if (dwSetEnd)
				{
					if (dwSetEndCheck == dwSetEnd)
					{
						isTrue = true;
					}
				}
			}
		}
	}
}

void function::DrawBoneLine(int index, const char * Start, const char * End, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vStart, vEnd;
	D3DXVECTOR3 vvStart, vvEnd;
	if (GetBoneMatrix(vStart, Start, index))
	{
		if (GetBoneMatrix(vEnd, End, index))
		{
			if (WorldToScreen(pDevice, vStart, vvStart))
			{
				if (WorldToScreen(pDevice, vEnd, vvEnd))
				{
					pMenu.DrawLine(pDevice, vvStart.x, vvStart.y, vvEnd.x, vvEnd.y, 1, Color);
				}
			}
		}
	}
}

bool function::GetBoneMatrix(D3DXVECTOR3 &Out, const char * bonename, int index)
{
	__try
	{
		auto pPlayer = (i3GameObj *)GetPlayerByIndex(index);
		if (!pPlayer) return false;

		auto pSceneObject = pPlayer->getSceneObject();
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

bool function::isAlive(int index)
{
	auto pState = (*(DWORD*)(*(DWORD*)(pUtils.modBase.dwBase + ADR_CHARACTERPOINTER) + 0x18 + OFS_CHARACTERSIZE * index));
	if (pState == 2)
		return true;
	return false;
}

bool function::isVisible(int iSlot)
{
	if (iSlot == -1)
		return false;
	dwPhtsX *pViewer = (dwPhtsX*)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?g_pPhysixCtx@@3PAVi3PhysixContext@@A*/XorStr<0x36, 38, 0x0BEC649D>("\x09\x50\x67\x49\x6A\x53\x45\x4E\x57\x47\x03\x35\x3A\x03\x04\x76\x16\x06\x1E\x20\x79\x1B\x24\x34\x3D\x26\x28\x12\x3D\x3D\x20\x30\x2E\x23\x18\x19\x1B" + 0x0BEC649D).s));
	DWORD dwSetStart = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xB1, 43, 0x36F71E14>("\x8E\xE1\xD6\xC0\xE6\xC2\xD6\xCA\xCD\xFA\xD2\x8F\xFE\xD1\xD3\xAC\xA8\xA6\xA6\xA1\x89\xAF\xA9\xAD\x89\x8A\x9A\x8D\x88\x96\x9F\x91\x85\x84\x96\x97\xE6\x92\x97\x98\x99\x80" + 0x36F71E14).s));
	DWORD dwSetEnd = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xA9, 41, 0xF4168FAB>("\x96\xF9\xCE\xD8\xE8\xC0\xCB\xF0\xD8\x81\xF0\xDB\xD9\xDA\xDE\xDC\xDC\xDF\xF7\xD5\xD3\xDB\xFF\x80\x90\x83\x86\x9C\x95\x87\x93\x9E\x8C\x89\xF8\x88\x8D\x8E\x8F\x8A" + 0xF4168FAB).s));
	DWORD dwInitialize = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*??0i3CollideeLine@@QAE@XZ*/XorStr<0x18, 26, 0xA4894190>("\x27\x26\x2A\x72\x2F\x5E\x71\x73\x4C\x48\x46\x46\x41\x69\x4F\x49\x4D\x69\x6A\x7A\x6D\x68\x6E\x77\x6A" + 0xA4894190).s));
	DWORD dwReyClass = (DWORD)(GetProcAddress((HMODULE)pUtils.modi3SceneDx.dwBase, /*?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z*/XorStr<0x6B, 85, 0xED6B6ACB>("\x54\x3E\x0C\x17\x0C\x11\x02\x06\x30\x18\x1A\x05\x12\x0B\x0D\x3A\x12\x4F\x2D\x16\x06\xF3\xE8\xFA\xC0\xEB\xEB\xF2\xE2\xF0\xFD\xCA\xCB\xDD\xCC\xCB\xDF\xD1\xC4\xDB\xA0\xCB\xC5\xDE\xCE\xCB\xD0\xC2\xC4\xD4\xD4\xCA\xC0\xF2\xE4\xF1\xF6\xE8\xF1\xE6\xE7\xF8\xE8\xFC\xC2\x9F\xEE\xC1\xC3\xDC\xD8\xD6\xD6\xD1\xF9\xDF\xD9\xDD\xF9\xFA\xF3\xF5\xFD\xE4" + 0xED6B6ACB).s));
	i3CollideeLine Line;
	i3CollideeLine* cLine;
	void *PhysX = pViewer->i3PhysixContext;
	cLine = &Line;
	D3DXVECTOR3 vMe, vEnemy;
	DWORD dwPhysix;
	GetBoneMatrix(vMe, bones[1], GetMyIndex());
	GetBoneMatrix(vEnemy, bones[1], iSlot);
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

bool function::WorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
{
	__try
	{
		auto Render = i3RenderContext::GetRenderContext();
		if (!Render)
			return false;

		D3DXVECTOR3 vScreen;
		D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
		pDevice->GetViewport(&pMenu.Viewport);

		pMenu.Viewport.X = pMenu.Viewport.Y = 0;
		pMenu.Viewport.MinZ = 0;
		pMenu.Viewport.MaxZ = 1;
		pUtils.hD3DXVec3Project(&vScreen, &PlayerPos, &pMenu.Viewport, Render->GetProjectMatrix(), Render->GetViewMatrix(), Render->GetWorldMatrix());

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

int function::GetTarget()
{
	int Result = -1;
	float fMaxDistance = 100.0f;
	D3DXVECTOR3 PlayerEnd, LocPlayer;
	for (int index = 0; index < 16; index++)
	{
		if (GetMyIndex() != index && GetMyIndex() % 2 != index % 2)
		{
			if (isVisible(index))
			{
				if (isAlive(index))
				{
					GetBoneMatrix(LocPlayer, bones[1], GetMyIndex());
					GetBoneMatrix(PlayerEnd, bones[1], index);
					if (CalcDistance(LocPlayer, PlayerEnd) < fMaxDistance)
					{
						fMaxDistance = CalcDistance(PlayerEnd, LocPlayer);
						Result = index;
					}
				}
			}
		}
	}
	return Result;
}


int function::GetPlayerByIndex(int index)
{
	auto pChara = *(DWORD*)(pUtils.modBase.dwBase + ADR_CHARACTERPOINTER);
	if (!pChara) return NULL;

	auto pPlayer = *(DWORD*)(pChara + 0x14 + (OFS_CHARACTERSIZE * index));
	if (!pPlayer) return NULL;

	return pPlayer;
}

int function::GetMyIndex()
{
	auto pLocal = *(DWORD*)(pUtils.modBase.dwBase + ADR_GAMECONTEXT);
	if (!pLocal) return 0;
	return *(BYTE*)(pLocal + OFS_TEAM);
}

float function::CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}
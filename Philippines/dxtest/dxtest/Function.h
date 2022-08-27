#include "stdafx.h"

class FunctionT
{
private:
	DWORD ADR_CHARACTERPOINTER = 0xE7F0A4; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
	DWORD OFS_CHARACTERSIZE = 0x114; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 13 //IMUL EAX,EAX,10C

	DWORD ADR_GAMECONTEXT = 0xE7EB6C;
	DWORD OFS_TEAM = 0x175C4; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

	DWORD OFS_TICKET = 0x1763C; //D9 84 81 ?? ?? ?? ?? 8B 4D F4 64 89 0D 00 00 00 00 //float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum
	DWORD OFS_TICKETSIZE = 0x48; // imul    eax, edi, 48h "Search OFS_TICKET"

	DWORD OFS_PLAYERINFO = 0x740;
	DWORD OFS_PLAYERINFOSIZE = 0x16A8;

	DWORD OFS_PLAYERPOS = 0x18;

	//W2S
	DWORD ADR_RENDERCONTEXT = 0x1406DC; //?g_pRenderContext@@3PAVi3RenderContext@@A
	DWORD OFS_VIEWMATRIX = 0x8B0; //?GetViewMatrix@i3RenderContext@@QAEPATMATRIX@@XZ
	DWORD OFS_PROJECTMATRIX = 0x8F0; //?GetProjectMatrix@i3RenderContext@@QAEPATMATRIX@@XZ
	DWORD OFS_WORLDMATRIX = 0x970; //?GetWorldMatrix@i3RenderContext@@QAEPATMATRIX@@XZ

private:
	DWORD GetCharacter(int i);
	DWORD GetPlayer();
	int GetMyIndex(DWORD pPlayer);
	BOOL IsAlive(int i);
	int GetTeam(int MyTeam);
	D3DXVECTOR3 GetPos(int i);
	BOOL W2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled);
	float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB);
public:
	VOID CallESP(LPDIRECT3DDEVICE9 pDevice);
	VOID CallMemory();
};

extern FunctionT* Function;

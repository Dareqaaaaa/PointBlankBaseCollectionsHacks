#pragma once

class function
{
public:
	function();
	~function();


	void Init();
	void CallInit(LPDIRECT3DDEVICE9 pDevice);
	void CallEsp(LPDIRECT3DDEVICE9 pDevice, DWORD pCharaManager, DWORD pLocal, DWORD pRenderContext, int iMyIndex);
	void CallAimBullet(LPDIRECT3DDEVICE9 pDevice, DWORD pCharaManager, DWORD pGameContext, DWORD pRenderContext, int iMyIndex);
	void CallAimbot(LPDIRECT3DDEVICE9 pDevice, DWORD pCharaManager, DWORD pRenderContext, int iMyIndex);
	void CallMemory(DWORD pParam);
private:
	DWORD ADR_GAMECONTEXT;
	DWORD OFS_TEAM; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

	DWORD OFS_TICKET; //D9 84 81 ?? ?? ?? ?? 8B 4D F4 64 89 0D 00 00 00 00 //float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum
	DWORD OFS_TICKETSIZE; // imul    eax, edi, 48h "Search OFS_TICKET"

	DWORD ADR_CHARACTERPOINTER; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
	DWORD OFS_CHARACTERSIZE; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 13 //IMUL EAX,EAX,10C

	DWORD ADR_PLAYERPOINTER; //39 3D ?? ?? ?? ?? 75 10 6A 01 8B CE
	DWORD OFS_FASTSHOT; //FF 15 ?? ?? ?? ?? 8B 0D ?? ?? ?? ?? 8B 55 E8 3B 84 0A  *(DWORD*)+2

	DWORD OFS_GAMEINFOSIZE; //69 C0 ?? ?? ?? ?? 05 ?? ?? ?? ?? 03 C1 8B 4D F4 +2 //getGameInfo_Chara
	DWORD OFS_GAMEINFOOFFSET; //69 C0 ?? ?? ?? ?? 05 ?? ?? ?? ?? 03 C1 8B 4D F4 +7

	DWORD ADR_ROOMPOINTER; //F6 C4 44 7A 26 A1 ?? ?? ?? ?? + *(DWORD*)+12

	//Aimbot
	DWORD End; //FF 75 08 8D BE ?? ?? ?? ?? 8B CF FF 15 ?? ?? ?? ??
	DWORD SetEnd; //FF 15 ?? ?? ?? ?? 8B 8E ?? ?? ?? ?? E8 ?? ?? ?? ?? 84 C0 //*(DWORD*)+2 

	//OPK
	DWORD SetPos; //?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z || i3FrameworkDx.dll
	DWORD GetButtonState; //?GetButtonState@i3InputMouse@@QAEIXZ || i3InputDx.dll
	

	DWORD ADR_NoRecoil1; //55 8B EC 51 51 53 57 8B F9 8D 5F 28 8B CB E8 ?? ?? ?? ??
	DWORD ADR_NoRecoil2; //55 8B EC 51 51 53 57 8B F9 8D 5F 28 8B CB E8 ?? ?? ?? ??

	DWORD ASM_UNLIAMMO; //50 8B CB FF 96 ?? ?? ?? ?? 8B 03 8B CB 6A 00
	DWORD ASM_AMMORELOAD; //DD 05 ?? ?? ?? ?? C7 45 F8 CD CC CC 3D 0F B7 02
	DWORD ASM_ACCURACY; //F0 3F 43 4D 65 ?? ?? 61 67 65 42 6F
	DWORD ASM_RESPAWNINDEATH; //75 07 C7 45 0C ?? ?? ?? ?? D9 46 04 8B CF
	DWORD ASM_FASTBOMB; //D9 45 FC D9 EE DB F1 5E
	DWORD ASM_GETCURHP; //5F C3 B8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 81 EC ?? ?? ?? ?? 56 + 2
	DWORD ASM_ANTIKICK; //55 8B EC 8B 45 08 56 8B F1 85 C0 78 15 0F 9F C0 0F B6 C0 50
	DWORD ASM_UNLOCKROOM; //33 C0 50 50 50 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 5E 8B E5
	DWORD ASM_SPEEDHACK; //8B 4D F4 D9 45 08 5F 5E  5B 64 89 0D 00 00 00 00
	DWORD ASM_GHOSTMODE; //DC 0D ?? ?? ?? ?? 89 45 D8 8B 43 04

	//isVisible
	DWORD ADR_VIEWER;
	DWORD ASM_SETSTART;
	DWORD ASM_SETEND;
	DWORD ASM_INITIALIZE;
	DWORD ASM_RAYCLASS;

	//Bypass
	DWORD KERNEL_GETLASTERROR; //6A ?? 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 7D 08 85 FF 75 ?? FF //+7F
	DWORD ANTI_CHEAT; //6A 10 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 7D 08
	DWORD ANTI_CHEAT_PUSH; //6A 10 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 7D 08 + *(DWORD*)3

	void HookBypass(DWORD pParam);
	
	void DrawBoneLine(DWORD pPlayer, DWORD pRenderContext, const char * Start, const char * End, DWORD Color, LPDIRECT3DDEVICE9 pDevice);
	bool GetBoneMatrix(DWORD pPlayer, D3DXVECTOR3 &Out, const char * bonename);
	void DrawPlayerName(int index, int x, int y);
	bool isAlive(DWORD pCharaManager, int index);
	bool isVisible(DWORD pCharaManager, int iMyIndex, int index, D3DXVECTOR3 vMe, D3DXVECTOR3 vEnemy);
	bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, DWORD pRenderContext, D3DVECTOR Player, D3DVECTOR &PlayerScaled);
	int GetTarget(DWORD pCharaManager, int iMyIndex, bool bVisisble = true);
	int GetPlayerByIndex(DWORD pCharaManager, int index);
	int GetHealth(DWORD pPlayer, int index);
	int GetMyIndex(DWORD pGameContext);
	void Write(void *adress, void *bytes, int size);
	float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB);
};

extern function pFunction;
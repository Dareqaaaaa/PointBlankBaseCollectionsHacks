//#include "AutoLogger.h"

/**************** Pointers *****************/
#define ResultPlayerBase2		0xE62AF0 // Can get by Searching "setMySlotIdxEx(int)" 
#define ResultHealthBase2		0xE633BC // g_pCharaManager == NULL
#define ResultGameContext2		0xE62DEC // void __thiscall UserContext::SendDeathChara(void)
#define ResultBaseAmmo2			0xD3EE58 // 55 8B EC 83 EC 18 89 4D  E8 8D 45 F0 50 8D 4D F4 51 8B 15 @@ STR_TBL_BATTLEGUI_NOTICE_RESPAWN
#define ResultDeviceBase		0x10ED84 // i3GfxDx.dll + ?g_pRenderContext@@3PAVi3RenderContext@@


/****************** Memory *********************/
#define ResultESP1				0x602A50 // ForciblyRemove @@  jnz     short loc_63F4D0 @@ push    offset aForciblyremo_0 ; "ForciblyRemove"
#define ResultESP2				0x66F2FD // %s -%dHP @@ jz      loc_6C69AD

#define ResultRecoilHorzAngle	0xCA8EE8 // RecoilHorzAngle
#define ResultRecoilVertAngle	0xCA8F08 // RecoilVertAngle
#define ResultDeviation_Max		0xCA9694 // Deviation_Max

/****************** Offsets *******************/
#define ResultTeam				0x449B4 // void __thiscall BattleSlotContext::setMySlotIdx(int)
#define ResultPlayerSize		0x1D0 // 69 C0 ?? ?? ?? ?? 8D 44  08 14 || class CGameCharaBase *__thiscall CGameCharaManager::RequestFreeAI || Last call    sub_51E810
#define ResultTarget1			0x16C // UpdateNickOnTarget(void) TOP! @@ mov     eax, [edx+16Ch]
#define ResultTarget2			0xD8 // int __thiscall CGameCharaCollisionContext::UpdateNickOnTarget(void) @@ UP dword ptr [eax+0D8h],  0xD8;
#define ResultAutoShot			0xA0C30 // i3InputDx.dll +  ?GetButtonState@i3InputMouse@@QAEIXZ @@ mov     eax, [eax+1Ch] 

/****************** Aimbot *******************/
#define ResultDeltaX			0xA0C00 // i3InputDx.dll + ?GetDeltaX@i3InputMouse@@QAEMXZ  @@ fld     dword ptr [eax+24h]
#define ResultDeltaY			0xA0C10 // i3InputDx.dll + ?GetDeltaY@i3InputMouse@@QAEMXZ  @@ fld     dword ptr [eax+28h]

/***************** IsVisible ******************/
#define ResultpPhysixCtx		0x21EDCC // ?g_pPhysixCtx@@3PAVi3PhysixContext@@A
#define ResultSetStart			0x20170 // ?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z
#define ResultSetEnd			0x1FFF0 // ?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
#define ResultInitialize		0x357F0 // ??0i3CollideeLine@@QAE@XZ
#define ResultRayClass			0x887E0 // ?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z

/******************** ESP ***********************/
#define ResultESPPlayerSize		0x1608 // BattleSlotContext::getGameInfo_Chara_Normal(int) const || imul    esi, 1608h
#define ResultESPPlayerPos		0x2508 // BattleSlotContext::getGameInfo_Chara_Normal(int) const || lea     eax, [esi+edi+2450h] + 0xB8
#define ResultESPHealthSize		0xC28 //CheatEngine Result == 0xC28

/**************** Replace Weapon ***************/
#define ResultNetCharSize		0x40 // const class NET_CHARA_INFO *__thiscall BattleSlotContext::getNetCharaInfo_Normal(int) const
#define ResultNetCharOffset		0xC0 // const class NET_CHARA_INFO *__thiscall BattleSlotContext::getNetCharaInfo_Normal(int) const
#define ResultSetWeaponSet		0x527F90 // void __thiscall CGameCharaManager::SetCharaWeaponSet(class CGameCharaBase *,const class NET_CHARA_INFO *)
#define ResultWeaponCheck		0x63C3C0 // void __cdecl GameContextUtil::CheckWeaponList(const struct ITEM_INFO *)

/*************** Player Weapon **************/
#define Result1stWeapon			0x90 // Search 103004 with pointer ResultPlayerBase2 + 0xB4 = 103004 
#define Result2ndPistol			0x98
#define Result3rdKnife			0xA0
#define Result4thGranade		0xA8

/**************** Variables ******************/
class Var{
public:
	//DIP
	int Dip[100];

	//Player
	int Aimbot[100];
	int AimKey[100];
	int ESP[100];
	int Auto[100];
	int Player[100];

	//Weapon Details
	int WeaponClass[100];
	int Weapon1st[100];
	int Pistol[100];
	int Knife[100];
	int Granade[100];

	//Weapon Main
	int Weapon1stMain[100];
	int PistolMain[100];
	int KnifeMain[100];
	int GranadeMain[100];

}var;

class RenderContext; 
class RenderData; 
class CGameBase; 
class CBonesContext; 
class Bone; 
class cGameStageInfo; 

DWORD DWGFX = (DWORD)GetModuleHandleA("i3GfxDx.dll"); 
RenderContext *pRC = (RenderContext*)(DWGFX + ResultDeviceBase); 

D3DVIEWPORT9 Viewport;
LPD3DXLINE pLine;
bool AimEnable = false;
bool Shot = false;
int AimHead = 0;
int	 AimSlot = 0;
int AimBody;
int SAimBody;

class RenderContext 
{ 
public: 
	RenderData* pRenderData; 
	char unknown4[912]; 
	D3DXVECTOR3 bone; 
	D3DXVECTOR3 bone1; 
	D3DXVECTOR3 bone2; 
}; 

class RenderData
{ 
public: 
	char _0x0000[0x8B0]; // i3GfxDx.dll + ?GetViewMatrix@i3RenderContext@@QAEPATMATRIX@@XZ
	D3DXMATRIX ViewMatrix; //0x08B0 
	D3DXMATRIX ProjMatrix; //0x08F0 
	D3DXMATRIX World; //0x0930 
	char _0x0970[0x490C]; 
	DWORD ScreenWidht; //0x527C 
	DWORD ScreenHeight; //0x5280 
	char _0x5284[0xC0]; 
	LPDIRECT3DDEVICE9 pDevice; //0x5344 
	char _0x5348[0xF8];
};

/******** ESP Deatils Start ********/
class CPlayers
{
public:
    D3DXVECTOR3 pos;
};
/********* ESP Details End *********/

/******** Misc Start **********/
struct CHealth
{
	BYTE CurHP;
};

struct CTeam
{
	BYTE iTeam;
};

struct CRank
{
	BYTE iRank;
};

struct CNames
{
    char szNames[33];
};

class GM
{
public:
	BYTE iRank;
	char _0x0001[15];
	WORD iHack;
};
/*********** Misc End **************/

/*********** IsVisible Start **************/
class i3CollideeLine
{ 
public: 
	D3DXVECTOR3 vTemp;
	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vDir; 
};

class i3PhysixHitResult
{ 
public: 
	char _0x0000[28];
	D3DXVECTOR3 FinalPos; 
	float Distance; 
};

class dwPhtsX{
public:
	void* i3PhysixContext;
};

/*********** IsVisible End **************/

int GetTeam(char MyTeam) 
{ 
	for(int i = 0; i < 16; i+=2) 
		if(i == MyTeam) return 2; 
	for(int i = 1; i< 16; i+=2) 
		if(i == MyTeam) return 1; 
	return -1; 
}

int GetCharaIndex()
{
	unsigned long dwBase	= *(DWORD*)(ResultPlayerBase2);
	CTeam *MyTeam = (CTeam*) ((dwBase + ResultTeam));
	return MyTeam->iTeam;
}

DWORD GetPlayerTarget(DWORD Index)
{
	DWORD dwBaseHealth  = *(PDWORD)(ResultHealthBase2);
	if(IsBadReadPtr((void*)dwBaseHealth, 4))
		return 0;
	DWORD PlayerIndexA = *(PDWORD)(dwBaseHealth + 0x14 + (Index * ResultPlayerSize));
	if(IsBadReadPtr((void*)PlayerIndexA, 4))
		return 0;
	DWORD PlayerIndexB = *(PDWORD)(PlayerIndexA + ResultTarget1);
	if(IsBadReadPtr((void*)PlayerIndexB, 4))
		return 0;
	//int __thiscall CGameCharaCollisionContext::UpdateNickOnTarget(void)
	DWORD IsTargetingEnemy = *(PDWORD)(PlayerIndexB + ResultTarget2);
	if(IsBadReadPtr((void*)IsTargetingEnemy, 4))
		return 0;
	return IsTargetingEnemy;
}

float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}

bool IsAlive(int Index)
{
	return true;
}

bool VisibleTarget(int iSlot) 
{ 
	if(iSlot == -1)
		return false;
	unsigned long dwBasePlayer = *(DWORD*)(ResultPlayerBase2); 
	DWORD dwi3Scenedx = (DWORD)GetModuleHandleA("i3SceneDx.dll");
	CPlayers *pPlayer = (CPlayers*)(dwBasePlayer + ResultESPPlayerSize * iSlot + ResultESPPlayerPos);
	CPlayers *pLocal = (CPlayers*)(dwBasePlayer + ResultESPPlayerSize * GetCharaIndex() + ResultESPPlayerPos);
	dwPhtsX *pViewer = (dwPhtsX*)(dwi3Scenedx + ResultpPhysixCtx); //?g_pPhysixCtx@@3PAVi3PhysixContext@@A
	DWORD dwSetStart = (dwi3Scenedx + ResultSetStart); //?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z
	DWORD dwSetEnd = (dwi3Scenedx + ResultSetEnd); //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
	DWORD dwInitialize = (dwi3Scenedx + ResultInitialize ); //??0i3CollideeLine@@QAE@XZ
	DWORD dwReyClass = (dwi3Scenedx + ResultRayClass); //?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z
	i3CollideeLine Line; 
	i3CollideeLine* cLine; 
	void *PhysX = pViewer->i3PhysixContext; 
	cLine = &Line; 
	D3DXVECTOR3 vMe, vEnemy; 
	DWORD dwPhysix; 
	vMe = pLocal->pos;
	vEnemy = pPlayer->pos;
	Line.vStart.y += 0.1f; 
	float distance = CalcDistance(vEnemy, vMe); 

	_asm
	{ 
		mov ecx, [cLine]; 
		call [dwInitialize];
		lea edx, vMe;
		push edx;
		mov ecx, [cLine];
		call [dwSetStart];
		lea eax, vEnemy; 
		push eax; 
		mov ecx, [cLine];
		call [dwSetEnd];
		push -1;
		push 0;
		push [cLine];
		mov ecx, [PhysX];
		//i3PhysixContext::RaycastClosest
		//?RaycastClosest@i3PhysixContext@@QAEPAU_tagi3PhysixHitResult@@PAVi3CollideeLine@@HI@Z
		call dword ptr ds:[dwReyClass];
		mov [dwPhysix], eax;
	}
	i3PhysixHitResult *pX = (i3PhysixHitResult*)dwPhysix; 

	if(pX == 0) 
		return false; 
	if(pX->Distance < distance) 
		return false;

	return true;
}

int GetPriorityTarget()
{
	int Result = -1;
	float fMaxDistance = 100.0f;
	D3DXVECTOR3 PlayerEnd, LocPlayer;
	unsigned long dwBasePlayer = *(DWORD*)(ResultPlayerBase2); 
	for (int index = 0; index < 16; index++)
	{
		CPlayers *pPlayer = (CPlayers*)(dwBasePlayer + ResultESPPlayerSize * index + ResultESPPlayerPos);
		CPlayers *pLocal = (CPlayers*)(dwBasePlayer + ResultESPPlayerSize * GetCharaIndex() + ResultESPPlayerPos);
		if(VisibleTarget(index))
		{
			if (IsAlive(index) && GetCharaIndex() != index)
			{
				if (GetCharaIndex() %2 != index % 2)
				{
					LocPlayer = pLocal->pos;
					PlayerEnd = pPlayer->pos;
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

bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
   D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
	D3DXMATRIX identity;
    D3DXVECTOR3 vScreen;
	pDevice->GetViewport(&Viewport);
	Viewport.X = Viewport.Y = 0;
    Viewport.MinZ     = 0;
    Viewport.MaxZ     = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
  
 if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
 {
     PlayerScaled.x = vScreen.x;
     PlayerScaled.y = vScreen.y ;
     PlayerScaled.z = vScreen.z;
	 return true; 
 }
 return false;
}


float fX = 10.0f, fY = 10.0f, fZ = 10.0f;
//"void __thiscall WeaponBase::DoLineColli"...
DWORD dwEnd = 0x559891;
DWORD dwReturnEnd = dwEnd + 0x9;
bool EndEnable;
DWORD dwTempEcx, dwTempEbx;
_declspec( naked ) void EndAim( )
{
    if ( EndEnable )
    {
        _asm
        {
            mov     [dwTempEcx], ecx;
            mov     [dwTempEbx], ebx;
            mov     ecx, [ebp+0x0C];
            mov     eax, [fX];
            mov     [ecx], ebx;
            mov     eax, [fY];
            mov     [ecx+0x04], ebx;
            mov     eax, [fZ];
            mov     [ecx+0x08], ebx;
            mov     ecx, [dwTempEcx];
            mov     ebx, [dwTempEbx];
        }
    }

    _asm
    {
		mov     eax, [ebp+8];
        lea     edi, [esi+0x3DC];
        jmp     dwReturnEnd;
    }
}

//void __thiscall i3CollideeLine::SetEnd(i3CollideeLine *this, union VEC3D *)
bool BulletEnable= false;
DWORD MathDx = (DWORD)GetModuleHandleA("i3MathDx.dll");
DWORD VEC3DEqual = (MathDx+0x17E0);
DWORD VEC3DDifference = (MathDx+0x19B0);

_declspec(naked)void i3CollideeEnd()
{
	_asm
	{
		cmp [BulletEnable], 0;
		je Skip;
		mov eax, [esp+4];
		mov [eax], edx;
		mov edx, [fX];
		mov [eax+0], edx;
		mov edx, [fY];
		mov [eax+4],edx;
		mov edx, [fZ];
		mov [eax+8], edx;
		mov edx, [ecx+8];
Skip:
		jmp Original;
		nop;
Original:
		PUSH EBP
		MOV EBP,ESP
		MOV EAX,DWORD PTR SS:[EBP+0x8]
		SUB ESP,0x0C
		PUSH ESI
		MOV ESI,ECX
		PUSH EDI
		LEA EDI,DWORD PTR DS:[ESI+0x18]
		PUSH EAX
		MOV ECX,EDI
		CALL DWORD PTR DS:[VEC3DEqual]
		LEA ECX,DWORD PTR DS:[ESI+0xC]
		PUSH ECX
		LEA EDX,DWORD PTR SS:[EBP-0xC]
		PUSH EDX
		MOV ECX,EDI
		CALL DWORD PTR DS:[VEC3DDifference]
		PUSH EAX
		LEA ECX,DWORD PTR DS:[ESI+0x24]
		CALL DWORD PTR DS:[VEC3DEqual]
		POP EDI
		POP ESI
		MOV ESP,EBP
		POP EBP
		RETN 4
	}
}

//************** AImbot Details *****************//
float MouseDeltaX, MouseDeltaY, MouseDeltaZ = 0;

__declspec(naked)void Aim_DeltaX()
{
	_asm
	{
		cmp [AimEnable],1
		je StartAim
NORMAL:
		fld dword ptr [ecx+0x24]
		retn
StartAim:
		cmp [AimEnable],0
		je NORMAL
		fld dword ptr [MouseDeltaX]
		retn
	}
}

__declspec(naked)void Aim_DeltaY()
{
	_asm
	{
		cmp [AimEnable],1
		je StartAim
NORMAL:
		fld dword ptr [ecx+0x28]
		retn
StartAim:
		cmp [AimEnable],0
		je NORMAL
		fld dword ptr [MouseDeltaY]
		retn
	}
}

_declspec(naked)void MouseHook()
{
	_asm
	{
		cmp		[Shot], 0
		je		Original
		mov     eax, 1
		retn
Original:
		mov     eax, [ecx+0x1C]
		retn
	}
}
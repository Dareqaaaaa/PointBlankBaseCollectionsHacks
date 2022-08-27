#include "Class.h"

int posiX,posiY,posiZ;

void JhemWrite(void *adress,void *bytes,int size)
{
	DWORD dwProtect;
	VirtualProtect((void*)adress,size,PAGE_EXECUTE_READWRITE,&dwProtect);
	memcpy((void *)adress,(PBYTE)bytes,size); 
	VirtualProtect((void*)adress,size,dwProtect,&dwProtect); 
}

bool HookReplace(unsigned long ADRexec, int OFSexec, int PTRexec)
{
if (!IsBadReadPtr((void*)ADRexec, sizeof(unsigned long)))
{
if (!IsBadReadPtr((void*)(*(unsigned long*)ADRexec + OFSexec), sizeof(unsigned long)))
{
*(int*)(*(unsigned long*)ADRexec + OFSexec) = PTRexec;
}
}
return 0;
}

DWORD CGameCharaBaseShoot(void)
{
	unsigned long dwBase = *(DWORD*)ResultHealthBase2;
	return dwBase;
}

DWORD CGetWeaponID(void)
{
	unsigned long dwBase = *(DWORD*)0xC93854;
	dwBase = *(DWORD*)dwBase + 0x10;
	return dwBase;
}

typedef void (__thiscall * tSetCharaWeaponSet)(DWORD CGameCharaManager,DWORD CGameCharaBase, DWORD pNetCharaInfo);
tSetCharaWeaponSet SetCharaWeaponSet;

void FakeReplace()
{
	DWORD BasePlayer_A = *(DWORD*)(ResultGameContext2);
	DWORD BasePlayer_B = *(DWORD*)(ResultHealthBase2);
	int MyIndex = GetCharaIndex();
	DWORD CGameCharaManager = CGameCharaBaseShoot();
	DWORD CGameCharaBase = *(DWORD*)(BasePlayer_B + 0x14 + (MyIndex*ResultPlayerSize));
	//DWORD pNetCharaInfo = BasePlayer_A + ((ResultNetCharSize) + (MyIndex*ResultNetCharOffset));
	DWORD pNetCharaInfo = CGetWeaponID() + ((0x28) + (MyIndex*2));
	SetCharaWeaponSet = (tSetCharaWeaponSet)ResultSetWeaponSet;
	SetCharaWeaponSet(CGameCharaManager, CGameCharaBase, pNetCharaInfo);
}

void LongPtr ( DWORD adress, DWORD offset, DWORD offset2, int Value ){__try{DWORD OldPtr;OldPtr = *(PDWORD)((DWORD)adress) + offset;OldPtr = *(PDWORD)((DWORD)OldPtr) + offset2;*(int*)(OldPtr) = Value;}__except (EXCEPTION_EXECUTE_HANDLER){}}
int WritePtr (unsigned long ads, unsigned long ptr, int value){__try{unsigned long WrtPointer = false;WrtPointer = *(unsigned long*)((ads))+ptr;*(int*)(WrtPointer) = value;return true;}__except (EXCEPTION_EXECUTE_HANDLER){return false;}}


VOID Replace1stWeapon(int WeaponID){int MyIndex = GetCharaIndex();HookReplace((DWORD)ResultGameContext2, Result1stWeapon+(MyIndex*ResultNetCharOffset), WeaponID);}
VOID ReplaceSMG(int WeaponID){int MyIndex = GetCharaIndex();	HookReplace((DWORD)ResultGameContext2, Result1stWeapon+(MyIndex*ResultNetCharOffset), WeaponID);}
VOID ReplaceSniper(int WeaponID){int MyIndex = GetCharaIndex();	HookReplace((DWORD)ResultGameContext2, Result1stWeapon+(MyIndex*ResultNetCharOffset), WeaponID);}
VOID ReplaceShotgun(int WeaponID){int MyIndex = GetCharaIndex();	HookReplace((DWORD)ResultGameContext2, Result1stWeapon+(MyIndex*ResultNetCharOffset), WeaponID);}
VOID ReplacePistol(int WeaponID){int MyIndex = GetCharaIndex();	HookReplace((DWORD)ResultGameContext2, Result2ndPistol+(MyIndex*ResultNetCharOffset), WeaponID);}
VOID ReplaceKnife(int WeaponID){int MyIndex = GetCharaIndex();	HookReplace((DWORD)ResultGameContext2, Result3rdKnife+(MyIndex*ResultNetCharOffset), WeaponID);}
VOID ReplaceGranade(int WeaponID){int MyIndex = GetCharaIndex();	HookReplace((DWORD)ResultGameContext2, Result4thGranade+(MyIndex*ResultNetCharOffset), WeaponID);}

bool bAmmo = false;
/*VOID PlayerHacks()
{
	DWORD Player = *(DWORD*)ResultPlayerBase2;
	if(Player!=0)
	{

		if(var.Player[2] == 1) //NoSpread
		{
			int poinn = 0x24;
			do
			{
			 LongPtr(ResultBaseAmmo2, 0x134, poinn, 1061997773);
			 poinn += 4;
			}
			while ( poinn <= 0x4C );
			LongPtr(ResultBaseAmmo2, 0x134, 0x18, 0);
			LongPtr(ResultBaseAmmo2, 0x134, 0x20, 0);
			for( int offfset = 0x50; offfset <= 0x6C; offfset += 4 ){
				LongPtr(ResultBaseAmmo2, 0x134, offfset, 0);
			}
		}

		if(var.Player[3] == 1) //Fast Shot
		{
			WritePtr(ResultBaseAmmo2, 0x108, 0); 
		}
	
		if(var.Player[4] == 1) //Multi Knife
		{
			if(GetAsyncKeyState(VK_LBUTTON))
			{__try{
				int value = *(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(ResultBaseAmmo2)+ 0x138) + 0x20) + 0x294); 
				*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(ResultBaseAmmo2)+ 0x138) + 0x20) + 0x290) = value;
			}__except (EXCEPTION_EXECUTE_HANDLER){}}
		}
	
		if(var.Player[5] == 1) //NFD
		{
			WritePtr(ResultBaseAmmo2, 0x11B, 0x40);
		}	

		if(var.Player[6] == 1)
		{
			if(bAmmo == false)
			{
				__ReadMem(ResultBaseAmmo2, 0x138, 0x18, 0x29C, 1);
				__ReadMem(ResultBaseAmmo2, 0x138, 0x1C, 0x29C, 2);
				bAmmo = true;
			}
			if(bAmmo == true)
			{
				_WriteMEM(ResultBaseAmmo2, 0x138, 0x18, 0x29C, Weapon);
				_WriteMEM(ResultBaseAmmo2, 0x138, 0x1C, 0x29C, Pistol);
			}
		}
	}
}*/

bool fixweapobug = false;

int RiflesID[] = {103004,103001,103002,103003,103005,103009,103010,103011,103013,103014,103015,103017,103018,103019,103020,103021,103022,103023,103024,103025,103026,103028,103029,103030,103031,103032,103033,103035,103037,116001};
int SMGID[] = {204006,204001,204002,204003,204004,204007,204008,204009,204010,204011,204012,204013,204014,204015,204016,204020,204021,204022,204023,204024,204025};
int SniperID[] = {305001,305002,305003,305004,305005,305006,305007,305008,305009,305010,305011,305012,305013};
int ShotgunID[] = {406001,406002,406003,406004,406005,406006,406007,406008,406009};
int PistolID[] = {202001,202002,202003,202005,202007};
int KnifeID[] = {301001,301002,301003,301004,301006,301009,301014};
int GrandeID[] = {407001,407002,407003,407004,407005,407006,407007};

VOID ReplaceWeapon()
{
	DWORD Player = *(DWORD*)ResultPlayerBase2;
	if(Player!=0)
	{

		if(GetAsyncKeyState(VK_F5)){

			FakeReplace();
			// Rifles
			if(var.WeaponClass[1] == 0){Replace1stWeapon(RiflesID[var.Weapon1st[1]]);}
			//SMG
			if(var.WeaponClass[1] == 1){ReplaceSMG(SMGID[var.Weapon1st[2]]);}			
			//Sniper
			if(var.WeaponClass[1] == 2){ReplaceSniper(SniperID[var.Weapon1st[3]]);}
			//Shotgun
			if(var.WeaponClass[1] == 3){ReplaceShotgun(ShotgunID[var.Weapon1st[4]]);}

			ReplacePistol(PistolID[var.Pistol[1]]); //Pistol
			ReplaceKnife(KnifeID[var.Knife[1]]); //Knife
			ReplaceGranade(GrandeID[var.Granade[1]]); //Grande

		}

		if(fixweapobug == false){
			if(  memcmp( (void*)ResultWeaponCheck, (void*)"\x55", 1 ) == 0 )
			{
				JhemWrite((void *)(ResultWeaponCheck),(void*)(PBYTE)"\xC3",1); //"void __cdecl GameContextUtil::CheckWeap"
			}
			fixweapobug = true;
		}
	}
}

VOID WallHack(DWORD Addys, DWORD Value)
{
    DWORD PB = (DWORD)GetModuleHandleA(STR_eGxf);
    __try 
    { 
        *(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(PB+Addys)+ 0x0) + 0x3C0) + 0x5C) = Value; 
    }__except(EXCEPTION_EXECUTE_HANDLER){ }
}

bool norecoil = false;
void noRecoil(){
	if (norecoil == false)
	{
		JhemWrite((void *)(ResultRecoilVertAngle),(void*)(PBYTE)"\x00",1); 
		JhemWrite((void *)(ResultRecoilHorzAngle),(void*)(PBYTE)"\x00",1); 
		JhemWrite((void *)(ResultDeviation_Max),(void*)(PBYTE)"\x00",1);
		norecoil = true;
	}
}

unsigned __stdcall Funtions(LPVOID Param)
{
	for(;;)
	{
		DWORD pbStart = (DWORD)GetModuleHandleA("PointBlank.exe"); 
		if (pbStart > 0)
		{
			Sleep(1000);
			JhemWrite((void*)(0x6644BE),(void*)"\x90\x90",2); 
		}
		Sleep(200);
	}
	return 1;
}
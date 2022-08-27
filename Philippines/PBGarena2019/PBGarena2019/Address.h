#include "StdAfx.h"

class AddressT
{
public:
	bool isSet;
public:
	DWORD ADR_GAMECONTEXT;
	DWORD OFS_TEAM;

	DWORD OFS_TICKET; //float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum 
	DWORD OFS_TICKETSIZE; // imul    eax, edi, 48h "Search OFS_TICKET"

	DWORD ADR_CHARACTERPOINTER;
	DWORD OFS_CHARACTERSIZE;

	DWORD ADR_PLAYERPOINTER; //39 3D ?? ?? ?? ?? 75 10 6A 01 8B CE
	DWORD OFS_FASTSHOT;

	//Memory
	DWORD GhostMode; //DC 0D ?? ?? ?? ?? 89 45 D8 8B 43 04
	DWORD RecoilHorzAngle; //RecoilHorzAngle
	DWORD RecoilVertAngle; //RecoilVertAngle
	DWORD Deviation_Max; //Deviation_Max

	//Aimbot
	DWORD CollideeLine; // pEnd != nullptr
	DWORD CollideeLineEnd; //SetEnd
	DWORD VEC3DSetEnd; //??4VEC3D@@QAEAAT0@ABT0@@Z

	//OPK
	DWORD SetPos; //?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z
public:
	void SetPointers();
};

extern AddressT * Address;

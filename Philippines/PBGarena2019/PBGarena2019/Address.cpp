#include "StdAfx.h"

AddressT * Address = new AddressT();

void AddressT::SetPointers()
{
	while (!isSet)
	{
		ADR_GAMECONTEXT = 0x94BC38;
		OFS_TEAM = 0x171B4; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

		OFS_TICKET = 0x1722C; //float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum 
		OFS_TICKETSIZE = 0x12; // imul    eax, edi, 48h "Search OFS_TICKET"

		ADR_CHARACTERPOINTER = 0x94C174; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
		OFS_CHARACTERSIZE = 0x10C; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 13 //IMUL EAX,EAX,10C

		ADR_PLAYERPOINTER = 0x9550C8; //39 3D ?? ?? ?? ?? 75 10 6A 01 8B CE
		OFS_FASTSHOT = 0x120;

		GhostMode = 0x7156A0; //DC 0D ?? ?? ?? ?? 89 45 D8 8B 43 04
		RecoilHorzAngle = 0x75D114; //RecoilHorzAngle
		RecoilVertAngle = 0x75D160; //RecoilVertAngle
		Deviation_Max = 0x75D180; //Deviation_Max

		//Aimbot
		CollideeLine = 0x48C; // pEnd != nullptr || PointBlank.exe || LEA EDI,DWORD PTR DS:[ESI+48C]
		CollideeLineEnd = 0x18; //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@ || i3ScenceDx.dll || 
		VEC3DSetEnd = 0x4140; //??4VEC3D@@QAEAAT0@ABT0@@Z || i3MathDx.dll

		//OPK
		SetPos = 0x635A0; //?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z || i3FrameworkDx.dll

		isSet = true;
	}
}


/*
//PB iNdo

#include "StdAfx.h"

AddressT * Address = new AddressT();

void AddressT::SetPointers()
{
	while (!isSet)
	{
		ADR_GAMECONTEXT = 0x979EB4; //0x94BC38;
		OFS_TEAM = 0x171B4; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

		OFS_TICKET = 0x1722C; //float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum
		OFS_TICKETSIZE = 0x12; // imul    eax, edi, 48h "Search OFS_TICKET"

		ADR_CHARACTERPOINTER = 0x97AC7C; //0x94C174; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
		OFS_CHARACTERSIZE = 0x114; //0x10C; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 13 //IMUL EAX,EAX,10C

		ADR_PLAYERPOINTER = 0x983390; //39 3D ?? ?? ?? ?? 75 10 6A 01 8B CE
		OFS_FASTSHOT = 0x120;

		GhostMode = 0x739828; //DC 0D ?? ?? ?? ?? 89 45 D8 8B 43 04
		RecoilHorzAngle = 0x781F04; //RecoilHorzAngle
		RecoilVertAngle = 0x781F50; //RecoilVertAngle
		Deviation_Max = 0x781F70; //Deviation_Max

		//Aimbot
		CollideeLine = 0x48C; // pEnd != nullptr || PointBlank.exe || LEA EDI,DWORD PTR DS:[ESI+48C]
		CollideeLineEnd = 0x18; //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z || i3ScenceDx.dll ||
		VEC3DSetEnd = 0x4140; //??4VEC3D@@QAEAAT0@ABT0@@Z || i3MathDx.dll

		//OPK
		SetPos = 0x65920; //?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z || i3FrameworkDx.dll

		isSet = true;
	}
}
*/
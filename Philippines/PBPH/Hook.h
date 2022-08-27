#include "Headers.h"

#define Detour_Type_0xE9 1 
#define Detour_Type_0xB8 2 
#define Detour_Type_0x68 3 
#define Detour_Type_0xE8 4 

DWORD CreateDetour(DWORD dwThread,DWORD dwAdress,DWORD dwType,DWORD dwSize)
{
        DWORD dwDetour,dwProtect,i;
        if (dwAdress&&dwThread&&dwSize>= dwSize)
        {
                dwDetour = (DWORD)VirtualAlloc(0,dwSize+dwSize,0x1000,0x40);
                if (dwDetour&&VirtualProtect((VOID*)dwAdress,dwSize,0x40,&dwProtect))
                {
                        for (i=0;i<dwSize;i++)
                        {
                                *(BYTE*)(dwDetour+i)=*(BYTE*)(dwAdress+i);
                        }
                        switch (dwType)
                        {
                            case Detour_Type_0xE9:
                                {
                                    *(BYTE*)(dwDetour+dwSize+0)=0xE9;
                                    *(DWORD*)(dwDetour+dwSize+1)=(dwAdress-dwDetour-dwSize);
                                    *(BYTE*)(dwAdress+0)=0xE9;
                                    *(DWORD*)(dwAdress+1)=(dwThread-dwAdress-dwSize);
                                }
                                break;
                                case Detour_Type_0xB8:
                                {
                                    *(BYTE*)(dwDetour+dwSize+0)=0xB8;
                                    *(DWORD*)(dwDetour+dwSize+1)=(dwAdress+dwSize);
                                    *(WORD*)(dwDetour+dwSize+5)=0xE0FF;
                                    *(BYTE*)(dwAdress+0)=0xB8;            
                                    *(DWORD*)(dwAdress+1)=(dwThread);
                                    *(WORD*)(dwAdress+5)=0xE0FF;
                                }
                                break;
                                case Detour_Type_0x68:
                                {
                                    *(BYTE*)(dwDetour+dwSize+0)=0x68;
                                    *(DWORD*)(dwDetour+dwSize+1)=(dwAdress+dwSize);
                                    *(WORD*)(dwDetour+dwSize+5)=0xC3;
                                    *(BYTE*)(dwAdress+0)=0x68;            
                                    *(DWORD*)(dwAdress+1)=(dwThread);
                                    *(WORD*)(dwAdress+5)=0xC3;
                                }
                                break;
                        }
                        VirtualProtect((VOID*)dwAdress,dwSize,dwProtect,&dwProtect);
                        VirtualProtect((VOID*)dwDetour,dwSize+dwSize,0x20,&dwProtect);
                        return dwDetour;
                }
        }
        Sleep(10);
        return (0);
}

void *DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
    BYTE *jmp;
    DWORD dwback;
    DWORD jumpto, newjump;
 
    VirtualProtect(src,len,PAGE_READWRITE,&dwback);
 
    if(src[0] == 0xE9)
    {
        jmp = (BYTE*)malloc(10);
        jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
        newjump = (jumpto-(DWORD)(jmp+5));
        jmp[0] = 0xE9;
        *(DWORD*)(jmp+1) = newjump;
        jmp += 5;
        jmp[0] = 0xE9;
        *(DWORD*)(jmp+1) = (DWORD)(src-jmp);
    }
    else
    {
        jmp = (BYTE*)malloc(5+len);
        memcpy(jmp,src,len);
        jmp += len;
        jmp[0] = 0xE9;
        *(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
    }
    src[0] = 0xE9;
    *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;
 
    for(int i = 5; i < len; i++)
        src[i] = 0x90;
 
    VirtualProtect(src,len,dwback,&dwback);
    return (jmp-len);
}

/*-------------------------------------------------------------------------------------------------------------------*/
BYTE Weapon,Pistol,Knife,Bomb,Smoke,Dual;
void __ReadMem(DWORD Base,DWORD Ofs1,DWORD Ofs2, DWORD Ofs3, int opt)
{
	DWORD Temp =0;
	if (IsBadReadPtr((PDWORD)Base,4)==0){
		Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
		if (IsBadReadPtr((PDWORD)Temp,4)==0){
			Temp=*(PDWORD)((DWORD)(Temp))+Ofs2;
			if (IsBadReadPtr((PDWORD)Temp,4)==0){
				Temp=*(PDWORD)((DWORD)(Temp))+Ofs3;
				if (IsBadReadPtr((PDWORD)Temp,4)==0){
					switch (opt)
					{
					case 1:
						Weapon = *(PBYTE)Temp;
					case 2:
						Pistol = *(PBYTE)Temp;
					case 3:
						Knife = *(PBYTE)Temp;
					case 4:
						Bomb = *(PBYTE)Temp;
					case 5:
						Smoke = *(PBYTE)Temp;
					case 6:
						Dual = *(PBYTE)Temp;
					}
				}
			}
		}
	}
}

void _WriteMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD Ptr3, DWORD WriteValue)
{
	DWORD Temp=0;
	if (IsBadReadPtr((PDWORD)Adr, 4) == 0)
	{ 
		Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
		if (IsBadReadPtr((PDWORD)Temp,4) == 0)
		{ 
			Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
			if (IsBadReadPtr((PDWORD)Temp,4) == 0)
			{ 
				Temp = *(PDWORD)((DWORD)(Temp)) + Ptr3;
				if (IsBadReadPtr((PDWORD)Temp,4) == 0)
				{
					*(PDWORD)Temp = WriteValue;
				}
			}
		}
	}
}

BOOL bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}
DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
		if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);

	return 0;
}

DWORD hFindPattern ( DWORD dwStartAddress,DWORD dwSize, BYTE *bMask, char * szMask, int codeOffset, BOOL extract )
{ 
    for ( DWORD i = 0; i < dwSize; i++ )
    {
        if ( bCompare((BYTE*)(dwStartAddress + i),bMask,szMask) )
        {
            if ( extract )  
            {
                return *(DWORD*)(dwStartAddress+i+codeOffset);
 
            } else {
 
                return  (DWORD)(dwStartAddress+i+codeOffset);
            }
        }
    }
    return NULL;
}
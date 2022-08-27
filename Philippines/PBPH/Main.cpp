#include "Headers.h"
#include "KeyPress.h"
#include "Xor.h"
#include "Hook.h"
#include "Menu.h"
ID3DXLine *g_pLine = NULL;
#include "Setting.h"
#include "Functions.h"
#include "ESP.h"
#include "Stride.h"
#include "HWID.h"



bool DeviceReset = true;

#define pD3DdeviceX             LPDIRECT3DDEVICE9

DWORD GetDevice__EndScene;
DWORD Return_EndScene;
DWORD retMyDIP;
HMODULE Module_d3d9;
LPDIRECT3DDEVICE9 ReadyDevice;
pD3DdeviceX g_pDevice = 0;
LPD3DXFONT pFont;
D3DVIEWPORT9 VPT	={0};
static LPDIRECT3DDEVICE9 pDevice; 

DWORD i3gfxs,g_pRenderContext;
LPDIRECT3DDEVICE9 npDevice;

DWORD  dwi3Gfx = (DWORD)GetModuleHandle("d3d9.dll");
DWORD ADR_Device = (dwi3Gfx+ResultDeviceBase);


CHAR *OnOff [] = { "[0/1]", "[1/1]" };
CHAR *AimType [] = { "[Head]", "[Body]" };
CHAR *AimKey [] = { "[LBtn]", "[Alt]" , "[CTRL]" };
CHAR *Rnk[] = {"[0/2]", "[1/2]", "[2/2]"};
CHAR *Folder[] = { "[+]", "[-]" };
CHAR *More[] = {"[0/7]", "[1/7]", "[2/7]", "[3/7]", "[4/7]", "[5/7]", "[6/7]", "[7/7]" };

CHAR *oWeaponType [] = { "[Rifle]", "[SMG]", "[Sniper]", "[Shotgun]" };
CHAR *oRifle1 [] = { "[K-2]", "[SG-550 Ext]", "[AK-47 Ext]", "[M4A1 Ext]", "[F2000 Ext]", "[AK-47 G]", "[M4A1 S]", "[K-201 Ext]", "[G36C Ext]", "[SG-550 S]", "[AK SOPMOD]", "[AK-47 Sl]", "[SG-550 Mb]", "[SG-550 Sl]", "[SG-550 Wh]", "[M4A1 Sl]", "[M4A1 Wh]", "[M4A1 G]", "[M4A1 G+]", "[AK-47 Sl]", "[SG-550 Mb]", "[AUG A3]", "[G36C Sl]", "[SG-550 Mb%]", "[G36C%]", "[F2000 Sl]", "[AK SOPMOD%]", "[SG-550-S D]", "[AUG A3]", "[RPG-7]"};
CHAR *oSubMa[] = { "[K-1]", "[MP5K Ext]", "[Spectre Ext]", "[K-1 Ext]", "[MP7 Ex]", "[MP5K G]", "[UMP45 Ext]", "[Spectre W]", "[P90 M.C]", "[P90 Ext]", "[KrissSuperV]", "[Kriss S.V]", "[MP5K Sl]", "[MP5K Wh]", "[Spectre Wh]", "[Spectre Sl]", "[K-1 Sl]", "[MP7 Sl]", "[UMP45 Sl]", "[MP5K D G]", "[Spectre W D]"};
CHAR *oSniper [] = { "[Dragunov]", "[PSG-1]", "[SSG-69]", "[SSG-69 S]", "[L115A1]", "[Dragunov G]", "[PSG-1 S]", "[SSG-69 Sl]", "[PSG-1 Sl]", "[Dragunov Sl]", "[Dragunov CS]", "[Dragunov CG]", "[Dragunov GD]" };
CHAR *oShotgun [] = { "[870MCS]", "[Cholchzhuna]", "[SPAS-15]", "[870MCS W]", "[M1887]", "[SPAS-15 Sl]", "[870MCS T]", "[870MCS Sl]", "[SPAS-15 Sl]" };


CHAR *oPistol [] = { "[Desert Eagle]", "[Mk 23 Ext]", "[K-5]", "[D-Eagle S]", "[C. Python]" };
CHAR *oKnife [] = { "[M7]", "[M9]", "[HAK]", "[Amok Kukri]", "[Mini Axe]", "[M7 G]", "[HAK Sl]" };
CHAR *oGranade [] = { "[K-400]", "[Smoke]", "[Flash]", "[C-5]", "[WP Smoke]", "[C-5 D]", "[Wp Smoke D]" };

//CHAR MenuTitle [ MAX_PATH ] = { "[RAML] PointBlank D3D" }; 

BOOL BFont = FALSE;

INT Variable[ MAX_PATH ];
INT VFolder[ MAX_PATH ];

void ShowMenu()
{
	Additem( STR_D3D, 1,		VFolder[ 0 ],				1,	Folder );
	if( VFolder[ 0 ] )
	{
		Additem( STR_Crosshair, 1,		Variable[ 0 ],				1,	OnOff );
		if( Variable[ 0 ] )
		{
			Additem( STR_Color,		4, CH_CRC,			0,	More );
		}
		Additem( STR_WallHack,		1, var.Dip[1],			0,	OnOff );
		Additem( STR_NoSmoke,		1, var.Dip[2],			0,	OnOff );
		Additem( STR_NoFog,			1, var.Dip[3],			0,	OnOff );
	}
	Additem( STR_ESP, 1,		VFolder[ 2 ],				1,	Folder );
	if( VFolder[ 2 ] )
	{
		Additem( STR_ESPName,					1, ESPName,					0,	OnOff );
		Additem( STR_ESPEdge,					1, ESPEdge,					0,	OnOff );
		Additem( STR_ESPEdgeColor,				7, var.ESP[1],				0,	More );
		Additem( STR_ESPBox,					1, ESPBox3D,				0,	OnOff );
		Additem( STR_ESPBoxColor,				7, var.ESP[2],				0,	More );
		Additem( STR_ESPLine,					1, ESPLine,					0,	OnOff );
		Additem( STR_ESPLineColor,				7, var.ESP[4],				0,	More );
		//Additem( STR_ESPBone,					1, ESPBone,					0,	OnOff );
		//Additem( STR_ESPBoneColor,				7, var.ESP[5],				0,	More );
		Additem( STR_ESPHealth,					1, ESPHealth,				0,	OnOff );
		//Additem( STR_HPType,					1, var.ESP[3],				0,	OnOff );
	}

	//Additem( STR_AimBot, 1,		VFolder[ 3 ],				1,	Folder );
	if( VFolder[ 3 ] )
	{
		Additem( STR_AimbotV,					1, var.Aimbot[2],			0,	OnOff );
		Additem( STR_AimbotType,				1, AimBody,					0,	AimType );
		Additem( STR_AimbotKey,					2, var.AimKey[1],			0,	AimKey );
	}
	//Additem( STR_SAimbot, 1,		VFolder[ 4 ],				1,	Folder );
	if( VFolder[ 4 ] )
	{
		Additem( STR_SAimbotV,					1, var.Aimbot[1],			0,	OnOff );
		Additem( STR_SAimbotType,				1, SAimBody,				0,	AimType );
		Additem( STR_SImbotKeu,					2, var.AimKey[1],			0,	AimKey );
	}

	//Additem( STR_Player, 1,		VFolder[ 40 ],				1,	Folder );
	if( VFolder[ 40 ] )
	{
		Additem( STR_AutoHead,					1, var.Aimbot[3],			0,	OnOff );
		Additem( STR_AutoBody,					1, var.Aimbot[4],			0,	OnOff );
		Additem( STR_AutoKill,					1, var.Auto[2],				0,	OnOff );
		Additem( STR_AutoShot,					1, var.Auto[1],				0,	OnOff );
		//Additem( STR_PlayerRank,				2, var.Player[1],			0,	Rnk );
		//Additem( STR_NFD,						2, var.Player[5],			0,	OnOff );
	}
	
	Additem( STR_Weapon, 1,		VFolder[ 50 ],				1,	Folder );
	if( VFolder[ 50 ] )
	{
		//Additem( STR_NoSpread,					1, var.Player[2],			0,	OnOff );
		//Additem( STR_FastShot,					1, var.Player[3],			0,	OnOff );
		//Additem( STR_MultiKnife,				1, var.Player[4],			0,	OnOff );
		//Additem( STR_AmmoHack,					1, var.Player[6],			0,	OnOff );
		Additem( STR_NoRecoil,					1, CH_NoRecoil,				0,	OnOff );
		Additem( STR_Spread,					1, CH_Accuracy,				0,	OnOff );

		
		//Additem( STR_WeaponHack, 1,		VFolder[ 51 ],				1,	Folder );
		if( VFolder[ 51 ] )
		{
			Additem( STR_WeaponType,				3, var.WeaponClass[1],				0,	oWeaponType );
			Additem( STR_Rifle,						29, var.Weapon1st[1],				0,	oRifle1 );
			Additem( STR_SMG,						20, var.Weapon1st[2],				0,	oSubMa );
			Additem( STR_Sniper,					12, var.Weapon1st[3],				0,	oSniper );
			Additem( STR_Shotgun,					8, var.Weapon1st[4],				0,	oShotgun );
			Additem( STR_Pistol,					4, var.Pistol[1],					0,	oPistol );
			Additem( STR_Knife,						6, var.Knife[1],					0,	oKnife );
			Additem( STR_Granade,					6, var.Granade[1],					0,	oGranade );
		}
	}


	Additem( STR_Options,			1, VFolder[ 20 ],			1,	Folder );
	if( VFolder[ 20 ] )
	{
		Additem( STR_MoveMenu,		1, Variable[ 1 ],			0,	OnOff );
		Additem( STR_EndGame,		1, Variable[ 2 ],			0,	OnOff );
	}		
}


void PostReset(LPDIRECT3DDEVICE9 pDevice)
{
	if( !BFont )
	{
		D3DXCreateFont( pDevice, 13, 0, 400, 1, 0, 1, 0, 4, 0 | (0<<4), "Verdana", &PFont );
		D3DXCreateLine(pDevice, &g_pLine);
		BFont = TRUE;
	}
}

void InstallPresent( LPDIRECT3DDEVICE9 pDevice )
{

	if( GetAsyncKeyState( VK_INSERT ) &1 )
		menu.ShowMenu =! menu.ShowMenu;

	//PostReset(pDevice);
	 WriteText(420, 2, Yellow, STR_Info);

	//SetAnnounceMessage(STR_Info);

	if( menu.ShowMenu && PFont )
	{
		pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );

		//Menu Top
		DrawBox( menu.matrixPos[ 0 ] - 10, menu.matrixPos[ 1 ] - 22, 190, 20, BTBlack, Black, pDevice );
		DrawBorder( menu.matrixPos[ 0 ] - 10, menu.matrixPos[ 1 ] - 22, 190, 20, 1, Black, pDevice );
		WriteText( menu.matrixPos[ 0 ] + 15 , menu.matrixPos[ 1 ] - 18, White, STR_MenutTittle );

		//Menu Boxy
		DrawBox( menu.matrixPos[ 0 ] - 10, menu.matrixPos[ 1 ], 190, ( ( menu.Current * 15 ) - 5 ), BBlack, Black, pDevice );
		DrawBorder( menu.matrixPos[ 0 ] - 10, menu.matrixPos[ 1 ], 190, ( ( menu.Current * 15 ) - 5 ), 1, Black, pDevice ); 
		DrawBorder( menu.matrixPos[ 0 ] - 10, ( ( menu.matrixPos[ 2 ] + 2 ) + ( menu.MenuSelection * 15 ) ), 190, 13, 1, Cyan, pDevice ); 

		menu.Current = 1;

		if( GetAsyncKeyState( VK_UP ) &1 )
			menu.MenuSelection--;

		if(GetAsyncKeyState( VK_DOWN ) &1 ) 
			menu.MenuSelection++;

		ShowMenu();

		if( menu.MenuSelection >= menu.Current )
			menu.MenuSelection = 1;
		else if( menu.MenuSelection <= 0 )
			menu.MenuSelection = ( menu.Current - 1 );
	}
	
	DWORD Player = *(DWORD*)ResultPlayerBase2;
	if(Player!=0)
	{
		
		ESPHacks(pDevice, PFont, g_pLine);
		//ReplaceWeapon();
	}
	//noRecoil();
	
	if( Variable[ 0 ] )
	{
		if( CH_CRC == 1){CrossHair( pDevice, White );}
		if( CH_CRC == 2){CrossHair( pDevice, Red );}
		if( CH_CRC == 3){CrossHair( pDevice, Green );}
		if( CH_CRC == 4){CrossHair( pDevice, Blue );}
		if( CH_CRC == 5){CrossHair( pDevice, Yellow );}
		if( CH_CRC == 6){CrossHair( pDevice, Pink );}
		if( CH_CRC == 7){CrossHair( pDevice, Orange );}
		if( CH_CRC == 8){CrossHair( pDevice, Black );}
	}


	if( Variable[ 1 ] )
	{
		POINT vec2Cursor;
		GetCursorPos( &vec2Cursor );
		menu.matrixPos[ 0 ] = vec2Cursor.x;
		menu.matrixPos[ 1 ] = vec2Cursor.y;
		menu.matrixPos[ 2 ] = ( vec2Cursor.y - 10 );
	}

	if( Variable[ 2 ] )
	{
		ExitProcess(0);
	}

	if( PFont )PFont->OnLostDevice();
	if( g_pLine )g_pLine->OnLostDevice();
	if( PFont )PFont->OnResetDevice();
	if( g_pLine )g_pLine->OnResetDevice();
}

void PreReset(pD3DdeviceX pDevice)
{
	if (PFont)
	{
		PFont = NULL;
	}
	if (g_pDevice != pDevice)
	{
		g_pDevice = pDevice;
	}
	if (PFont)
	{
		PFont->Release();
		PFont = NULL;
		PFont = FALSE;
	}
	PFont = NULL;
}

void PresetDevice()
{
	PreReset(pDevice);
	DeviceReset = true;
	ReadyDevice = pDevice;
}

bool bCreateFont = true;

void FontReset()
{
	if( PFont )
		PFont->OnLostDevice();
	if( PFont )
		PFont->OnResetDevice();

	if( g_pLine )
		g_pLine->OnLostDevice();
	if( g_pLine )
		g_pLine->OnResetDevice();
}

VOID CrossHair(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->GetViewport( &VPT );
	DWORD ScrX		= VPT.Width / 2; 
    DWORD ScrY		= VPT.Height / 2; 
	D3DRECT R1	= { ScrX - 14, ScrY - 1, ScrX + 13, ScrY};
    pDevice->Clear( 1, &R1, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 255, 20, 255, 20 ), 0,  0 );
	D3DRECT R2	= { ScrX - 1, ScrY - 14, ScrX, ScrY + 13};
    pDevice->Clear( 1, &R2, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 255, 20, 255, 20 ), 0,  0 ); 
}

VOID WriteText( LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text )
{    
    RECT rect;
    SetRect( &rect, x, y, x, y );
    pFont->DrawText( NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color );
}

void Render()
{
	if (DeviceReset == true)
	{
		if (pDevice != ReadyDevice)
		{
			DeviceReset = false;
			PresetDevice();
			
		}
	}
	if (DeviceReset == true)
	{
		if (pFont == NULL)
		{
			PostReset(pDevice);
			
			ReadyDevice = pDevice;
		}
		else
		{
			//Loop
			FontReset();

		}
	}

	InstallPresent(pDevice);

}

__declspec(naked) void MidFunction_EndScene()
{
	__asm
	{
			mov edi, edi
			push ebp
			mov ebp, esp
			mov pDevice, esi
			pushad
			call[Render]
			popad
			jmp[Return_EndScene]
	}
}

BYTE HOOK_PAT_8[] = { "\x8B\xFF\x55\x8B\xEC\xFF\x75\x08\x8B\x01\x6A\x3E\xFF\x90\xF4\x00" };
CHAR HOOK_MAS_8[] = { "xxxxxxxxxxxxxxx?" };

BYTE HOOK_PAT_7[] = { "\x8B\xFF\x55\x8B\xEC\x8B\x55\x08\x8B\x01\x8B\x80\xF4\x00\x00\x00\x52\x6A\x3E\xFF\xD0\x5D\xC2\x04\x00" };
CHAR HOOK_MAS_7[] = { "xxxxxxxxxxxxxxxxxxxxxxxxx" };

BYTE HOOK_PAT_XP[] = {"\x8B\xFF\x55\x8B\xEC\x8B\x55\x08\x8B\x01\x52\x6A \x3E"};
CHAR HOOK_MAS_XP[] = {"xxxxxxxxxxxxx"};


bool CheckWindowsVersion(DWORD dwMajorVersion, DWORD dwMinorVersion, DWORD dwProductType)
{
	OSVERSIONINFOEX VersionInfo;
	ZeroMemory(&VersionInfo, sizeof(OSVERSIONINFOEX));
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
	GetVersionEx((OSVERSIONINFO*) &VersionInfo);
	if (VersionInfo.dwMajorVersion == dwMajorVersion)
	{
		if (VersionInfo.dwMinorVersion == dwMinorVersion)
		{
			if (VersionInfo.wProductType == dwProductType)
			{
				return (TRUE);
			}
		}
	}
	return (FALSE);
}


unsigned __stdcall InstallHook(LPVOID Param)
{
	Module_d3d9 = LoadLibraryA(ed3d9);
	DWORD *vtbl;
	DWORD adr;
	if (CheckWindowsVersion(6, 2, VER_NT_WORKSTATION)) // Windows 8 / 8.1
	{
		GetDevice__EndScene = FindPattern((DWORD) Module_d3d9, 0xFFFFFF, (PBYTE) HOOK_PAT_8, (PCHAR) HOOK_MAS_8);
		adr = FindPattern((DWORD) Module_d3d9, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	}
	else if (CheckWindowsVersion(6, 0, VER_NT_WORKSTATION) || CheckWindowsVersion(6, 1, VER_NT_WORKSTATION)) // Windows 7 / Vista
	{
		GetDevice__EndScene = FindPattern((DWORD) Module_d3d9, 0xFFFFFF, (PBYTE) HOOK_PAT_7, (PCHAR) HOOK_MAS_7);
		adr = FindPattern((DWORD) Module_d3d9, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	}
	else if (CheckWindowsVersion(5, 1, VER_NT_WORKSTATION) || CheckWindowsVersion(5, 2, VER_NT_WORKSTATION)) // Windows XP
	{
		GetDevice__EndScene = FindPattern((DWORD) Module_d3d9, 0xFFFFFF, (PBYTE) HOOK_PAT_XP, (PCHAR) HOOK_MAS_XP);
		adr = FindPattern((DWORD) Module_d3d9, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	}

	memcpy(&vtbl, (void*) (adr + 2), 4);

	Return_EndScene = GetDevice__EndScene + 0x5;
	retMyDIP = vtbl[147] + 0x5;
	GetHP = (tGetHP)0x4F99E0;
	CreateDetour((DWORD) MidFunction_EndScene, (DWORD) GetDevice__EndScene, Detour_Type_0xE9, 5);

	return 1;
}

unsigned __stdcall MaeThreadCall(LPVOID Param)
{
	DWORD dwStartAddress = 0x400000;
	do {
		dwStartAddress = (DWORD)GetModuleHandleA(STR_PointBlank);
	}while(!dwStartAddress);

	if(FindProcessId(STR_fiddler1) || FindProcessId(STR_fiddler2))
	{

	}else{
		_beginthreadex(0, 0, InstallHook, 0, 0, 0);
		_beginthreadex(0, 0, Funtions, 0, 0, 0);
	}
	return 1;
}

long m_lRetVal; 
const char* m_szFileName;         
const char* szSection;
const char* szKey;
const char* szDefaultValue;
LPCSTR ReadKeyString(LPCTSTR, LPCTSTR, LPCTSTR, LPCTSTR);

LPCSTR ReadKeyString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue, LPCTSTR m_szFileName)
{
	char szResult[4096];
	char buffer[4096];
	m_lRetVal = GetPrivateProfileString(szSection, szKey, szDefaultValue, szResult,	sizeof(buffer), m_szFileName);

	return szResult;
}

unsigned __stdcall MaeThread(LPVOID Param)
{
	//SearchPatterns();
	CHAR strtemp[MAX_PATH], strsetting[MAX_PATH], buffer[MAX_PATH];
	LPCSTR tmp = reinterpret_cast<LPCSTR>(getenv(STR_temp));
	GetLongPathNameA(tmp,buffer,MAX_PATH);
	strcpy(strtemp , buffer);
	strcat(strtemp, STR_txt);

	strcat(strsetting, buffer);
	strcat(strsetting, STR_setting);

	LPCSTR user,pass;
	user = ReadKeyString(_T(STR_account), _T(STR_user), _T("?"), strsetting);
	pass = ReadKeyString(_T(STR_account), _T(STR_pass), _T("?"), strsetting);

	std::string sSite = STR_site;
	sSite+= user;
	sSite+= STR_sitep;
	sSite+=	pass;
	sSite+= STR_sitet;
	LPCSTR site = sSite.c_str();

	std::string cHWID1 = STR_site;
	cHWID1+= user;
	cHWID1+= STR_sitep;
	cHWID1+=	pass;
	cHWID1+= STR_hwid1;
	LPCSTR gHWID1 = cHWID1.c_str();


	std::string cHWID2 = STR_site;
	cHWID2+= user;
	cHWID2+= STR_sitep;
	cHWID2+=	pass;
	cHWID2+= STR_hwid2;
	LPCSTR gHWID2 = cHWID2.c_str();

	std::string cHWID3 = STR_site;
	cHWID3+= user;
	cHWID3+= STR_sitep;
	cHWID3+=	pass;
	cHWID3+= STR_hwid3;
	LPCSTR gHWID3 = cHWID3.c_str();


	int HWID1 = GetHWID(gHWID1, "ZRC");
	int HWID2 = GetHWID(gHWID2, "ZRC");
	int HWID3 = GetHWID(gHWID3, "ZRC");

	if(URLDownloadToFileA(NULL , site , strtemp , NULL , NULL ) == S_OK)
	{
		std::string password = "";
		std::ifstream inputFile(strtemp);
		
		if( inputFile.is_open() )
		{
			std::getline( inputFile, password );
			inputFile.close();
			
			if(password == status)
			{
				if(CheckValidHardwareID(HWID1, HWID2, HWID3) == true)
				{
					_beginthreadex(0, 0, MaeThreadCall, 0, 0, 0);
				}else{
					MessageBox(0, STR_error4, "",0);
					ExitProcess(0);
				}
			}else{
				MessageBox(0, STR_error1, "",0);
				ExitProcess(0);
			}
		}else{
				MessageBox(0, STR_error2, "",0);
				ExitProcess(0);
		}
	}else{
		MessageBox(0, STR_error3, "",0);
	}
	return 0;
}

BOOL WINAPI DllMain ( HMODULE hDll, DWORD dwReason, LPVOID lpReserved )
{
	DisableThreadLibraryCalls(hDll);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		//_beginthreadex(0, 0, InstallHook, 0, 0, 0);
		_beginthreadex(0, 0, Funtions, 0, 0, 0);
		//_beginthreadex(0, 0, MaeThread, 0, 0, 0);
		//ShellExecute(0,"Open","http://www.ramleague.net/",0,0,SW_SHOWNORMAL);
	}
	return true;
}
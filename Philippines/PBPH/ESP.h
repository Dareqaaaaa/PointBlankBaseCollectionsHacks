#include "Aimbot.h"
#include "ESPDraw.h"
#pragma warning(disable: 4244)

typedef int (__thiscall * tGetHP)(DWORD CGameCharaManager, double known);
tGetHP GetHP;

void ESPHacks(LPDIRECT3DDEVICE9 pDevice, LPD3DXFONT pFont, LPD3DXLINE S_Line) 
{ 
	unsigned long dwBasePlayer = *(DWORD*)(ResultPlayerBase2); 
	unsigned long dwBaseHealth = *(DWORD*)(ResultHealthBase2); 

	for (int i = 0; i<=16; i++) 
	{ 
		DWORD CGameCharaBase = *(DWORD*)(dwBaseHealth + 0x14 + (i*ResultPlayerSize));
		CPlayers *pPlayer = (CPlayers*)(dwBasePlayer + ResultESPPlayerSize * i + ResultESPPlayerPos);
		CPlayers *pLocal = (CPlayers*)(dwBasePlayer + ResultESPPlayerSize * GetCharaIndex() + ResultESPPlayerPos);

		D3DVECTOR Player, HeadPos;
		D3DVECTOR PlayerScaled, HeadScaled;

		DWORD OnTopX = GetSystemMetrics(0) / 2;
		DWORD OnTopY = GetSystemMetrics(1);

		Player.x = pPlayer->pos.x;
		Player.y = pPlayer->pos.y;
		Player.z = pPlayer->pos.z;
		
		HeadPos.x = pPlayer->pos.x;
		HeadPos.y = 1.5f + pPlayer->pos.y;
		HeadPos.z = pPlayer->pos.z;

		char hphp[100];

		if (ADDXW2S(pDevice,HeadPos,HeadScaled))
		{
			sprintf_s(hphp,"ID: [ %d ]", i);
			WriteText(PlayerScaled.x , PlayerScaled.y, Green, hphp);

			HealthBar(pDevice, (int)PlayerScaled.x-25,(int)PlayerScaled.y, GetHP(CGameCharaBase,0.0));

			if(ESPName)
			{
				//JhemWrite((void*)(ResultESP1),(void*)"\x90\x90",2); 
			}else{
				//JhemWrite((void*)(ResultESP1),(void*)"\x75\x58",2); 
			}

			if(ESPEdge)
			{
				if(var.ESP[1] == 0){DrawBox2D(pPlayer, White, pDevice,S_Line);}
				if(var.ESP[1] == 1){DrawBox2D(pPlayer, Red, pDevice,S_Line);}
				if(var.ESP[1] == 2){DrawBox2D(pPlayer, Green, pDevice,S_Line);}
				if(var.ESP[1] == 3){DrawBox2D(pPlayer, Blue, pDevice,S_Line);}
				if(var.ESP[1] == 4){DrawBox2D(pPlayer, Yellow, pDevice,S_Line);}
				if(var.ESP[1] == 5){DrawBox2D(pPlayer, Pink, pDevice,S_Line);}
				if(var.ESP[1] == 6){DrawBox2D(pPlayer, Orange, pDevice,S_Line);}
				if(var.ESP[1] == 7){DrawBox2D(pPlayer, Black, pDevice,S_Line);}
			}

			if(ESPBox3D)
			{
				if(var.ESP[2] == 0){DrawBox3D(pPlayer, White, pDevice);}
				if(var.ESP[2] == 1){DrawBox3D(pPlayer, Red, pDevice);}
				if(var.ESP[2] == 2){DrawBox3D(pPlayer, Green, pDevice);}
				if(var.ESP[2] == 3){DrawBox3D(pPlayer, Blue, pDevice);}
				if(var.ESP[2] == 4){DrawBox3D(pPlayer, Yellow, pDevice);}
				if(var.ESP[2] == 5){DrawBox3D(pPlayer, Pink, pDevice);}
				if(var.ESP[2] == 6){DrawBox3D(pPlayer, Orange, pDevice);}
				if(var.ESP[2] == 7){DrawBox3D(pPlayer, Black, pDevice);}
			}

			if (ADDXW2S(pDevice,Player,PlayerScaled))
			{
				if (ESPLine)
				{
					if(var.ESP[4] == 0){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, White, S_Line);}
					if(var.ESP[4] == 1){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, Red, S_Line);}
					if(var.ESP[4] == 2){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, Green, S_Line);}
					if(var.ESP[4] == 3){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, Blue, S_Line);}
					if(var.ESP[4] == 4){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, Yellow, S_Line);}
					if(var.ESP[4] == 5){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, Pink, S_Line);}
					if(var.ESP[4] == 6){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, Orange, S_Line);}
					if(var.ESP[4] == 7){DrawLine2(OnTopX, OnTopY, (int)PlayerScaled.x - 1.5, (int)PlayerScaled.y, 1, Black, S_Line);}
				}

				if(ESPHealth)
				{
					//JhemWrite((void*)(ResultESP2),(void*)"\x90\x90\x90\x90\x90\x90",6); 
				}else{
					//JhemWrite((void*)(ResultESP2),(void*)"\x0F\x84\x1F\x01\x00\x00",6); 
					//if(var.ESP[3] == 0){Healthbarnew(pDevice, (int)PlayerScaled.x-25,(int)PlayerScaled.y, pHealth->CurHP);}
					//if(var.ESP[3] == 1){DrawString((int)PlayerScaled.x-2.5,(int)PlayerScaled.y,Green,pFont,"HP[%0.f] ",pHealth->CurHP);}
				}
			}
		}
	} 
}
#pragma warning(disable: 4244)
#pragma warning(disable: 4309)
#pragma warning(disable: 4305)

bool Aim_true = false;
void Thread_Aimbot()
{
	DWORD InputMouse = (DWORD)GetModuleHandleA("i3InputDx.dll");
	DWORD InSnce = (DWORD) GetModuleHandleA("i3SceneDx.dll");
	if(Aim_true == false)
	{
		//Hook Aim & Mouse
		DetourCreate((PBYTE) InputMouse + ResultDeltaX,(PBYTE)Aim_DeltaX, 0x5);
		DetourCreate((PBYTE) InputMouse + ResultDeltaY,(PBYTE)Aim_DeltaY, 0x5);
		DetourCreate((PBYTE) InSnce + ResultSetEnd, (PBYTE)i3CollideeEnd, 0x5); //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
		Aim_true = true;
	}
}

void DoHook()
{
	DWORD Player = *(DWORD*)ResultPlayerBase2;
	if(Player != 0)
	{
		DWORD IntMse = (DWORD)GetModuleHandleA("i3InputDx.dll");
		DetourCreate((PBYTE) IntMse + ResultAutoShot,(PBYTE)MouseHook, 7);
	}
}

void DoAimBot()
{
	unsigned long dwBase	= *(DWORD*)(ResultPlayerBase2);;
	int ScreenCenterX = GetSystemMetrics(0) / 2;
	int ScreenCenterY = GetSystemMetrics(1) / 2;
		
	if(var.Aimbot[2] == 1)
	{
		if(AimHead)
		{
			int AimSlot = GetPriorityTarget();
			if(AimSlot != -1)
			{
				CPlayers *pPlayer = (CPlayers*)(dwBase + ResultESPPlayerSize * AimSlot + ResultESPPlayerPos);
				D3DXVECTOR3 OnWorld=pPlayer->pos;
				if(pPlayer!=NULL){
					int x = ( GetSystemMetrics( 0 ) / 2);
					int y = ( GetSystemMetrics( 1 ) / 2);
					AimEnable = true;

					int LocalX;
					int LocalY;

					switch(AimBody)
					{
					case 0:
						LocalX = OnWorld.x;
						LocalY = OnWorld.y + 1.5f;
					break;
					case 1:
						LocalX = OnWorld.x;
						LocalY = OnWorld.y + 1.0f;
					break;
					}

					if(LocalX == ScreenCenterX && LocalY == ScreenCenterY)
					{ 
						MouseDeltaX = 0;
						MouseDeltaY = 0;
					}else{
						MouseDeltaX = LocalX - ScreenCenterX;
						MouseDeltaY = LocalY - ScreenCenterY;
					}
				}else{
					AimEnable = false;
				}
			}else{
				AimEnable = false;
			}
		}else{
			AimEnable = false;
		}
	}

	if(var.AimKey[1] == 0) //LButtom
	{
		if(GetAsyncKeyState(VK_LBUTTON)){AimHead = true;}else{AimHead = false;}
	}

	if(var.AimKey[1] == 1) //LButtom
	{
		if(GetAsyncKeyState(VK_MENU)){AimHead = true;}else{AimHead = false;}
	}

	if(var.AimKey[1] == 2) //LButtom
	{
		if(GetAsyncKeyState(VK_CONTROL)){AimHead = true;}else{AimHead = false;}
	}
}

void AimBot()
{
	DWORD g_pPlayer = *(DWORD*)ResultPlayerBase2; 
	if(g_pPlayer != 0x0000)
	{
		int AimSlot = GetPriorityTarget();
		if(AimSlot != -1)
		{
			CPlayers *pPlayer = (CPlayers*)(g_pPlayer + ResultESPPlayerSize * AimSlot + ResultESPPlayerPos);
			D3DXVECTOR3 OnWorld;
			int BoneIndexSelector = 0;
			switch(SAimBody)
			{
			case 0:
				OnWorld.x=pPlayer->pos.x;
				OnWorld.x=1.5f+pPlayer->pos.y;
				OnWorld.x=pPlayer->pos.z;
				break;
			case 1:
				OnWorld.x=pPlayer->pos.x;
				OnWorld.x=1.0f+pPlayer->pos.y;
				OnWorld.x=pPlayer->pos.z;
				break;
			}
			if (pPlayer!=NULL)
			{
				BulletEnable = true;
				fX = OnWorld.x;
				fY = OnWorld.y + 0.1f;
				fZ = OnWorld.z;
				var.Aimbot[3] == 0;
				var.Aimbot[4] == 0;
			}else BulletEnable = false;
		}else BulletEnable = false;
	}
}

void HeadAim()
{
	DWORD g_pPlayer  = *(DWORD*)ResultPlayerBase2; 
	if(g_pPlayer != 0x0000)
	{
		int AimSlot = GetPriorityTarget();
		if(AimSlot != -1)
		{
			CPlayers *pPlayer = (CPlayers*)(g_pPlayer + ResultESPPlayerSize * AimSlot + ResultESPPlayerPos);
			if (pPlayer!=NULL)
			{
				BulletEnable = true;
				fX = pPlayer->pos.x;
				fY = 1.5f + pPlayer->pos.y;
				fZ = pPlayer->pos.z;
				var.Aimbot[1] == 0;
				var.Aimbot[4] == 0;
			}else BulletEnable = false;
		}else BulletEnable = false;
    }
}

void BodyAim()
{
	DWORD g_pPlayer  = *(DWORD*)ResultPlayerBase2; 
	if(g_pPlayer != 0x0000)
	{
		int AimSlot = GetPriorityTarget();
		if(AimSlot != -1)
		{
			CPlayers *pPlayer = (CPlayers*)(g_pPlayer + ResultESPPlayerSize * AimSlot + ResultESPPlayerPos);
			if (pPlayer!=NULL)
			{
				BulletEnable = true;
				fX = pPlayer->pos.x;
				fY = 1.0f + pPlayer->pos.y;
				fZ = pPlayer->pos.z;
				var.Aimbot[1] == 0;
				var.Aimbot[3] == 0;
			}else BulletEnable = false;
		}else BulletEnable = false;
    }
}

void DoAimBullet()
{
	if(var.Aimbot[1])
	{
		AimBot();
		if(var.Aimbot[1] == 0 && !var.Aimbot[1]){BulletEnable = false;}
	}

	if(var.Aimbot[3])
	{
		HeadAim();
		if(var.Aimbot[3] == 0 && !var.Aimbot[3]){BulletEnable = false;}
	}

	if(var.Aimbot[4])
	{
		BodyAim();
		if(var.Aimbot[4] == 0 && !var.Aimbot[4]){BulletEnable = false;}
	}
	if(var.Aimbot[2] == 0 && !var.Aimbot[2]){AimEnable = false;}
}

void AutoShot()
{
	if(var.Auto[1]== 1){
		if(GetPlayerTarget(GetCharaIndex()) > 0)
				Shot = true;
			else Shot = false;
	}else Shot = false;
}

void NormalAimBot(LPDIRECT3DDEVICE9 pDevice)
{
	DWORD g_pPlayer  = *(DWORD*)ResultPlayerBase2; 
	if(g_pPlayer != 0x0000)
	{
		D3DVECTOR Scaled, WScaled;
		int Priority = GetPriorityTarget();
		if(Priority != -1)
		{
			CPlayers *pPlayer = (CPlayers*)(g_pPlayer + ResultESPPlayerSize * Priority + ResultESPPlayerPos);
			if (pPlayer!=NULL)
			{
				Scaled.x = pPlayer->pos.x;
				Scaled.y = pPlayer->pos.y;
				Scaled.z = pPlayer->pos.z;
				if (ADDXW2S(pDevice,Scaled,WScaled))
				{
					EndEnable = true;
					fX = WScaled.x;
					fY = WScaled.y;
					fZ = WScaled.z;
					WriteText(WScaled.x, WScaled.y, Yellow, "Target");
					DetourCreate((PBYTE)dwEnd, (PBYTE)EndAim, 0x9);
				}
			}
		}else{
			EndEnable = false;
			DetourCreate((PBYTE)dwEnd, (PBYTE)EndAim, 0x9);
		}
	}else{
        EndEnable = false;
		DetourCreate((PBYTE)dwEnd, (PBYTE)EndAim, 0x9);
    }
}


VOID DoHacks()
{
	Thread_Aimbot();
	DoHook();
	DoAimBot();
	DoAimBullet();
	AutoShot();
}
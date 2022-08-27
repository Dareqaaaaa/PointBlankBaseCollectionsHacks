#include "stdafx.h"

FunctionT* Function = new FunctionT();

VOID FunctionT::CallESP(LPDIRECT3DDEVICE9 pDevice)
{	
	DWORD pChara = GetCharacter(0);

	auto pPlayer = Utils->Read<DWORD>(Utils->modBase.dwBase + ADR_GAMECONTEXT);

	BYTE MyIndex = Utils->Read<int>(pPlayer + OFS_TEAM);
	printf("%d\n", MyIndex);
	D3DXVECTOR3 pPosFoot = GetPos(MyIndex);

	for (int i = 0; i < 16; i++)
	{
		//if (i == MyIndex)
		//	continue;

		if (MyIndex % 2 == i % 2)
			continue;

		if (!IsAlive(i))
			continue;
		
		D3DXVECTOR3 vPosHead = GetPos(i), vScreenHead;

		wchar_t pbuffer[100];
		swprintf(pbuffer, 100, L"[%i] - [%0.2f] [%0.2f] [%0.2f]", i, vPosHead.x, vPosHead.y, vPosHead.z);
		DirectX->WriteText(100, 100 + (20 * i), pbuffer, D3DCOLOR_ARGB(255, 255, 255, 255));

		if (W2S(pDevice, D3DXVECTOR3(vPosHead.x, vPosHead.y + 1.0f, vPosHead.z), vScreenHead))
		{
			if (Utils->esp.line)
			{
				DWORD OnTopX = GetSystemMetrics(0) / 2;
				DWORD OnTopY = GetSystemMetrics(1);
				DirectX->DrawLine(vScreenHead.x, vScreenHead.y, OnTopX, OnTopY - 10, 1.0f, D3DCOLOR_ARGB(255, 255, 000, 000), false, 1.0f, 0xFFFFF);
			}

			D3DXVECTOR3 vPosFoot = GetPos(i), vScreenFoot;
			if (W2S(pDevice, D3DXVECTOR3(vPosFoot.x, vPosFoot.y, vPosFoot.z), vScreenFoot))
			{
				if (Utils->esp.distance)
				{
					float distance = CalcDistance(GetPos(MyIndex), vPosFoot) / 2;
					wchar_t buffer[100];
					swprintf(buffer, 100, L"[%0.2f]", distance);
					DirectX->WriteText(vScreenFoot.x, vScreenFoot.y, buffer, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				if (Utils->esp.box)
				{
					D3DXVECTOR3 Box = vScreenHead - vScreenFoot;
					if (Box.y < 0)
						Box.y *= -1;

					int BoxWidth = (int)Box.y / 2;
					int DrawX = (int)vScreenHead.x - (BoxWidth / 2);
					int DrawY = (int)vScreenHead.y;
					DirectX->DrawRect(DrawX, DrawY, BoxWidth, (int)Box.y, 1.0f, D3DCOLOR_ARGB(255, 255, 000, 000), false, false, 1.0f, 0xFFFFF);
				}
			}
		}
	}
}

VOID FunctionT::CallMemory()
{
	auto pBattle = Utils->Read<DWORD>(Utils->modBase.dwBase + ADR_GAMECONTEXT);
	if (pBattle)
	{
		DWORD On = 0x3F4CE1C6, Off = 0x00000000;
		DWORD dwFastSwitch = (0xC + OFS_TICKET);
		DWORD dwFastReload = (0x10 + OFS_TICKET);
		DWORD dwSpeedRun = (0x24 + OFS_TICKET);
		DWORD dwFastRespawn = (0x30 + OFS_TICKET);
		DWORD dwNoFallDmage = (0x34 + OFS_TICKET);

		if (Utils->memory.fastreload)
		{
			if (Utils->Read<DWORD>(pBattle + dwFastReload + GetMyIndex(pBattle) * OFS_TICKETSIZE) != On)
			{
				Utils->Write<DWORD>(pBattle + dwFastReload + GetMyIndex(pBattle) * OFS_TICKETSIZE, On);
			}
		}
		else {
			if (Utils->Read<DWORD>(pBattle + dwFastReload + GetMyIndex(pBattle) * OFS_TICKETSIZE) == On)
				Utils->Write<DWORD>(pBattle + dwFastReload + GetMyIndex(pBattle) * OFS_TICKETSIZE, Off);
		}

		if (Utils->memory.fastswitch)
		{
			if (Utils->Read<DWORD>(pBattle + dwFastSwitch + GetMyIndex(pBattle) * OFS_TICKETSIZE) != On)
			{
				Utils->Write<DWORD>(pBattle + dwFastSwitch + GetMyIndex(pBattle) * OFS_TICKETSIZE, On);
			}
		}
		else {
			if (Utils->Read<DWORD>(pBattle + dwFastSwitch + GetMyIndex(pBattle) * OFS_TICKETSIZE) == On)
				Utils->Write<DWORD>(pBattle + dwFastSwitch + GetMyIndex(pBattle) * OFS_TICKETSIZE, Off);
		}

		if (Utils->memory.fastrespawn)
		{
			if (Utils->Read<DWORD>(pBattle + dwFastRespawn + GetMyIndex(pBattle) * OFS_TICKETSIZE) != On)
			{
				Utils->Write<DWORD>(pBattle + dwFastRespawn + GetMyIndex(pBattle) * OFS_TICKETSIZE, On);
			}
		}
		else {
			if (Utils->Read<DWORD>(pBattle + dwFastRespawn + GetMyIndex(pBattle) * OFS_TICKETSIZE) == On)
				Utils->Write<DWORD>(pBattle + dwFastRespawn + GetMyIndex(pBattle) * OFS_TICKETSIZE, Off);
		}

		if (Utils->memory.nofalldamage)
		{
			if (Utils->Read<DWORD>(pBattle + dwNoFallDmage + GetMyIndex(pBattle) * OFS_TICKETSIZE) != 0x454CE1C6)
			{
				Utils->Write<DWORD>(pBattle + dwNoFallDmage + GetMyIndex(pBattle) * OFS_TICKETSIZE, 0x454CE1C6);
			}
		}
		else {
			if (Utils->Read<DWORD>(pBattle + dwNoFallDmage + GetMyIndex(pBattle) * OFS_TICKETSIZE) == 0x454CE1C6)
				Utils->Write<DWORD>(pBattle + dwNoFallDmage + GetMyIndex(pBattle) * OFS_TICKETSIZE, 0xB7A7C5AC);
		}

		if (Utils->memory.speedrun)
		{
			if (Utils->Read<DWORD>(pBattle + dwSpeedRun + GetMyIndex(pBattle) * OFS_TICKETSIZE) != 0x3EBAD1C6)
			{
				Utils->Write<DWORD>(pBattle + dwSpeedRun + GetMyIndex(pBattle) * OFS_TICKETSIZE, 0x3EBAD1C6);
			}
		}
		else {
			if (Utils->Read<DWORD>(pBattle + dwSpeedRun + GetMyIndex(pBattle) * OFS_TICKETSIZE) == 0x3EBAD1C6)
				Utils->Write<DWORD>(pBattle + dwSpeedRun + GetMyIndex(pBattle) * OFS_TICKETSIZE, 0);
		}
	}
}
DWORD FunctionT::GetCharacter(int i)
{
	DWORD pChara = Utils->Read<DWORD>(Utils->modBase.dwBase + ADR_CHARACTERPOINTER);
	if (!pChara) return 0;

	return Utils->Read<DWORD>(pChara + 0x14 + (OFS_CHARACTERSIZE * i));
}

DWORD FunctionT::GetPlayer()
{
	return Utils->Read<DWORD>(Utils->modBase.dwBase + ADR_GAMECONTEXT);
}

int FunctionT::GetMyIndex(DWORD pPlayer)
{
	return Utils->Read<int>(pPlayer + OFS_TEAM);
}

BOOL FunctionT::IsAlive(int i)
{
	DWORD pChara = Utils->Read<DWORD>(Utils->modBase.dwBase + ADR_CHARACTERPOINTER);
	if (!pChara) return false;

	auto pState = Utils->Read<DWORD>(pChara + 0x18 + (OFS_CHARACTERSIZE * i));
	if (pState == 2)
		return true;

	return false;
}

int FunctionT::GetTeam(int MyTeam)
{
	for (int i = 0; i < 16; i += 2)
		if (i == MyTeam) return 2;
	for (int i = 1; i < 16; i += 2)
		if (i == MyTeam) return 1;
	return -1;
}

D3DXVECTOR3 FunctionT::GetPos(int i)
{
	auto ppPlayer = Utils->Read<DWORD>(GetCharacter(i) + 0xD0);
	auto pppPlayer = Utils->Read<DWORD>(ppPlayer + 0x50);
	return Utils->Read<D3DXVECTOR3>(pppPlayer + 0x40);
}

BOOL FunctionT::W2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
{
	DWORD pRenderContext = Utils->Read<DWORD>(Utils->modi3GfxDx.dwBase + ADR_RENDERCONTEXT);
	if (!pRenderContext)
		return FALSE;

	D3DXMATRIX view = Utils->Read<D3DXMATRIX>(pRenderContext + OFS_VIEWMATRIX);
	D3DXMATRIX projection = Utils->Read<D3DXMATRIX>(pRenderContext + OFS_PROJECTMATRIX);
	D3DXMATRIX world = Utils->Read<D3DXMATRIX>(pRenderContext + OFS_WORLDMATRIX);

	D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z), vScreen;
	D3DVIEWPORT9 Viewport;
	pDevice->GetViewport(&Viewport);

	Viewport.X = Viewport.Y = 0;
	Viewport.MinZ = 0;
	Viewport.MaxZ = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &projection, &view, &world);

	if (vScreen.z < 1.0f)
	{
		PlayerScaled.x = vScreen.x;
		PlayerScaled.y = vScreen.y;
		PlayerScaled.z = vScreen.z;
		return true;
	}
	return false;
}

float FunctionT::CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}

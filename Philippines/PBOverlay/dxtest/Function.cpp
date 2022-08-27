#include "stdafx.h"

FunctionT* Function = new FunctionT();

VOID FunctionT::CallESP(LPDIRECT3DDEVICE9 pDevice)
{
	
	auto pGame = *(DWORD*)Globals->Base.Address + ADR_CHARACTERPOINTER;
	if (!pGame)
		return;

	int health = GetUserHP(getMyIndex());
	wchar_t fHP[100];
	swprintf_s(fHP, L"HP: %d", health);
	DirectX->DrawString(150, 115, fHP, D3DCOLOR_ARGB(255, 000, 255, 000), Globals->DebugSettings.DrawTextOutline, Globals->DebugSettings.TextOutlineColor);

}
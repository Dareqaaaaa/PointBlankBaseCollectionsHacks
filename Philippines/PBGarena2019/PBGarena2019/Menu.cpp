#include "stdafx.h"

MenuT * Menu = new MenuT();

void MenuT::CreateMenu(LPDIRECT3DDEVICE9 pDevice)
{
	const char *opt_Auto[] = { "[AUTO]" };
	const char *opt_OnOff[] = { "[OFF]", "[ON]" };
	const char *opt_BoneKey[] = { "[SHIFT]", "[LBUTTON]", "[AUTO]" };
	const char *opt_BoneTarget[] = { "[Head]", "[Neck]", "[Body]" };
	const char *opt_BoneOption[] = { "[Recommended]", "[Normal]", "[Big]" };

	if (GetAsyncKeyState(VK_INSERT) & 1)
		Show = !Show;

	if (Show)
	{
		if (GetAsyncKeyState(VK_UP) & 1)
			MenuSelection--;

		if (GetAsyncKeyState(VK_DOWN) & 1)
			MenuSelection++;

		DrawBox(pDevice, 20, 11, 190, 20, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
		cWriteText(110, 14, Green, "POINTBLANK RAML");
		DrawBox(pDevice, 20, 34, 190, (Current * 15), 1, D3DCOLOR_ARGB(220, 50, 50, 50), D3DCOLOR_ARGB(220, 5, 5, 5));

		DrawBorder(pDevice, 20, 26 + (MenuSelection * 15), 190, 15, 1, White);

		DrawBox(pDevice, 20, 35 + (Current * 15), 190, 18, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
		cWriteText(110, 38 + (Current * 15), Green, "WWW.RAMLEAGUE.NET");

		Current = 1;

		Kategorie(pDevice, "[Aimbot]");
		AddItem(pDevice, "Enable Aimbot", Utils->aimbot.main, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Smooth", Utils->aimbot.smooth, opt_BoneOption, 2);
		AddItem(pDevice, "Aimbot Fov", Utils->aimbot.fov, opt_BoneOption, 2);
		AddItem(pDevice, "Aimbot Draw", Utils->aimbot.draw, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Target", Utils->aimbot.target, opt_BoneTarget, 2);
		AddItem(pDevice, "Aimbot Key", Utils->aimbot.key, opt_BoneKey, 2);

		Kategorie(pDevice, "[AimBullet]");
		AddItem(pDevice, "Enable AimBullet", Utils->aimbullet.main, opt_OnOff, 1);
		AddItem(pDevice, "AimBullet Draw", Utils->aimbullet.draw, opt_OnOff, 1);
		AddItem(pDevice, "AimBullet Target", Utils->aimbullet.target, opt_BoneTarget, 2);

		Kategorie(pDevice, "[ESP]");
		AddItem(pDevice, "ESP Box", Utils->esp.espbox, opt_OnOff, 1);
		AddItem(pDevice, "ESP Line", Utils->esp.espline, opt_OnOff, 1);
		AddItem(pDevice, "ESP Skeleton", Utils->esp.espbone, opt_OnOff, 1);
		AddItem(pDevice, "ESP Distance", Utils->esp.espdistance, opt_OnOff, 1);

		Kategorie(pDevice, "[Memory]");
		AddItem(pDevice, "Ghost Mode", Utils->memory.ghostmode, opt_OnOff, 1);
		AddItem(pDevice, "Fast Shoot", Utils->memory.fastshot, opt_OnOff, 1);
		AddItem(pDevice, "Fast Switch", Utils->memory.fastswitch, opt_OnOff, 1);
		AddItem(pDevice, "Fast Reload", Utils->memory.fastreload, opt_OnOff, 1);
		AddItem(pDevice, "Fast Knife/Reload", Utils->memory.fastreloadknife, opt_OnOff, 1);
		AddItem(pDevice, "Rapid Fire", Utils->memory.rapidfire, opt_OnOff, 1);
		AddItem(pDevice, "Fast Respawn", Utils->memory.fastrespawn, opt_OnOff, 1);
		AddItem(pDevice, "OPK [Home]", Utils->memory.opk, opt_OnOff, 1);
		AddItem(pDevice, "No Recoil", Utils->memory.norecoil, opt_Auto, 0);
		AddItem(pDevice, "No Spread", Utils->memory.nospread, opt_Auto, 0);

		if (MenuSelection >= Current)
			MenuSelection = 1;

		if (MenuSelection < 1)
			MenuSelection = Current;
	}
}

int MenuT::CheckTabs(int x, int y, int w, int h)
{
	GetCursorPos(&cPos);
	ScreenToClient(GetForegroundWindow(), &cPos);
	if (cPos.x > x && cPos.x < x + w && cPos.y > y && cPos.y < y + h)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 1)
		{
			return 1;
		}
		return 2;
	}
	return 0;
}

void MenuT::DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

void MenuT::FillRGB(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void MenuT::DrawBorder(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor)
{
	FillRGB(pDevice, x, (y + h - px), w, px, BorderColor);
	FillRGB(pDevice, x, y, px, h, BorderColor);
	FillRGB(pDevice, x, y, w, px, BorderColor);
	FillRGB(pDevice, x + w - px, y, px, h, BorderColor);
}

void MenuT::DrawBox(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, DWORD Fill, DWORD Border)
{
	FillRGB(pDevice, x, y, w, h, Fill);
	DrawBorder(pDevice, x, y, w, h, px, Border);
}

void MenuT::WriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void MenuT::lWriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_RIGHT, color);
}

void MenuT::cWriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_CENTER, color);
}

void MenuT::Kategorie(LPDIRECT3DDEVICE9 pDevice, const char *text)
{
	if (Show)
	{
		int Check = CheckTabs(PosX, PosY + (Current * 15), 190, 10);
		DWORD ColorText;

		ColorText = KategorieFarbe;

		if (Check == 2)
			ColorText = ItemCurrent;

		if (MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText(PosX - 5, PosY + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 175, PosY + (Current * 15) - 1, ColorText, "[-]");
		Current++;
	}
}

void MenuT::AddItem(LPDIRECT3DDEVICE9 pDevice, const char *text, int &var, const char **opt, int MaxValue)
{
	if (Show)
	{
		int Check = CheckTabs(PosX, PosY + (Current * 15), 190, 10);
		DWORD ColorText;

		if (var)
		{
			DrawBox(pDevice, PosX, PosY + (Current * 15) + 2, 5, 5, 1, Green, D3DCOLOR_ARGB(220, 5, 5, 5));
			ColorText = ItemColorOn;
		}
		if (var == 0)
		{
			DrawBox(pDevice, PosX, PosY + (Current * 15) + 2, 5, 5, 1, Red, D3DCOLOR_ARGB(220, 5, 5, 5));
			ColorText = ItemColorOff;
		}

		if (Check == 1)
		{
			var++;
			if (var > MaxValue)
				var = 0;
		}

		if (Check == 2)
			ColorText = ItemCurrent;

		if (MenuSelection == Current)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				var++;
				if (var > MaxValue)
					var = 0;
			}
			else if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				var--;
				if (var < 0)
					var = MaxValue;
			}
		}

		if (MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText(PosX + 8, PosY + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, opt[var]);
		Current++;
	}
}
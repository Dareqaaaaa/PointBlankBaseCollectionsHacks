#include "stdafx.h"
#include "utils.h"
#include "menu.h"

menu pMenu;

menu::menu()
{

}


menu::~menu()
{
}


void menu::Init()
{
	if (!Create)
	{
		MenuSelection = 0;
		Current = 1;
		PosX = 30;
		PosY = 27;
		Show = 1;
		Create = false;
	}
}

BOOL menu::IsKeyPressed(int Key, DWORD dwTimeOut)
{
	if (HIWORD(GetKeyState(Key)))
	{
		if (!kPressingKey[Key].bPressed || (kPressingKey[Key].dwStartTime && (kPressingKey[Key].dwStartTime + dwTimeOut) <= GetTickCount()))
		{
			kPressingKey[Key].bPressed = TRUE;
			if (dwTimeOut > NULL)
				kPressingKey[Key].dwStartTime = GetTickCount();
			return TRUE;
		}
	}
	else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;
}


void menu::CreateMenu(LPDIRECT3DDEVICE9 pDevice)
{
	const char *opt_Auto[] = { "[AUTO]" };
	const char *opt_OnOff[] = { "[OFF]", "[ON]" };
	const char *opt_BoneKey[] = { "[SHIFT]", "[LBUTTON]", "[AUTO]" };
	const char *opt_BoneTarget[] = { "[Head]", "[Neck]", "[Body]" };
	const char *opt_BoneOption[] = { "[Recommended]", "[Normal]", "[Big]" };

	if (IsKeyPressed(VK_INSERT, 0) & 1)
		Show = !Show;

	if (Show)
	{
		if (IsKeyPressed(VK_UP, 0) & 1)
			MenuSelection--;

		if (IsKeyPressed(VK_DOWN, 0) & 1)
			MenuSelection++;

		Current = 1;

		Kategorie(pDevice, "[Aimbot]");
		AddItem(pDevice, "Enable Aimbot", pUtils.aimbot.main, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Smooth", pUtils.aimbot.smooth, opt_BoneOption, 2);
		AddItem(pDevice, "Aimbot Fov", pUtils.aimbot.fov, opt_BoneOption, 2);
		AddItem(pDevice, "Aimbot Draw", pUtils.aimbot.draw, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Target", pUtils.aimbot.target, opt_BoneTarget, 2);
		AddItem(pDevice, "Aimbot Key", pUtils.aimbot.key, opt_BoneKey, 2);

		Kategorie(pDevice, "[AimBullet]");
		AddItem(pDevice, "Enable AimBullet", pUtils.aimbullet.main, opt_OnOff, 1);
		AddItem(pDevice, "AimBullet Draw", pUtils.aimbullet.draw, opt_OnOff, 1);
		AddItem(pDevice, "AimBullet Target", pUtils.aimbullet.target, opt_BoneTarget, 2);

		Kategorie(pDevice, "[ESP]");
		AddItem(pDevice, "ESP Box", pUtils.esp.box, opt_OnOff, 1);
		AddItem(pDevice, "ESP Line", pUtils.esp.line, opt_OnOff, 1);
		AddItem(pDevice, "ESP Skeleton", pUtils.esp.bone, opt_OnOff, 1);
		AddItem(pDevice, "ESP Distance", pUtils.esp.distace, opt_OnOff, 1);

		Kategorie(pDevice, "[Memory]");
		AddItem(pDevice, "No Recoil", pUtils.memory.norecoil, opt_OnOff, 1);
		AddItem(pDevice, "Fast Shoot (EZ DC)", pUtils.memory.fastshot, opt_OnOff, 1);
		AddItem(pDevice, "Fast Switch", pUtils.memory.fastswitch, opt_OnOff, 1);
		AddItem(pDevice, "Fast Reload", pUtils.memory.fastreload, opt_OnOff, 1);
		AddItem(pDevice, "Fast Knife/Reload (EZ DC)", pUtils.memory.fastreloadknife, opt_OnOff, 1);
		AddItem(pDevice, "Rapid Fire (EZ DC)", pUtils.memory.rapidfire, opt_OnOff, 1);
		AddItem(pDevice, "Fast Respawn", pUtils.memory.fastrespawn, opt_OnOff, 1);
		AddItem(pDevice, "No Fall Damage", pUtils.memory.nofalldamage, opt_OnOff, 1);
		AddItem(pDevice, "Speed++ (EZ DC)", pUtils.memory.speedhack, opt_OnOff, 1);

		if (MenuSelection >= Current)
			MenuSelection = 1;

		if (MenuSelection < 1)
			MenuSelection = Current;

		DrawBorder(pDevice, 20, 26 + (MenuSelection * 15), 190, 15, 1, D3DCOLOR_ARGB(255, 255, 255, 255));

		cWriteText(110, 14, D3DCOLOR_ARGB(255, 000, 255, 000), "POINTBLANK RAML");
		DrawBox(pDevice, 20, 11, 190, 20, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
		DrawBox(pDevice, 20, 34, 190, (Current * 15), 1, D3DCOLOR_ARGB(220, 50, 50, 50), D3DCOLOR_ARGB(220, 5, 5, 5));

		cWriteText(110, 38 + (Current * 15), D3DCOLOR_ARGB(255, 000, 255, 000), "WWW.RAMLEAGUE.NET");
		DrawBox(pDevice, 20, 35 + (Current * 15), 190, 18, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
	}
}

int menu::CheckTabs(int x, int y, int w, int h)
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

void menu::DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, float width, DWORD color)
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

void menu::FillRGB(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DXVECTOR2 vLine[2];

	pLine->SetWidth(w);
	pLine->SetAntialias(false);
	pLine->SetGLLines(false);

	vLine[0].x = x + w / 2;
	vLine[0].y = y;
	vLine[1].x = x + w / 2;
	vLine[1].y = y + h;

	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

void menu::DrawBorder(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor)
{
	FillRGB(pDevice, x, (y + h - px), w, px, BorderColor);
	FillRGB(pDevice, x, y, px, h, BorderColor);
	FillRGB(pDevice, x, y, w, px, BorderColor);
	FillRGB(pDevice, x + w - px, y, px, h, BorderColor);
}

void menu::DrawBox(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, DWORD Fill, DWORD Border)
{
	FillRGB(pDevice, x, y, w, h, Fill);
	DrawBorder(pDevice, x, y, w, h, px, Border);
}

void menu::WriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void menu::lWriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_RIGHT, color);
}

void menu::cWriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_CENTER, color);
}

void menu::Kategorie(LPDIRECT3DDEVICE9 pDevice, const char *text)
{
	if (Show)
	{
		int Check = CheckTabs(PosX, PosY + (Current * 15), 190, 10);
		DWORD ColorText;

		ColorText = D3DCOLOR_ARGB(255, 255, 000, 000);

		if (Check == 2)
			ColorText = D3DCOLOR_ARGB(255, 255, 000, 000);

		if (MenuSelection == Current)
			ColorText = D3DCOLOR_ARGB(255, 255, 000, 000);

		WriteText(PosX - 5, PosY + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 175, PosY + (Current * 15) - 1, ColorText, "[-]");
		Current++;
	}
}

void menu::AddItem(LPDIRECT3DDEVICE9 pDevice, const char *text, int &var, const char **opt, int MaxValue)
{
	if (Show)
	{
		int Check = CheckTabs(PosX, PosY + (Current * 15), 190, 10);
		DWORD ColorText;

		if (var)
		{
			DrawBox(pDevice, PosX, PosY + (Current * 15) + 2, 5, 5, 1, D3DCOLOR_ARGB(255, 000, 255, 000), D3DCOLOR_ARGB(220, 5, 5, 5));
			ColorText = D3DCOLOR_ARGB(255, 255, 255, 255);
		}
		if (var == 0)
		{
			DrawBox(pDevice, PosX, PosY + (Current * 15) + 2, 5, 5, 1, D3DCOLOR_ARGB(255, 255, 000, 000), D3DCOLOR_ARGB(220, 5, 5, 5));
			ColorText = D3DCOLOR_ARGB(255, 200, 200, 200);
		}

		if (Check == 1)
		{
			var++;
			if (var > MaxValue)
				var = 0;
		}

		if (Check == 2)
			ColorText = D3DCOLOR_ARGB(255, 255, 000, 000);

		if (MenuSelection == Current)
		{
			if (IsKeyPressed(VK_RIGHT, 0) & 1)
			{
				var++;
				if (var > MaxValue)
					var = 0;
			}
			else if (IsKeyPressed(VK_LEFT, 0) & 1)
			{
				var--;
				if (var < 0)
					var = MaxValue;
			}
		}

		if (MenuSelection == Current)
			ColorText = D3DCOLOR_ARGB(255, 255, 000, 000);

		WriteText(PosX + 8, PosY + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, opt[var]);
		Current++;
	}
}
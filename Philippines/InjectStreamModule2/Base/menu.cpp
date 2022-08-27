#include "stdafx.h"
#include "utils.h"
#include "menu.h"
#include "Xor.h"

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

void menu::ResetFont(LPDIRECT3DDEVICE9 pDevice)
{
	pFont->OnLostDevice();
	pLine->OnLostDevice();

	pFont->OnResetDevice();
	pLine->OnResetDevice();
}

void menu::CreateMenu(LPDIRECT3DDEVICE9 pDevice)
{
	
	enum {
		opt_Auto = 0,
		opt_OnOff = 1,
		opt_BoneKey = 2,
		opt_BoneTarget = 3,
		opt_BoneOption = 4,
		opt_EspTeam = 5,
		opt_SpeedHack = 8,
		opt_PanicKey = 6,
		opt_CloseMenu = 7
	};
	
	if (IsKeyPressed(VK_INSERT, 0) & 1)
		Show = !Show;

	if (IsKeyPressed(VK_DELETE, 0) & 1)
		ExitProcess(1);

	if (Show)
	{
		if (IsKeyPressed(VK_UP, 0))
			MenuSelection--;

		if (IsKeyPressed(VK_DOWN, 0))
			MenuSelection++;

		if (MenuSelection >= Current)
			MenuSelection = 1;

		if (MenuSelection < 1)
			MenuSelection = Current;

		DrawBox(pDevice, 20, 11, 190, 20, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
		DrawBox(pDevice, 20, 34, 190, (Current * 15), 1, D3DCOLOR_ARGB(220, 50, 50, 50), D3DCOLOR_ARGB(220, 5, 5, 5));
		cWriteText(110, 14, D3DCOLOR_ARGB(255, 000, 255, 000), /*POINT BLANK X*/XorStr<0xCA, 14, 0x72905673>("\x9A\x84\x85\x83\x9A\xEF\x92\x9D\x93\x9D\x9F\xF5\x8E" + 0x72905673).s);

		//DrawBox(pDevice, 20, 35 + (Current * 15), 190, 18, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
		//cWriteText(110, 38 + (Current * 15), D3DCOLOR_ARGB(255, 000, 255, 000), /*WWW.RAMLEAGUE.NET*/XorStr<0x52, 18, 0x71C90AC0>("\x05\x04\x03\x7B\x04\x16\x15\x15\x1F\x1A\x1B\x08\x1B\x71\x2E\x24\x36" + 0x71C90AC0).s);

		DrawBorder(pDevice, 20, 26 + (MenuSelection * 15), 190, 15, 1, D3DCOLOR_ARGB(255, 255, 255, 255));

		Current = 1;

		Kategorie(pDevice, /*[D3D]*/XorStr<0x93, 6, 0xC9B9FC22>("\xC8\xD0\xA6\xD2\xCA" + 0xC9B9FC22).s);
		AddItem(pDevice, /*Crosshair*/XorStr<0xC1, 10, 0x13AAE53D>("\x82\xB0\xAC\xB7\xB6\xAE\xA6\xA1\xBB" + 0x13AAE53D).s, pUtils.d3d.crosshair, opt_OnOff, 1);

		Kategorie(pDevice, /*[Aimbot]*/XorStr<0xCB, 9, 0xD8CB92F5>("\x90\x8D\xA4\xA3\xAD\xBF\xA5\x8F" + 0xD8CB92F5).s);
		AddItem(pDevice, /*Enable Aimbot*/XorStr<0xBA, 14, 0x77905AAA>("\xFF\xD5\xDD\xDF\xD2\xDA\xE0\x80\xAB\xAE\xA6\xAA\xB2" + 0x77905AAA).s, pUtils.aimbot.main, opt_OnOff, 1);
		AddItem(pDevice, /*Aimbot Smooth*/XorStr<0xB7, 14, 0xBF9DFF33>("\xF6\xD1\xD4\xD8\xD4\xC8\x9D\xED\xD2\xAF\xAE\xB6\xAB" + 0xBF9DFF33).s, pUtils.aimbot.smooth, opt_BoneOption, 2);
		AddItem(pDevice, /*Aimbot Fov*/XorStr<0x4B, 11, 0x33AEE50D>("\x0A\x25\x20\x2C\x20\x24\x71\x14\x3C\x22" + 0x33AEE50D).s, pUtils.aimbot.fov, opt_BoneOption, 2);
		AddItem(pDevice, /*Aimbot Draw*/XorStr<0xDE, 12, 0x8A901E12>("\x9F\xB6\x8D\x83\x8D\x97\xC4\xA1\x94\x86\x9F" + 0x8A901E12).s, pUtils.aimbot.draw, opt_OnOff, 1);
		AddItem(pDevice, /*Aimbot Target*/XorStr<0xC3, 14, 0x340D99F1>("\x82\xAD\xA8\xA4\xA8\xBC\xE9\x9E\xAA\xBE\xAA\xAB\xBB" + 0x340D99F1).s, pUtils.aimbot.target, opt_BoneTarget, 2);
		AddItem(pDevice, /*Aimbot Key*/XorStr<0x30, 11, 0xD1AD3B58>("\x71\x58\x5F\x51\x5B\x41\x16\x7C\x5D\x40" + 0xD1AD3B58).s, pUtils.aimbot.key, opt_BoneKey, 2);

		Kategorie(pDevice, /*[AimBullet]*/XorStr<0x62, 12, 0xC60E7F18>("\x39\x22\x0D\x08\x24\x12\x04\x05\x0F\x1F\x31" + 0xC60E7F18).s);
		AddItem(pDevice, /*Enable AimBullet*/XorStr<0x76, 17, 0x1790087B>("\x33\x19\x19\x1B\x16\x1E\x5C\x3C\x17\x12\xC2\xF4\xEE\xEF\xE1\xF1" + 0x1790087B).s, pUtils.aimbullet.main, opt_OnOff, 1);
		AddItem(pDevice, /*Aimbullet Autoshot*/XorStr<0xCE, 19, 0xF4D883A4>("\x8F\xA6\xBD\xB3\xA7\xBF\xB8\xB0\xA2\xF7\x99\xAC\xAE\xB4\xAF\xB5\xB1\xAB" + 0xF4D883A4).s, pUtils.aimbullet.autoshot, opt_OnOff, 1);
		AddItem(pDevice, /*AimBullet Draw*/XorStr<0x0E, 15, 0xCADAE901>("\x4F\x66\x7D\x53\x67\x7F\x78\x70\x62\x37\x5C\x6B\x7B\x6C" + 0xCADAE901).s, pUtils.aimbullet.draw, opt_OnOff, 1);
		AddItem(pDevice, /*AimBullet Target*/XorStr<0xCE, 17, 0x93CB7D51>("\x8F\xA6\xBD\x93\xA7\xBF\xB8\xB0\xA2\xF7\x8C\xB8\xA8\xBC\xB9\xA9" + 0x93CB7D51).s, pUtils.aimbullet.target, opt_BoneTarget, 2);

		Kategorie(pDevice, /*[TeleBomb]*/XorStr<0x9D, 11, 0x262F94D4>("\xC6\xCA\xFA\xCC\xC4\xE0\xCC\xC9\xC7\xFB" + 0x262F94D4).s);
		AddItem(pDevice, /*Enable TeleBomb*/XorStr<0xC2, 16, 0x04B5FB53>("\x87\xAD\xA5\xA7\xAA\xA2\xE8\x9D\xAF\xA7\xA9\x8F\xA1\xA2\xB2" + 0x04B5FB53).s, pUtils.telebomb.main, opt_OnOff, 1);
		AddItem(pDevice, /*TeleBomb Draw*/XorStr<0x2F, 14, 0xD668CA25>("\x7B\x55\x5D\x57\x71\x5B\x58\x54\x17\x7C\x4B\x5B\x4C" + 0xD668CA25).s, pUtils.telebomb.draw, opt_OnOff, 1);

		Kategorie(pDevice, /*[ESP]*/XorStr<0x9D, 6, 0x981B3AD4>("\xC6\xDB\xCC\xF0\xFC" + 0x981B3AD4).s);
		AddItem(pDevice, /*ESP Team*/XorStr<0xCC, 9, 0x717BF84B>("\x89\x9E\x9E\xEF\x84\xB4\xB3\xBE" + 0x717BF84B).s, pUtils.esp.team, opt_EspTeam, 2);
		AddItem(pDevice, /*ESP Box*/XorStr<0x7C, 8, 0x2B61AC97>("\x39\x2E\x2E\x5F\xC2\xEE\xFA" + 0x2B61AC97).s, pUtils.esp.box, opt_OnOff, 1);
		AddItem(pDevice, /*ESP Line*/XorStr<0xB3, 9, 0x0FB0F644>("\xF6\xE7\xE5\x96\xFB\xD1\xD7\xDF" + 0x0FB0F644).s, pUtils.esp.line, opt_OnOff, 1);
		AddItem(pDevice, /*ESP Name*/XorStr<0x14, 9, 0x1BAC5D8E>("\x51\x46\x46\x37\x56\x78\x77\x7E" + 0x1BAC5D8E).s, pUtils.esp.name, opt_OnOff, 1);
		AddItem(pDevice, /*ESP Health*/XorStr<0xE5, 11, 0x025B5BFC>("\xA0\xB5\xB7\xC8\xA1\x8F\x8A\x80\x99\x86" + 0x025B5BFC).s, pUtils.esp.health, opt_OnOff, 1);
		AddItem(pDevice, /*ESP Health Bar*/XorStr<0x96, 15, 0xC4DE2E39>("\xD3\xC4\xC8\xB9\xD2\xFE\xFD\xF1\xEA\xF7\x80\xE3\xC3\xD1" + 0xC4DE2E39).s, pUtils.esp.healthbar, opt_OnOff, 1);
		AddItem(pDevice, /*ESP Skeleton*/XorStr<0x1C, 13, 0x81F5D387>("\x59\x4E\x4E\x3F\x73\x4A\x47\x4F\x41\x51\x49\x49" + 0x81F5D387).s, pUtils.esp.bone, opt_OnOff, 1);
		AddItem(pDevice, /*ESP Distance*/XorStr<0xC6, 13, 0x01E4A159>("\x83\x94\x98\xE9\x8E\xA2\xBF\xB9\xAF\xA1\xB3\xB4" + 0x01E4A159).s, pUtils.esp.distace, opt_OnOff, 1);

		Kategorie(pDevice, /*[Memory]*/XorStr<0x55, 9, 0xA7001F8D>("\x0E\x1B\x32\x35\x36\x28\x22\x01" + 0xA7001F8D).s);
		AddItem(pDevice, /*No Recoil*/XorStr<0xFF, 10, 0x57B39FF4>("\xB1\x6F\x21\x50\x66\x67\x6A\x6F\x6B" + 0x57B39FF4).s, pUtils.memory.norecoil, opt_OnOff, 1);
		AddItem(pDevice, /*Accuracy*/XorStr<0x58, 9, 0xF62C808B>("\x19\x3A\x39\x2E\x2E\x3C\x3D\x26" + 0xF62C808B).s, pUtils.memory.accuracy, opt_OnOff, 1);
		AddItem(pDevice, /*Unli Ammo*/XorStr<0x98, 10, 0xA4BCDF2F>("\xCD\xF7\xF6\xF2\xBC\xDC\xF3\xF2\xCF" + 0xA4BCDF2F).s, pUtils.memory.unliammo, opt_OnOff, 1);
		AddItem(pDevice, /*Respawn In Death*/XorStr<0x4B, 17, 0x26038F0C>("\x19\x29\x3E\x3E\x2E\x27\x3F\x72\x1A\x3A\x75\x12\x32\x39\x2D\x32" + 0x26038F0C).s, pUtils.memory.respawnindeath, opt_OnOff, 1);
		AddItem(pDevice, /*Fast Bomb*/XorStr<0xE1, 10, 0x870E01A0>("\xA7\x83\x90\x90\xC5\xA4\x88\x85\x8B" + 0x870E01A0).s, pUtils.memory.fastbomb, opt_OnOff, 1);
		AddItem(pDevice, /*Fast Shoot*/XorStr<0xA2, 11, 0x7119F608>("\xE4\xC2\xD7\xD1\x86\xF4\xC0\xC6\xC5\xDF" + 0x7119F608).s, pUtils.memory.fastshot, opt_OnOff, 1);
		AddItem(pDevice, /*Fast Switch*/XorStr<0x33, 12, 0xD8EB5081>("\x75\x55\x46\x42\x17\x6B\x4E\x53\x4F\x5F\x55" + 0xD8EB5081).s, pUtils.memory.fastswitch, opt_OnOff, 1);
		AddItem(pDevice, /*Fast Reload*/XorStr<0xB2, 12, 0xC5BC1111>("\xF4\xD2\xC7\xC1\x96\xE5\xDD\xD5\xD5\xDA\xD8" + 0xC5BC1111).s, pUtils.memory.fastreload, opt_OnOff, 1);
		AddItem(pDevice, /*Fast Knife/Reload*/XorStr<0x7E, 18, 0x6642CFF7>("\x38\x1E\xF3\xF5\xA2\xC8\xEA\xEC\xE0\xE2\xA7\xDB\xEF\xE7\xE3\xEC\xEA" + 0x6642CFF7).s, pUtils.memory.fastreloadknife, opt_OnOff, 1);
		AddItem(pDevice, /*Rapid Fire*/XorStr<0xF1, 11, 0x3456E4BF>("\xA3\x93\x83\x9D\x91\xD6\xB1\x91\x8B\x9F" + 0x3456E4BF).s, pUtils.memory.rapidfire, opt_OnOff, 1);
		AddItem(pDevice, /*Fast Respawn*/XorStr<0x2F, 13, 0x5A22AFF2>("\x69\x51\x42\x46\x13\x66\x50\x45\x47\x59\x4E\x54" + 0x5A22AFF2).s, pUtils.memory.fastrespawn, opt_OnOff, 1);
		AddItem(pDevice, /*No Fall Damage*/XorStr<0xAB, 15, 0xE759F8F8>("\xE5\xC3\x8D\xE8\xCE\xDC\xDD\x92\xF7\xD5\xD8\xD7\xD0\xDD" + 0xE759F8F8).s, pUtils.memory.nofalldamage, opt_OnOff, 1);
		AddItem(pDevice, /*Speed Hack*/XorStr<0x09, 11, 0x63A54445>("\x5A\x7A\x6E\x69\x69\x2E\x47\x71\x72\x79" + 0x63A54445).s, pUtils.memory.speedhack, opt_SpeedHack, 2);

		Kategorie(pDevice, /*[Room]*/XorStr<0x22, 7, 0xFFD63D19>("\x79\x71\x4B\x4A\x4B\x7A" + 0xFFD63D19).s);
		AddItem(pDevice, /*Anti Kick*/XorStr<0x0C, 10, 0x7308D62C>("\x4D\x63\x7A\x66\x30\x5A\x7B\x70\x7F" + 0x7308D62C).s, pUtils.memory.antikick, opt_OnOff, 1);
		AddItem(pDevice, /*Unlock Room*/XorStr<0x73, 12, 0xF0B2C963>("\x26\x1A\x19\x19\x14\x13\x59\x28\x14\x13\x10" + 0xF0B2C963).s, pUtils.memory.unlockroom, opt_OnOff, 1);

		Kategorie(pDevice, /*[Menu]*/XorStr<0x7E, 7, 0x12167B52>("\x25\x32\xE5\xEF\xF7\xDE" + 0x12167B52).s);
		AddItem(pDevice, /*Panic Key*/XorStr<0x65, 10, 0x204AA387>("\x35\x07\x09\x01\x0A\x4A\x20\x09\x14" + 0x204AA387).s, pUtils.menu.panickey, opt_PanicKey, 0);
		AddItem(pDevice, /*Open/Close Menu*/XorStr<0x13, 16, 0x7B945880>("\x5C\x64\x70\x78\x38\x5B\x75\x75\x68\x79\x3D\x53\x7A\x4E\x54" + 0x7B945880).s, pUtils.menu.closemenu, opt_CloseMenu, 0);
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
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void menu::DrawCross(LPDIRECT3DDEVICE9 pDevice, int X, int Y, int Size, float LineWidth, D3DCOLOR CrossColor)
{
	DrawLine(pDevice, X - Size / 2, Y, X - 1, Y, LineWidth, CrossColor);
	DrawLine(pDevice, X + Size / 2, Y, X, Y, LineWidth, CrossColor);
	DrawLine(pDevice, X, Y - Size / 2, X, Y - 1, LineWidth, CrossColor);
	DrawLine(pDevice, X, Y + Size / 2, X, Y, LineWidth, CrossColor);
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
	DrawBorder(pDevice, x, y, w, h, px, Border);
	FillRGB(pDevice, x, y, w, h, Fill);
}

void menu::WriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void menu::sWriteText(int x, int y, DWORD color, const char *text, ...)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	char buf[1024] = { '\0' };
	va_list va_alist;

	va_start(va_alist, text);
	vsprintf_s(buf, text, va_alist);
	va_end(va_alist);

	pFont->DrawTextA(NULL, buf, -1, &rect, DT_NOCLIP | DT_CENTER, color);
	
	SetRect(&rect, x - 1, y, x - 1, y);
	pFont->DrawTextA(NULL, buf, -1, &rect, DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, 000, 000, 000));

	SetRect(&rect, x + 1, y, x + 1, y);
	pFont->DrawTextA(NULL, buf, -1, &rect, DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, 000, 000, 000));

	SetRect(&rect, x, y - 1, x, y - 1);
	pFont->DrawTextA(NULL, buf, -1, &rect, DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, 000, 000, 000));

	SetRect(&rect, x, y + 1, x, y + 1);
	pFont->DrawTextA(NULL, buf, -1, &rect, DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, 000, 000, 000));
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

void menu::AddItem(LPDIRECT3DDEVICE9 pDevice, const char *text, int &var, int opt, int MaxValue)
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

		enum {
			opt_Auto = 0,
			opt_OnOff = 1,
			opt_BoneKey = 2,
			opt_BoneTarget = 3,
			opt_BoneOption = 4,
			opt_EspTeam = 5,
			opt_SpeedHack = 8,
			opt_PanicKey = 6,
			opt_CloseMenu = 7
		};

		char optBuff[100];
		if(opt == opt_Auto)
			lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[AUTO]*/XorStr<0x24, 7, 0x919EFAF4>("\x7F\x64\x73\x73\x67\x74" + 0x919EFAF4).s);
		else if (opt == opt_OnOff)
		{
			if(var == 0)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[OFF]*/XorStr<0x29, 6, 0x577879EC>("\x72\x65\x6D\x6A\x70" + 0x577879EC).s);
			else
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[ON]*/XorStr<0x41, 5, 0x0B9B1D39>("\x1A\x0D\x0D\x19" + 0x0B9B1D39).s);
		}
		else if (opt == opt_BoneKey)
		{
			if(var == 0)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[SHIFT]*/XorStr<0xFB, 8, 0x0B670FB7>("\xA0\xAF\xB5\xB7\xB9\x54\x5C" + 0x0B670FB7).s);
			else if(var == 1)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[LBUTTON]*/XorStr<0x32, 10, 0x3E95469D>("\x69\x7F\x76\x60\x62\x63\x77\x77\x67" + 0x3E95469D).s);
			else
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText,  /*[AUTO]*/XorStr<0x24, 7, 0x919EFAF4>("\x7F\x64\x73\x73\x67\x74" + 0x919EFAF4).s);
		}
		else if (opt == opt_BoneTarget) {
			if(var == 0)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Head]*/XorStr<0x48, 7, 0xA45624E1>("\x13\x01\x2F\x2A\x28\x10" + 0xA45624E1).s);
			else if(var == 1)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Neck]*/XorStr<0xA9, 7, 0xDB83C422>("\xF2\xE4\xCE\xCF\xC6\xF3" + 0xDB83C422).s);
			else
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Body]*/XorStr<0x3A, 7, 0x7538F3E7>("\x61\x79\x53\x59\x47\x62" + 0x7538F3E7).s);
		}
		else if (opt == opt_BoneOption) {
			if (var == 0)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Recommended]*/XorStr<0xA8, 14, 0x089CDBDE>("\xF3\xFB\xCF\xC8\xC3\xC0\xC3\xCA\xDE\xD5\xD7\xD7\xE9" + 0x089CDBDE).s);
			else if (var == 1)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Normal]*/XorStr<0x46, 9, 0x6719DA1C>("\x1D\x09\x27\x3B\x27\x2A\x20\x10" + 0x6719DA1C).s);
			else
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Big]*/XorStr<0xBB, 6, 0xD3677754>("\xE0\xFE\xD4\xD9\xE2" + 0xD3677754).s);
		}
		else if (opt == opt_EspTeam) {
			if(var == 0)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[All]*/XorStr<0xB2, 6, 0xCAB93E2C>("\xE9\xF2\xD8\xD9\xEB" + 0xCAB93E2C).s);
			else if(var == 1)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Enemy]*/XorStr<0x31, 8, 0xDBAE2024>("\x6A\x77\x5D\x51\x58\x4F\x6A" + 0xDBAE2024).s);
			else
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[Team]*/XorStr<0x74, 7, 0x44A1B25E>("\x2F\x21\x13\x16\x15\x24" + 0x44A1B25E).s);
		}
		else if (opt == opt_SpeedHack){
			if (var == 0)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[OFF]*/XorStr<0x29, 6, 0x577879EC>("\x72\x65\x6D\x6A\x70" + 0x577879EC).s);
			else if (var == 1)
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[1x]*/XorStr<0xA0, 5, 0x06E928B1>("\xFB\x90\xDA\xFE" + 0x06E928B1).s);
			else
				lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[2x]*/XorStr<0x23, 5, 0x25B79363>("\x78\x16\x5D\x7B" + 0x25B79363).s);
		}
		else if (opt == opt_PanicKey) {
			lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[DELETE]*/XorStr<0x1A, 9, 0x993B0A3C>("\x41\x5F\x59\x51\x5B\x4B\x65\x7C" + 0x993B0A3C).s);
		}
		else if (opt == opt_CloseMenu) {
			lWriteText(PosX + 173, PosY + (Current * 15) - 1, ColorText, /*[INSERT]*/XorStr<0x69, 9, 0x606F167A>("\x32\x23\x25\x3F\x28\x3C\x3B\x2D" + 0x606F167A).s);
		}
		Current++;
	}
}
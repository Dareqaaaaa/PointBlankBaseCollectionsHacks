#pragma once

#include "stdafx.h"

#define Green				D3DCOLOR_ARGB(255, 000, 255, 000)
#define Red					D3DCOLOR_ARGB(255, 255, 000, 000)
#define Blue				D3DCOLOR_ARGB(255, 000, 000, 255)
#define Orange				D3DCOLOR_ARGB(255, 255, 165, 000)
#define Yellow				D3DCOLOR_ARGB(255, 255, 255, 000)
#define Pink				D3DCOLOR_ARGB(255, 255, 192, 203)
#define Cyan				D3DCOLOR_ARGB(255, 000, 255, 255)
#define Purple				D3DCOLOR_ARGB(255, 160, 032, 240)
#define Black				D3DCOLOR_ARGB(255, 000, 000, 000) 
#define White				D3DCOLOR_ARGB(255, 255, 255, 255)
#define Grey				D3DCOLOR_ARGB(255, 112, 112, 112)
#define SteelBlue			D3DCOLOR_ARGB(255, 033, 104, 140)
#define LightSteelBlue		D3DCOLOR_ARGB(255, 201, 255, 255)
#define LightBlue			D3DCOLOR_ARGB(255, 026, 140, 306)
#define Salmon				D3DCOLOR_ARGB(255, 196, 112, 112)
#define Brown				D3DCOLOR_ARGB(255, 168, 099, 020)
#define Teal				D3DCOLOR_ARGB(255, 038, 140, 140)
#define Lime				D3DCOLOR_ARGB(255, 050, 205, 050)
#define ElectricLime		D3DCOLOR_ARGB(255, 204, 255, 000)
#define Gold				D3DCOLOR_ARGB(255, 255, 215, 000)
#define OrangeRed			D3DCOLOR_ARGB(255, 255, 069, 000)
#define GreenYellow			D3DCOLOR_ARGB(255, 173, 255, 047)
#define AquaMarine			D3DCOLOR_ARGB(255, 127, 255, 212)
#define SkyBlue				D3DCOLOR_ARGB(255, 000, 191, 255)
#define SlateBlue			D3DCOLOR_ARGB(255, 132, 112, 255)
#define Crimson				D3DCOLOR_ARGB(255, 220, 020, 060)
#define DarkOliveGreen		D3DCOLOR_ARGB(255, 188, 238, 104)
#define PaleGreen			D3DCOLOR_ARGB(255, 154, 255, 154)
#define DarkGoldenRod		D3DCOLOR_ARGB(255, 255, 185, 015)
#define FireBrick			D3DCOLOR_ARGB(255, 255, 048, 048)
#define DarkBlue			D3DCOLOR_ARGB(255, 000, 000, 204)
#define DarkerBlue			D3DCOLOR_ARGB(255, 000, 000, 153)
#define DarkYellow			D3DCOLOR_ARGB(255, 255, 204, 000)
#define LightYellow			D3DCOLOR_ARGB(255, 255, 255, 153)
#define DarkOutline			D3DCOLOR_ARGB(255, 37,   48,  52)
#define TBlack				D3DCOLOR_ARGB(180, 000, 000, 000) 
#define cGray				D3DCOLOR_ARGB(255, 200, 200, 200)

#define ItemColorOn White
#define ItemColorOff cGray
#define ItemCurrent Red
#define GroupColor Red
#define KategorieFarbe Red
#define ItemText cGray

struct MenuT
{
private:
	int MenuSelection;
	int Current;
	int PosX;
	int PosY;
	int Show;
	POINT cPos;
public:
	bool Create;
	LPD3DXFONT pFont;
	ID3DXLine *pLine;
	D3DVIEWPORT9 Viewport;
public:
	int CheckTabs(int x, int y, int w, int h);
	void DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, float width, DWORD color);
	void FillRGB(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color);
	void DrawBorder(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor);
	void DrawBox(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, DWORD Fill, DWORD Border);
	void WriteText(int x, int y, DWORD color, const char *text);
	void lWriteText(int x, int y, DWORD color, const char *text);
	void cWriteText(int x, int y, DWORD color, const char *text);
	void Kategorie(LPDIRECT3DDEVICE9 pDevice, const char *text);
	void AddItem(LPDIRECT3DDEVICE9 pDevice, const char *text, int &var, const char **opt, int MaxValue);
public:
	void CreateMenu(LPDIRECT3DDEVICE9 pDevice);

public:
	MenuT()
	{
		MenuSelection = 0;
		Current = 1;
		PosX = 30;
		PosY = 27;
		Show = 1;
		Create = false;
	}
};

extern MenuT * Menu;
int MenuSelection = 0;
int Current = true;

int PosX = 30;
int PosY = 27;

int Show = true;

POINT cPos;

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

int CheckTabs(int x, int y, int w, int h)
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

struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

void DrawLine(LPDIRECT3DDEVICE9 pDevice,float x, float y, float x2, float y2, float width, DWORD color)
{
	if (!pLine)
		D3DXCreateLine(pDevice, &pLine);

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

void FillRGB(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawBorder(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor)
{
	FillRGB(pDevice, x, (y + h - px), w, px, BorderColor);
	FillRGB(pDevice, x, y, px, h, BorderColor);
	FillRGB(pDevice, x, y, w, px, BorderColor);
	FillRGB(pDevice, x + w - px, y, px, h, BorderColor);
}

void DrawBox(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, DWORD Fill, DWORD Border)
{
	FillRGB(pDevice, x, y, w, h, Fill);
	DrawBorder(pDevice, x, y, w, h, px, Border);
}

void WriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void lWriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_RIGHT, color);
}

void cWriteText(int x, int y, DWORD color, const char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(0, text, -1, &rect, DT_NOCLIP | DT_CENTER, color);
}

void Kategorie(LPDIRECT3DDEVICE9 pDevice, const char *text)
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

		WriteText(PosX - 5, PosY + (Current * 15) - 1, ColorText, "TEST");
		lWriteText(PosX + 175, PosY + (Current * 15) - 1, ColorText, "[-]");
		Current++;
	}
}

void AddItem(LPDIRECT3DDEVICE9 pDevice, const char *text, int &var, const char **opt, int MaxValue)
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

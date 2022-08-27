int MenuSelection = 0;
int Current = true;

int PosX = 30;
int PosY = 27;

int Show = true;

POINT cPos;

#define ItemColorOn White
#define ItemColorOff cGray
#define ItemCurrent Red
#define GroupColor Red
#define KategorieFarbe Red
#define ItemText cGray

int CheckTabs (int x, int y, int w, int h)
{
	GetCursorPos(&cPos);
	ScreenToClient(GetForegroundWindow(),&cPos);
	if(cPos.x > x && cPos.x < x + w && cPos.y > y && cPos.y < y + h)
	{
		if(GetAsyncKeyState(VK_LBUTTON)&1)
		{
			return 1;
		}
		return 2;
	}
	return 0;
}

void CrossPic (LPDIRECT3DDEVICE9 pDevice)
{
	D3DVIEWPORT9 pViewport;
	pDevice->GetViewport(&pViewport);
	DWORD cx = pViewport.Width / 2;
	DWORD cy = pViewport.Height / 2;
	D3DRECT rec2 = {cx-5, cy, cx+6, cy+1};
	D3DRECT rec3 = {cx, cy-5, cx+1, cy+6};
	pDevice->Clear(1, &rec2, D3DCLEAR_TARGET, Red, 0, 0); 
	pDevice->Clear(1, &rec3, D3DCLEAR_TARGET, Red, 0, 0); 
}

struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

void DrawLine (LPDIRECT3DDEVICE9 pDevice, float X, float Y, float X2, float Y2, DWORD dwColor)
{
	if(!pDevice) return;
	D3DTLVERTEX qV[2] = 
	{ 
		{(float)X, (float)Y, 0.0f, 1.0f, dwColor},
		{(float)X2, (float)Y2, 0.0f, 1.0f, dwColor},
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	pDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
}

void FillRGB (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec = {x, y, x + w, y + h};
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawBorder (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor)
{
	FillRGB(pDevice, x,(y + h - px), w, px, BorderColor);
	FillRGB(pDevice, x, y, px, h, BorderColor);
	FillRGB(pDevice, x, y, w, px, BorderColor);
	FillRGB(pDevice, x + w - px, y, px, h, BorderColor);
}

void DrawBox (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, DWORD Fill, DWORD Border)
{
	FillRGB(pDevice,x, y, w, h, Fill);
	DrawBorder(pDevice,x, y, w, h, px, Border);
}

void WriteText (int x, int y, DWORD color, char *text)
{    
    RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void lWriteText (int x, int y, DWORD color, char *text)
{    
	RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_RIGHT, color);
}

void cWriteText (int x, int y, DWORD color, char *text)
{    
	RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_CENTER, color);
}

void Kategorie (LPDIRECT3DDEVICE9 pDevice, char *text)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190, 10);
		DWORD ColorText;

		ColorText = KategorieFarbe;

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText(PosX - 5,	PosY  + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 175,	PosY  + (Current * 15) - 1, ColorText, "[-]");
		Current++;
	}
}

void AddItem (LPDIRECT3DDEVICE9 pDevice, char *text, int &var, char **opt, int MaxValue)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190, 10);
		DWORD ColorText;

		if(var)
		{
			DrawBox(pDevice, PosX, PosY  + (Current * 15) + 2, 5, 5, 1, Green, D3DCOLOR_ARGB(220,5,5,5));
			ColorText = ItemColorOn;
		}
		if(var == 0)
		{
			DrawBox(pDevice, PosX, PosY  + (Current * 15) + 2, 5, 5, 1, Red, D3DCOLOR_ARGB(220,5,5,5));
			ColorText = ItemColorOff;
		}

		if(Check == 1)
		{
			var++;
			if(var > MaxValue)
				var = 0;
		}

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current) 
		{
			if(GetAsyncKeyState(VK_RIGHT)&1)
			{
				var++;
				if(var > MaxValue)
					var = 0;
			}
			else if(GetAsyncKeyState(VK_LEFT)&1)
			{
				var--;
				if(var < 0)
					var = MaxValue;
			}
		}

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText(PosX + 8,	PosY  + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 173,	PosY  + (Current * 15) - 1, ColorText, opt[var]);
		Current++;
	}
}
#pragma once

static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}
kPressingKey[256];

class menu
{
private:
	int MenuSelection;
	int Current;
	int PosX;
	int PosY;
	int Show;
	POINT cPos;

public:
	menu();
	~menu();

	bool Create;
	LPD3DXFONT pFont;
	ID3DXLine *pLine;
	D3DVIEWPORT9 Viewport;

	void Init();
	void ResetFont(LPDIRECT3DDEVICE9 pDevice);

	BOOL IsKeyPressed(int Key, DWORD dwTimeOut);
	int CheckTabs(int x, int y, int w, int h);
	void DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, float width, DWORD color);
	void FillRGB(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color);
	void DrawCross(LPDIRECT3DDEVICE9 pDevice, int X, int Y, int Size, float LineWidth, D3DCOLOR CrossColor);
	void DrawBorder(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor);
	void DrawBox(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, DWORD Fill, DWORD Border);
	void WriteText(int x, int y, DWORD color, const char *text);
	void sWriteText(int x, int y, DWORD color, const char *text, ...);
	void lWriteText(int x, int y, DWORD color, const char *text);
	void cWriteText(int x, int y, DWORD color, const char *text);
	void Kategorie(LPDIRECT3DDEVICE9 pDevice, const char *text);
	void AddItem(LPDIRECT3DDEVICE9 pDevice, const char *text, int &var, int opt, int MaxValue);

	void CreateMenu(LPDIRECT3DDEVICE9 pDevice);
};
extern menu pMenu;

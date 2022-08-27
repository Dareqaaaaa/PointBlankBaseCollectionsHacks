
#pragma once
#include "stdafx.h"

struct DirectXT
{
public:
	IDirect3D9Ex* DX;
	IDirect3DDevice9Ex* DXDevice;
	D3DPRESENT_PARAMETERS DXParams;
	ID3DXLine* DXLine;
	ID3DXFont* DXFont;

	POINT cPos;
	int MenuSelection = 0;
	int Current = true;
	int PosX = 30;
	int PosY = 27;
	int Show = true;
private:
	void WriteTextShadow(int x, int y, std::wstring Text, DWORD TextColor);
	void lWriteTextShadow(int x, int y, std::wstring Text, DWORD TextColor);
	void cWriteTextShadow(int x, int y, std::wstring Text, DWORD TextColor);

public:
	void ESPDrawText(int x, int y, DWORD color, char *text);
	void DrawRect(int X, int Y, int Width, int Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawLine(int X, int Y, int XX, int YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawCross(int X, int Y, int Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, int OutlineWidth, D3DCOLOR OutlineColor);
	void DrawHealthBar(float x, float y, int Health, bool vertical);
	void WriteText(int X, int Y, std::wstring Text, D3DCOLOR TextColor);
	void lWriteText(int X, int Y, std::wstring Text, D3DCOLOR TextColor);
	void cWriteText(int X, int Y, std::wstring Text, D3DCOLOR TextColor);
	bool SetupDirectX(HWND Handle, int Width, int Height);
	bool Valid();
	void Render();

private:
	//menu
	int CheckTabs(int x, int y, int w, int h);
	void AddMenu(std::wstring Text);
	void AddItem(std::wstring text, int &var, std::wstring *opt, int MaxValue);
	void CreateMenu();
};

extern DirectXT* DirectX;
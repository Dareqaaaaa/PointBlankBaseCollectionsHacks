
#include "stdafx.h"

DirectXT* DirectX = new DirectXT();

bool DirectXT::Valid()
{
	if (DXDevice->TestCooperativeLevel() == D3D_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DirectXT::DrawLine(int X, int Y, int XX, int YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
	D3DXVECTOR2 Points[2];
	Points[0] = D3DXVECTOR2(X, Y);
	Points[1] = D3DXVECTOR2(XX, YY);
	if (Outlined)
	{
		DXLine->SetWidth(OutlineWidth * 2 + LineWidth);
		DXLine->Draw(Points, 2, OutlineColor);
	}
	DXLine->SetWidth(LineWidth);
	DXLine->Draw(Points, 2, LineColor);
}

void DirectXT::DrawString(int X, int Y, std::wstring Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor)
{
	RECT Rect;
	Rect.top = Y;
	Rect.left = X;
	if (Outlined)
	{
		RECT OutlineRectTop;
		OutlineRectTop.top = Y - 1;
		OutlineRectTop.left = X;
		RECT OutlineRectLeft;
		OutlineRectLeft.top = Y;
		OutlineRectLeft.left = X - 1;
		RECT OutlineRectRight;
		OutlineRectRight.top = Y;
		OutlineRectRight.left = X + 1;
		RECT OutlineRectBottom;
		OutlineRectBottom.top = Y + 1;
		OutlineRectBottom.left = X;
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectTop, DT_NOCLIP, OutlineColor);
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectLeft, DT_NOCLIP, OutlineColor);
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectRight, DT_NOCLIP, OutlineColor);
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectBottom, DT_NOCLIP, OutlineColor);
	}
	DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &Rect, DT_NOCLIP, TextColor);
}

void DirectXT::DrawRect(int X, int Y, int Width, int Height, float LineWidth, D3DCOLOR LineColor, bool Outlined, bool Filled, float OutlineWidth, D3DCOLOR OutlineColor)
{
	
	if (Filled)
	{
		if (Outlined)
		{
			DrawLine(X - OutlineWidth, Y + Height / 2, X + Width + OutlineWidth, Y + Height / 2, Height, OutlineColor, true, OutlineWidth, OutlineColor);
		}
		DrawLine(X, Y + Height / 2, X + Width, Y + Height / 2, Height, LineColor, false, 0, 0);
	}
	else
	{
		
		if (Outlined)
		{
			DrawLine(X, Y, X, Y + Height, LineWidth, LineColor, true, OutlineWidth, OutlineColor);
			DrawLine(X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, true, OutlineWidth, OutlineColor);
			DrawLine(X + Width, Y + Height, X + Width, Y,  LineWidth, LineColor, true, OutlineWidth, OutlineColor);
			DrawLine(X + Width, Y, X, Y, LineWidth, LineColor, true, OutlineWidth, OutlineColor);
		}
		else
		{
			DrawLine(X, Y, X, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine(X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine(X + Width, Y + Height, X + Width, Y, LineWidth, LineColor, false, 0, 0);
			DrawLine(X + Width, Y, X, Y, LineWidth, LineColor, false, 0, 0);
		}
	}
}

void DirectXT::DrawCross(int X, int Y, int Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, int OutlineWidth, D3DCOLOR OutlineColor)
{
	D3DXVECTOR2 Points[4];
	if (Outlined)
	{
		DrawLine(X - Size / 2 - OutlineWidth, Y, X - 1, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine(X + Size / 2 + OutlineWidth, Y, X, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine(X, Y - Size / 2 - OutlineWidth, X, Y - 1, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine(X, Y + Size / 2 + OutlineWidth, X, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
	}
		DrawLine(X - Size / 2, Y, X - 1, Y, LineWidth, CrossColor, false, 0, 0);
		DrawLine(X + Size / 2, Y, X, Y, LineWidth, CrossColor, false, 0, 0);
		DrawLine(X, Y - Size / 2, X, Y - 1, LineWidth, CrossColor, false, 0, 0);
		DrawLine(X, Y + Size / 2, X, Y, LineWidth, CrossColor, false, 0, 0);
}

void DirectXT::CreateMenu()
{
	std::wstring  opt_OnOff[] = { L"[0/1]", L"[1/1]" };

	if (GetAsyncKeyState(VK_INSERT) & 1)
		Show = !Show;

	if (Show)
	{
		if (GetAsyncKeyState(VK_UP) & 1)
			MenuSelection--;

		if (GetAsyncKeyState(VK_DOWN) & 1)
			MenuSelection++;

		DrawRect(20, 11, 190, 20, 1.0f, D3DCOLOR_ARGB(220, 96, 144, 242), true, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
		DrawString(55, 14, L"[RAML-WR] 2019", D3DCOLOR_ARGB(255, 000, 255, 000), true, D3DCOLOR_ARGB(255, 000, 000, 000));

		DrawRect(20, 34, 190, (Current * 15), 1.0f, D3DCOLOR_ARGB(220, 50, 50, 50), true, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
		DrawRect(20, 26 + (MenuSelection * 15), 190, 15, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255), true, false, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));

		DrawRect(20, 35 + (Current * 15), 190, 18, 1.0f, D3DCOLOR_ARGB(220, 96, 144, 242), true, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
		DrawString(45, 38 + (Current * 15), L"www.ramleague.net", D3DCOLOR_ARGB(255, 000, 255, 000), true, D3DCOLOR_ARGB(255, 000, 000, 000));

		Current = 1;
		AddMenu(L"ESP");
		AddItem(L"ESP Health", Utils->esp.health, opt_OnOff, 1);
		AddItem(L"ESP Line", Utils->esp.line, opt_OnOff, 1);
		AddItem(L"ESP Distance", Utils->esp.distance, opt_OnOff, 1);


		if (MenuSelection >= Current)
			MenuSelection = 1;

		if (MenuSelection < 1)
			MenuSelection = Current;
	}
}

void DirectXT::Render()
{
	if (Valid())
	{
		DXDevice->Clear(NULL, NULL, D3DCLEAR_TARGET, NULL, 1, NULL);
		DXDevice->BeginScene();
		DrawCross(Overlay->Width / 2, Overlay->Height / 2, 15, 1, D3DCOLOR_RGBA(0, 255, 0, 255), true, 1, D3DCOLOR_RGBA(0, 0, 0, 255));
		if (Globals->DebugSettings.EnableDebugLog)
		{
			DrawString(Overlay->X, Overlay->Y, Debug->DebugLog, Globals->DebugSettings.TextColor, Globals->DebugSettings.DrawTextOutline,  Globals->DebugSettings.TextOutlineColor);
		}

		wchar_t basePtr[100];
		swprintf_s(basePtr, L"Base:[0x%X]", Globals->Base.Address);
		DrawString(150, 130, basePtr, D3DCOLOR_ARGB(255, 000, 255, 000), false, 0x0);

		CreateMenu();

		Function->CallESP(DXDevice);

		DXDevice->EndScene();
		DXDevice->PresentEx(NULL, NULL, NULL, NULL, NULL);
	}
}

int DirectXT::CheckTabs(int x, int y, int w, int h)
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

void DirectXT::AddMenu(std::wstring Text)
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

		DrawString(PosX - 5, PosY + (Current * 15) - 1, Text, ColorText, true, D3DCOLOR_ARGB(255, 000, 000, 000));
		DrawString(PosX + 140, PosY + (Current * 15) - 1, L"[-]", ColorText, true, D3DCOLOR_ARGB(255, 000, 000, 000));

		Current++;
	}
}

void DirectXT::AddItem(std::wstring text, int &var, std::wstring *opt, int MaxValue)
{
	if (Show)
	{
		int Check = CheckTabs(PosX, PosY + (Current * 15), 190, 10);
		DWORD ColorText;

		if (var)
		{
			DrawRect(PosX, PosY + (Current * 15) + 2, 5, 5, 1.0f, D3DCOLOR_ARGB(255, 000, 255, 000), false, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
			ColorText = D3DCOLOR_ARGB(255, 255, 255, 255);
		}
		if (var == 0)
		{
			DrawRect(PosX, PosY + (Current * 15) + 2, 5, 5, 1.0f, D3DCOLOR_ARGB(255, 255, 000, 000), false, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
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
			ColorText = D3DCOLOR_ARGB(255, 255, 000, 000);

		DrawString(PosX + 8, PosY + (Current * 15) - 1, text, ColorText, true, D3DCOLOR_ARGB(255, 000, 000, 000));
		DrawString(PosX + 140, PosY + (Current * 15) - 1, opt[var], ColorText, true, D3DCOLOR_ARGB(255, 000, 000, 000));

		Current++;
	}
}


bool DirectXT::SetupDirectX(HWND Handle, int Width, int Height)
{
	Debug->Log(L"Setting up DirectX...");
	Direct3DCreate9Ex(D3D_SDK_VERSION, &DX);
	if (DX)
	{
		ZeroMemory(&DXParams, sizeof(DXParams));
		DXParams.Windowed = TRUE;
		DXParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		DXParams.hDeviceWindow = Handle;
		DXParams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		DXParams.BackBufferFormat = D3DFMT_A8R8G8B8;
		DXParams.BackBufferWidth = Width;
		DXParams.BackBufferHeight = Height;
		DXParams.EnableAutoDepthStencil = TRUE;
		DXParams.AutoDepthStencilFormat = D3DFMT_D16;
		DX->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DXParams, 0, &DXDevice);
		if (DXDevice)
		{
			D3DXCreateLine(DXDevice, &DXLine);
			if (DXLine)
			{
				D3DXCreateFont(DXDevice, 16, NULL, FW_SEMIBOLD, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial", &DXFont);
				if (DXFont)
				{
					Debug->Log(L"DirectX setup was successful.");
					return true;
				}
				else
				{
					MessageBoxW(NULL, L"D3DXCreateFont Failed!", L"Fatal Error", MB_OK);
					return false;
				}
			}
			else
			{
				MessageBoxW(NULL, L"D3DXCreateLine Failed!", L"Fatal Error", MB_OK);
				return false;
			}
		}
		else
		{
			MessageBoxW(NULL, L"CreateDeviceEx Failed!", L"Fatal Error", MB_OK);
			return false;
		}
	}
	else
	{
		MessageBoxW(NULL, L"Direct3DCreate9Ex Failed!", L"Fatal Error", MB_OK);
		return false;
	}
}
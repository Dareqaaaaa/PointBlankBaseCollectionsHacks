
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

void DirectXT::ESPDrawText(int x, int y, DWORD color, char *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	DXFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void DirectXT::WriteTextShadow(int x, int y, std::wstring Text, DWORD TextColor)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	DXFont->DrawTextW(NULL, Text.c_str(), -1, &rect, DT_NOCLIP | DT_LEFT, TextColor);
}

void DirectXT::lWriteTextShadow(int x, int y, std::wstring Text, DWORD TextColor)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	DXFont->DrawTextW(NULL, Text.c_str(), -1, &rect, DT_NOCLIP | DT_RIGHT, TextColor);
}

void DirectXT::cWriteTextShadow(int x, int y, std::wstring Text, DWORD TextColor)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	DXFont->DrawTextW(NULL, Text.c_str(), -1, &rect, DT_NOCLIP | DT_CENTER, TextColor);
}

void DirectXT::WriteText(int X, int Y, std::wstring Text, D3DCOLOR TextColor)
{
	WriteTextShadow(X - 1, Y, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	WriteTextShadow(X + 1, Y, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	WriteTextShadow(X, Y - 1, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	WriteTextShadow(X, Y + 1, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	WriteTextShadow(X, Y, Text, TextColor);
}

void DirectXT::lWriteText(int X, int Y, std::wstring Text, D3DCOLOR TextColor)
{
	lWriteTextShadow(X - 1, Y, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	lWriteTextShadow(X + 1, Y, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	lWriteTextShadow(X, Y - 1, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	lWriteTextShadow(X, Y + 1, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	lWriteTextShadow(X, Y, Text, TextColor);
}

void DirectXT::cWriteText(int X, int Y, std::wstring Text, D3DCOLOR TextColor)
{
	cWriteTextShadow(X - 1, Y, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	cWriteTextShadow(X + 1, Y, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	cWriteTextShadow(X, Y - 1, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	cWriteTextShadow(X, Y + 1, Text, D3DCOLOR_ARGB(255, 29, 29, 29));
	cWriteTextShadow(X, Y, Text, TextColor);
}

void DirectXT::DrawHealthBar(float x, float y, int Health, bool vertical)
{
	if (Health > 0)
	{
		if (!vertical)
		{
			DrawRect(x - 1, y - 1, 102, 7, 1.0f, D3DCOLOR_ARGB(255, 20, 20, 20), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 1)
				DrawRect(x, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 10)
				DrawRect(x + 10, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 20)
				DrawRect(x + 20, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 255, 125, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 30)
				DrawRect(x + 30, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 255, 125, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 40)
				DrawRect(x + 40, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 50)
				DrawRect(x + 50, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 60)
				DrawRect(x + 60, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 0, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 70)
				DrawRect(x + 70, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 0, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 80)
				DrawRect(x + 80, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 0, 0, 255), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 90)
				DrawRect(x + 90, y, 10, 5, 1.0f, D3DCOLOR_ARGB(255, 0, 0, 255), false, true, 1.0f, 0xFFFFF);

			for (size_t i = 0; i < 20; i++)
				DrawRect(x + (i * 5), y, 1, 5, 1.0f, D3DCOLOR_ARGB(255, 81, 75, 61), false, true, 1.0f, 0xFFFFF);
		}
		if (vertical)
		{
			DrawRect(x - 1, y - 1, 7, 102, 1.0f, D3DCOLOR_ARGB(255, 20, 20, 20), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 1)
				DrawRect(x, y, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 10)
				DrawRect(x, y + 10, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 255, 0, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 20)
				DrawRect(x, y + 20, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 255, 125, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 30)
				DrawRect(x, y + 30, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 255, 125, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 40)
				DrawRect(x, y + 40, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 50)
				DrawRect(x, y + 50, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 60)
				DrawRect(x, y + 60, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 0, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 70)
				DrawRect(x, y + 70, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 0, 255, 0), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 80)
				DrawRect(x, y + 80, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 0, 0, 255), false, true, 1.0f, 0xFFFFF);

			if (Health < 101 && Health > 90)
				DrawRect(x, y + 90, 5, 10, 1.0f, D3DCOLOR_ARGB(255, 0, 0, 255), false, true, 1.0f, 0xFFFFF);

			for (size_t i = 0; i < 20; i++)
				DrawRect(x, y + (i * 5), 5, 1, 1.0f, D3DCOLOR_ARGB(255, 81, 75, 61), false, true, 1.0f, 0xFFFFF);
		}
	}
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

static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}
kPressingKey[256];
BOOL IsKeyPressed(int Key, DWORD dwTimeOut)
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

void DirectXT::CreateMenu()
{
	std::wstring  opt_OnOff[] = { L"[0/1]", L"[1/1]" };
	std::wstring  opt_Invisible[] = { L"[0/4]", L"[1/4]", L"[2/4]", L"[3/4]", L"[4/4]" };

	if (IsKeyPressed(VK_INSERT, 0) & 1)
		Show = !Show;

	if (Show)
	{
		if (IsKeyPressed(VK_UP, 0) & 1)
			MenuSelection--;

		if (IsKeyPressed(VK_DOWN, 0) & 1)
			MenuSelection++;

		DrawRect(20, 11, 190, 20, 1.0f, D3DCOLOR_ARGB(220, 96, 144, 242), true, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
		cWriteText(110, 14, L"PBPH RAML", D3DCOLOR_ARGB(255, 000, 255, 000));

		DrawRect(20, 34, 190, (Current * 15), 1.0f, D3DCOLOR_ARGB(220, 50, 50, 50), true, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
		DrawRect(20, 26 + (MenuSelection * 15), 190, 15, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255), true, false, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));

		DrawRect(20, 35 + (Current * 15), 190, 18, 1.0f, D3DCOLOR_ARGB(220, 96, 144, 242), true, true, 0.0f, D3DCOLOR_ARGB(220, 5, 5, 5));
		cWriteText(110, 38 + (Current * 15), L"www.ramleague.net", D3DCOLOR_ARGB(255, 000, 255, 000));

		Current = 1;
		AddMenu(L"Misc");
		AddItem(L"Crosshair", Utils->d3d.crosshair, opt_OnOff, 1);
		AddMenu(L"ESP");
		AddItem(L"ESP Box", Utils->esp.box, opt_OnOff, 1);
		AddItem(L"ESP Distance", Utils->esp.distance, opt_OnOff, 1);
		AddItem(L"ESP Line", Utils->esp.line, opt_OnOff, 1);
		AddMenu(L"Memory");
		AddItem(L"FastReload", Utils->memory.fastreload, opt_OnOff, 1);
		AddItem(L"FastSwitch", Utils->memory.fastswitch, opt_OnOff, 1);
		AddItem(L"FastRespawn", Utils->memory.fastrespawn, opt_OnOff, 1);
		AddItem(L"NoRecoil", Utils->memory.norecoil, opt_OnOff, 1);
		AddItem(L"NoFallDamage", Utils->memory.nofalldamage, opt_OnOff, 1);
		AddItem(L"SpeedRun++", Utils->memory.speedrun, opt_OnOff, 1);

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

		//crosshair
		if(Utils->d3d.crosshair)
			DrawCross(Overlay->Width / 2, Overlay->Height / 2, 15, 1, D3DCOLOR_RGBA(0, 255, 0, 255), true, 1, D3DCOLOR_RGBA(0, 0, 0, 255));
		CreateMenu();

		POINT curPos;
		GetCursorPos(&curPos);

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

		WriteText(PosX - 5, PosY + (Current * 15) - 1, Text, ColorText);
		lWriteText(PosX + 175, PosY + (Current * 15) - 1, L"[-]", ColorText);

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

		WriteText(PosX + 8, PosY + (Current * 15) - 1, text, ColorText);
		lWriteText(PosX + 173, PosY + (Current * 15) - 1, opt[var], ColorText);

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
				D3DXCreateFont(DXDevice, 16, NULL, FW_SEMIBOLD, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Arial", &DXFont);
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
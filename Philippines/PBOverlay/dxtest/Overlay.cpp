
#include "stdafx.h"

OverlayT* Overlay = new OverlayT();

LRESULT CALLBACK OverlayT::WndProc(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
	{
		if (DirectX->Valid())
		{
			BeginPaint(Handle, NULL);
			DirectX->Render();
			EndPaint(Handle, NULL);
		}
		else
		{
			MessageBoxW(NULL, L"DirectX Device Lost!", L"Fatal Error", MB_OK);
			CloseWindow(Handle);
		}
	}
	default:
	{
		return DefWindowProc(Handle, Message, wParam, lParam);
	}
	}
}

bool OverlayT::RepositionWindow(std::wstring Name)
{
	HWND WinHandle = FindWindowW(NULL, Name.c_str());
	if (WinHandle)
	{
		RECT WinRect;
		GetClientRect(WinHandle, &WinRect);
		Width = WinRect.right - WinRect.left;
		Height = WinRect.bottom - WinRect.top;
		ZeroMemory(&WinRect, sizeof(WinRect));
		GetWindowRect(WinHandle, &WinRect);
		X = WinRect.left;
		Y = WinRect.top;
		if (Handle)
		{
			SetWindowPos(Handle, HWND_TOPMOST, X, Y, Width, Height, NULL);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool OverlayT::SetupOverlay()
{
	Debug->Log(L"Setting up overlay...");
	ZeroMemory(&Class, sizeof(Class));
	Class.cbSize = sizeof(Class);
	Class.hInstance = GetModuleHandle(NULL);
	Class.lpfnWndProc = WndProc;
	Class.lpszClassName = Globals->OverlaySettings.Name.c_str();
	Class.style = CS_HREDRAW | CS_VREDRAW;
	Class.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	if (RegisterClassEx(&Class))
	{
		Handle = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, Class.lpszClassName, Class.lpszClassName, WS_POPUP, X, Y, Width, Height, NULL, NULL, Class.hInstance, NULL);
		if(Handle)
		{
			Debug->Log(L"Overlay setup was successful.");
			SetLayeredWindowAttributes(Handle, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
			ShowWindow(Handle, 1);
			MARGINS Margins = { -1, -1, -1, -1 };
			DwmExtendFrameIntoClientArea(Handle, &Margins);
			if (DirectX->SetupDirectX(Handle, Width, Height))
			{
				return true;
			}
			else
			{
				MessageBoxW(NULL, L"SetupDirectX Failed!", L"Fatal Error", MB_OK);
				DestroyWindow(Handle);
				UnregisterClass(Class.lpszClassName, Class.hInstance);
				return false;
			}
		}
		else
		{
			MessageBoxW(NULL, L"CreateWindowEx Failed!", L"Fatal Error", MB_OK);
			UnregisterClass(Class.lpszClassName, Class.hInstance);
			return false;
		}
	}
	else
	{
		MessageBoxW(NULL, L"RegisterClassEx Failed!", L"Fatal Error", MB_OK);
		return false;
	}
}

void OverlayT::RefreshOverlay()
{
	bool FoundWindow = RepositionWindow(Globals->OverlaySettings.ReferenceWindowName);
	if (Handle)
	{
		InvalidateRect(Handle, NULL, false);
		if (GetMessage(&Message, Handle, NULL, NULL))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	else if (FoundWindow)
	{
		Debug->Log(L"Game window found.");
		SetupOverlay();
	}
	else
	{
		Debug->Log(L"Failed to find game window...");
	}
	Sleep(Globals->OverlaySettings.RefreshRate);
}
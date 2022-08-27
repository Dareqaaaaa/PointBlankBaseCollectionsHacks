
#pragma once
#include "stdafx.h"

struct OverlayT
{
	HWND Handle;
	MSG Message;
	WNDCLASSEX Class;
	int Width;
	int Height;
	int X;
	int Y;
	static LRESULT CALLBACK WndProc(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam);
	bool SetupOverlay();
	bool RepositionWindow(std::wstring ReferenceWindowName);
	void RefreshOverlay();
};

extern OverlayT* Overlay;
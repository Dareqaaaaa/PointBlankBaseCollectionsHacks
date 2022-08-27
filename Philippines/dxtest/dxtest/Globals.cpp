
#include "stdafx.h"

GlobalsT* Globals = new GlobalsT();

GlobalsT::GlobalsT()
{
	OverlaySettings.Name = "RAML-PBPH-1.0";
	OverlaySettings.RefreshRate = 10;
	OverlaySettings.ReferenceWindowName = L"Point Blank";
	DebugSettings.DrawTextOutline = true;
	DebugSettings.EnableDebugLog = false;
	DebugSettings.TextColor = D3DCOLOR_RGBA(0, 255, 0, 255);
	DebugSettings.TextOutlineColor = D3DCOLOR_RGBA(0, 0, 0, 255);
	DebugSettings.MaxLines = 40;
}
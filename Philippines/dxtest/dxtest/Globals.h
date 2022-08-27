
#pragma once
#include "stdafx.h"

struct GlobalsT
{
	GlobalsT();
	struct
	{
		int RefreshRate;
		char * Name;
		std::wstring ReferenceWindowName;
	}OverlaySettings;

	struct
	{
		//esp shit goes here
	}ESPSettings;

	struct
	{
		int MaxLines;
		bool EnableDebugLog;
		D3DCOLOR TextColor;
		D3DCOLOR TextOutlineColor;
		bool DrawTextOutline;
	}DebugSettings;
};

extern GlobalsT* Globals;
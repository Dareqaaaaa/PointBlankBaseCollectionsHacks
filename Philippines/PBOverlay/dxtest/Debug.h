
#pragma once
#include "stdafx.h"

struct DebugT
{
	std::wstring DebugLog;
	void Log(std::wstring Text);
};

extern DebugT* Debug;
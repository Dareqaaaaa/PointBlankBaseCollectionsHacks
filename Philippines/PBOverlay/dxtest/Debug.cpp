
#include "stdafx.h"

DebugT* Debug = new DebugT();

void DebugT::Log(std::wstring Text)
{
	int LineCount = 0;
	for (std::wstring::iterator i = DebugLog.begin(); i < DebugLog.end(); i++)
	{
		if ((*i) == L'\n')
		{
			LineCount++;
		}
	}
	if (LineCount > Globals->DebugSettings.MaxLines)
	{
		DebugLog.clear();
	}
	if (DebugLog.length() == 0)
	{
		DebugLog.append(L"DEBUG MESSAGES:\n\n");
	}
	Text.append(L"\n");
	DebugLog.append(Text);

}
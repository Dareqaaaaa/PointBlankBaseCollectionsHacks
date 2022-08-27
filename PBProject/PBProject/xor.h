#ifndef _XOR_H
#define _XOR_H
template <int XORSTART, int BUFLEN, int XREFKILLER>

class XorStr
{
private: 
	XorStr();
public: 
	char s[BUFLEN];

	XorStr(const char * xs);

	~XorStr()
	{
		for (int i = 0; i<BUFLEN; i++) s[i] = 0; 
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr (const char * xs)
{
	int xvalue = XORSTART;
	int i = 0;

	for (; i < (BUFLEN - 1); i++) 
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}

	s[BUFLEN - 1] = 0;
}

#define eGxf		/*i3GfxDx.dll*/XorStr<0x2C,12,0x3B0CAB3D>("\x45\x1E\x69\x49\x48\x75\x4A\x1D\x50\x59\x5A"+0x3B0CAB3D).s
#define eRenderContext /*?g_pRenderContext@@3PAVi3RenderContext@@A*/XorStr<0x0B,42,0xF373A705>("\x34\x6B\x52\x7E\x5D\x75\x7F\x76\x76\x66\x56\x79\x79\x6C\x7C\x62\x6F\x5C\x5D\x2D\x4F\x61\x77\x4B\x10\x76\x40\x48\x43\x4D\x5B\x69\x44\x42\x59\x4B\x57\x44\x71\x72\x72"+0xF373A705).s
#define eKernel32	/*kernel32*/XorStr<0x41,9,0x1533420A>("\x2A\x27\x31\x2A\x20\x2A\x74\x7A"+0x1533420A).s
#define eNtdll		/*ntdll.dll*/XorStr<0x5D,10,0x5C5E14EA>("\x33\x2A\x3B\x0C\x0D\x4C\x07\x08\x09"+0x5C5E14EA).s
#define ed3d9		/*d3d9.dll*/XorStr<0xEC,9,0x4C39F2EF>("\x88\xDE\x8A\xD6\xDE\x95\x9E\x9F"+0x4C39F2EF).s
#define eMenu		/*[RAML] D3D Menu*/XorStr<0xF5,16,0xE692D013>("\xAE\xA4\xB6\xB5\xB5\xA7\xDB\xB8\xCE\xBA\xDF\x4D\x64\x6C\x76"+0xE692D013).s
#define ePB			/*PointBlank.exe*/XorStr<0x26,15,0x0CD748A1>("\x76\x48\x41\x47\x5E\x69\x40\x4C\x40\x44\x1E\x54\x4A\x56"+0x0CD748A1).s
#define eSite		/*www.ramleague.net*/XorStr<0xC9,18,0x79C93728>("\xBE\xBD\xBC\xE2\xBF\xAF\xA2\xBC\xB4\xB3\xB4\xA1\xB0\xF8\xB9\xBD\xAD"+0x79C93728).s

#endif
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
		for(int i=0; i<BUFLEN; i++) 
			s[i] = 0;
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr (const char * xs)
{
	int xvalue = XORSTART;
	int i = 0;

	for(; i<(BUFLEN - 1); i++) 
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = 0;
}

#define ed3d9		/*d3d9.dll*/XorStr<0xEC,9,0x4C39F2EF>("\x88\xDE\x8A\xD6\xDE\x95\x9E\x9F"+0x4C39F2EF).s
#define ei3GfxDx	/*i3GfxDx.dll*/XorStr<0x22,12,0x1D26D95A>("\x4B\x10\x63\x43\x5E\x63\x50\x07\x4E\x47\x40"+0x1D26D95A).s
#define ei3MathDx	/*i3MathDx.dll*/XorStr<0x95,13,0x9F9CD917>("\xFC\xA5\xDA\xF9\xED\xF2\xDF\xE4\xB3\xFA\xF3\xCC"+0x9F9CD917).s
#define ei3SceneDx	/*i3SceneDx.dll*/XorStr<0x23,14,0x680A62FA>("\x4A\x17\x76\x45\x42\x46\x4C\x6E\x53\x02\x49\x42\x43"+0x680A62FA).s
#define eWR		/*WarRock.exe*/XorStr<0x0B,12,0x4288E8DE>("\x5C\x6D\x7F\x5C\x60\x73\x7A\x3C\x76\x6C\x70"+0x4288E8DE).s
#define ePB		/*PointBlank.exe*/XorStr<0xFA,15,0x0CDB20D9>("\xAA\x94\x95\x93\x8A\xBD\x6C\x60\x6C\x68\x2A\x60\x7E\x62"+0x0CDB20D9).s
#define eKernel32	/*kernel32*/XorStr<0x41,9,0x1533420A>("\x2A\x27\x31\x2A\x20\x2A\x74\x7A"+0x1533420A).s
#define eNtdll		/*ntdll.dll*/XorStr<0x5D,10,0x5C5E14EA>("\x33\x2A\x3B\x0C\x0D\x4C\x07\x08\x09"+0x5C5E14EA).s
#define ed3d9		/*d3d9.dll*/XorStr<0xEC,9,0x4C39F2EF>("\x88\xDE\x8A\xD6\xDE\x95\x9E\x9F"+0x4C39F2EF).s
#define ed3d9_29	/*d3dx9_29.dll*/XorStr<0xEA,13,0xF4BEC287>("\x8E\xD8\x88\x95\xD7\xB0\xC2\xC8\xDC\x97\x98\x99"+0xF4BEC287).s
#define eCreateFont	/*D3DXCreateFontA*/XorStr<0x3C,16,0xE86E53B5>("\x78\x0E\x7A\x67\x03\x33\x27\x22\x30\x20\x00\x28\x26\x3D\x0B"+0xE86E53B5).s
#define eMenuCF		/*[RAML] Crossfire Hack*/XorStr<0xE4,22,0xD895417E>("\xBF\xB7\xA7\xAA\xA4\xB4\xCA\xA8\x9E\x82\x9D\x9C\x96\x98\x80\x96\xD4\xBD\x97\x94\x93"+0xD895417E).s
#define eSite		/*www.ramleague.net*/XorStr<0xC9,18,0x79C93728>("\xBE\xBD\xBC\xE2\xBF\xAF\xA2\xBC\xB4\xB3\xB4\xA1\xB0\xF8\xB9\xBD\xAD"+0x79C93728).s
#define eWarning	/*Unknown GM is trying to fuck you!*/XorStr<0xB3,34,0x714C0278>("\xE6\xDA\xDE\xD8\xD8\xCF\xD7\x9A\xFC\xF1\x9D\xD7\xCC\xE0\xB5\xB0\xBA\xAD\xAB\xA1\xE7\xBC\xA6\xEA\xAD\xB9\xAE\xA5\xEF\xA9\xBE\xA7\xF2"+0x714C0278).s
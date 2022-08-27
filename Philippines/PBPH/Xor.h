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

#define eRAML /*www.ramleague.net*/XorStr<0xDA,18,0x96B2EF18>("\xAD\xAC\xAB\xF3\xAC\xBE\x8D\x8D\x87\x82\x83\x90\x83\xC9\x86\x8C\x9E"+0x96B2EF18).s
#define eGxf /*i3GfxDx.dll*/XorStr<0x2C,12,0x3B0CAB3D>("\x45\x1E\x69\x49\x48\x75\x4A\x1D\x50\x59\x5A"+0x3B0CAB3D).s
#define eProductName /*ProductName*/XorStr<0x67,12,0xE35480A7>("\x37\x1A\x06\x0E\x1E\x0F\x19\x20\x0E\x1D\x14"+0xE35480A7).s
#define eSoftware /*SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion*/XorStr<0xBC,45,0xE23DA7B2>("\xEF\xF2\xF8\xEB\x97\x80\x90\x86\x98\x88\xAF\xA4\xBA\xA6\xB9\xA4\xAA\xB9\x92\x98\xB9\xBF\xB6\xBC\xA3\xA6\xF6\x99\x8C\x85\x99\xAE\xAE\xAF\xBB\xB1\x94\xB7\x87\x91\x97\x8C\x89\x89"+0xE23DA7B2).s
#define ed3d9		/*d3d9.dll*/XorStr<0xB9,9,0x64C42EE0>("\xDD\x89\xDF\x85\x93\xDA\xD3\xAC"+0x64C42EE0).s
#define eWinXP /*Windows XP*/XorStr<0x60,11,0x87266DB9>("\x37\x08\x0C\x07\x0B\x12\x15\x47\x30\x39"+0x87266DB9).s
#define eWinVista /*Windows Vista*/XorStr<0x68,14,0xB396AE14>("\x3F\x00\x04\x0F\x03\x1A\x1D\x4F\x26\x18\x01\x07\x15"+0xB396AE14).s
#define eWin7 /*Windows 7*/XorStr<0xB8,10,0x3F830099>("\xEF\xD0\xD4\xDF\xD3\xCA\xCD\x9F\xF7"+0x3F830099).s
#define status /*1*/XorStr<0x09,2,0xA36D18E4>("\x38"+0xA36D18E4).s

#endif
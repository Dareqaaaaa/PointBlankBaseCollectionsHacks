#pragma once

struct PModule
{
	DWORD dwBase;
	DWORD dwSize;
};


class utils
{
public:
	utils();
	~utils();

	PModule modBase;
	PModule modi3SceneDx;
	PModule modi3GfxDx;
	PModule modi3FrameworkDx;
	PModule modi3MathDx;
	PModule modD3DX43;

	HRESULT hD3DXCreateLine(LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE*ppLine);
	HRESULT hD3DXCreateFont(IDirect3DDevice9 *pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCTSTR pFacename, LPD3DXFONT *ppFont);
	D3DXVECTOR3 * hD3DXVec3Project(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DVIEWPORT9 *pViewport, CONST D3DXMATRIX *pProjection, CONST D3DXMATRIX *pView, CONST D3DXMATRIX *pWorld);

	void * DetourCreate(BYTE *src, const BYTE *dst, const int len);
	BOOL GetSwapChainAddress(void ** pTable, size_t Size);
	PModule* GetClientModule();

	struct sesp
	{
		int main;
		int bone;
		int box;
		int distace;
		int line;
	}esp;

	struct smemory
	{
		int main;
		int fastshot;
		int fastreloadknife;
		int rapidfire;
		int fastreload;
		int fastrespawn;
		int fastswitch;
		int nofalldamage;
		int speedhack;
		int norecoil;
	}memory;

	struct saimbot
	{
		int main;
		int smooth;
		int fov;
		int draw;
		int key;
		int target;
	}aimbot;

	struct saimbullet
	{
		int main;
		int target;
		int draw;
	}aimbullet;
private:
	typedef HRESULT(__stdcall* oD3DXCreateLine)(LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE *ppLine);
	typedef HRESULT(__stdcall* oD3DXCreateFont)(IDirect3DDevice9 *pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCTSTR pFacename, LPD3DXFONT *ppFont);
	typedef D3DXVECTOR3*(__stdcall * oD3DXVec3Project)(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DVIEWPORT9 *pViewport, CONST D3DXMATRIX *pProjection, CONST D3DXMATRIX *pView, CONST D3DXMATRIX *pWorld);


	PModule GetBaseAddress();
};
extern utils pUtils;

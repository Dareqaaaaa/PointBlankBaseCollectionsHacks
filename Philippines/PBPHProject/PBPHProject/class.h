#pragma once


HMODULE i3FrameworkDx = GetModuleHandleA(/*i3FrameworkDx.dll*/XorStr<0x9B, 18, 0xFE033128>("\xF2\xAF\xDB\xEC\xFE\xCD\xC4\xD5\xCC\xD6\xCE\xE2\xDF\x86\xCD\xC6\xC7" + 0xFE033128).s);
HMODULE i3MathDx = GetModuleHandleA(/*i3MathDx.dll*/XorStr<0x0C, 13, 0xF750A491>("\x65\x3E\x43\x6E\x64\x79\x56\x6B\x3A\x71\x7A\x7B" + 0xF750A491).s);
HMODULE i3SceneDx = GetModuleHandleA(/*i3SceneDx.dll*/XorStr<0x9A, 14, 0x8DDF9D84>("\xF3\xA8\xCF\xFE\xFB\xF1\xC5\xE5\xDA\x8D\xC0\xC9\xCA" + 0x8DDF9D84).s);
HMODULE i3GfxDx = GetModuleHandleA(/*i3GfxDx.dll*/XorStr<0x92, 12, 0x707656D2>("\xFB\xA0\xD3\xF3\xEE\xD3\xE0\xB7\xFE\xF7\xF0" + 0x707656D2).s);

class i3CollideeLine
{
public:
	D3DXVECTOR3 vTemp;
	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vDir;
public:
	static i3CollideeLine* Singleton()
	{
		typedef i3CollideeLine* (__stdcall * tgetHandler)();
		tgetHandler getHandler = (tgetHandler)((DWORD)GetProcAddress(i3SceneDx, /*?new_object_fun@i3CollideeLine@@SAPAV1@XZ*/XorStr<0xD5, 42, 0xC3DBDC62>("\xEA\xB8\xB2\xAF\x86\xB5\xB9\xB6\xB8\xBD\xAB\xBF\x87\x97\x8D\xA4\x8C\xD5\xA4\x87\x85\x86\x82\x88\x88\x8B\xA3\x99\x9F\x97\xB3\xB4\xA6\xB7\xA7\xB9\xAF\xCB\xBB\xA4\xA7" + 0xC3DBDC62).s));
		return (i3CollideeLine*)(getHandler());
	}
};

class i3PhysixHitResult
{
public:
	char _0x0000[28];
	D3DXVECTOR3 FinalPos;
	float Distance;
};

class dwPhtsX {
public:
	void* i3PhysixContext;
};

class i3RenderContext
{
public:
	D3DXMATRIX* GetProjectMatrix()
	{
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(i3GfxDx, /*?GetProjectMatrix@i3RenderContext@@QAEPATMATRIX@@XZ*/XorStr<0x27, 52, 0xF8A010B3>("\x18\x6F\x4C\x5E\x7B\x5E\x42\x44\x4A\x53\x45\x7F\x52\x40\x47\x5F\x4F\x78\x50\x09\x69\x59\x53\x5A\x5A\x32\x02\x2D\x2D\x30\x20\x3E\x33\x08\x09\x1B\x0A\x09\x1D\x0F\x1B\x1D\x10\x06\x01\x1D\x0D\x16\x17\x00\x03" + 0xF8A010B3).s)))(this);
	}
	D3DXMATRIX* GetWorldMatrix() {
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(i3GfxDx, /*?GetWorldMatrix@i3RenderContext@@QAEPATMATRIX@@XZ*/XorStr<0xD8, 50, 0x5EABD911>("\xE7\x9E\xBF\xAF\x8B\xB2\xAC\xB3\x84\xAC\x83\x97\x96\x8C\x9E\xA7\x81\xDA\xB8\x8E\x82\x89\x8B\x9D\xB3\x9E\x9C\x87\x91\x8D\x82\xB7\xB8\xA8\xBB\xBE\xAC\xBC\xAA\xB2\x41\x55\x50\x4A\x5C\x45\x46\x5F\x52" + 0x5EABD911).s)))(this);
	}
	D3DXMATRIX* GetViewMatrix() {
		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(i3GfxDx, /*?GetViewMatrix@i3RenderContext@@QAEPATMATRIX@@XZ*/XorStr<0xA3, 49, 0xF6D3D3AA>("\x9C\xE3\xC0\xD2\xF1\xC1\xCC\xDD\xE6\xCD\xD9\xDC\xC6\xC8\xF1\xDB\x80\xE6\xD0\xD8\xD3\xDD\xCB\xF9\xD4\xD2\xC9\xDB\xC7\xB4\x81\x82\x92\x85\x80\x96\x86\x9C\x84\x8B\x9F\x9E\x84\x96\x8F\x90\x89\x88" + 0xF6D3D3AA).s)))(this);
	}
};

class i3SceneObject
{
private:
	typedef D3DXMATRIX * (__thiscall * oFindCacheMatrixByName)(i3SceneObject *, const char *);
	typedef int(__thiscall * oFindBoneIndexByName)(i3SceneObject *, const char *);
public:
	int FindBoneIndexByName(const char * bonename) {
		static const oFindBoneIndexByName pFineBoneIndexByName = (oFindBoneIndexByName)GetProcAddress(i3SceneDx, /*?FindBoneIndexByName@i3SceneObject@@QBEHPBD@Z*/XorStr<0xB3, 46, 0x965DB1D9>("\x8C\xF2\xDC\xD8\xD3\xFA\xD6\xD4\xDE\xF5\xD3\xDA\xDA\xB8\x83\xBB\x8D\xA5\xA8\xA3\x87\xA1\xFA\x99\xA8\xA9\xA3\xAB\x80\xB2\xBB\xB7\xB0\xA0\x95\x96\x86\x9A\x9C\x92\x8B\x9E\x99\x9E\x85" + 0x965DB1D9).s);
		return pFineBoneIndexByName(this, bonename);
	}
	D3DXMATRIX * FindCacheMatrixByName(const char * bonename) {
		static const oFindCacheMatrixByName pFindCacheMatrixByName = (oFindCacheMatrixByName)GetProcAddress(i3SceneDx, /*?FindCacheMatrixByName@i3SceneObject@@QBEPATMATRIX@@PBD@Z*/XorStr<0xEA, 58, 0xFB82033F>("\xD5\xAD\x85\x83\x8A\xAC\x91\x92\x9A\x96\xB9\x94\x82\x85\x91\x81\xB8\x82\xB2\x9C\x93\x9A\x40\x68\x31\x50\x67\x60\x68\x62\x47\x6B\x60\x6E\x6F\x79\x4E\x4F\x41\x53\x57\x43\x55\x41\x5B\x56\x4C\x4B\x53\x43\x5C\x5D\x4E\x5D\x64\x61\x78" + 0xFB82033F).s);
		return (D3DXMATRIX *)pFindCacheMatrixByName(this, bonename);
	}
};

class i3GameNode
{
private:
	typedef i3GameNode * (__thiscall  * oGetFirstChild)(i3GameNode *);
public:

	i3GameNode * getFirstChild(void) {
		static const oGetFirstChild pGetFirstChild = (oGetFirstChild)GetProcAddress(i3FrameworkDx, /*?getFirstChild@i3GameNode@@QAEPAV1@XZ*/XorStr<0x86, 38, 0x32DCFC4A>("\xB9\xE0\xED\xFD\xCC\xE2\xFE\xFE\xFA\xCC\xF8\xF8\xFE\xF7\xD4\xFC\xA5\xD0\xF9\xF4\xFF\xD5\xF3\xF9\xFB\xDF\xE0\xF0\xE3\xE6\xF4\xE4\xF0\x96\xE8\xF1\xF0" + 0x32DCFC4A).s);
		return (i3GameNode *)pGetFirstChild(this);
	}
};

class i3GameObj
{
private:
	typedef i3SceneObject * (__thiscall * oGetSceneObject)(i3GameObj *);
	typedef D3DXVECTOR3 * (__thiscall * oGetPos)(i3GameObj *);
public:
	i3SceneObject * getSceneObject(void) {
		static const oGetSceneObject pGetSceneObject = (oGetSceneObject)GetProcAddress(i3FrameworkDx, /*?getSceneObject@i3GameObj@@QBEPAVi3SceneObject@@XZ*/XorStr<0x20, 51, 0x21681C6B>("\x1F\x46\x47\x57\x77\x46\x43\x49\x4D\x66\x48\x41\x49\x4E\x5A\x6F\x59\x02\x75\x52\x59\x50\x79\x55\x52\x79\x7A\x6A\x7E\x78\x6E\x7E\x16\x28\x71\x10\x27\x20\x28\x22\x07\x2B\x20\x2E\x2F\x39\x0E\x0F\x08\x0B" + 0x21681C6B).s);
		return (i3SceneObject *)pGetSceneObject(this);
	}
	D3DXVECTOR3 * getPos(void) {
		static const oGetPos pGetPos = (oGetPos)GetProcAddress(i3FrameworkDx, /*?GetPos@i3GameObj@@QAEPATVEC3D@@XZ*/XorStr<0x95, 35, 0xA85CE5B3>("\xAA\xD1\xF2\xEC\xC9\xF5\xE8\xDC\xF4\xAD\xD8\xC1\xCC\xC7\xEC\xC6\xCF\xE6\xE7\xF9\xE8\xEF\xFB\xED\xF9\xF8\xEA\xF3\x82\xF6\xF3\xF4\xED\xEC" + 0xA85CE5B3).s);
		return (D3DXVECTOR3 *)pGetPos(this);
	}
};

class CGame
{
private:
	//
	i3RenderContext * GetRenderContext()
	{
		return (i3RenderContext *)(*(DWORD*)(GetProcAddress(i3GfxDx, /*?g_pRenderContext@@3PAVi3RenderContext@@A*/XorStr<0xB8, 42, 0xC8ED595D>("\x87\xDE\xE5\xCB\xEE\xD8\xD0\xDB\xA5\xB3\x81\xAC\xAA\xB1\xA3\xBF\xBC\x89\x8A\xF8\x9C\x8C\x98\xA6\xE3\x83\xB7\xBD\xB0\xB0\xA4\x94\xB7\xB7\xAE\xBE\xA4\xA9\x9E\x9F\xA1" + 0xC8ED595D).s)));
	}
};

int GetTeam(int MyTeam)
{
	for (int i = 0; i < 16; i += 2)
		if (i == MyTeam) return 2;
	for (int i = 1; i < 16; i += 2)
		if (i == MyTeam) return 1;
	return -1;
}
float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}
#include "stdafx.h"

class FunctionT
{
private:
	DWORD ADR_GAMECONTEXT = 0x91E3A0; //8B 0D ?? ?? ?? ?? 33 C0 85 DB 0F 95 C0 40 50 FF
	DWORD OFS_TEAM = 0x17EF4; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

	DWORD ADR_CHARACTERPOINTER = 0x91EB80; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
	DWORD OFS_CHARACTERSIZE = 0x0E0; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 6

	//i3GfxGx.dll
	DWORD ADR_RESULTDEVICE = 0x12C4DC; // i3GfxDx.dll + ?g_pRenderContext@@3PAVi3RenderContext@@A

	//MEMORY
	DWORD ASM_GETCURHP = 0x4690B; //int __thiscall CGameCharaBase::getCurHP(void)

	//BONE MATRIXS
	DWORD ASM_ARRAYBONES = 0x3D9BE; //m_Bone
	DWORD OFS_ARRAYBONES = 0x1F8;
	DWORD ASM_BONECONTEXT = 0x3DA58; //m_pBoneContext
	DWORD OFS_BONECONTEXT = 0x268;

	//AIMBOT
	DWORD ADR_AIMBULLET = 0x6E78C0; //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
	DWORD ASM_VEC3DEQUAL = 0x40F0; //i3MathDx.dll + VEC3D::operator=(VEC3D const &)
	DWORD ASM_VEC3DMINUS = 0x45F0; //i3MathDx.dll + VEC3D::operator-(VEC3D const &)

	//ISVISLBLE
	DWORD ResultpPhysixCtx = 0x241410; //?g_pPhysixCtx@@3PAVi3PhysixContext@@A
	DWORD ResultSetStart = 0x25300; //?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z
	DWORD ResultSetEnd = 0x250C0;	//?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
	DWORD ResultInitialize = 0x20100; //??0i3CollideeLine@@QAE@XZ
	DWORD ResultRayClass = 0xA0760; //?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z

	//Recoil
	DWORD RecoildTest1 = 0x7470C4; //RecoilHorzAngle
	DWORD RecoildTest2 = 0x747110; //RecoilVertAngle
	DWORD Deviation_Max = 0x747130; //Deviation_Max

	class RenderData
	{
	public:
		char _0x0000[0x8B0];
		D3DXMATRIX ViewMatrix; //0x8B0
		D3DXMATRIX ProjMatrix; //0x8F0
		char _0x0001[0x40]; //0x930
		D3DXMATRIX World; //0x970
		char _0x0918[0x4A24]; //0x5394
		LPDIRECT3DDEVICE9 pDevice; //0x53D4
	};

	//IsVisible Class
	class i3CollideeLine
	{
	public:
		D3DXVECTOR3 vTemp;
		D3DXVECTOR3 vStart;
		D3DXVECTOR3 vEnd;
		D3DXVECTOR3 vDir;
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

private:
	D3DMATRIX* getArrayBones(int ptr)
	{
		auto Func = (int(__thiscall*)(DWORD))(Globals->Base.Address + ASM_ARRAYBONES);
		return (D3DMATRIX*)Func((DWORD)ptr + OFS_ARRAYBONES);
	}

	int getBoneContext(int ptr)
	{
		auto Func = (int(__thiscall*)(int))(Globals->Base.Address + ASM_BONECONTEXT);
		return Func(ptr + OFS_BONECONTEXT);
	}

	int getCurHP(int ptr)
	{
		auto Func = (int(__thiscall*)(int))*(DWORD*)(Globals->Base.Address + ASM_GETCURHP);
		return Func(ptr);
	}

private:
	int getMyIndex()
	{
		auto pLocal = *(DWORD*)Globals->Base.Address + ADR_GAMECONTEXT;
		if (!pLocal)
			return 0;
		return *(BYTE*)pLocal + OFS_TEAM;
	}

	int GetPlayerByID(int index)
	{
		return (*(DWORD*)(*(DWORD*)(Globals->Base.Address + ADR_CHARACTERPOINTER) + 0x14 + OFS_CHARACTERSIZE * index));
	}
private:
	int GetUserHP(int index)
	{
		auto Player = GetPlayerByID(index);
		if (!Player)
			return 0;
		return getCurHP(Player);
	}

	bool isAlive(int index)
	{
		if (GetUserHP(index) > 1)
			return true;
		return false;
	}

	int GetTeam(int MyTeam)
	{
		for (int i = 0; i < 16; i += 2)
			if (i == MyTeam) return 2;
		for (int i = 1; i < 16; i += 2)
			if (i == MyTeam) return 1;
		return -1;
	}

	bool GetUserBone(D3DXVECTOR3 &Out, int index, int BoneIndex)
	{
		auto Player = GetPlayerByID(index);
		if (Player)
		{
			auto BoneContext = getBoneContext(Player);
			if (BoneContext)
			{
				auto BoneArray = getArrayBones(BoneContext);
				Out.x = *(float*)(DWORD)(BoneArray)+ 0x30 + (0x40 * BoneIndex);
				Out.y = *(float*)(DWORD)(BoneArray)+ 0x34 + (0x40 * BoneIndex);
				Out.z = *(float*)(DWORD)(BoneArray)+ 0x38 + (0x40 * BoneIndex);
				return true;
			}
		}
		return false;
	}

	bool W2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
	{
		auto i3GfxDx = (DWORD)GetModuleHandleA("i3GfxDx.dll");
		if (!i3GfxDx)
			return false;

		auto *pRC = *(RenderData**)(i3GfxDx + ADR_RESULTDEVICE);
		if (!pRC)
			return false;

		D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
		D3DXVECTOR3 vScreen;

		D3DVIEWPORT9 Viewport;
		pDevice->GetViewport(&Viewport);

		Viewport.X = Viewport.Y = 0;
		Viewport.MinZ = 0;
		Viewport.MaxZ = 1;
		D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->ProjMatrix, &pRC->ViewMatrix, &pRC->World);

		if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
		{
			PlayerScaled.x = vScreen.x;
			PlayerScaled.y = vScreen.y;
			PlayerScaled.z = vScreen.z;
			return true;
		}
		return false;
	}

	bool isVisible(int iSlot)
	{
		if (iSlot == -1)
			return false;
		DWORD dwi3Scenedx = (DWORD)GetModuleHandleA("i3SceneDx.dll");
		dwPhtsX *pViewer = (dwPhtsX*)(dwi3Scenedx + ResultpPhysixCtx); //?g_pPhysixCtx@@3PAVi3PhysixContext@@A
		DWORD dwSetStart = (dwi3Scenedx + ResultSetStart); //?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z
		DWORD dwSetEnd = (dwi3Scenedx + ResultSetEnd); //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
		DWORD dwInitialize = (dwi3Scenedx + ResultInitialize); //??0i3CollideeLine@@QAE@XZ
		DWORD dwReyClass = (dwi3Scenedx + ResultRayClass); //?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z
		i3CollideeLine Line;
		i3CollideeLine* cLine;
		void *PhysX = pViewer->i3PhysixContext;
		cLine = &Line;
		D3DXVECTOR3 vMe, vEnemy;
		DWORD dwPhysix;
		GetUserBone(vMe, getMyIndex(), 7);
		GetUserBone(vEnemy, iSlot, 7);
		Line.vStart.y += 0.1f;
		float distance = CalcDistance(vEnemy, vMe);

		_asm
		{
			mov ecx, [cLine];
			call[dwInitialize];
			lea edx, vMe;
			push edx;
			mov ecx, [cLine];
			call[dwSetStart];
			lea eax, vEnemy;
			push eax;
			mov ecx, [cLine];
			call[dwSetEnd];
			push - 1;
			push 0;
			push[cLine];
			mov ecx, [PhysX];
			call dword ptr ds : [dwReyClass];
			mov[dwPhysix], eax;
		}
		i3PhysixHitResult *pX = (i3PhysixHitResult*)dwPhysix;

		if (pX == 0)
			return false;
		if (pX->Distance < distance)
			return false;

		return true;
	}
private:
	float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
	{
		return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
			((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
			((VecA.z - VecB.z) * (VecA.z - VecB.z)));
	}

public:
	DWORD ADR_CHECK = ADR_CHARACTERPOINTER;
	VOID CallESP(LPDIRECT3DDEVICE9 pDevice);

};

extern FunctionT* Function;

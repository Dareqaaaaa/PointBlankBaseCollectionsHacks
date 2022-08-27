//PointBlank.exe
DWORD ADR_GAMECONTEXT = 0x91E3A0; //8B 0D ?? ?? ?? ?? 33 C0 85 DB 0F 95 C0 40 50 FF
DWORD OFS_TEAM = 0x17EF4; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

DWORD ADR_CHARACTERPOINTER = 0x91EB80; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
DWORD OFS_CHARACTERSIZE = 0x0E0; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 6

//i3GfxGx.dll
DWORD ADR_RESULTDEVICE = 0x12C4DC; // i3GfxDx.dll + ?g_pRenderContext@@3PAVi3RenderContext@@A

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

//Misc Class
class CLocalPlayerID
{
public:
	BYTE ID;
};


int GetTeam(int MyTeam)
{
	for (int i = 0; i < 16; i += 2)
		if (i == MyTeam) return 2;
	for (int i = 1; i < 16; i += 2)
		if (i == MyTeam) return 1;
	return -1;
}

int GetMyIndex()
{
	DWORD InfBase = *(DWORD *)(dwBaseAddress + ADR_GAMECONTEXT);
	CLocalPlayerID *LocID = (CLocalPlayerID *)(InfBase + OFS_TEAM);
	return LocID->ID;
}

bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
{
	DWORD DWGFX = (DWORD)GetModuleHandleA("i3GfxDx.dll");
	if (!DWGFX)
		return false;

	RenderData *pRC = *(RenderData**)(DWGFX + ADR_RESULTDEVICE);
	if (!pRC)
		return false;

	if (!pRC->ProjMatrix || !pRC->ViewMatrix || !pRC->World)
		return false;

	D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
	D3DXVECTOR3 vScreen;
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

float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}
/*
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
	GetUserBone(vMe, GetMyIndex(), 7);
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

int GetTarget()
{
	int Result = -1;
	float fMaxDistance = 100.0f;
	D3DXVECTOR3 PlayerEnd, LocPlayer;
	for (int index = 0; index < 16; index++)
	{
		if (GetMyIndex() != index && GetMyIndex() % 2 != index % 2)
		{
			if (isVisible(index))
			{
				if (isAlive(index))
				{
					GetUserBone(LocPlayer, GetMyIndex(), 7);
					GetUserBone(PlayerEnd, index, 7);
					if (CalcDistance(LocPlayer, PlayerEnd) < fMaxDistance)
					{
						fMaxDistance = CalcDistance(PlayerEnd, LocPlayer);
						Result = index;
					}
				}
			}
		}
	}
	return Result;
}*/


HMODULE i3FrameworkDx = GetModuleHandle("i3FrameworkDx.dll"),
i3MathDx = GetModuleHandle("i3MathDx.dll"),
i3SceneDx = GetModuleHandle("i3SceneDx.dll");


class i3SceneObject
{
private:
	typedef D3DXMATRIX * (__thiscall * oFindCacheMatrixByName)(i3SceneObject *, const char *);
	typedef int(__thiscall * oFindBoneIndexByName)(i3SceneObject *, const char *);
public:
	int FindBoneIndexByName(const char * bonename) {
		static const oFindBoneIndexByName pFineBoneIndexByName = (oFindBoneIndexByName)GetProcAddress(i3SceneDx, "?FindBoneIndexByName@i3SceneObject@@QAEHPBD@Z");
		return pFineBoneIndexByName(this, bonename);
	}
	D3DXMATRIX * FindCacheMatrixByName(const char * bonename) {
		static const oFindCacheMatrixByName pFindCacheMatrixByName = (oFindCacheMatrixByName)GetProcAddress(i3SceneDx, "?FindCacheMatrixByName@i3SceneObject@@QAEPATMATRIX@@PBD@Z");
		return (D3DXMATRIX *)pFindCacheMatrixByName(this, bonename);
	}
};

class i3GameObj
{
private:
	typedef i3SceneObject * (__thiscall * oGetSceneObject)(i3GameObj *);//4116
	typedef D3DXVECTOR3 * (__thiscall * oGetPos)(i3GameObj *);//1351
public:
	i3SceneObject * getSceneObject(void) {
		static const oGetSceneObject pGetSceneObject = (oGetSceneObject)GetProcAddress(i3FrameworkDx, "?getSceneObject@i3GameObj@@QAEPAVi3SceneObject@@XZ");
		return (i3SceneObject *)pGetSceneObject(this);
	}
	D3DXVECTOR3 * getPos(void) {
		static const oGetPos pGetPos = (oGetPos)GetProcAddress(i3FrameworkDx, "?GetPos@i3GameObj@@QAEPATVEC3D@@XZ");
		return (D3DXVECTOR3 *)pGetPos(this);
	}
};

class GameObjectManager
{
public:
	i3GameObj* GetCharaByID(int index)
	{
		return (i3GameObj*)(*(DWORD*)(*(DWORD*)(dwBaseAddress + ADR_CHARACTERPOINTER) + 0x14 + OFS_CHARACTERSIZE * index));
	}
}GameObject;


const char * bones[] = {
	"Neck",			//0
	"Head",			//1
	"Spine1",		//2
	"Pelvis",		//3
	"L Clavicle",	//4
	"R Clavicle",	//5
	"L UpperArm",	//6
	"L Forearm",	//7
	"L Hand",		//8
	"L Thumb1",		//9
	"R UpperArm",	//10
	"R Forearm",	//11
	"R Hand",		//12
	"R Thumb1",		//13
	"L Thigh",		//14
	"L Calf",		//15
	"L Foot",		//16
	"L Toe",		//17
	"R Thigh",		//18
	"R Calf",		//19
	"R Foot",		//20
	"R Toe"			//21
};

bool GetBoneMatrix(D3DXVECTOR3 &Out, const char * bonename, int index)
{
	auto pPlayer = GameObject.GetCharaByID(index);
	if (!pPlayer) return false;

	auto pSceneObject = pPlayer->getSceneObject();
	if (!pSceneObject) return false;

	auto pFindBoneIndexByName = pSceneObject->FindBoneIndexByName(bonename);
	if (!pFindBoneIndexByName) return false;

	auto pFindCacheMatrixByName = pSceneObject->FindCacheMatrixByName(bonename);
	if (!pFindCacheMatrixByName) return false;

	Out.x = pFindCacheMatrixByName->_41;
	Out.y = pFindCacheMatrixByName->_42;
	Out.z = pFindCacheMatrixByName->_43;

	return true;
}
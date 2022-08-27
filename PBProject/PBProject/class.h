/**************** Variables ******************/
class RenderContext; 
class RenderData; 
DWORD DWGFX = (DWORD)GetModuleHandleA("i3GfxDx.dll"); 
RenderContext *pRC = (RenderContext*)(DWGFX + 0x112DA4); 
D3DVIEWPORT9 Viewport;

class RenderContext 
{ 
public:
	RenderData* pRenderData;
};

class RenderData
{ 
public:
	char _0x0000[0x8B0];
    D3DXMATRIX ViewMatrix; //0x8B0
    D3DXMATRIX ProjMatrix; //0x8F0
	D3DXMATRIX World; //0x930
    char _0x0918[0x49E8];
    LPDIRECT3DDEVICE9 pDevice; //0x5358
};

/******** Misc Start **********/
class CLocalPlayerID
{
public:
	BYTE ID;
};

class CDeathPlayer
{
public:
	BYTE Death[16];
};

struct CNames
{
    char szNames[33];
};

/*********** IsVisible Start **************/
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

class dwPhtsX{
public:
	void* i3PhysixContext;
};

/*********** IsVisible End **************/
/*
int GetCharaIndex()//"void __thiscall CGameContext::setMySlot"
{
	DWORD InfBase = *(DWORD *)g_pGameContext;// g_pGameContext 
	CLocalPlayerID *LocID = (CLocalPlayerID *) (InfBase + 0x2A0BC); 
	return LocID->ID;
}

BYTE GetUserLife(int index)//void __thiscall CGameContext::setUserDeath(int,bool);
{
	DWORD InfBase = *(DWORD *)g_pGameContext;//g_pGameContext 
	CDeathPlayer *Life = (CDeathPlayer *) (InfBase + 0x2CC14);
	return Life->Death[index];
}

D3DXVECTOR3 GetUserVector(DWORD i)//struct GAMEINFO_CHARACTER *__thiscall CGameContext::getGameInfo_Chara
{
	DWORD dwBasePlayer = *(PDWORD)(g_pGameContext);
	CPlayers *pPlayer = (CPlayers*)((*(PDWORD)(dwBasePlayer + 0x4 * i + 0x281CC)) + 0x64);
	return pPlayer->pos;
}
*/

int GetTeam(char MyTeam) 
{ 
	for(int i = 0; i < 16; i+=2) 
		if(i == MyTeam) return 2; 
	for(int i = 1; i < 16; i+=2) 
		if(i == MyTeam) return 1; 
	return -1; 
}

bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
	D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
    D3DXVECTOR3 vScreen;
	pDevice->GetViewport(&Viewport);
	Viewport.X = Viewport.Y = 0;
    Viewport.MinZ     = 0;
    Viewport.MaxZ     = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
  
	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
	{
		PlayerScaled.x = vScreen.x;
		PlayerScaled.y = vScreen.y;
		PlayerScaled.z = vScreen.z;
		return true; 
	}
	return false;
}

class CGameCharaBoneContextPH
{
public:

	int getgetArrayBonesDecode(DWORD var)
	{
		int var1;
		auto Func = (char(__thiscall*)(DWORD, int*, int, int))0x4F13D0;
		Func(var, &var1, 4, 0);
		return var1;
	}

	D3DMATRIX* getArrayBones()
	{
		return (D3DMATRIX*)getgetArrayBonesDecode((DWORD)this + 0x118);
	}
};

class CGameCharaBasePH
{
public:
	int getCurHP()
	{
		auto Func = (int(__thiscall*)(CGameCharaBasePH*))0x4FAC80;
		return Func(this);
	}

	int getBoneContextDecode(CGameCharaBasePH* var)
	{
		int var1;
		auto Func = (char(__thiscall*)(CGameCharaBasePH*, int*, int, int))0x4F1BE0;
		Func(var, &var1, 4, 0);
		return var1;
	}

	CGameCharaBoneContextPH* getBoneContext()
	{
		return (CGameCharaBoneContextPH*)getBoneContextDecode(this + 0x284);
	}
};

class CGameCharaManagerPH
{
public:
	CGameCharaBasePH* GetCharaByID(int index)
	{
		return (CGameCharaBasePH*)(*(DWORD*)(*(DWORD*)(0xE3EC70) + 0x14 + 0x1AC * index));
	}
}CGame;

inline bool GetUserBone(D3DXVECTOR3 &Out, int index, int BoneIndex) 
{
	CGameCharaBasePH* Game = CGame.GetCharaByID(index);
	if(Game != NULL)
	{
		Out.x = *(float*)((DWORD)(Game->getBoneContext()->getArrayBones()) + 0x30 + (0x40 * BoneIndex));
		Out.y = *(float*)((DWORD)(Game->getBoneContext()->getArrayBones()) + 0x34 + (0x40 * BoneIndex));
		Out.z = *(float*)((DWORD)(Game->getBoneContext()->getArrayBones()) + 0x38 + (0x40 * BoneIndex));
		return true;
	}
	return false;
}
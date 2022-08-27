#pragma once
class function
{
public:
	function();
	~function();


	void Init();
	void CallEsp(LPDIRECT3DDEVICE9 pDevice);
	void CallAimBullet(LPDIRECT3DDEVICE9 pDevice);
	void CallAimbot(LPDIRECT3DDEVICE9 pDevice);
	void CallMemory();

	DWORD dwSetEndCheck;
	float fX;
	float fY;
	float fZ;
	int BulletEnable;
	void AimCheck(bool &isTrue);

private:
	DWORD ADR_GAMECONTEXT;
	DWORD OFS_TEAM; //8B 80 ?? ?? ?? ?? 75 14 50 8B CE E8 ?? ?? ?? ??

	DWORD OFS_TICKET; //D9 84 81 ?? ?? ?? ?? 8B 4D F4 64 89 0D 00 00 00 00 //float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum
	DWORD OFS_TICKETSIZE; // imul    eax, edi, 48h "Search OFS_TICKET"

	DWORD ADR_CHARACTERPOINTER; //8B 0D ?? ?? ?? ?? FF B0 ?? ?? ?? ??
	DWORD OFS_CHARACTERSIZE; //55 8B EC 8B 45 08 83 F8 0F 77 ?? 69 C0 ?? ?? ?? ?? + 13 //IMUL EAX,EAX,10C

	DWORD ADR_PLAYERPOINTER; //39 3D ?? ?? ?? ?? 75 10 6A 01 8B CE
	DWORD OFS_FASTSHOT;

	//Aimbot
	DWORD CollideeLine; // pEnd != nullptr || PointBlank.exe || LEA EDI,DWORD PTR DS:[ESI+48C]
	DWORD CollideeLineEnd; //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z || i3ScenceDx.dll || 
	DWORD CollideeLineStart; //?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z || i3ScenceDx.dll || 
	DWORD VEC3DSetEnd; //??4VEC3D@@QAEAAT0@ABT0@@Z || i3MathDx.dll

	//OPK
	DWORD SetPos; //?SetPos@i3GameObj@@QAEXPATVEC3D@@@Z || i3FrameworkDx.dll

	DWORD ADR_NoRecoil1; //55 8B EC 51 51 53 57 8B F9 8D 5F 28 8B CB E8 ?? ?? ?? ??
	DWORD ADR_NoRecoil2; //55 8B EC 51 51 53 57 8B F9 8D 5F 28 8B CB E8 ?? ?? ?? ??

	void DrawBoneLine(int index, const char * Start, const char * End, DWORD Color, LPDIRECT3DDEVICE9 pDevice);
	bool GetBoneMatrix(D3DXVECTOR3 &Out, const char * bonename, int index);
	bool isAlive(int index);
	bool isVisible(int iSlot);
	bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled);
	int GetTarget();
	int GetPlayerByIndex(int index);
	int GetMyIndex();
	float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB);
};

extern function pFunction;
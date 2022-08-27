#pragma warning(disable:4305)
/*
bool BulletEnable= false;
float fX = 0x0A, fY = 0x01, fZ = 0x0A;
_declspec(naked)void i3CollideeEnd()
{
	_asm
	{
		cmp [BulletEnable], 0;
		je Skip;
		mov eax, [esp+4];
		mov [eax], edx;
		mov edx, [fX];
		mov [eax+0], edx;
		mov edx, [fY];
		mov [eax+4],edx;
		mov edx, [fZ];
		mov [eax+8], edx;
		mov edx, [ecx+8];
Skip:
		jmp Original;
		nop;
Original:
		mov eax, [esp+4];
		fld dword ptr [eax];
		fstp dword ptr [ecx+0x18];
		fld dword ptr [eax+0x04];
		fstp dword ptr [ecx+0x1C];
		fld dword ptr [eax+0x08];
		fstp dword ptr [ecx+0x20];
		fld dword ptr [ecx+0x18];
		fsub dword ptr [ecx+0x0C];
		fstp dword ptr [ecx+0x24];
		fld dword ptr [ecx+0x1C];
		fsub dword ptr [ecx+0x10];
		fstp dword ptr [ecx+0x28];
		fld dword ptr [ecx+0x20];
		fsub dword ptr [ecx+0x14];
		fstp dword ptr [ecx+0x2C];
		ret 4;
	}
}

float CalcDistance(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
		((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}

bool VisibleTarget(int iSlot) 
{ 
	if(iSlot == -1)
		return false;
	DWORD dwi3Scenedx = (DWORD)GetModuleHandleA("i3SceneDx.dll");
	dwPhtsX *pViewer = (dwPhtsX*)(dwi3Scenedx + ResultpPhysixCtx); //?g_pPhysixCtx@@3PAVi3PhysixContext@@A
	DWORD dwSetStart = (dwi3Scenedx + ResultSetStart); //?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z
	DWORD dwSetEnd = (dwi3Scenedx + ResultSetEnd); //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
	DWORD dwInitialize = (dwi3Scenedx + ResultInitialize ); //??0i3CollideeLine@@QAE@XZ
	DWORD dwReyClass = (dwi3Scenedx + ResultRayClass); //?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z
	i3CollideeLine Line; 
	i3CollideeLine* cLine; 
	void *PhysX = pViewer->i3PhysixContext; 
	cLine = &Line; 
	D3DXVECTOR3 vMe, vEnemy; 
	DWORD dwPhysix; 
	vMe = GetUserVector(GetCharaIndex());
	vEnemy = GetUserVector(iSlot);
	Line.vStart.y += 0.1f; 
	float distance = CalcDistance(vEnemy, vMe); 

	_asm
	{ 
		mov ecx, [cLine]; 
		call [dwInitialize];
		lea edx, vMe;
		push edx;
		mov ecx, [cLine];
		call [dwSetStart];
		lea eax, vEnemy; 
		push eax; 
		mov ecx, [cLine];
		call [dwSetEnd];
		push -1;
		push 0;
		push [cLine];
		mov ecx, [PhysX];
		//i3PhysixContext::RaycastClosest
		//?RaycastClosest@i3PhysixContext@@QAEPAU_tagi3PhysixHitResult@@PAVi3CollideeLine@@HI@Z
		call dword ptr ds:[dwReyClass];
		mov [dwPhysix], eax;
	}
	i3PhysixHitResult *pX = (i3PhysixHitResult*)dwPhysix; 

	if(pX == 0) 
		return false; 
	if(pX->Distance < distance) 
		return false;

	return true;
}

int AutomaticTarget()
{
	int Result = -1;
	float NearDistance = 1000.0f;
	for(int i = 0; i<=16; i++)
	{
		if (!GetUserLife(i) && GetCharaIndex() != i && VisibleTarget(i))
		{
			if (GetCharaIndex() %2 != i % 2)
			{
				if(CalcDistance(GetUserVector(GetCharaIndex()), GetUserVector(i)) < NearDistance)
				{
					NearDistance = CalcDistance(GetUserVector(GetCharaIndex()), GetUserVector(i));
					Result = i;
				}
			}
		}
	}
	return Result;
}

void HeadAim()
{
	DWORD pPlayer  = *(DWORD*)g_pPlayer; 
	if(pPlayer != 0x0000)
	{
		int AimSlot = AutomaticTarget();
		if(AimSlot != -1)
		{
			BulletEnable = true;
			fX = GetUserVector(AimSlot).x;
			fY = 1.5f + GetUserVector(AimSlot).y;
			fZ = GetUserVector(AimSlot).z;
		}else BulletEnable = false;
    }
}

bool Aim_true = false;
void Thread_Aimbot()
{
	DWORD InSnce = (DWORD) GetModuleHandleA("i3SceneDx.dll");
	if(Aim_true == false)
	{
		Tools.DetourFunc((PBYTE) InSnce + ResultSetEnd, (PBYTE)i3CollideeEnd, 0xE9); //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
		Aim_true = true;
	}
}

VOID DoAimbot()
{
	Thread_Aimbot();
	if(opt.aimbot.aimbot){HeadAim();}
}


class CGameCharaBoneContext
{
public:
	D3DMATRIX* getArrayBones()
	{
		auto Func = (D3DMATRIX* (__thiscall*)(DWORD))0x528950;// void __thiscall CGameCharaBoneContext:: 
		return Func((DWORD)this + 0x118);
	}
};

class CGameCharaBase
{
public:
	int getCurHP()
	{
		auto Func = (int(__thiscall*)(CGameCharaBase*))0x52C2A0;//int __thiscall CGameCharaBase::getCurHP // 
		return Func(this);
	}
	CGameCharaBoneContext* getBoneContext()
	{
		auto Func = (CGameCharaBoneContext* (__thiscall*)(CGameCharaBase*))0x4FC7B0;// 4 acima class i3Texture *__thiscall CGameCharaManager::GetBeretEmblemTexture(enum ITEM_RES_ID,enum ETextureKind)
		return Func(this);
	}
};

class CGameCharaManager
{
public:
	CGameCharaBase* GetCharaByNetId(int IdxSlot)
	{
		auto Func = (CGameCharaBase* (__thiscall*)(CGameCharaManager*, int))0x4BF650;// class CGameCharaBase *__thiscall CGameCharaManager::getCharaByNet
		return Func(this, IdxSlot);
	}
	static CGameCharaManager* Singleton()
	{
		return (CGameCharaManager*)(*(PDWORD)0x000000);
	}
};

inline bool GetUserBone(D3DXVECTOR3 &Out, int index, int BoneIndex) // Função meio polemica 
{
	__try
	{
		Out.x = *(float*)((DWORD)(CGameCharaManager::Singleton()->GetCharaByNetId(index)->getBoneContext()->getArrayBones()) + 0x30 + (0x40 * BoneIndex));
		Out.y = *(float*)((DWORD)(CGameCharaManager::Singleton()->GetCharaByNetId(index)->getBoneContext()->getArrayBones()) + 0x34 + (0x40 * BoneIndex));
		Out.z = *(float*)((DWORD)(CGameCharaManager::Singleton()->GetCharaByNetId(index)->getBoneContext()->getArrayBones()) + 0x38 + (0x40 * BoneIndex));
	return true;
	}
__except (EXCEPTION_EXECUTE_HANDLER){}
}*/
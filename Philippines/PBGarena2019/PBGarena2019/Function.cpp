#include "stdafx.h"

FunctionT * Function = new FunctionT();


void FunctionT::CallESP(LPDIRECT3DDEVICE9 pDevice)
{
	auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
	if (!pLocal) return;

	for (int i = 0; i < 16; i++)
	{
		if (isAlive(i) && GetMyIndex() != i)
		{
			DWORD EspColor = (GetMyIndex() % 2 != i % 2) ? (isVisible(i)) ? Green : Red : Blue;

			//Head
			D3DXVECTOR3 vWorldHead, vScreenHead;
			if (GetBoneMatrix(vWorldHead, Utils->bones[1], i))
			{
				if (WorldToScreen(vWorldHead, vScreenHead))
				{
					if (Utils->esp.espbone)
						EspDrawBone(i, EspColor, pDevice);

					if (Utils->esp.espline)
						Menu->DrawLine(pDevice, Menu->Viewport.Width / 2, Menu->Viewport.Height, (int)vScreenHead.x, (int)vScreenHead.y, 1.0f, EspColor);
				}

				//Foot
				D3DXVECTOR3 vWorlFoot, vScreenFoot;
				if (GetBoneMatrix(vWorlFoot, Utils->bones[16], i))
				{
					if (WorldToScreen(vWorlFoot, vScreenFoot))
					{
						if (Utils->esp.espdistance)
						{
							D3DXVECTOR3 vMyHead;
							if (GetBoneMatrix(vMyHead, Utils->bones[1], GetMyIndex()))
							{
								int distance = CalcDistance(vMyHead, vWorldHead);
								char buff[20];
								sprintf_s(buff, "[%d] M", distance);
								Menu->WriteText(vScreenFoot.x - 10, vScreenFoot.y + 10, White, buff);
							}
						}

						//ESP Box
						if (Utils->esp.espbox)
						{
							D3DXVECTOR3 Box = vScreenHead - vScreenFoot;

							if (Box.y < 0)
								Box.y *= -1;

							int BoxWidth = (int)Box.y / 2;
							int DrawX = (int)vScreenHead.x - (BoxWidth / 2);
							int DrawY = (int)vScreenHead.y;

							Menu->DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 2, EspColor);
							Menu->DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 1, 0xFF000000);
						}
					}
				}
			}
		}
	}
}

void FunctionT::CallAimbot()
{
	if (!Utils->aimbot.main) return;

	float ScreenCoordX = Menu->Viewport.Width / 2;
	float ScreenCoordY = Menu->Viewport.Height / 2;

	float aimsmooth = 0.4f;
	if (Utils->aimbot.smooth) aimsmooth = (float)(Utils->aimbot.smooth * aimsmooth);

	float aimfov = 10.f;
	if (Utils->aimbot.fov) aimfov = (float)(Utils->aimbot.fov * aimfov);

	float radiusx = aimfov * (ScreenCoordX / 100);
	float radiusy = aimfov * (ScreenCoordY / 100);

	auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
	if (!pLocal) return;

	const char * boneTarget = (Utils->aimbot.target == 1) ? Utils->bones[0] : (Utils->aimbot.target == 2) ? Utils->bones[2] : Utils->bones[0];

	int Target = GetTarget();
	if (Target != -1)
	{
		D3DXVECTOR3 OnWorld, OnScreen;
		if (GetBoneMatrix(OnWorld, boneTarget, Target))
		{
			if (WorldToScreen(OnWorld, OnScreen))
			{
				if (OnScreen.x >= ScreenCoordX - radiusx && OnScreen.x <= ScreenCoordX + radiusx && OnScreen.y >= ScreenCoordY - radiusy && OnScreen.y <= ScreenCoordY + radiusy)
				{

					if (Utils->aimbot.draw)
						Menu->WriteText(OnScreen.x, OnScreen.y, Red, "Target");

					double DistX = OnScreen.x - ScreenCoordX;
					double DistY = OnScreen.y - ScreenCoordY;

					DistX = (int)floorf((float(DistX) / 2.0f) + 0.5f);
					DistY = (int)floorf((float(DistY) / 2.0f) + 0.5f);

					if (Utils->aimbot.key == 0)
					{
						if (GetAsyncKeyState(VK_SHIFT))
							mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
					}
					else if (Utils->aimbot.key == 1)
					{
						if (GetAsyncKeyState(VK_LBUTTON))
							mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
					}
					else {
						mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
					}
				}
			}
		}
	}
}

void FunctionT::CallAimBullet()
{
	if (!Utils->aimbullet.main)
	{
		BulletEnable = false;
		return;
	}

	auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
	if (!pLocal)
	{
		BulletEnable = false;
		return;
	}

	const char * boneTarget = (Utils->aimbullet.target == 1) ? Utils->bones[0] : (Utils->aimbullet.target == 2) ? Utils->bones[2] : Utils->bones[0];

	int Target = GetTarget();
	if (Target != -1)
	{
		D3DXVECTOR3 OnWorld, OnScreen;
		if (GetBoneMatrix(OnWorld, boneTarget, Target))
		{
			BulletEnable = true;
			fX = OnWorld.x;
			fY = OnWorld.y + 0.1f;
			fZ = OnWorld.z;

			if (WorldToScreen(OnWorld, OnScreen))
			{
				if (Utils->aimbullet.draw)
					Menu->WriteText(OnScreen.x, OnScreen.y, Red, "Target");
			}
		}
		else BulletEnable = false;
	}
	else BulletEnable = false;
}

_declspec(naked)void hkVectorSetEnd()
{
	static DWORD dwAddy;
	static float tfX, tfY, tfZ;
	static bool isSetEnd = false, AimBullet = false;
	_asm
	{
		push    ebp
		mov     ebp, esp
		mov     eax, [ebp + 8]
		mov[dwAddy], ecx
		pushad
	}

	Function->dwSetEndCheck = dwAddy;
	tfX = Function->fX;
	tfY = Function->fY;
	tfZ = Function->fZ;
	AimBullet = Function->BulletEnable;

	Function->AimCheck(isSetEnd);

	if (isSetEnd && AimBullet)
	{
		_asm
		{
			popad
			fld     dword ptr[tfX]
			fstp    dword ptr[ecx]
			fld     dword ptr[tfY]
			fstp    dword ptr[ecx + 4]
			fld     dword ptr[tfZ]
			mov     eax, ecx
			fstp    dword ptr[ecx + 8]
		}
	}
	else
	{
		_asm
		{
			popad
			fld     dword ptr[eax]
			fstp    dword ptr[ecx]
			fld     dword ptr[eax + 4]
			fstp    dword ptr[ecx + 4]
			fld     dword ptr[eax + 8]
			mov     eax, ecx
			fstp    dword ptr[ecx + 8]
		}
	}

	_asm
	{
		pop     ebp
		retn    4
	}
}

DWORD jmpSetPos;
_declspec(naked)void hkSetPos()
{
	static DWORD BackUpEBX, Addy;
	static float fPx, fPy, fPz;
	static bool EnableOPK = false, EnableOpkk = false;
	_asm
	{
		push ebp
		mov ebp, esp
		push esi
		push edi
		mov [Addy], ecx
		pushad
	}

	EnableOpkk = Utils->memory.opk;
	Function->SetPosHelper(Addy, EnableOPK);
	fPx = Function->fPX;
	fPy = Function->fPY;
	fPz = Function->fPZ;

	_asm
	{
		popad
		cmp[EnableOpkk], 0
		je Skip
		cmp[EnableOPK], 0
		je Skip
		mov edx, [ebp + 0x8]

		mov[BackUpEBX], ebx
		mov ebx, [fPx]
		mov[edx], ebx

		mov ebx, [fPy]
		mov[edx + 0x4], ebx

		mov ebx, [fPz]
		mov[edx + 0x8], ebx

		mov ebx, [BackUpEBX]
	Skip:
		jmp jmpSetPos
	}
}

void FunctionT::SetPosHelper(DWORD ptr, bool &test)
{
	int counter = 0;
	test = false;
	auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
	if (pLocal)
	{
		for (int i = 0; i < 16; i++)
		{
			if ((GetMyIndex() % 2 != i % 2) && isAlive(i))
			{
				auto pPlayer = GetPlayerByIndex(Garena->dwGetRealBase(), i);
				if (pPlayer)
				{
					if (ptr)
					{
						if (ptr == pPlayer)
						{
							counter = i;
							test = true;
						}
					}
				}
			}
		}

		if (!SavePosition)
		{
			auto myPos = pLocal->getPos();
			if (myPos)
			{
				fPX = myPos->x;
				fPY = myPos->y + 0.1f;
				fPZ = myPos->z;
				SavePosition = true;
			}
		}
	}
}

void FunctionT::CallMemoryGame()
{
	DWORD dwHook = (DWORD)Utils->i3MathDx + Address->VEC3DSetEnd;
	DetourFunction((PBYTE)dwHook, (PBYTE)hkVectorSetEnd);

	DWORD dwSetPos = (DWORD)Utils->i3FrameworkDx + Address->SetPos;
	jmpSetPos = dwSetPos + 0x5;
	DetourFunction((PBYTE)dwSetPos, (PBYTE)hkSetPos);

	while (true)
	{
		if (Utils->memory.opk)
		{
			auto pLocal = (i3GameObj *)GetPlayerByIndex(GetMyIndex());
			if (pLocal)
			{
				if (GetAsyncKeyState(VK_HOME))
					SavePosition = false;
			}else SavePosition = false;
		}
		
		auto pGame = *(DWORD*)(Garena->dwBase + Address->ADR_PLAYERPOINTER);
		if (pGame)
		{
			DWORD On = 0x3F4CE1C6, Off = 0x00000000;
			
			if (Utils->memory.fastshot)
				*(DWORD*)(pGame + Address->OFS_FASTSHOT) = 0;

			if(GetAsyncKeyState(VK_LBUTTON))
				*(BYTE*)(Garena->dwBase + (Address->GhostMode + 0x07)) = (Utils->memory.ghostmode != 0) ? 0x10 : 0x3F;

			if (Utils->memory.fastreloadknife)
				*(BYTE*)(*(DWORD*)(*(DWORD*)(pGame + 0x2C) + 0x2C) + 0x6B) = 66;
			
			if (Utils->memory.rapidfire)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
					*(BYTE*)(*(DWORD*)(*(DWORD*)(pGame + 0x2C) + 0x2C) + 0x5C) = 3;
			}

			auto pBattle = *(DWORD*)(Garena->dwBase + Address->ADR_GAMECONTEXT);
			if (pBattle)
			{
				if (Utils->memory.fastreload)
				{
					if (*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x10) + GetMyIndex() * Address->OFS_TICKETSIZE) != On ||
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x10) + GetMyIndex() * Address->OFS_TICKETSIZE) == On)
					{
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x10) + GetMyIndex() * Address->OFS_TICKETSIZE) = On;
					}
				}
				else {
					if (*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x10) + GetMyIndex() * Address->OFS_TICKETSIZE) == On)
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x10) + GetMyIndex() * Address->OFS_TICKETSIZE) = Off;
				}
				if (Utils->memory.fastswitch)
				{
					if (*(DWORD*)(pBattle + (Address->OFS_TICKET + 0xC) + GetMyIndex() * Address->OFS_TICKETSIZE) != On ||
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0xC) + GetMyIndex() * Address->OFS_TICKETSIZE) == On)
					{
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0xC) + GetMyIndex() * Address->OFS_TICKETSIZE) = On;
					}
				}
				else {
					if (*(DWORD*)(pBattle + (Address->OFS_TICKET + 0xC) + GetMyIndex() * Address->OFS_TICKETSIZE) == On)
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0xC) + GetMyIndex() * Address->OFS_TICKETSIZE) = Off;
				}

				if (Utils->memory.fastrespawn)
				{
					if (*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x30) + GetMyIndex() * Address->OFS_TICKETSIZE) != On ||
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x30) + GetMyIndex() * Address->OFS_TICKETSIZE) == On)
					{
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x30) + GetMyIndex() * Address->OFS_TICKETSIZE) = On;
					}
				}
				else {
					if (*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x30) + GetMyIndex() * Address->OFS_TICKETSIZE) == On)
						*(DWORD*)(pBattle + (Address->OFS_TICKET + 0x30) + GetMyIndex() * Address->OFS_TICKETSIZE) = Off;
				}
			}
		}
		Sleep(300);
	}
}

void FunctionT::AimCheck(bool &isTrue)
{
	isTrue = false;
	if (dwSetEndCheck)
	{
		auto pPlayer = (i3GameNode *)GetPlayerByIndex(Garena->dwGetRealBase(), GetMyIndex());
		if (pPlayer)
		{
			auto FirstChild = pPlayer->getFirstChild() + Address->CollideeLine;
			if (FirstChild)
			{
				auto dwSetEnd = (DWORD)FirstChild + Address->CollideeLineEnd;
				if (dwSetEnd)
				{
					if (dwSetEndCheck == dwSetEnd)
					{
						isTrue = true;
					}
				}
			}
		}
	}
}

void FunctionT::CallMemory(DWORD dwBase)
{
	*(BYTE*)(dwBase + Address->RecoilHorzAngle) = 0x00;
	*(BYTE*)(dwBase + Address->RecoilVertAngle) = 0x00;
	*(BYTE*)(dwBase + Address->Deviation_Max) = 0x00;
}

void FunctionT::DrawBoneLine(int index, const char * Start, const char * End, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vStart, vEnd;
	D3DXVECTOR3 vvStart, vvEnd;
	if (GetBoneMatrix(vStart, Start, index))
	{
		if (GetBoneMatrix(vEnd, End, index))
		{
			if (WorldToScreen(vStart, vvStart))
			{
				if (WorldToScreen(vEnd, vvEnd))
				{
					Menu->DrawLine(pDevice, vvStart.x, vvStart.y, vvEnd.x, vvEnd.y, 1, Color);
				}
			}
		}
	}
}

void FunctionT::EspDrawBone(int index, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	//Body
	DrawBoneLine(index, Utils->bones[0], Utils->bones[1], Color, pDevice);
	DrawBoneLine(index, Utils->bones[1], Utils->bones[2], Color, pDevice);
	DrawBoneLine(index, Utils->bones[2], Utils->bones[3], Color, pDevice);
	DrawBoneLine(index, Utils->bones[0], Utils->bones[4], Color, pDevice);
	DrawBoneLine(index, Utils->bones[0], Utils->bones[5], Color, pDevice);
	//Left Arm
	DrawBoneLine(index, Utils->bones[4], Utils->bones[6], Color, pDevice);
	DrawBoneLine(index, Utils->bones[6], Utils->bones[7], Color, pDevice);
	DrawBoneLine(index, Utils->bones[7], Utils->bones[8], Color, pDevice);
	//DrawBoneLine(index, Utils->bones[8], bones[9], Color, pDevice);
	//Right Arm
	DrawBoneLine(index, Utils->bones[5], Utils->bones[10], Color, pDevice);
	DrawBoneLine(index, Utils->bones[10], Utils->bones[11], Color, pDevice);
	DrawBoneLine(index, Utils->bones[11], Utils->bones[12], Color, pDevice);
	//DrawBoneLine(index, Utils->bones[12], bones[13], Color, pDevice);
	//Left Foot
	DrawBoneLine(index, Utils->bones[3], Utils->bones[14], Color, pDevice);
	DrawBoneLine(index, Utils->bones[14], Utils->bones[15], Color, pDevice);
	DrawBoneLine(index, Utils->bones[15], Utils->bones[16], Color, pDevice);
	DrawBoneLine(index, Utils->bones[16], Utils->bones[17], Color, pDevice);
	//Right Foot
	DrawBoneLine(index, Utils->bones[3], Utils->bones[18], Color, pDevice);
	DrawBoneLine(index, Utils->bones[18], Utils->bones[19], Color, pDevice);
	DrawBoneLine(index, Utils->bones[19], Utils->bones[20], Color, pDevice);
	DrawBoneLine(index, Utils->bones[20], Utils->bones[21], Color, pDevice);
}

bool FunctionT::WorldToScreen(D3DVECTOR Player, D3DVECTOR &PlayerScaled)
{
	__try
	{
		auto pRenderContext = GetRenderContext();
		if (!pRenderContext) return false;

		D3DXVECTOR3 vScreen;
		D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);

		Menu->Viewport.X = Menu->Viewport.Y = 0;
		Menu->Viewport.MinZ = 0;
		Menu->Viewport.MaxZ = 1;
		D3DXVec3Project(&vScreen, &PlayerPos, &Menu->Viewport, pRenderContext->GetProjectMatrix(), pRenderContext->GetViewMatrix(), pRenderContext->GetWorldMatrix());

		if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Menu->Viewport.Width && vScreen.y < Menu->Viewport.Height)
		{
			PlayerScaled.x = vScreen.x;
			PlayerScaled.y = vScreen.y;
			PlayerScaled.z = vScreen.z;
			return true;
		}
		return false;
	}
	__except (TRUE) { return false; }
}

bool FunctionT::isVisible(int iSlot)
{

	if (iSlot == -1)
		return false;
	dwPhtsX *pViewer = (dwPhtsX*)(GetProcAddress(Utils->i3SceneDx, /*?g_pPhysixCtx@@3PAVi3PhysixContext@@A*/XorStr<0x36, 38, 0x0BEC649D>("\x09\x50\x67\x49\x6A\x53\x45\x4E\x57\x47\x03\x35\x3A\x03\x04\x76\x16\x06\x1E\x20\x79\x1B\x24\x34\x3D\x26\x28\x12\x3D\x3D\x20\x30\x2E\x23\x18\x19\x1B" + 0x0BEC649D).s));
	DWORD dwSetStart = (DWORD)(GetProcAddress(Utils->i3SceneDx, /*?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xB1, 43, 0x36F71E14>("\x8E\xE1\xD6\xC0\xE6\xC2\xD6\xCA\xCD\xFA\xD2\x8F\xFE\xD1\xD3\xAC\xA8\xA6\xA6\xA1\x89\xAF\xA9\xAD\x89\x8A\x9A\x8D\x88\x96\x9F\x91\x85\x84\x96\x97\xE6\x92\x97\x98\x99\x80" + 0x36F71E14).s));
	DWORD dwSetEnd = (DWORD)(GetProcAddress(Utils->i3SceneDx, /*?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0xA9, 41, 0xF4168FAB>("\x96\xF9\xCE\xD8\xE8\xC0\xCB\xF0\xD8\x81\xF0\xDB\xD9\xDA\xDE\xDC\xDC\xDF\xF7\xD5\xD3\xDB\xFF\x80\x90\x83\x86\x9C\x95\x87\x93\x9E\x8C\x89\xF8\x88\x8D\x8E\x8F\x8A" + 0xF4168FAB).s));
	DWORD dwInitialize = (DWORD)(GetProcAddress(Utils->i3SceneDx, /*??0i3CollideeLine@@QAE@XZ*/XorStr<0x18, 26, 0xA4894190>("\x27\x26\x2A\x72\x2F\x5E\x71\x73\x4C\x48\x46\x46\x41\x69\x4F\x49\x4D\x69\x6A\x7A\x6D\x68\x6E\x77\x6A" + 0xA4894190).s));
	DWORD dwReyClass = (DWORD)(GetProcAddress(Utils->i3SceneDx, /*?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z*/XorStr<0x6B, 85, 0xED6B6ACB>("\x54\x3E\x0C\x17\x0C\x11\x02\x06\x30\x18\x1A\x05\x12\x0B\x0D\x3A\x12\x4F\x2D\x16\x06\xF3\xE8\xFA\xC0\xEB\xEB\xF2\xE2\xF0\xFD\xCA\xCB\xDD\xCC\xCB\xDF\xD1\xC4\xDB\xA0\xCB\xC5\xDE\xCE\xCB\xD0\xC2\xC4\xD4\xD4\xCA\xC0\xF2\xE4\xF1\xF6\xE8\xF1\xE6\xE7\xF8\xE8\xFC\xC2\x9F\xEE\xC1\xC3\xDC\xD8\xD6\xD6\xD1\xF9\xDF\xD9\xDD\xF9\xFA\xF3\xF5\xFD\xE4" + 0xED6B6ACB).s));
	i3CollideeLine Line;
	i3CollideeLine* cLine;
	void *PhysX = pViewer->i3PhysixContext;
	cLine = &Line;
	D3DXVECTOR3 vMe, vEnemy;
	DWORD dwPhysix;
	GetBoneMatrix(vMe, Utils->bones[1], GetMyIndex());
	GetBoneMatrix(vEnemy, Utils->bones[1], iSlot);
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

int FunctionT::GetTarget()
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
					GetBoneMatrix(LocPlayer, Utils->bones[1], GetMyIndex());
					GetBoneMatrix(PlayerEnd, Utils->bones[1], index);
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
}

D3DXVECTOR3 * FunctionT::GetPlayerPos(int index)
{
	__try {
		auto pPlayer = (i3GameObj *)GetPlayerByIndex(index);
		if (pPlayer) return 0;

		return pPlayer->getPos();
	}
	__except (true) {
		return 0;
	}
}

bool FunctionT::GetBoneMatrix(D3DXVECTOR3 &Out, const char * bonename, int index)
{
	__try 
	{
		auto pPlayer = (i3GameObj *)GetPlayerByIndex(index);
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
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

bool FunctionT::isAlive(int index)
{
	auto pState = (*(DWORD*)(*(DWORD*)(Garena->dwBase + Address->ADR_CHARACTERPOINTER) + 0x18 + Address->OFS_CHARACTERSIZE * index));
	if (pState == 2)
		return true;
	return false;
}

int FunctionT::GetMyIndex()
{
	auto pLocal = *(DWORD*)(Garena->dwBase + Address->ADR_GAMECONTEXT);
	if (!pLocal) return 0;
	return *(BYTE*)(pLocal + Address->OFS_TEAM);
}

int FunctionT::GetPlayerByIndex(int index)
{
	auto pChara = *(DWORD*)(Garena->dwBase + Address->ADR_CHARACTERPOINTER);
	if (!pChara) return NULL;

	auto pPlayer = *(DWORD*)(pChara + 0x14 + (Address->OFS_CHARACTERSIZE * index));
	if (!pPlayer) return NULL;

	return pPlayer;
}

int FunctionT::GetPlayerByIndex(DWORD dwBase, int index)
{
	if (!dwBase) return NULL;

	auto pChara = *(DWORD*)(dwBase + Address->ADR_CHARACTERPOINTER);
	if (!pChara) return NULL;

	auto pPlayer = *(DWORD*)(pChara + 0x14 + (Address->OFS_CHARACTERSIZE * index));
	if (!pPlayer) return NULL;

	return pPlayer;
}

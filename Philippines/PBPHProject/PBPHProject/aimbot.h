void AimBot(int BoneIndex)
{
	int Target = GetTarget();
	if(Target != -1)
	{
		D3DXVECTOR3 OnWorld;
		if (GetUserBone(OnWorld, Target, BoneIndex))
		{
			BulletEnable = true;
			fX = OnWorld.x;
			fY = OnWorld.y + 0.1f;
			fZ = OnWorld.z;
		}else BulletEnable = false;
	}else BulletEnable = false;
}

bool Aim_true = false;
void HookAimbot()
{
	if(Aim_true == false)
	{
		MakePTR((PBYTE)ADR_AIMBULLET, (DWORD)i3CollideeEnd);
		Aim_true = true;
	}
}

void CallAimbot()
{
	DWORD Player = *(DWORD*)ADR_CHARACTERPOINTER;
	if(Player != NULL)
	{
		if(opt.aimbot.autohead)AimBot(7);
		else if(opt.aimbot.autoneck)AimBot(6);
		else if(opt.aimbot.autobody)AimBot(5);
		else;

	}
}
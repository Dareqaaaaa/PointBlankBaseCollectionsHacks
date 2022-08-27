#pragma warning(disable:4309)


void InstallMemory()
{

}

void InstallNoRecoil()
{
	*(BYTE*)ResultWeaponCheck = 0xC3;
	*(BYTE*)ResultRecoilHorzAngle = 0x00;
	*(BYTE*)ResultRecoilVertAngle = 0x00;
	*(BYTE*)ResultDeviation_Max = 0x00;
}
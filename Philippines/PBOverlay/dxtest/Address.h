#define ADR_PLAYERPOINTER       0xB2FA74
#define ADR_SERVERPOINTER       0xB2EA18
#define ADR_REMOTEPOINTER		0xB2FA78
#define ADR_DEVICEPOINTER       0xB2D138

#define OFS_DEVICE				0x2B930
#define OFS_VIEW				0x31E38
#define OFS_PROJ				0x31E78

#define OFS_NOFALLDAMAGE        0x70AC
#define OFS_POSX                0x70C4
#define OFS_POSY                0x70CC
#define OFS_POSZ                0x70D4

#define MEM_STAMINA				0x90949C



bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
{
	auto pMatrix = Driver.ReadVirtualMemory<int>(Utils->PID, ADR_DEVICEPOINTER);
	if (!pMatrix)
		return FALSE;

	auto view = Driver.ReadVirtualMemory<D3DXMATRIX>(Utils->PID, pMatrix + OFS_VIEW);
	auto projection = Driver.ReadVirtualMemory<D3DXMATRIX>(Utils->PID, pMatrix + OFS_PROJ);

	D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
	D3DXVECTOR3 vScreen;

	D3DVIEWPORT9 Viewport;
	pDevice->GetViewport(&Viewport);

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);

	Viewport.X = Viewport.Y = 0;
	Viewport.MinZ = 0;
	Viewport.MaxZ = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &projection, &view, &identity);

	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
	{
		PlayerScaled.x = vScreen.x;
		PlayerScaled.y = vScreen.y;
		PlayerScaled.z = vScreen.z;
		return true;
	}
	return false;
}
class CESP {
public:
	void DrawBone(int index, const char * Start, const char * End, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
	{
		D3DXVECTOR3 vStart, vEnd;
		D3DXVECTOR3 vvStart, vvEnd;
		if (GetBoneMatrix(vStart, Start, index))
		{
			if (GetBoneMatrix(vEnd, End, index))
			{
				if (ADDXW2S(pDevice, vStart, vvStart))
				{
					if (ADDXW2S(pDevice, vEnd, vvEnd))
					{
						DrawLine(pDevice, vvStart.x, vvStart.y, vvEnd.x, vvEnd.y, 1, Color);
					}
				}
			}
		}
	}

	void ESPDrawSkeleton(int index, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
	{
		//Body
		DrawBone(index, bones[0], bones[1], Color, pDevice);
		DrawBone(index, bones[1], bones[2], Color, pDevice);
		DrawBone(index, bones[2], bones[3], Color, pDevice);
		DrawBone(index, bones[0], bones[4], Color, pDevice);
		DrawBone(index, bones[0], bones[5], Color, pDevice);
		//Left Arm
		DrawBone(index, bones[4], bones[6], Color, pDevice);
		DrawBone(index, bones[6], bones[7], Color, pDevice);
		DrawBone(index, bones[7], bones[8], Color, pDevice);
		//DrawBone(index, bones[8], bones[9], Color, pDevice);
		//Right Arm
		DrawBone(index, bones[5], bones[10], Color, pDevice);
		DrawBone(index, bones[10], bones[11], Color, pDevice);
		DrawBone(index, bones[11], bones[12], Color, pDevice);
		//DrawBone(index, bones[12], bones[13], Color, pDevice);
		//Left Foot
		DrawBone(index, bones[3], bones[14], Color, pDevice);
		DrawBone(index, bones[14], bones[15], Color, pDevice);
		DrawBone(index, bones[15], bones[16], Color, pDevice);
		DrawBone(index, bones[16], bones[17], Color, pDevice);
		//Right Foot
		DrawBone(index, bones[3], bones[18], Color, pDevice);
		DrawBone(index, bones[18], bones[19], Color, pDevice);
		DrawBone(index, bones[19], bones[20], Color, pDevice);
		DrawBone(index, bones[20], bones[21], Color, pDevice);
	}

	VOID ESPHealthBar(D3DXVECTOR3 Head, D3DXVECTOR3 Foot, int health, LPDIRECT3DDEVICE9 pDevice)
	{
		DWORD Color;
		D3DXVECTOR3 Box = Head - Foot;
		if (Box.y < 0)
			Box.y *= -1;

		int BoxWidth = (int)Box.y / 2;
		int DrawX = (int)Head.x - (BoxWidth / 2);
		int DrawY = (int)Head.y;

		int DrawWidth = health * (Foot.y - Head.y) / 100;

		if (health > 100)
			health = 100;

		if (health > 75)
			Color = 0xFF00FF00;
		else if (health > 40)
			Color = 0xFFFF9B00;
		else
			Color = 0xFFFF0000;

		FillRGB(pDevice, DrawX - 6, DrawY - 1, 5, (int)Box.y + 2, Black);
		FillRGB(pDevice, DrawX - 5, DrawY, 3, DrawWidth, Color);
	}

	void ESPDrawBox(D3DXVECTOR3 Head, D3DXVECTOR3 Foot, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
	{

		D3DXVECTOR3 Box = Head - Foot;

		if (Box.y  < 0)
			Box.y *= -1;

		int BoxWidth = (int)Box.y / 2;
		int DrawX = (int)Head.x - (BoxWidth / 2);
		int DrawY = (int)Head.y;

		DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 2, Color);
		DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 1, 0xFF000000);
	}

}ESP;

VOID CallESP(LPDIRECT3DDEVICE9 pDevice)
{
	DWORD pCharacter = *(DWORD*)(dwBaseAddress + ADR_CHARACTERPOINTER);
	if (!pCharacter)
		return;

	/*
	for (int i = 0; i < 16; i++)
	{
		D3DXVECTOR3 PlayerStart, PlayerHead, PlayerEnd, PlayerFoot;
		DWORD ESPColor = (GetMyIndex() % 2 != i % 2) ? (isVisible(i)) ? Green : Red : Blue;

		if (GetUserBone(PlayerStart, i, 7) && GetMyIndex() != i && isAlive(i))
		{

			if (ADDXW2S(pDevice, PlayerStart, PlayerHead))
			{
				//ESP PlayerHead
				if (opt.esp.espbone)
					ESP.ESPDrawSkeleton(i, ESPColor, pDevice);

				if (opt.esp.espline)
					DrawLine(pDevice, Viewport.Width / 2, Viewport.Height, (int)PlayerHead.x, (int)PlayerHead.y, 1, ESPColor);

				if (GetUserBone(PlayerEnd, i, 8))
				{
					if (ADDXW2S(pDevice, PlayerEnd, PlayerFoot))
					{
						if (opt.esp.esphealth)
							ESP.ESPHealthBar(PlayerHead, PlayerFoot, GetUserHealth(i), pDevice);

						if (opt.esp.espbox)
							ESP.ESPDrawBox(PlayerHead, PlayerFoot, ESPColor, pDevice);
					}
				}
			}
		}
	}*/
}
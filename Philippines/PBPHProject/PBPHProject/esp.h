#pragma warning(disable:4244)
#pragma warning(disable:4101)
#pragma warning(disable:4305)

class CESP{
public:
	void DrawBone(int iSlot, int Start, int End, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
	{ 
		D3DXVECTOR3 vStart,vEnd; 
		D3DXVECTOR3 vvStart,vvEnd; 
		if(GetUserBone(vStart, iSlot, Start))
		{
			if(GetUserBone(vEnd, iSlot, End))
			{
				if(ADDXW2S(pDevice, vStart, vvStart)) 
				{ 
					if (ADDXW2S(pDevice, vEnd, vvEnd)) 
					{ 
						DrawLine(pDevice, vvStart.x, vvStart.y, vvEnd.x, vvEnd.y, Color);
					} 
				} 
			}
		}
	}

	void ESPDrawSkeleton(int iSlot,DWORD Color,LPDIRECT3DDEVICE9 pDevice) 
	{ 
		DrawBone(iSlot,6,7,Color,pDevice); 
		DrawBone(iSlot,0,6,Color,pDevice); 
		DrawBone(iSlot,6,10,Color,pDevice); 
		DrawBone(iSlot,6,11,Color,pDevice);  
		DrawBone(iSlot,0,12,Color,pDevice); 
		DrawBone(iSlot,0,13,Color,pDevice); 
		DrawBone(iSlot,12,14,Color,pDevice);  
		DrawBone(iSlot,13,15,Color,pDevice); 
		DrawBone(iSlot,14,8,Color,pDevice);  
		DrawBone(iSlot,15,9,Color,pDevice);  
	}

	VOID ESPHealthBar( D3DXVECTOR3 Head, D3DXVECTOR3 Foot, int health, LPDIRECT3DDEVICE9 pDevice)
	{
		DWORD Color;
		D3DXVECTOR3 Box =  Head - Foot;
		if( Box.y < 0 )
				Box.y *= -1;
 
		int BoxWidth = (int)Box.y / 2;
		int DrawX = (int)Head.x - ( BoxWidth / 2 );
		int DrawY = (int)Head.y;
 
		int DrawWidth = health * (Foot.y - Head.y) / 100;
 
		if( health > 100 )
				health = 100;
 
		if( health > 75 )
				Color = 0xFF00FF00;
		else if( health > 40 )
				Color = 0xFFFF9B00;
		else
				Color = 0xFFFF0000;
        
		FillRGB(pDevice, DrawX - 6, DrawY - 1, 5, (int)Box.y + 2, Black);
		FillRGB(pDevice, DrawX - 5, DrawY, 3, DrawWidth, Color);
	}

	void ESPDrawBox( D3DXVECTOR3 Head, D3DXVECTOR3 Foot, DWORD Color, LPDIRECT3DDEVICE9 pDevice )
	{

		D3DXVECTOR3 Box =  Head - Foot;

 		if( Box.y  < 0 )
 			Box.y *= -1;

		int BoxWidth    = (int)Box.y / 2;
		int DrawX		= (int)Head.x - ( BoxWidth / 2 );
		int DrawY		= (int)Head.y;

		DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 2, Color);
		DrawBorder(pDevice, DrawX, DrawY, BoxWidth, (int)Box.y, 1, 0xFF000000);
	}

}ESP;

VOID CallPlayerESP(LPDIRECT3DDEVICE9 pDevice)
{ 
	DWORD Player = *(DWORD*)(ADR_CHARACTERPOINTER);
	if(Player != NULL)
	{
		for (int i = 0; i < 16; i++) 
		{
			D3DXVECTOR3 Player, PlayerScaled;
			D3DXVECTOR3 PlayerEnd, PlayerFoot;
			DWORD ESPColor = (GetMyIndex() % 2 != i % 2)? (isVisible(i))? Green : Red : Blue;
			if(GetUserBone(Player, i, 7) && GetMyIndex() != i && isAlive(i))
			{
				if (ADDXW2S(pDevice, Player, PlayerScaled))
				{
					D3DVIEWPORT9 viewP;
					pDevice->GetViewport(&viewP);
					DWORD ScreenCenterX = viewP.Width/2;
					DWORD ScreenCenterY = viewP.Height;

					if(opt.esp.espbone)
						ESP.ESPDrawSkeleton(i, ESPColor, pDevice);

					if(opt.esp.espline)
							DrawLine(pDevice, ScreenCenterX, ScreenCenterY, (int)PlayerScaled.x, (int)PlayerScaled.y, ESPColor);

					//Foot
					if(GetUserBone(PlayerEnd, i, 8))
					{
						if (ADDXW2S(pDevice, PlayerEnd, PlayerFoot))
						{
							if(opt.esp.esphealth)
								ESP.ESPHealthBar(PlayerScaled, PlayerFoot, GetUserHealth(i), pDevice);

							if(opt.esp.espbox)
								ESP.ESPDrawBox(PlayerScaled, PlayerFoot, ESPColor, pDevice);
						}
					}
				}
			}
		}
	} 
}

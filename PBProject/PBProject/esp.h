#pragma warning(disable:4244)
#pragma warning(disable:4101)
#pragma warning(disable:4305)

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
					Menu.DrawLine(pDevice, vvStart.x, vvStart.y, vvEnd.x, vvEnd.y, Color);
				} 
			} 
		}
	}
} 

void DrawSkeleton(int iSlot,DWORD Color,LPDIRECT3DDEVICE9 pDevice) 
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

VOID CallPlayerESP(LPDIRECT3DDEVICE9 pDevice)
{ 
	DWORD dwGameChara = *(PDWORD)(0xE3EC70);
	if(dwGameChara != NULL)
	{
		for (int i = 0; i < 16; i++) 
		{
			D3DXVECTOR3 Player, PlayerScaled;
			DWORD ESPColor = Blue;
			if(GetUserBone(Player, i, 7))
			{
				if (ADDXW2S(pDevice,Player,PlayerScaled))
				{
					/*D3DVIEWPORT9 viewP;
					pDevice->GetViewport(&viewP);
					DWORD ScreenCenterX = viewP.Width/2;
					DWORD ScreenCenterY = viewP.Height;*/

					DrawSkeleton(i, ESPColor, pDevice);
				}
			}
		}
	} 
}

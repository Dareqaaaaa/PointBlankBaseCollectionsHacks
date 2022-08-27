#pragma warning(disable: 4244)

void DrawString(float x, float y, DWORD COLOR, LPD3DXFONT pFont, const char *fmt, ...)
{
	RECT FontPos = {x, y, x + 20, y + 10};
	char buf[1024] = {'\0'};
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf(buf, fmt, va_alist);
	va_end(va_alist);
	
	pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP , Black);
	pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP , Black);
	pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP , Black);
	pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP , Black);
	pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP , Black);

	pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP , COLOR);
}

VOID  DrawBox2(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, Color }, { x, y, 0.0f, 0.0f, Color }, { x + w, y + h, 0.0f, 0.0f, Color }, { x + w, y, 0.0f, 0.0f, Color } };
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}

void DrawLine(float x, float y, float x2, float y2, float width, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
    D3DXVECTOR2 vLine[2];
    g_pLine->SetWidth( width );
    g_pLine->SetAntialias( false );
    g_pLine->SetGLLines( true );
    vLine[0].x = x;
    vLine[0].y = y;
    vLine[1].x = x2;
    vLine[1].y = y2;
    g_pLine->Begin();
    g_pLine->Draw( vLine, 2, color );
    g_pLine->End();
}

void DrawLine2(float StartX, float StartY, float EndX, float EndY, int Width, D3DCOLOR dColor, LPD3DXLINE S_Line)
{
	S_Line[0].SetWidth(Width);
	S_Line[0].SetGLLines(0);
	S_Line[0].SetAntialias(1);

	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;

	S_Line[0].Begin();
	S_Line[0].Draw(v2Line, 2, dColor);
	S_Line[0].End();
}

 
void CornerBox(int x, int y, int w, int h, D3DCOLOR Draw, LPD3DXLINE S_Line)
{
        int bWidth = w;
        int bHeight = h;
        DrawLine2(x, y, x, y + (bHeight / 5), 3, Draw, S_Line);
        DrawLine2(x, y, x + (bWidth / 5), y, 3, Draw, S_Line);
        DrawLine2(x + bWidth, y, x + bWidth - (bWidth / 5), y, 3, Draw, S_Line);
        DrawLine2(x + bWidth, y, x + bWidth, y + (bHeight / 5), 3, Draw, S_Line);
        DrawLine2(x, y + bHeight, x + (bWidth / 5), y + bHeight, 3, Draw, S_Line);
        DrawLine2(x, y + bHeight, x, y + bHeight - (bHeight / 5), 3, Draw, S_Line);
        DrawLine2(x + bWidth, y + bHeight, x + bWidth - (bWidth / 5), y + bHeight, 3, Draw, S_Line);
        DrawLine2(x + bWidth, y + bHeight, x + bWidth, y + bHeight - (bHeight / 5), 3, Draw, S_Line);
}
 
void EdgedOutline(int x, int y, int w, int h, D3DCOLOR Draw, LPD3DXLINE S_Line) {
        CornerBox(x - 1, y - 1, w + 2, h + 2, D3DCOLOR_ARGB(0, 0, 0, 255), S_Line);
        CornerBox(x, y, w, h, Draw, S_Line);
}

void DrawD3DBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice) 
{ 
    FillRGB(x,(y + h - px), w, px, BorderColor, pDevice); 
    FillRGB(x, y, px, h, BorderColor, pDevice); 
    FillRGB(x, y, w, px, BorderColor, pDevice); 
    FillRGB(x + w - px, y, px, h, BorderColor, pDevice); 
} 

void DrawD3DBox(int x, int y, int w, int h, D3DCOLOR Color, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)  
{ 

    DrawD3DBorder(x, y, w, h, 2, BorderColor, pDevice); 
     
    const DWORD D3D_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE; 
    struct Vertex { 
        float x, y, w, h; 
        D3DCOLOR Color; 
    } 
    V[4] = {{(float) x, (float)(y + h), 0.0f, 0.0f, Color},  
            {(float) x, (float)y, 0.0f, 0.0f, Color},  
            {(float)(x + w), (float)(y + h), 0.0f, 0.0f, Color},  
            {(float)(x + w), (float)y, 0.0f, 0.0f, Color} 
    }; 
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); 
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
    pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); 
    pDevice->SetRenderState(D3DRS_FOGENABLE, D3DZB_FALSE); 

    pDevice->SetFVF(D3D_FVF); 
    pDevice->SetTexture(0, NULL); 
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex)); 
} 


VOID  DrawBorder2(int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9* pDevice)
{
	DrawBox2(x, y, 1, h, Color, pDevice);
	DrawBox2(x, y + h, w, 1, Color, pDevice);
	DrawBox2(x, y, w, 1, Color, pDevice);
	DrawBox2(x + w, y, 1, h + 1, Color, pDevice);
}

void DrawBox3D(CPlayers* pPlayer,DWORD Color,LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vStart,vEnd;
	D3DXVECTOR3 vvStart,vvEnd;

	vStart.x = pPlayer->pos.x;
	vStart.y = 1.5f + pPlayer->pos.y;
	vStart.z = pPlayer->pos.z;

	vEnd.x = pPlayer->pos.x;
	vEnd.y = pPlayer->pos.y;
	vEnd.z = pPlayer->pos.z;

	if(ADDXW2S(pDevice,vStart,vvStart))
	{
		if(ADDXW2S(pDevice,vEnd,vvEnd))
		{
			float w = (vvEnd.y - vvStart.y)/4; 
			DrawD3DBox(vvStart.x-w, vvStart.y, w*2, vvEnd.y - vvStart.y, Color, Color, pDevice); 
		}
	}
}

void DrawBox2D(CPlayers* pPlayer,DWORD Color,LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE S_Line)
{
	D3DXVECTOR3 vStart,vEnd;
	D3DXVECTOR3 vvStart,vvEnd;

	vStart.x = pPlayer->pos.x;
	vStart.y = 1.5f + pPlayer->pos.y;
	vStart.z = pPlayer->pos.z;

	vEnd.x = pPlayer->pos.x;
	vEnd.y = pPlayer->pos.y;
	vEnd.z = pPlayer->pos.z;

	if(ADDXW2S(pDevice,vStart,vvStart))
	{
		if(ADDXW2S(pDevice,vEnd,vvEnd))
		{
			float w = (vvEnd.y - vvStart.y)/4; 
			EdgedOutline(vvStart.x-w, vvStart.y, w*2, vvEnd.y - vvStart.y, Color, S_Line);
		}
	}
}

HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
    if(FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
        return E_FAIL;
    
    WORD colour16 = ((WORD)((colour32>>28)&0xF)<<12)
	            	|(WORD)(((colour32>>20)&0xF)<<8)
	             	|(WORD)(((colour32>>12)&0xF)<<4)
                 	|(WORD)(((colour32>>4)&0xF)<<0);

    D3DLOCKED_RECT d3dlr;    
    (*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
    WORD *pDst16 = (WORD*)d3dlr.pBits;

    for(int xy=0; xy < 8*8; xy++)
        *pDst16++ = colour16;

    (*ppD3Dtex)->UnlockRect(0);

    return S_OK;
}

void HealthBar(LPDIRECT3DDEVICE9 pDevice,float x, float y, int Health)
{
	DWORD HPcol = D3DCOLOR_ARGB(255, 0, 255, 0);
	if (Health < 90)HPcol = D3DCOLOR_ARGB(255, 255, 255, 0);
	if (Health < 80)HPcol = D3DCOLOR_ARGB(255, 255, 100, 0);
	if (Health < 40)HPcol = D3DCOLOR_ARGB(255, 255, 00, 0);
	if (Health < 10)HPcol = D3DCOLOR_ARGB(255, 0, 0, 0);
	DrawBorder(x-1,y-1,52,5,1,D3DCOLOR_ARGB(255, 0, 0, 0),pDevice);
	FillRGB(x,y,Health/2,3,HPcol,pDevice);
}
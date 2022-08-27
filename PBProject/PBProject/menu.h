#include "stdafx.h"
#pragma warning(disable: 4244)
#pragma warning(disable: 4101)

#define Cyan		D3DCOLOR_ARGB( 255, 000, 255, 255 )
#define Red			D3DCOLOR_ARGB( 255, 255, 000, 000 )
#define Green		D3DCOLOR_ARGB( 255, 127, 255, 000 )
#define Blue		D3DCOLOR_ARGB( 255, 000, 000, 255 )
#define White		D3DCOLOR_ARGB( 255, 255, 255, 255 )
#define Black		D3DCOLOR_ARGB( 255, 000, 000, 000 )
#define Purple		D3DCOLOR_ARGB( 255, 128, 000, 128 )
#define Grey		D3DCOLOR_ARGB( 255, 112, 112, 112 )
#define Yellow		D3DCOLOR_ARGB( 255, 255, 255,  51 )
#define Pink		D3DCOLOR_ARGB( 255, 255, 192, 203 )
#define Orange		D3DCOLOR_ARGB( 255, 255, 140, 000 )
#define TBlack    D3DCOLOR_ARGB( 128, 000, 000, 000 )
#define BTBlack   D3DCOLOR_ARGB( 255, 255, 000, 000 )
#define BBlack    D3DCOLOR_ARGB( 255, 54, 54, 54 )

#define Menu_Current    D3DCOLOR_ARGB( 255, 255, 255, 255 )
#define Menu_Active 	D3DCOLOR_ARGB( 255, 127, 255, 000 )
#define Menu_Titel		D3DCOLOR_ARGB( 255, 255, 255, 255 )
#define Menu_Folder		D3DCOLOR_ARGB( 255, 255, 000, 000 )
#define Menu_Inactiv	D3DCOLOR_ARGB( 255, 255, 255, 255 )


	INT Show = 1,
	Current = 1,
	D3DMenu = 1;

bool BMenu = 1;

class CMenu
{
public:
	LPD3DXFONT PFont;
	ID3DXLine *pLine; 

	D3DXVECTOR3 GetMidPoint (D3DXVECTOR3 V1, D3DXVECTOR3 V2)
	{
		D3DXVECTOR3 Mid;
		Mid.x = (V1.x + V2.x) / 2;
		Mid.y = (V1.y + V2.y) / 2;
		Mid.z = (V1.z + V2.z) / 2;
		return Mid;
	}

	struct D3DTLVERTEX
	{
		float x, y, z, rhw;
		DWORD color;
	};

	void DrawLine(LPDIRECT3DDEVICE9 pDevice, float X, float Y, float X2, float Y2, DWORD dwColor)
	{
		if(!pDevice) return;
		D3DTLVERTEX qV[2] = 
		{ 
			{(float)X, (float)Y, 0.0f, 1.0f, dwColor},
			{(float)X2, (float)Y2, 0.0f, 1.0f, dwColor},
		};
		pDevice->SetTexture(0, NULL);
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		pDevice->SetRenderState(D3DRS_FOGENABLE, false);
		pDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
		pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
	}

	VOID DrawD3DText( INT x, INT y, DWORD Color, CHAR *Text )
	{
		RECT rect;
		SetRect( &rect, x, y, x, y );
		Menu.PFont->DrawTextA( 0, Text, -1, &rect, DT_LEFT | DT_NOCLIP, Color );
	}

	VOID DrawD3DItems( INT x, INT y, DWORD Color, CHAR *Text )
	{
		RECT rect;
		SetRect( &rect, x, y, x, y );
		Menu.PFont->DrawText( 0, Text, -1, &rect, DT_RIGHT | DT_NOCLIP, Color );
	}

	VOID FillRGB( INT x, INT y, INT w, INT h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice )
	{
		if( w < 0 )w = 1;
		if( h < 0 )h = 1;
		if( x < 0 )x = 1;
		if( y < 0 )y = 1;

		D3DRECT Rec = { x, y, x + w, y + h };
		pDevice->Clear( 1, &Rec, D3DCLEAR_TARGET, Color, 0, 0 );
	}

	VOID DrawBorder( INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice )
	{
		FillRGB( x,( y + h - px ), w, px, BorderColor, pDevice );
		FillRGB( x, y, px, h, BorderColor, pDevice );
		FillRGB( x, y, w, px, BorderColor, pDevice );
		FillRGB( ( x + w - px ), y, px, h, BorderColor, pDevice );
	}

	VOID DrawBox( INT x, INT y, INT w, INT h, D3DCOLOR BoxColor, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice )
	{
		FillRGB( x, y, w, h, BoxColor, pDevice );
		DrawBorder( x, y, w, h, 1, BorderColor, pDevice );
	}


	VOID Additem(  CHAR *Text, INT MaxValue, INT &Value, INT Folder, CHAR **Opt  )
	{
		if( BMenu )
		{
			if( D3DMenu == Current ) 
			{
				if( GetAsyncKeyState( VK_RIGHT ) &1 )
				{
					if( Value < MaxValue )
					Value++;
				}
				else if( GetAsyncKeyState( VK_LEFT ) &1 )
				{
					if( Value > 0 )
					Value--;
				}
			}

			if( D3DMenu == Current )
			{
				if( Folder == 1 )
				{
					DrawD3DText( 30 - 10, 47 + ( Current * 15 ), Menu_Current, Text );
					DrawD3DItems( 30 + 170, 47 + ( Current * 15 ), Menu_Current, Opt[Value] );
				}
				else
				{
					DrawD3DText( 30 - 10, 47 + ( Current * 15 ), Menu_Current, Text );
					DrawD3DItems( 30 + 170, 47 + ( Current * 15 ), Menu_Current, Opt[Value] );
				}
			}

			else if( Value > 0 )
			{
				if( Folder == 1 )
				{
					DrawD3DText( 30 - 10, 47 + ( Current * 15 ), Menu_Folder, Text);
					DrawD3DItems( 30 + 170, 47 + ( Current * 15 ), Menu_Folder, Opt[Value]);
				}
				else
				{
					DrawD3DText(  30 - 10, 47 + ( Current * 15 ), Menu_Active, Text );
					DrawD3DItems(  30 + 170, 47 + ( Current * 15 ), Menu_Active, Opt[Value] );
				}
			}
			else
			{
				if( Folder == 1 )
				{
					DrawD3DText( 30 - 10, 47 + ( Current * 15 ), Menu_Folder, Text);
					DrawD3DItems( 30 + 170, 47 + ( Current * 15 ), Menu_Folder, Opt[Value]);
				}
				else
				{
					DrawD3DText( 30 - 10, 47  + ( Current * 15 ), Grey, Text );
					DrawD3DItems( 30 + 170, 47  + ( Current * 15 ), Grey, Opt[Value] );
				}
			}

			Current++;
		}
	}
}
Menu;
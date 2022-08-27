/*********************************************************/
/* CA Base D3D Menu Selection V5
/* Creditos:
/*	Solify's	-> CA Base D3D Menu Selection.
/*  WE11ington  -> Disponibilizou Para Combat Arms Brasil.
/*  luizimloko  -> Menu Selection V5.
/*********************************************************/
#include "Headers.h"

#define Red       D3DCOLOR_ARGB(255, 255, 000, 000)
#define Green     D3DCOLOR_ARGB(255, 127, 255, 000)
#define Orange    D3DCOLOR_ARGB(255, 255, 140, 000)
#define Blue      D3DCOLOR_ARGB(255, 000, 000, 255)
#define Yellow    D3DCOLOR_ARGB(255, 255, 255,  51)
#define Black     D3DCOLOR_ARGB(255, 000, 000, 000)
#define Grey      D3DCOLOR_ARGB(255, 112, 112, 112)
#define Gold      D3DCOLOR_ARGB(255, 255, 215, 000)
#define Pink      D3DCOLOR_ARGB(255, 255, 192, 203)
#define Purple    D3DCOLOR_ARGB(255, 128, 000, 128)
#define White     D3DCOLOR_ARGB(255, 255, 255, 249)
#define Cyan      D3DCOLOR_ARGB(255, 000, 255, 255)
#define Magenta   D3DCOLOR_ARGB(255, 255, 000, 255)
#define TBlack    D3DCOLOR_ARGB(128, 000, 000, 000)
#define BTBlack   D3DCOLOR_ARGB(255, 15, 72, 127)
#define BBlack    D3DCOLOR_ARGB(255, 54, 54, 54)

struct CMenu
{
	INT MenuSelection,
		matrixPos[ 3 ],
		Current;

	BOOL ShowMenu;

	CMenu( VOID )
	{
		ShowMenu = 1;
		Current = 1;

		matrixPos[ 0 ] = 30; //x1
		matrixPos[ 1 ] = 70; //y1
		matrixPos[ 2 ] = 60; //y2
		matrixPos[ 3 ] = 00; //x2
	}
}
menu;

LPD3DXFONT PFont;

VOID WriteText( INT x, INT y, D3DCOLOR Color, CHAR *String )
{
	RECT Rect;
	SetRect( &Rect, x, y, x, y );
	PFont->DrawTextA( 0, String, -1, &Rect, DT_LEFT | DT_NOCLIP, Color );
}

VOID WriteTextR( INT x, INT y, DWORD Color, CHAR *Text )
{
	RECT rect;
	SetRect( &rect, x, y, x, y );
	PFont->DrawText( 0, Text, -1, &rect, DT_RIGHT | DT_NOCLIP, Color );
}

VOID DrawRect( LPDIRECT3DDEVICE9 pDevice, INT x, INT y, INT h, INT w, DWORD Color )
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;

	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 0, 0 );
}

VOID FillRGB( INT x, INT y, INT w, INT h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice )
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 0, 0 );
}

VOID DrawBorder( INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice )
{
	FillRGB(x,(y + h - px), w, px, BorderColor, pDevice);
	FillRGB(x, y, px, h, BorderColor, pDevice);
	FillRGB(x, y, w, px, BorderColor, pDevice);
	FillRGB(x + w - px, y, px, h, BorderColor, pDevice);
}

void DrawBox( int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
    FillRGB( x, y, w, h,        BoxColor, pDevice );
    DrawBorder( x, y, w, h, 1,    BorderColor, pDevice );
}  

#define PISSS 3.14159265

struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};

D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v;
	v.fX = X;
	v.fY = Y;
	v.fZ = Z;
	v.fRHW = RHW;
	v.Color = color;
	v.fU = U;
	v.fV = V;
	return v;
}


void Circle( float x, float y, float rad, bool center, DWORD color ,LPDIRECT3DDEVICE9 pDevice)
{
	const int NUMPOINTS = 34;

	if(!center)
	{
		x += rad;
		y -= rad;
	}

	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;
	WedgeAngle = (float)( (2*PISSS) / NUMPOINTS );
	for( i=0; i<=NUMPOINTS; i++ )
	{
		Theta = i * WedgeAngle;
		X = (float)( x + rad * cos(Theta) );
		Y = (float)( y - rad * sin(Theta) );
		Circle[i] = CreateD3DTLVERTEX( X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f );
	}
	pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	pDevice->SetTexture( 0, NULL );
	pDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]) );
}

VOID CrossHair( LPDIRECT3DDEVICE9 pDevice, D3DCOLOR Color )
{
	D3DVIEWPORT9 Viewport;
	pDevice->GetViewport( &Viewport );
	DWORD ScreenX = Viewport.Width / 2;
	DWORD ScreenY = Viewport.Height / 2;
	D3DRECT rec1 = { ScreenX - 15, ScreenY, ScreenX + 15, ScreenY + 02 };
	D3DRECT rec2 = { ScreenX, ScreenY - 15, ScreenX + 02, ScreenY + 15 };
	pDevice->Clear( 1, &rec1, D3DCLEAR_TARGET, Color, 0, 0 );
	pDevice->Clear( 1, &rec2, D3DCLEAR_TARGET, Color, 0, 0 );
}

VOID Additem( CHAR *String, INT MaxValue, INT &Variable, INT Folder, CHAR **Option )
{
	if( menu.ShowMenu )
	{
		if( menu.MenuSelection == menu.Current )
		{
			if( GetAsyncKeyState( VK_RIGHT ) &1 )
			{
				if( Variable < MaxValue )
					Variable++;
			}
			else if( GetAsyncKeyState( VK_LEFT ) &1 )
			{
				if( Variable > 0 )
					Variable--;
			}
		}

		if( menu.MenuSelection == menu.Current )
		{
			WriteText( menu.matrixPos[ 0 ] - 3, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Cyan, String );
			WriteTextR( menu.matrixPos[ 0 ] + 172, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Cyan, Option[ Variable ] );
		}
		else if( Variable > 0 )
		{
			if( Folder == 1 )
			{
				WriteText( menu.matrixPos[ 0 ] - 3, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Red, String );
				WriteTextR( menu.matrixPos[ 0 ] + 172, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Red, Option[ Variable ] );
			}
			else
			{
				WriteText( menu.matrixPos[ 0 ] - 3, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Green, String );
				WriteTextR( menu.matrixPos[ 0 ] + 172, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Green, Option[ Variable ] );
			}
		}
		else
		{
			if( Folder == 1 )
			{
				WriteText( menu.matrixPos[ 0 ] - 3, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Red, String );
				WriteTextR( menu.matrixPos[ 0 ] + 172, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), Red, Option[ Variable ] );
			}
			else
			{
				WriteText( menu.matrixPos[ 0 ] - 3, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), White, String );
				WriteTextR( menu.matrixPos[ 0 ] + 172, menu.matrixPos[ 2 ] + ( menu.Current * 15 ), White, Option[ Variable ] );
			}
		}

		menu.Current++;
	}
}
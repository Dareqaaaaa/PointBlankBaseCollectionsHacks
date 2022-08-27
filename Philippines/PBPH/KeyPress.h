#include <windows.h>

int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;
#define			RainbowTextTest D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)

static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}
kPressingKey[256];
BOOL IsKeyPressed(int Key,DWORD dwTimeOut)
{
	if( HIWORD( GetKeyState( Key ) ) )
	{
		if( !kPressingKey[Key].bPressed || ( kPressingKey[Key].dwStartTime && ( kPressingKey[Key].dwStartTime + dwTimeOut ) <= GetTickCount( ) ) )
		{
			kPressingKey[Key].bPressed = TRUE;
			if( dwTimeOut > NULL )
				kPressingKey[Key].dwStartTime = GetTickCount( );
			return TRUE;
		}
	}else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;
}
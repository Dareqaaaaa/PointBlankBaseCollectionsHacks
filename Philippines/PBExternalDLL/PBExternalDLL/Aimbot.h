void CallAimbot(LPDIRECT3DDEVICE9 pDevice)
{
	if (!opt.aimbot.main)
		return;

	float ScreenCoordX = Viewport.Width / 2;
	float ScreenCoordY = Viewport.Height / 2;

	float aimsmooth = 0.6f;
	if (opt.aimbot.smooth)
		aimsmooth = (float)(opt.aimbot.smooth * aimsmooth);

	float aimfov = 10.f;
	if (opt.aimbot.fov)
		aimfov = (float)(opt.aimbot.fov * aimfov);

	float radiusx = aimfov * (ScreenCoordX / 100);
	float radiusy = aimfov * (ScreenCoordY / 100);

	/*
	DWORD Player = *(DWORD*)(dwBaseAddress + ADR_CHARACTERPOINTER);
	if (Player)
	{
		int Target = GetTarget();
		if (Target != -1)
		{
			D3DXVECTOR3 OnWorld, OnScreen;
			if (GetUserBone(OnWorld, Target, 7))
			{
				if (ADDXW2S(pDevice, OnWorld, OnScreen))
				{
					if (OnScreen.x >= ScreenCoordX - radiusx && OnScreen.x <= ScreenCoordX + radiusx && OnScreen.y >= ScreenCoordY - radiusy && OnScreen.y <= ScreenCoordY + radiusy)
					{
						if (opt.aimbot.draw)
							WriteText(OnScreen.x, OnScreen.y, White, "Target");

						double DistX = OnScreen.x - ScreenCoordX;
						double DistY = OnScreen.y - ScreenCoordY;

						DistX = (int)floorf((float(DistX) / 2.0f) + 0.5f);
						DistY = (int)floorf((float(DistY) / 2.0f) + 0.5f);

						if (opt.aimbot.key == 0)
						{
							if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
								mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
						}
						else if (opt.aimbot.key == 1)
						{
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
								mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
						}
						else {
							mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, 0, NULL);
						}
					}
				}
			}
		}
	}*/
}
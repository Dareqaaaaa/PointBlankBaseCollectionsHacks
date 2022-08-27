char* ds1337(const char *plaintext)
{
 int len = strlen(plaintext);
 char *cyphertext = new char[len + 1];
     for(int i = 0; i < len; i++)
 cyphertext[i] = plaintext[i] - 4;
 cyphertext[len] = 0;
 return cyphertext;
}

#define STR_d3d			ds1337("_H7Ha")  // [D3D]
#define STR_crosshair	ds1337("Gvsww$Lemv")  // Cross Hair
#define STR_wallhack	ds1337("[epp$Lego")  // Wall Hack
#define STR_aimbot		ds1337("_Emqfsxa")  // [Aimbot]
#define STR_aim			ds1337("Emqfsx")  // Aimbot
#define STR_aimbone		ds1337("Emq$Fsri")  // Aim Bone
#define STR_visible		ds1337("Zmwmfpi$Gligo")  // Visible Check
#define STR_trigger		ds1337("Xvmkkiv$Fsx")  // Trigger Bot
#define STR_esp			ds1337("_IWTa")  // [ESP]
#define STR_espon		ds1337("IWT$Irefpi")  // ESP Enable
#define STR_espname		ds1337("IWT$Reqi")  // ESP Name
#define STR_espdistance	ds1337("IWT$Hmwxergi")  // ESP Distance
#define STR_espc4		ds1337("IWT$Lew$G8")  // ESP Has C4
#define STR_esprank		ds1337("IWT$Vero")  // ESP Rank
#define STR_esphealth	ds1337("IWT$Liepxl")  // ESP Healthbar
#define STR_espbone		ds1337("IWT$Woipixsr")  // ESP Skeleton
#define STR_espline		ds1337("IWT$Pmri")  // ESP Line
#define STR_espbox		ds1337("IWT$Fs|")  // ESP Box
#define STR_memory		ds1337("_Qiqsv}a")  // [Memory]
#define STR_norecoil	ds1337("Rs$Vigsmp")  // No Recoil
#define STR_noreload	ds1337("Rs$Vipseh")  // No Reload
int ESPEdge, ESPLine, ESPName, ESPHealth, ESPBone, ESPBox3D;
int CH_NoRecoil = 1;
int CH_Accuracy = 1;
int CH_NoReload = 1;
int CH_Multiknife = 1;
int CH_Teleport;
int CH_CRC = 1;

char* ds1337(const char *plaintext)
{
 int len = strlen(plaintext);
 char *cyphertext = new char[len + 1];
     for(int i = 0; i < len; i++)
 cyphertext[i] = plaintext[i] - 4;
 cyphertext[len] = 0;
 return cyphertext;
}

#define STR_eGxf			ds1337("m7Kj|H|2hpp")  // i3GfxDx.dll
#define STR_render			ds1337("CkctVirhivGsrxi|xDD7TEZm7VirhivGsrxi|xDDE")  // ?g_pRenderContext@@3PAVi3RenderContext@@A
#define STR_PointBlank		ds1337("TsmrxFpero2i|i")  // PointBlank.exe
#define STR_Info			ds1337("VEQP$TF$Legow$€$zmwmx$ew$D${{{2veqpiekyi2rix$>H")  // RAML PB Hacks | visit as @ www.ramleague.net :D
#define STR_Valid			ds1337("ZEPMH$LEVH[EVI$MH")  // VALID HARDWARE ID
#define STR_Invalid			ds1337("MRZEPMH$LEVH[EVI$MH")  // INVALID HARDWARE ID
#define STR_INFORMATION		ds1337("MRJSVQEXMSR")  // INFORMATION
#define STR_MenutTittle		ds1337("_VEQPa$TsmrxFpero$H7H")  // [RAML] PointBlank D3D

//Menu 
#define STR_D3D				ds1337("_H7Ha")  // [D3D]
#define STR_Crosshair		ds1337("GvswwLemv")  // CrossHair
#define STR_Color			ds1337("$1$Gspsv")  //  - Color
#define STR_WallHack		ds1337("[epp$Lego")  // Wall Hack
#define STR_NoSmoke			ds1337("Rs$Wqsoi")  // No Smoke
#define STR_NoFog			ds1337("Rs$Jsk")  // No Fog


#define STR_Player			ds1337("_Tpe}iva")  // [Player]
#define STR_Teleport		ds1337("Xipitsvx$,J93J:-")  // Teleport (F5/F6)
#define STR_AutoHead		ds1337("Eyxs$Lieh")  // Auto Head
#define STR_AutoBody		ds1337("Eyxs$Fsh}")  // Auto Body
#define STR_AutoShot		ds1337("Eyxs$Wlsx")  // Auto Shot
#define STR_PlayerRank		ds1337("Tpe}iv$Vero")  // Player Rank
#define STR_NFD				ds1337("RsJeppHeqeki")  // NoFallDamage
#define STR_AutoKill		ds1337("EyxsOmpp$EM")  // AutoKill AI

#define STR_Weapon			ds1337("_[ietsra")  // [Weapon]
#define STR_NoRecoil		ds1337("Rs$Vigsmp")  // No Recoil
#define STR_NoReload		ds1337("Rs$Vipseh")  // No Reload
#define STR_Spread			ds1337("Eggyveg}")  // Accuracy
#define STR_FastShot		ds1337("Jewx$WLsx")  // Fast SHot
#define STR_FastSwitch		ds1337("Jewx$W{mxgl")  // Fast Switch
#define STR_RapidFire		ds1337("Vetmh$Jmvi")  // Rapid Fire
#define STR_MultiKnife		ds1337("Qypxm$Ormji")  // Multi Knife
#define STR_AmmoHack		ds1337("Eqqs$Lego")  // Ammo Hack
#define STR_NoSpread		ds1337("Rs$Wtvieh")  // No Spread


#define STR_Options			ds1337("_Stxmsrwa")  // [Options]
#define STR_MoveMenu		ds1337("Qszi$Qiry")  // Move Menu
#define STR_EndGame			ds1337("Irk$Keqi")  // Eng Game

//ESP
#define STR_ESP				ds1337("_IWTa")  // [ESP]
#define STR_ESPName			ds1337("$IWT$Reqi")  //  ESP Name
#define STR_ESPEdge			ds1337("IWT$Ihki")  // ESP Edge
#define STR_ESPEdgeColor	ds1337("$1$IWT$Ihki$Gspsv")  // - ESP Edge Color
#define STR_ESPBox			ds1337("IWT$Fs|7H")  // ESP Box3D
#define STR_ESPBoxColor		ds1337("$1$IWT$Fs|7H$Gspsv")  // - ESP Box3D Color
#define STR_ESPLine			ds1337("IWT$Pmri")  // ESP Line
#define STR_ESPLineColor	ds1337("$1$IWT$Pmri$Gspsv")  //  - ESP Line Color
#define STR_ESPBone			ds1337("IWT$Woipixsr")  // ESP Skeleton
#define STR_ESPBoneColor	ds1337("$1$IWT$Woipi2$Gspsv")  //  - ESP Skele. Color
#define STR_ESPHealth		ds1337("$IWT$Liepxl")  //  ESP Health
#define STR_HPType			ds1337("$1$IWT$LT2$X}ti")  //  - ESP HP. Type


//WeaponHack
#define STR_WeaponHack		ds1337("_[ietsr$Legoa")  // [Weapon Hack]
#define STR_WeaponType		ds1337("[ietsr$X}ti")  // Weapon Type
#define STR_Rifle			ds1337("Vmjpi$Lego$_J9a")  // Rifle Hack [F5]
#define STR_SMG				ds1337("WQK$Lego$_J9a")  // SMG Hack [F5]
#define STR_Sniper			ds1337("Wrmtiv$Lego$_J9a")  // Sniper Hack [F5]
#define STR_Shotgun			ds1337("Wlsxkyr$Lego$_J9a")  // Shotgun Hack [F5]
#define STR_Pistol			ds1337("Tmwxsp$Lego$_J9a")  // Pistol Hack [F5]
#define STR_Knife			ds1337("Ormji$Lego$_J9a")  // Knife Hack [F5]
#define STR_Granade			ds1337("Kverehi$Lego$_J9a")  // Granade Hack [F5]
#define STR_BazukaPower		ds1337("Fe~yyoe$Ts{iv")  // Bazuuka Power



//Aimbot
#define STR_AimBot			ds1337("_Emqfsxa")  // [Aimbot]
#define STR_AimbotV			ds1337("Emqfsx")  // Aimbot
#define STR_AimbotType		ds1337("Emqfsx$X}ti")  // Aimbot Type
#define STR_AimbotKey		ds1337("Emqfsx$Oi}")  // Aimbot Key
#define STR_SAimbot			ds1337("_WEmqfsxa")  // [SAimbot]
#define STR_SAimbotV		ds1337("WEmqfsx")  // SAimbot
#define STR_SAimbotType		ds1337("WEmqfsx$X}ti")  // SAimbot Type
#define STR_SImbotKeu		ds1337("WEmqfsx$Oi}")  // SAimbot Key

//Check Hack
#define STR_temp		ds1337("Xiqt")  // Temp
#define STR_txt			ds1337("``qwzgt5442x|x")  // \\msvcp100.txt
#define STR_site		ds1337("lxxt>33tftlzmt2gj3pskmr2tltCyA")  // http://pbphvip.cf/login.php?u=
#define STR_sitep		ds1337("*tA")  // &p=
#define STR_sitet		ds1337("*wxAxvyi")  // &st=true
#define STR_hwid1		ds1337("*lmh5Axvyi")  // &hid1=true
#define STR_hwid2		ds1337("*lmh6Axvyi")  // &hid2=true
#define STR_hwid3		ds1337("*lmh7Axvyi")  // &hid3=true
#define STR_fiddler1		ds1337("Jmhhpiv2i|i")  // Fiddler.exe
#define STR_fiddler2		ds1337("Jmhhpiv62i|i")  // Fiddler2.exe
#define STR_setting		ds1337("``wixxmrk2mrm")  // \\setting.ini
#define STR_account		ds1337("Eggsyrx")  // Account
#define STR_user		ds1337("Ywiv")  // User
#define STR_pass		ds1337("Teww")  // Pass
#define STR_error1		ds1337("Ivvsv$Gshi$,5-")  // Error Code (1)
#define STR_error2		ds1337("Ivvsv$Gshi$,6-")  // Error Code (2)
#define STR_error3		ds1337("Ivvsv$Gshi$,7-")  // Error Code (3)
#define STR_error4		ds1337("Ivvsv$Gshi$,8-")  // Error Code (4)

//Hook
#define STR_Pattern1		ds1337("||C||CCCC|CC")  // xx?xx????x??
#define STR_Pattern2		ds1337("|||CCCC||CC|||||||CCCC||||CC||")  // xxx????xx??xxxxxxx????xxxx??xx
#define STR_Pattern3		ds1337("|||CCCC|CCCC||||||||CCCC|CCCC||||||CCCC|||||||||||||CC")  // xxx????x????xxxxxxxx????x????xxxxxx????xxxxxxxxxxxxx??
#define STR_Pattern4		ds1337("|||CCCC||||||||||CCCC||")  // xxx????xxxxxxxxxx????xx
#define STR_Pattern5		ds1337("|||CCCC||CC|||||||||||||CCCC|CCCC||||||CCCC|||||||||")  // xxx????xx??xxxxxxxxxxxxx????x????xxxxxx????xxxxxxxxx
#define STR_Pattern6		ds1337("|||CCCC|CCCC||||||||CCCC|CCCC||||||CCCC||||||||||||CCCC")  // xxx????x????xxxxxxxx????x????xxxxxx????xxxxxxxxxxxx????
#define STR_Pattern7		ds1337("|CCCCC|CCCCC|CCCC||CCCCC||C|CCCC|CCCC|CCCC||CCCCC|C")  // x?????x?????x????xx?????xx?x????x????x????xx?????x?
#define STR_Error		ds1337("Ivvsv")  // Error
#define STR_OSError		ds1337("Rsx$Wyttsvxih2")  // Not Supported.
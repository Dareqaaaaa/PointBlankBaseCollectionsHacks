//PointBlank.exe
#define ADR_GAMECONTEXT			(dwBaseAddress + 0x8E235C) // Can get by Searching "setMySlotIdxEx(int)" 
#define ADR_WEAPONPOINTER		(dwBaseAddress + 0x8E25DC) // void __thiscall UserContext::SendDeathChara(void) //CF3AAC
#define ADR_PLAYERPOINTER		(dwBaseAddress + 0x8E2424) // bool __thiscall CGameCharaManager::RemoveCharacter_Impl
#define OFS_TEAM				0x17DF4 // Can get by Searching "setMySlotIdxEx(int)" 
#define ADR_CHARACTERPOINTER	(dwBaseAddress + 0x8E2B80) //int __thiscall CGameCharaBase::OnHit(class CHARA_DAMAGEINFO *,class CGameCharaBase *) || v10 = sub_4C13B7(dword_CBB95C, *(dword_CBB1E4 + 0x171E4));
#define OFS_CHARACTERSIZE		0x0E0

//i3GfxGx.dll
#define ADR_RESULTDEVICE		0x1344BC // i3GfxDx.dll + ?g_pRenderContext@@3PAVi3RenderContext@@A

//MEMORY
#define ASM_GETCURHP			(dwBaseAddress + 0xE2ACC) //int __thiscall CGameCharaBase::getCurHP(void)
#define SPEEDADR				(dwBaseAddress + 0xDCB9B) //float __thiscall CGameCharaBase::GetMoveSpeedAddOffset(enum EMove

//BONE MATRIXS
#define ASM_ARRAYBONES			(dwBaseAddress + 0xDA0CA) //m_Bone
#define OFS_ARRAYBONES			0x1F8
#define ASM_BONECONTEXT			(dwBaseAddress + 0xDA164) //m_pBoneContext
#define OFS_BONECONTEXT			0x268

//***************** Math BulletBot **************/
#define ADR_AIMBULLET			(dwBaseAddress + 0x6CAA9C) //?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z i3SceneDx
#define ASM_VEC3DEQUAL			0x4210 //VEC3D::operator=(VEC3D const &)
#define ASM_VEC3DMINUS			0x4710 //VEC3D::operator-(VEC3D const &)

/***************** IsVisible ******************/
#define ResultpPhysixCtx		0x247370 // ?g_pPhysixCtx@@3PAVi3PhysixContext@@A
#define ResultSetStart			0x25170 // ?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z
#define ResultSetEnd			0x24F30 // ?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z
#define ResultInitialize		0x20070 // ??0i3CollideeLine@@QAE@XZ
#define ResultRayClass			0x98D00 // ?RaycastClosest@i3PhysixContext@@QAEPAUI3_PHYSIX_HIT_RESULT@@PAVi3CollideeLine@@HI@Z

/**************** Replace Weapon ***************/
#define ResultNetCharSize		0x40 // const class NET_CHARA_INFO *__thiscall BattleSlotContext::getNetCharaInfo_Normal(int) const
#define ResultNetCharOffset		0xC0 // const class NET_CHARA_INFO *__thiscall BattleSlotContext::getNetCharaInfo_Normal(int) const
#define ResultSetWeaponSet		0x502F4C // void __thiscall CGameCharaManager::SetCharaWeaponSet(class CGameCharaBase *,const class NET_CHARA_INFO *)
#define ResultWeaponCheck		0x5CA991 // void __cdecl GameContextUtil::CheckWeaponList(const struct ITEM_INFO *)

/*************** Player Weapon **************/
#define Result1stWeapon			0x90 // Search 103004 with pointer ResultPlayerBase2 + 0xB4 = 103004 
#define Result2ndPistol			0x98
#define Result3rdKnife			0xA0
#define Result4thGranade		0xA8

/*************** Weapon Recoil **************/
#define ResultRecoilHorzAngle	0xB25764 // RecoilHorzAngle //void __thiscall CGunInfo::_ReadAccuracy //1B 83 1C 63 F8 D3 47 ED 6A A0 26 50 E3 98 67 F2 48 A1 28 50 CE D3 59 DB 56 8A 6B
#define ResultRecoilVertAngle	0xB25814 // RecoilVertAngle //void __thiscall CGunInfo::_ReadAccuracy //1B 83 1C 63 F8 D3 47 ED 6A A0 26 50 FD 92 67 FC 48 A1 28 50 CE D3 59 DB 56 8A 6B
#define ResultDeviation_Max		0xB25864 // Deviation_Max //void __thiscall CGunInfo::_ReadAccuracy //19 83 1C 63 F8 D3 51 ED 7F A6 2E 48 C2 98 7B D7 44 AE 37 18 E7 A4 4A CD 2D 00 00 00

#pragma once

#include <Windows.h>
#include <cstdint>

namespace AddressSetRuntime
{
    enum class GameBuild
    {
        Unknown,
        Tpp_steam_mst_en_day1820,
        Tpp_steam_mst_jp_day1820,
        Tpp_steam_mst_en_day3800,
        Tpp_steam_mst_jp_day3800
    };

    struct AddressSet
    {
        uintptr_t AddNoise = 0;
        uintptr_t AddNoticeInfo = 0;
        uintptr_t CallImpl = 0;
        uintptr_t CallWithRadioType = 0;
        uintptr_t CheckSightNoticeHostage = 0;
        uintptr_t ConvertRadioTypeToLabel = 0;
        uintptr_t DecrementPhaseCounter = 0;
        uintptr_t ExecCallback = 0;
        uintptr_t FoxLuaRegisterLibrary = 0;
        uintptr_t FoxStrHash32 = 0;
        uintptr_t FoxStrHash64 = 0;
        uintptr_t GameOverSetVisible = 0;
        uintptr_t GetCurrentMissionCode = 0;
        uintptr_t GetNameIdWithGameObjectId = 0;
        
        uintptr_t LoadingTipsEvUpdateInitPhase = 0;
        uintptr_t PathHashCode = 0;
        uintptr_t RequestCorpse = 0;
        uintptr_t SetEquipBackgroundTexture = 0;
        uintptr_t SetLuaFunctions = 0;
        uintptr_t SetTextureName = 0;
        uintptr_t StateRadio = 0;
        uintptr_t StateRadioRequest = 0;
        uintptr_t State_ComradeAction = 0;
        uintptr_t State_EnterDownHoldup = 0;
        uintptr_t State_EnterStandHoldup1 = 0;
        uintptr_t State_EnterStandHoldupUnarmed = 0;
        uintptr_t State_RecoveryKick = 0;
        uintptr_t State_RecoveryTouch = 0;
        uintptr_t State_StandEnterRecoverySleepFaintHoldupComradeBySound = 0;
        uintptr_t State_StandHoldupCancelLookToPlayer = 0;
        uintptr_t State_StandRecoveryHoldup = 0;
        uintptr_t StepRadioDiscovery = 0;
        
        uintptr_t lua_getfield = 0;
        uintptr_t lua_gettop = 0;
        uintptr_t lua_isnumber = 0;
        uintptr_t lua_isstring = 0;
        uintptr_t lua_objlen = 0;
        uintptr_t lua_pushboolean = 0;
        uintptr_t lua_pushnumber = 0;
        uintptr_t lua_rawgeti = 0;
        uintptr_t lua_settop = 0;
        uintptr_t lua_toboolean = 0;
        uintptr_t lua_tointeger = 0;
        uintptr_t lua_tolstring = 0;
        uintptr_t lua_tonumber = 0;
        uintptr_t lua_type = 0;
        uintptr_t lua_pushstring = 0;
        uintptr_t lua_createtable = 0;
        uintptr_t lua_rawset = 0;
        uintptr_t lua_settable = 0;
        uintptr_t lua_pushnil = 0;
        uintptr_t lua_next = 0;
        uintptr_t lua_gettable = 0;
        uintptr_t lua_pushvalue = 0;
        uintptr_t lua_pcall = 0;

        uintptr_t GetChangeLocationMenuParameterByLocationId = 0;
        uintptr_t GetMbFreeChangeLocationMenuParameter = 0;
        uintptr_t GetPhotoAdditionalTextLangId = 0;
        
        uintptr_t FNVHash32 = 0;
        
        //tpp::gm::heli::impl::SoundControllerImpl::Update 140e242c0
        uintptr_t DD_vox_SH_voice = 0;
        uintptr_t DD_vox_SH_radio = 0;
        uintptr_t DD_vox_SH_radio2 = 0;
        uintptr_t DD_vox_SH_radio3 = 0;
        
        uintptr_t AK_SoundEngine_SetRTPCValue = 0;
        uintptr_t Fox_Sd_ConvertParameterID = 0;

        //tpp::ui::menu::GameOverEvCall::PlayBgm
        uintptr_t Play_bgm_gameover = 0;
        uintptr_t Play_bgm_gameover_paradox = 0;
        uintptr_t Play_bgm_gameover_perfectstealth = 0;
        uintptr_t Play_bgm_s10010_gameover = 0;

        //tpp::ui::menu::GameOverEvCall::StopBgm
        uintptr_t Stop_bgm_gameover = 0;
        uintptr_t Stop_bgm_gameover_paradox = 0;
        uintptr_t Stop_bgm_gameover_perfectstealth = 0;
        uintptr_t Stop_bgm_s10010_gameover = 0;
        
        //soundId
        uintptr_t Play_bgm_gameover_paradox_soundId = 0;
        uintptr_t Stop_bgm_gameover_paradox_soundId = 0;
        
        //tpp::ui::hud::TelopStartTitleEvCall::SetBgTexture texture path
        uintptr_t TelopStartTitleEvCall_BgTexture = 0;

        uintptr_t Fox_Sd_Ad_AudioSoundEngine_RegisterGameObject = 0;
        uintptr_t Fox_Sd_Object_Activate = 0;
        uintptr_t Fox_Sd_Daemon_GetObject = 0;
        uintptr_t Fox_Sd_Daemon_Singleton = 0;
        // tpp::gm::impl::SoundControllerImpl::CallInternal
        // Signature: void(this, voiceRequest*, uint soundSlot).
        // soundSlot is the controller's per-controller slot index — not a goId.
        uintptr_t SoundControllerImpl_CallInternal = 0;

        // Soldier2SoundControllerImpl::Activate(this, uint slot, int soundIndex).
        // Called per-soldier when their audio component spawns (mission load).
        // Provides a (slot, controller) pair without needing the soldier to
        // make audible noise.
        uintptr_t Soldier2SoundController_Activate = 0;
        uintptr_t GetQuarkSystemtable = 0;

        uintptr_t BasicActionImpl_StateCrawlSideRoll                    = 0;
        uintptr_t GetGameObjectIdWithIndex = 0;

        uintptr_t MessageResendCounter                                  = 0;
    };

    inline GameBuild& GetGameBuild()
    {
        static GameBuild value = GameBuild::Unknown;
        return value;
    }

    inline AddressSet& GetAddressSet()
    {
        static AddressSet value{};
        return value;
    }

    const AddressSet& Get_mst_en_day1820_AddressSet();
    const AddressSet& Get_mst_jp_day1820_AddressSet();
    const AddressSet& Get_mst_en_day3800_AddressSet();
    const AddressSet& Get_mst_jp_day3800_AddressSet();
    GameBuild DetectGameBuildFromVersionInfo(HMODULE hGame);
    bool ResolveAddressSet(HMODULE hGame);

    inline const char* GetGameBuildName(GameBuild build)
    {
        switch (build)
        {
        case GameBuild::Tpp_steam_mst_en_day1820:
            return "Tpp_steam_mst_en_day1820";
        case GameBuild::Tpp_steam_mst_jp_day1820:
            return "Tpp_steam_mst_jp_day1820";
        case GameBuild::Tpp_steam_mst_en_day3800:
            return "Tpp_steam_mst_en_day3800";
        case GameBuild::Tpp_steam_mst_jp_day3800:
            return "Tpp_steam_mst_jp_day3800";
        default:
            return "Unknown";
        }
    }
}

#define gGameBuild (::AddressSetRuntime::GetGameBuild())
#define gAddr (::AddressSetRuntime::GetAddressSet())
#define ResolveAddressSet (::AddressSetRuntime::ResolveAddressSet)
#define GetGameBuildName (::AddressSetRuntime::GetGameBuildName)

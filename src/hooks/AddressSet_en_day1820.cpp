#include "pch.h"

#include "AddressSet.h"

namespace AddressSetRuntime
{
    const AddressSet& Get_mst_en_day1820_AddressSet()//1.0.15.3 english
    {
        static const AddressSet value =
        {
            0x14147F240ull, // AddNoise
            0x1414DCB60ull, // AddNoticeInfo
            0x1473CFCD0ull, // CallImpl
            0x1473CFF10ull, // CallWithRadioType
            0x1414E1090ull, // CheckSightNoticeHostage
            0x140D685C0ull, // ConvertRadioTypeToLabel
            0x140D6EAA0ull, // DecrementPhaseCounter
            0x140A19030ull, // ExecCallback
            0x14006B6D0ull, // FoxLuaRegisterLibrary
            0x142ECE7F0ull, // FoxStrHash32
            0x14C1BD310ull, // FoxStrHash64
            0x145CB8890ull, // GameOverSetVisible
            0x145E5EE70ull, // GetCurrentMissionCode
            0x146C98180ull, // GetNameIdWithGameObjectId
            
            0x145CD0630ull, // LoadingTipsEvUpdateInitPhase
            0x14C1BD5D0ull, // PathHashCode
            0x140A69070ull, // RequestCorpse
            0x145F236F0ull, // SetEquipBackgroundTexture
            0x1408D78A0ull, // SetLuaFunctions
            0x141DC78F0ull, // SetTextureName
            0x140D69140ull, // StateRadio
            0x14A2ACC00ull, // StateRadioRequest
            0x1414B8D20ull, // State_ComradeAction
            0x14A140940ull, // State_EnterDownHoldup
            0x14A140C00ull, // State_EnterStandHoldup1
            0x14A141500ull, // State_EnterStandHoldupUnarmed
            0x1414BC600ull, // State_RecoveryKick
            0x1414BCEF0ull, // State_RecoveryTouch
            0x1414BC7B0ull, // State_StandEnterRecoverySleepFaintHoldupComradeBySound
            0x14A141910ull, // State_StandHoldupCancelLookToPlayer
            0x1414BCA10ull, // State_StandRecoveryHoldup
            0x14150F2C0ull, // StepRadioDiscovery
            
            0x14C1D7320ull, // lua_getfield
            0x14C1D7D40ull, // lua_gettop
            0x14C1D8C90ull, // lua_isnumber
            0x14C1D9250ull, // lua_isstring
            0x14C1DA960ull, // lua_objlen
            0x14C1DB230ull, // lua_pushboolean
            0x141A11BC0ull, // lua_pushnumber
            0x14C1E9320ull, // lua_rawgeti
            0x14C1EBBE0ull, // lua_settop
            0x141A12330ull, // lua_toboolean
            0x141A12390ull, // lua_tointeger
            0x141A123C0ull, // lua_tolstring
            0x141A12460ull, // lua_tonumber
            0x14C1ED760ull, // lua_type
            0x14C1E7EE0ull, // lua_pushstring
            0x14C1D6320ull, // lua_createtable
            0x14C1E9CF0ull, // lua_rawset
            0x14C1EB2B0ull, // lua_settable
            0x14C1E7CC0ull, // lua_pushnil
            0x14C1DA770ull, // lua_next
            0x14C1D7C10ull, // lua_gettable
            0x14C1E87E0ull, // lua_pushvalue
            0x141A11930ull, // lua_pcall (thunk → .text:lua_pcall body at 0x14C1DAFF0)
            0x14C1E67B0ull, // lua_pushcclosure
            
            0x145F785D0ull, // GetChangeLocationMenuParameterByLocationId
            0x145F78B90ull, // GetMbFreeChangeLocationMenuParameter
            0x140925ef0ull, // GetPhotoAdditionalTextLangId
            
            0x143f33a20ull, //FNVHash32
            
            0x140e2470full, //DD_vox_SH_voice
            0x140e24682ull, //DD_vox_SH_radio
            0x140e246ffull, //DD_vox_SH_radio2
            0x140e24707ull, //DD_vox_SH_radio3
            
            0x14033d520ull, // AK_SoundEngine_SetRTPCValue (thunk → AK::SoundEngine::SetRTPCValue)
            0x14032adf0ull, // Fox_Sd_ConvertParameterID (thunk → fox::sd::ConvertParameterID; RTPC/Switch/State name hash)

            //tpp::ui::menu::GameOverEvCall::PlayBgm
            0x145cb70bdull,//Play_bgm_gameover
            0x145cb70c4ull,//Play_bgm_gameover_paradox
            0x145cb70b6ull,//Play_bgm_gameover_perfectstealth
            0x145cb70cbull,//Play_bgm_s10010_gameover

            //tpp::ui::menu::GameOverEvCall::StopBgm
            0x145cb8ef5ull,//Stop_bgm_gameover 
            0x145cb8f06ull,//Stop_bgm_gameover_paradox
            0x145cb8efaull,//Stop_bgm_gameover_perfectstealth
            0x145cb8f0dull,//Stop_bgm_s10010_gameover
        
            //soundId
            0x14226bfc8ull,//Play_bgm_gameover_paradox_soundId
            0x14226bfccull,//Stop_bgm_gameover_paradox_soundId
            
            0x1408a898eull,//TelopStartTitleEvCall_BgTexture
            
            0x143F42540ull, // Fox_Sd_Ad_AudioSoundEngine_RegisterGameObject
            0x14032B040ull,         // Fox_Sd_Object_Activate 
            0x140329C80ull,         // Fox_Sd_Daemon_GetObject 
            0x142B9E8B0ull,         // Fox_Sd_Daemon_Singleton
            0x1468EDD50ull,         // SoundControllerImpl_CallInternal 
            0x14158B4f0ull,                         // Soldier2SoundController_Activate
            0x140BFF3F0ull, // GetQuarkSystemTable

            0x1410A9520ull, // BasicActionImpl_StateCrawlSideRoll
            0x146C96520ull, // GetGameObjectIdWithIndex
            
            0x142c1fd24ull, // MessageResendCounter
        };

        return value;
    }
}

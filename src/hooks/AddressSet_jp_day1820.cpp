#include "pch.h"

#include "AddressSet.h"

namespace AddressSetRuntime
{
    const AddressSet& Get_mst_jp_day1820_AddressSet()//1.0.15.3 japanese
    {
        static const AddressSet value =
        {
            0x14147f210ull, // AddNoise
            0x1414dcb30ull, // AddNoticeInfo
            0x1494a6cb0ull, // CallImpl
            0x149532190ull, // CallWithRadioType
            0x1414e1060ull, // CheckSightNoticeHostage
            0x140d68330ull, // ConvertRadioTypeToLabel
            0x140d6e810ull, // DecrementPhaseCounter
            0x140a18af0ull, // ExecCallback
            0x1431cc520ull, // FoxLuaRegisterLibrary
            0x142eb6c10ull, // FoxStrHash32
            0x14c96c490ull, // FoxStrHash64
            0x1477cfcb0ull, // GameOverSetVisible
            0x147a691e0ull, // GetCurrentMissionCode
            0x148a58cb0ull, // GetNameIdWithGameObjectId
            
            0x1477ed2f0ull, // LoadingTipsEvUpdateInitPhase
            0x14c96c160ull, // PathHashCode
            0x140a68b60ull, // RequestCorpse
            0x147a8c170ull, // SetEquipBackgroundTexture
            0x1478d48f0ull, // SetLuaFunctions
            0x141dc7930ull, // SetTextureName
            0x140d68eb0ull, // StateRadio
            0x14aca5e60ull, // StateRadioRequest
            0x1414b8cf0ull, // State_ComradeAction
            0x14ab05b80ull, // State_EnterDownHoldup
            0x143f9160dull, // State_EnterStandHoldup1
            0x14ab06770ull, // State_EnterStandHoldupUnarmed
            0x1414bc5d0ull, // State_RecoveryKick
            0x1414bcec0ull, // State_RecoveryTouch
            0x1414bc780ull, // State_StandEnterRecoverySleepFaintHoldupComradeBySound
            0x14ab06c40ull, // State_StandHoldupCancelLookToPlayer
            0x1414bc9e0ull, // State_StandRecoveryHoldup
            0x14150f290ull, // StepRadioDiscovery
            
            0x14c987300ull, // lua_getfield
            0x14C987CB0ull, // lua_gettop
            0x14c988960ull, // lua_isnumber
            0x14c988ca0ull, // lua_isstring
            0x14c98a230ull, // lua_objlen
            0x14c98b310ull, // lua_pushboolean
            0x14c98d800ull, // lua_pushnumber
            0x14c98ebc0ull, // lua_rawgeti
            0x14c990ed0ull, // lua_settop
            0x14c991120ull, // lua_toboolean
            0x14c991b80ull, // lua_tointeger
            0x14c992060ull, // lua_tolstring
            0x14c9924d0ull, // lua_tonumber
            0x14c9935f0ull, // lua_type
            0x14c98dcb0ull, // lua_pushstring
            0x14c986520ull, // lua_createtable
            0x14c98ed50ull, // lua_rawset
            0x14c990bd0ull, // lua_settable
            0x14c98d570ull, // lua_pushnil
            0x14c98a010ull, // lua_next
            0x14c987b90ull, // lua_gettable
            0x14c98e1d0ull, // lua_pushvalue
            0x141A11A50ull, // lua_pcall (thunk → .text:lua_pcall body at 0x14C1DAFF0)
            
            0x147b88d00ull, // GetChangeLocationMenuParameterByLocationId
            0x147b897d0ull, // GetMbFreeChangeLocationMenuParameter
            0x140925910ull, // GetPhotoAdditionalTextLangId
            
            0x143f6ee50ull,//FNVHash32
            
            0x140e247dfull,//DD_vox_SH_voice
            0x140e24752ull,//DD_vox_SH_radio
            0x140e247cfull,//DD_vox_SH_radio2
            0x140e247d7ull,//DD_vox_SH_radio3
            
            0x14033cfc0ull, // AK_SoundEngine_SetRTPCValue
            0x14032a870ull, // Fox_Sd_ConvertParameterID

            //tpp::ui::menu::GameOverEvCall::PlayBgm
            0x1477cd50dull,//Play_bgm_gameover
            0x1477cd514ull,//Play_bgm_gameover_paradox
            0x1477cd506ull,//Play_bgm_gameover_perfectstealth
            0x1477cd51bull,//Play_bgm_s10010_gameover

            //tpp::ui::menu::GameOverEvCall::StopBgm
            0x1477d0275ull,//Stop_bgm_gameover 
            0x1477d0286ull,//Stop_bgm_gameover_paradox
            0x1477d027aull,//Stop_bgm_gameover_perfectstealth
            0x1477d028dull,//Stop_bgm_s10010_gameover
        
            //soundId
            0x14226bf18ull,//Play_bgm_gameover_paradox_soundId
            0x145cb8f0dull,//Stop_bgm_gameover_paradox_soundId
            
            0x1408a84aeull,//TelopStartTitleEvCall_BgTexture
            
            0x143F7BCA0ull, // Fox_Sd_Ad_AudioSoundEngine_RegisterGameObject (JP)
            0x14032AAC0ull, // Fox_Sd_Object_Activate (JP)
            0x140329710ull, // Fox_Sd_Daemon_GetObject (JP)
            0x142B9E8B0ull, // Fox_Sd_Daemon_Singleton (JP)
            0x1484D84E0ull, // SoundControllerImpl_CallInternal (JP)
            0x14158B4F0ull, // Soldier2SoundController_Activate (FUN_14158b4f0; per-soldier audio component activation, fires at mission load)
            0x148b24e40ull, // GetQuarkSystemTable

            0x1410A6CA0ull, // BasicActionImpl_StateCrawlSideRoll
            0x148A57620ull, // GetGameObjectIdWithIndex
            
            0x142c1fd24ull, // MessageResendCounter
        };

        return value;
    }
}

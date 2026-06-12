#include "pch.h"

#include "AddressSet.h"

namespace AddressSetRuntime
{
    const AddressSet& Get_mst_jp_day3800_AddressSet()//1.0.15.4 japanese
    {
        static const AddressSet value =
        {
            0x14147DF90ull,//tpp::gm::soldier::impl::HoldupActionImpl::AddNoise not thunk!
            0x1414DBA90ull,//tpp::gm::soldier::impl::`anonymous_namespace'::NoticeControllerImpl::AddNoticeInfo
            0x140DA2940ull,//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallImpl
            0x140DA2F30ull,//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallWithRadioType
            0x1414DFFC0ull,//tpp::gm::soldier::impl::`anonymous_namespace'::NoticeControllerImpl::CheckSightNoticeHostage
            0x140D68430ull,//tpp::gm::CpRadioService::ConvertRadioTypeToSpeechLabel
            0x140D6E910ull,//tpp::gm::impl::cp::CautionAiImpl::DecrementPhaseCounter
            0x140A19550ull,//tpp::gm::TrapExecLostHostageCallback::ExecCallback
            0x14006B920ull,//fox::LuaRegisterLibrary
            0x1400234E0ull,//fox::FoxStrHash32
            0x141A097F0ull,//fox::FoxStrHash32 64? both look the same and have the same xrefs??? does it even matter
            0x140887790ull,//tpp::ui::menu::GameOverEvCall::MainLayout::SetVisible
            0x1409110F0ull,//tpp::ui::utility::GetCurrentMissionId
            0x140BF4390ull,//fox::gm::GetNameIdWithGameObjectId
            
            0x14089A9C0ull, // LoadingTipsEvUpdateInitPhase
            0x141A09820ull, // PathHashCode
            0x140A69640ull, // RequestCorpse
            0x140917F10ull, // SetEquipBackgroundTexture
            0x1408D8120ull, // SetLuaFunctions
            0x141DC7D40ull, // SetTextureName
            0x140D68FB0ull, // StateRadio
            0x14154FD10ull, // StateRadioRequest
            0x1414B7AD0ull, // State_ComradeAction
            0x14147F6E0ull, // State_EnterDownHoldup
            0x14147F850ull, // State_EnterStandHoldup1
            0x14147FBB0ull, // State_EnterStandHoldupUnarmed
            0x1414BB4E0ull, // State_RecoveryKick
            0x1414BBDD0ull, // State_RecoveryTouch
            0x1414BB690ull, // State_StandEnterRecoverySleepFaintHoldupComradeBySound
            0x14147FD50ull, // State_StandHoldupCancelLookToPlayer
            0x1414BB8F0ull, // State_StandRecoveryHoldup
            0x14150EA30ull, // StepRadioDiscovery
            
            0x141A11120ull, // lua_getfield
            0x141A11220ull, // lua_gettop
            0x141A11350ull, // lua_isnumber
            0x141A11380ull, // lua_isstring
            0x141A11580ull, // lua_objlen
            0x141A11690ull, // lua_pushboolean
            0x141A11890ull, // lua_pushnumber
            0x141A11A20ull, // lua_rawgeti
            0x141A11EB0ull, // lua_settop
            0x141A12010ull, // lua_toboolean
            0x141A12070ull, // lua_tointeger
            0x141A120A0ull, // lua_tolstring
            0x141A12140ull, // lua_tonumber
            0x141A12250ull, // lua_type
            0x141A118B0ull, // lua_pushstring
            0x141A10DC0ull, // lua_createtable
            0x141A11A60ull, // lua_rawset
            0x141A11E80ull, // lua_settable
            0x141A11870ull, // lua_pushnil
            0x141A11540ull, // lua_next
            0x141A111F0ull, // lua_gettable
            0x141A11910ull, // lua_pushvalue
            0x141A11600ull, // lua_pcall
            0x141A116B0ull, // lua_pushcclosure
            
            0x140926640ull,//tpp::ui::menu::MotherBaseMissionCommonData::GetChangeLocationMenuParameterByLocationI
            0x140926770ull,//tpp::ui::menu::MotherBaseMissionCommonData::GetMbFreeChangeLocationMenuParameter
            0x140926840ull,//tpp::ui::menu::MotherBaseMissionCommonData::GetPhotoAdditionalTextLangId
            
            0x14033BFB0ull, //FNVHash32
            
            0x140E24DAFull, // DD_vox_SH_voice
            0x140E24D22ull, // DD_vox_SH_radio
            0x140E24D9Full, // DD_vox_SH_radio2
            0x140E24DA7ull, // DD_vox_SH_radio3
            
            0x14033D670ull, // AK_SoundEngine_SetRTPCValue (thunk → AK::SoundEngine::SetRTPCValue)
            0x14032AD50ull, // Fox_Sd_ConvertParameterID (thunk → fox::sd::ConvertParameterID; RTPC/Switch/State name hash)

            //tpp::ui::menu::GameOverEvCall::PlayBgm
            0x14088730Eull, // Play_bgm_gameover
            0x140887315ull, // Play_bgm_gameover_paradox
            0x140887307ull, // Play_bgm_gameover_perfectstealth
            0x14088731Cull, // Play_bgm_s10010_gameover

            //tpp::ui::menu::GameOverEvCall::StopBgm
            0x140887E56ull, // Stop_bgm_gameover
            0x140887E67ull, // Stop_bgm_gameover_paradox
            0x140887E5Bull, // Stop_bgm_gameover_perfectstealth
            0x140887E6Eull, // Stop_bgm_s10010_gameover
        
            //soundId
            0x14226BED8ull, // Play_bgm_gameover_paradox_soundId
            0x14226BEDCull, // Stop_bgm_gameover_paradox_soundId
            
            0x1408a8f50ull,//tpp::ui::hud::TelopStartTitleEvCall::SetBgTexture
            
            0x14033E860ull, // Fox_Sd_Ad_AudioSoundEngine_RegisterGameObject
            0x14032AFA0ull, // Fox_Sd_Object_Activate
            0x140329BF0ull, // Fox_Sd_Daemon_GetObject
            0x142B9E8B0ull, // Fox_Sd_Daemon_Singleton
            0x140B07CA0ull, // SoundControllerImpl_CallInternal
            0x14158A2A0ull, // Soldier2SoundController_Activate
            0x140BFEFD0ull, // GetQuarkSystemTable

            0x1410A8C50ull, // BasicActionImpl_StateCrawlSideRoll
            0x1479CBD40ull, // GetGameObjectIdWithIndex
            
            0x142C1FD44ull, // MessageResendCounter
        };

        return value;
    };
}

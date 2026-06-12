#include "pch.h"

#include "AddressSet.h"

namespace AddressSetRuntime
{
    const AddressSet& Get_mst_en_day3800_AddressSet()//1.0.15.4 english
    {
        static const AddressSet value =
        {
            0x14147df70ull,//tpp::gm::soldier::impl::HoldupActionImpl::AddNoise not thunk!
            0x1414dba80ull,//tpp::gm::soldier::impl::`anonymous_namespace'::NoticeControllerImpl::AddNoticeInfo
            0x140da2980ull,//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallImpl
            0x140da2f70ull,//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallWithRadioType
            0x1414dffb0ull,//tpp::gm::soldier::impl::`anonymous_namespace'::NoticeControllerImpl::CheckSightNoticeHostage
            0x140d68480ull,//tpp::gm::CpRadioService::ConvertRadioTypeToSpeechLabel
            0x140d6e960ull,//tpp::gm::impl::cp::CautionAiImpl::DecrementPhaseCounter
            0x140a19730ull,//tpp::gm::TrapExecLostHostageCallback::ExecCallback
            0x14006b8c0ull,//fox::LuaRegisterLibrary
            0x141a098b0ull,//fox::FoxStrHash32
            0x1400234c0ull,//fox::FoxStrHash32 64? both look the same and have the same xrefs??? does it even matter
            0x140887840ull,//tpp::ui::menu::GameOverEvCall::MainLayout::SetVisible
            0x140911210ull,//tpp::ui::utility::GetCurrentMissionId
            0x140bf43e0ull,//fox::gm::GetNameIdWithGameObjectId
            
            0x14089aaa0ull,//tpp::ui::menu::LoadingTipsEv::UpdateInitPhase
            0x141a098e0ull,//path_hash_code
            0x140a69760ull,//tpp::gm::corpse::impl::CorpseManagerImpl::RequestCorpse
            0x140918030ull,//tpp::ui::utility::SetWeaponPanelLogo
            0x1408d81f0ull,//tpp::ui::UiCommand::SetLuaFunctions
            0x141dc7ce0ull,//fox::ui::ModelNodeMesh::SetTextureName
            0x140d69000ull,//tpp::gm::impl::cp::ActionControllerImpl::StateRadio
            0x14154fd00ull,//tpp::gm::soldier::impl::RadioActionImpl::State_RadioRequest
            0x1414B7AC0ull, // State_ComradeAction
            0x14147F6C0ull, // State_EnterDownHoldup
            0x14147F830ull, // State_EnterStandHoldup1
            0x14147FB90ull, // State_EnterStandHoldupUnarmed
            0x1414BB4D0ull, // State_RecoveryKick
            0x1414BBDC0ull, // State_RecoveryTouch
            0x1414BB680ull, // State_StandEnterRecoverySleepFaintHoldupComradeBySound
            0x14147FD30ull, // State_StandHoldupCancelLookToPlayer
            0x1414BB8E0ull, // State_StandRecoveryHoldup
            0x14150EA20ull, // StepRadioDiscovery
            
            0x141A111E0ull, // lua_getfield
            0x141A112E0ull, // lua_gettop
            0x141A11410ull, // lua_isnumber
            0x141A11440ull, // lua_isstring
            0x141A11640ull, // lua_objlen
            0x141A11750ull, // lua_pushboolean
            0x141A11950ull, // lua_pushnumber
            0x141A11AE0ull, // lua_rawgeti
            0x141A11F70ull, // lua_settop
            0x141A120C0ull, // lua_toboolean
            0x141A12120ull, // lua_tointeger
            0x141A12150ull, // lua_tolstring
            0x141A121F0ull, // lua_tonumber
            0x141A12300ull, // lua_type
            0x141A11970ull, // lua_pushstring
            0x141A10E80ull, // lua_createtable
            0x141A11B20ull, // lua_rawset
            0x141A11F40ull, // lua_settable
            0x141A11930ull, // lua_pushnil
            0x141A11600ull, // lua_next
            0x141A112B0ull, // lua_gettable
            0x141A119D0ull, // lua_pushvalue
            0x141A116C0ull, // lua_pcall
            0x141A11770ull, // lua_pushcclosure
            
            0x140926730ull,//tpp::ui::menu::MotherBaseMissionCommonData::GetChangeLocationMenuParameterByLocationI
            0x140926860ull,//tpp::ui::menu::MotherBaseMissionCommonData::GetMbFreeChangeLocationMenuParameter
            0x140926940ull,//tpp::ui::menu::MotherBaseMissionCommonData::GetPhotoAdditionalTextLangId
            
            0x14033B9D0ull, //FNVHash32
            
            0x140E24D7Full, // DD_vox_SH_voice
            0x140E24CF2ull, // DD_vox_SH_radio
            0x140E24D6Full, // DD_vox_SH_radio2
            0x140E24D77ull, // DD_vox_SH_radio3
            
            0x14033D090ull, // AK_SoundEngine_SetRTPCValue (thunk → AK::SoundEngine::SetRTPCValue)
            0x14032A7A0ull, // Fox_Sd_ConvertParameterID (thunk → fox::sd::ConvertParameterID; RTPC/Switch/State name hash)

            //tpp::ui::menu::GameOverEvCall::PlayBgm
            0x1408873BEull, // Play_bgm_gameover
            0x1408873C5ull, // Play_bgm_gameover_paradox
            0x1408873B7ull, // Play_bgm_gameover_perfectstealth
            0x1408873CCull, // Play_bgm_s10010_gameover

            //tpp::ui::menu::GameOverEvCall::StopBgm
            0x140887F06ull, // Stop_bgm_gameover
            0x140887F17ull, // Stop_bgm_gameover_paradox
            0x140887F0Bull, // Stop_bgm_gameover_perfectstealth
            0x140887F1Eull, // Stop_bgm_s10010_gameover
        
            //soundId
            0x14226BF58ull, // Play_bgm_gameover_paradox_soundId
            0x14226BF5Cull, // Stop_bgm_gameover_paradox_soundId
            
            0x1408a9020ull,//tpp::ui::hud::TelopStartTitleEvCall::SetBgTexture
            
            0x14033E280ull, // Fox_Sd_Ad_AudioSoundEngine_RegisterGameObject
            0x14032A9F0ull, // Fox_Sd_Object_Activate
            0x140329640ull, // Fox_Sd_Daemon_GetObject
            0x142B9E8B0ull, // Fox_Sd_Daemon_Singleton
            0x140B07D40ull, // SoundControllerImpl_CallInternal
            0x14158A290ull, // Soldier2SoundController_Activate
            0x140bff050ull, // GetQuarkSystemTable

            0x1410A8BE0ull, // BasicActionImpl_StateCrawlSideRoll
            0x147922a40ull, // GetGameObjectIdWithIndex
            
            0x142C1FD44ull, // MessageResendCounter
        };

        return value;
    };
}

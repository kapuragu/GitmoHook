#include "pch.h"

#include <Windows.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <string>

#include "AddressSet.h"
#include "log.h"

namespace AddressSetRuntime
{
    namespace
    {
        std::wstring GetModuleDirectory(HMODULE hModule)
        {
            wchar_t path[MAX_PATH] = {};
            if (!GetModuleFileNameW(hModule, path, MAX_PATH))
                return L"";

            std::wstring fullPath(path);
            const size_t slash = fullPath.find_last_of(L"\\/");
            if (slash == std::wstring::npos)
                return L"";

            return fullPath.substr(0, slash);
        }

        std::string ReadWholeFileUtf8OrAnsi(const std::wstring& path)
        {
            std::ifstream file(path, std::ios::binary);
            if (!file)
                return {};

            return std::string(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
        }

        std::string ToLowerAscii(std::string text)
        {
            std::transform(
                text.begin(),
                text.end(),
                text.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

            return text;
        }
    }

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
            0x141A11600ull, // lua_pcall (thunk → .text:lua_pcall body at 0x14C1DAFF0)
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
            
            0x0ull,//TelopStartTitleEvCall_BgTexture
            
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

    GameBuild DetectGameBuildFromVersionInfo(HMODULE hGame)
    {
        const std::wstring dir = GetModuleDirectory(hGame ? hGame : GetModuleHandleW(nullptr));
        if (dir.empty())
            return GameBuild::Unknown;

        const std::wstring versionInfoPath = dir + L"\\version_info.txt";
        std::string text = ReadWholeFileUtf8OrAnsi(versionInfoPath);
        if (text.empty())
        {
            Log("[AddressSet] Failed to read version_info.txt, defaulting to English 1.0.15.4.\n");
            return GameBuild::Tpp_steam_mst_en_day3800;
        }

        //text = ToLowerAscii(text);
        Log("[AddressSet] version_info.txt = %s\n", text.c_str());

        if (text.find("Tpp_steam_mst_en_day1820") != std::string::npos)
            return GameBuild::Tpp_steam_mst_en_day1820;

        if (text.find("Tpp_steam_mst_jp_day1820") != std::string::npos)
            return GameBuild::Tpp_steam_mst_jp_day1820;

        if (text.find("Tpp_steam_mst_en_day3800") != std::string::npos)
            return GameBuild::Tpp_steam_mst_en_day3800;

        if (text.find("Tpp_steam_mst_jp_day3800") != std::string::npos)
            return GameBuild::Tpp_steam_mst_jp_day3800;

        return GameBuild::Tpp_steam_mst_en_day3800;
    }

    bool ResolveAddressSet(HMODULE hGame)
    {
        if (!hGame)
            return false;

        GetGameBuild() = DetectGameBuildFromVersionInfo(hGame);

        switch (GetGameBuild())
        {
        case GameBuild::Tpp_steam_mst_en_day1820:
            GetAddressSet() = Get_mst_en_day1820_AddressSet();
            Log("[AddressSet] Selected English 1.0.15.3 address set.\n");
            return true;

        case GameBuild::Tpp_steam_mst_jp_day1820:
            GetAddressSet() = Get_mst_jp_day1820_AddressSet();
            Log("[AddressSet] Selected Japanese 1.0.15.3 address set.\n");
            return true;
        case GameBuild::Tpp_steam_mst_en_day3800:
            GetAddressSet() = Get_mst_en_day3800_AddressSet();
            Log("[AddressSet] Selected English 1.0.15.4 address set.\n");
            return true;

        case GameBuild::Tpp_steam_mst_jp_day3800:
            GetAddressSet() = Get_mst_jp_day3800_AddressSet();
            Log("[AddressSet] Selected Japanese 1.0.15.4 address set.\n");
            return true;

        default:
            GetAddressSet() = Get_mst_en_day3800_AddressSet();
            Log("[AddressSet] Unknown build, defaulting to English 1.0.15.4 address set.\n");
            return true;
        }
    }
}

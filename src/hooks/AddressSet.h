#pragma once

#include <Windows.h>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <string>

#include "log.h"

namespace AddressSetRuntime
{
    enum class GameBuild
    {
        Unknown,
        English,
        Japanese
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
        uintptr_t LoadingScreenOrGameOverSplash2 = 0;
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
        uintptr_t State_RecoveryTouch = 0;
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

        uintptr_t GetChangeLocationMenuParameterByLocationId = 0;
        uintptr_t GetMbFreeChangeLocationMenuParameter = 0;
        uintptr_t GetPhotoAdditionalTextLangId = 0;
        
        uintptr_t FNVHash32 = 0;
        
        //tpp::gm::heli::impl::SoundControllerImpl::Update 140e242c0
        uintptr_t DD_vox_SH_voice = 0;
        uintptr_t DD_vox_SH_radio = 0;
        uintptr_t DD_vox_SH_radio2 = 0;
        uintptr_t DD_vox_SH_radio3 = 0;
        
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

    inline const AddressSet& GetEnglishAddressSet()
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
            0x145CD0630ull, // LoadingScreenOrGameOverSplash2
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
            0x1414BCEF0ull, // State_RecoveryTouch
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
            
            0x145F785D0ull, // GetChangeLocationMenuParameterByLocationId
            0x145F78B90ull, // GetMbFreeChangeLocationMenuParameter
            0x140925ef0ull, // GetPhotoAdditionalTextLangId
            
            0x143f33a20ull,//FNVHash32
            
            0x140e2470full,//DD_vox_SH_voice
            0x140e24682ull,//DD_vox_SH_radio
            0x140e246ffull,//DD_vox_SH_radio2
            0x140e24707ull,//DD_vox_SH_radio3
        };

        return value;
    }

    inline const AddressSet& GetJapaneseAddressSet()
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
            0x1477ed2f0ull, // LoadingScreenOrGameOverSplash2
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
            0x1414bcec0ull, // State_RecoveryTouch
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
            
            0x147b88d00ull, // GetChangeLocationMenuParameterByLocationId
            0x147b897d0ull, // GetMbFreeChangeLocationMenuParameter
            0x140925910ull, // GetPhotoAdditionalTextLangId
            
            0x143f6ee50ull,//FNVHash32
            
            0x140e247dfull,//DD_vox_SH_voice
            0x140e24752ull,//DD_vox_SH_radio
            0x140e247cfull,//DD_vox_SH_radio2
            0x140e247d7ull,//DD_vox_SH_radio3
        };

        return value;
    }

    inline std::wstring GetModuleDirectory(HMODULE hModule)
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

    inline std::string ReadWholeFileUtf8OrAnsi(const std::wstring& path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file)
            return {};

        return std::string(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
    }

    inline std::string ToLowerAscii(std::string text)
    {
        std::transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        return text;
    }

    inline GameBuild DetectGameBuildFromVersionInfo(HMODULE hGame)
    {
        const std::wstring dir = GetModuleDirectory(hGame ? hGame : GetModuleHandleW(nullptr));
        if (dir.empty())
            return GameBuild::Unknown;

        const std::wstring versionInfoPath = dir + L"\\version_info.txt";
        std::string text = ReadWholeFileUtf8OrAnsi(versionInfoPath);
        if (text.empty())
        {
            Log("[AddressSet] Failed to read version_info.txt, defaulting to English.\n");
            return GameBuild::English;
        }

        text = ToLowerAscii(text);
        Log("[AddressSet] version_info.txt = %s\n", text.c_str());

        if (text.find("mst_en") != std::string::npos)
            return GameBuild::English;

        if (text.find("mst_jp") != std::string::npos)
            return GameBuild::Japanese;

        return GameBuild::English;
    }

    inline const char* GetGameBuildName(GameBuild build)
    {
        switch (build)
        {
        case GameBuild::English:
            return "English";
        case GameBuild::Japanese:
            return "Japanese";
        default:
            return "Unknown";
        }
    }

    inline bool ResolveAddressSet(HMODULE hGame)
    {
        if (!hGame)
            return false;

        GetGameBuild() = DetectGameBuildFromVersionInfo(hGame);

        switch (GetGameBuild())
        {
        case GameBuild::English:
            GetAddressSet() = GetEnglishAddressSet();
            Log("[AddressSet] Selected English address set.\n");
            return true;

        case GameBuild::Japanese:
            GetAddressSet() = GetJapaneseAddressSet();
            Log("[AddressSet] Selected Japanese address set.\n");
            return true;

        default:
            GetAddressSet() = GetEnglishAddressSet();
            Log("[AddressSet] Unknown build, defaulting to English address set.\n");
            return true;
        }
    }
}

#define gGameBuild (::AddressSetRuntime::GetGameBuild())
#define gAddr (::AddressSetRuntime::GetAddressSet())
#define ResolveAddressSet (::AddressSetRuntime::ResolveAddressSet)
#define GetGameBuildName (::AddressSetRuntime::GetGameBuildName)

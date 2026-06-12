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

        text = ToLowerAscii(text);
        Log("[AddressSet] version_info.txt = %s\n", text.c_str());
        
        const bool jp   = text.find("mst_jp") != std::string::npos;
        const bool prev = text.find("day1820") != std::string::npos;   // 1.0.15.3
        
        if (prev)
            return jp ? GameBuild::Tpp_steam_mst_jp_day1820 : GameBuild::Tpp_steam_mst_en_day1820;
        return jp ? GameBuild::Tpp_steam_mst_jp_day3800 : GameBuild::Tpp_steam_mst_en_day3800;    // day3800 / default = current
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

#include "pch.h"
#include <Windows.h>
#include <atomic>
#include <cstdio>

#include "MinHook.h"
#include "log.h"
#include "BuiltInModules.h"
#include "FeatureModule.h"
#include "hooks/AddressSet.h"

bool Install_SetLuaFunctions_Hook();

extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace
{
    static std::atomic_bool gStarted{ false };
    static std::atomic_bool gConsoleReady{ false };
    static void LogOwnBuildStamp()
    {
        const auto* base = reinterpret_cast<const std::uint8_t*>(&__ImageBase);
        const auto* dos  = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
        const auto* nt   = reinterpret_cast<const IMAGE_NT_HEADERS*>(
            base + dos->e_lfanew);
        const DWORD stamp = nt->FileHeader.TimeDateStamp;

        const __time64_t t = static_cast<__time64_t>(stamp);
        tm utc{};
        if (_gmtime64_s(&utc, &t) == 0)
            Log("[DLL] GitmoHook.dll link stamp 0x%08X "
                "(%04d-%02d-%02d %02d:%02d:%02d UTC)\n",
                static_cast<unsigned>(stamp),
                utc.tm_year + 1900, utc.tm_mon + 1, utc.tm_mday,
                utc.tm_hour, utc.tm_min, utc.tm_sec);
        else
            Log("[DLL] GitmoHook.dll link stamp 0x%08X\n",
                static_cast<unsigned>(stamp));
    }
}


#ifdef _DEBUG
static void SetupConsole()
{
    if (gConsoleReady.load())
        return;

    EnsureConsole();
    gConsoleReady.store(true);

    printf("[DLL] Console ready\n");
    fflush(stdout);
}
#endif

static DWORD WINAPI InitThread(LPVOID)
{
#ifdef _DEBUG
    SetupConsole();
#endif

    InitLog();

    LogDebug("[DLL] InitThread started.\n");
    LogOwnBuildStamp();

    HMODULE hGame = GetModuleHandleW(nullptr);

    const MH_STATUS st = MH_Initialize();
#ifdef _DEBUG
    Log("[DLL] MH_Initialize -> %d\n", static_cast<int>(st));
#endif
    if (st != MH_OK && st != MH_ERROR_ALREADY_INITIALIZED)
        return 0;

    if (!ResolveAddressSet(hGame))
    {
        Log("[DLL] ResolveAddressSet failed.\n");
        return 0;
    }
    
    RegisterBuiltInFeatureModules();

    const bool allOk = FeatureModuleRegistry::Instance().InstallAll(hGame);
    const MH_STATUS applySt = MH_ApplyQueued();
    Log("[DLL] FeatureModuleRegistry::InstallAll -> %s\n", allOk ? "OK" : "PARTIAL/FAIL");
    if (applySt == MH_OK)
        LogDebug("[DLL] MH_ApplyQueued -> OK\n");
    else
        Log("[DLL] MH_ApplyQueued -> %d (FAILED)\n", static_cast<int>(applySt));

#ifdef _DEBUG
    Log("[DLL] InitThread done.\n");
#endif
    return 0;
}

static void UninstallAll(bool processTerminating)
{
    if (processTerminating)
    {

#ifdef _DEBUG
        Log("[DLL] DLL_PROCESS_DETACH: process terminating, skipping "
            "FeatureModule uninstall (per MSDN guidance - other DLLs "
            "may already be unloaded). OS will reclaim address space.\n");
#endif
        fflush(stdout);
        fflush(stderr);
        CloseLog();

        if (gConsoleReady.load())
            FreeConsole();
        return;
    }

    FeatureModuleRegistry::Instance().UninstallAll();
    MH_Uninitialize();
#ifdef _DEBUG
    Log("[DLL] UninstallAll done.\n");
#endif

    fflush(stdout);
    fflush(stderr);

    CloseLog();

    if (gConsoleReady.load())
        FreeConsole();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);

            bool expected = false;
            if (!gStarted.compare_exchange_strong(expected, true))
                return TRUE;

            ResolveAddressSet(GetModuleHandleW(nullptr));

            HANDLE hThread = CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
            if (hThread)
                CloseHandle(hThread);

            return TRUE;
        }

    case DLL_PROCESS_DETACH:
        {
            UninstallAll(lpReserved != nullptr);
            return TRUE;
        }
    }

    return TRUE;
}
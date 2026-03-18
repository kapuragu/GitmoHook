#include "pch.h"
#include <Windows.h>
#include <atomic>
#include <cstdio>

#include "MinHook.h"
#include "log.h"

// Installs the Lua registration hook.
bool Install_SetLuaFunctions_Hook();
bool Install_GameOver_Location40_Hook();
bool Install_LoadingScreen_Location40_Hook();
bool Install_SetEquipBackgroundTexture_Location_Hooks();
bool Install_HeliCallVoice_Hook();
bool Install_ChangeLocationMenu_Hook();

// Removes the Lua registration hook.
bool Uninstall_SetLuaFunctions_Hook();
bool Uninstall_GameOver_Location40_Hook();
bool Uninstall_LoadingScreen_Location40_Hook();
bool Uninstall_SetEquipBackgroundTexture_Location_Hooks();
bool Uninstall_HeliCallVoice_Hook();
bool Uninstall_ChangeLocationMenu_Hook();

namespace
{
    static std::atomic_bool gStarted{ false };
    static std::atomic_bool gConsoleReady{ false };
}

// Creates or attaches a console for debug logging.
static void SetupConsole()
{
    if (gConsoleReady.load())
        return;

    if (!AllocConsole())
        AttachConsole(ATTACH_PARENT_PROCESS);

    FILE* fp = nullptr;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    SetConsoleTitleW(L"V_FrameWork");
    gConsoleReady.store(true);

    printf("[DLL] Console ready\n");
    fflush(stdout);
}

// Initializes MinHook and all runtime hooks on a worker thread.
static DWORD WINAPI InitThread(LPVOID)
{
    #ifdef _DEBUG
    SetupConsole();
    #endif // DEBUG


    Log("[DLL] InitThread started.\n");

    const MH_STATUS st = MH_Initialize();
    Log("[DLL] MH_Initialize -> %d\n", static_cast<int>(st));
    if (st != MH_OK && st != MH_ERROR_ALREADY_INITIALIZED)
        return 0;

    const bool okLua = Install_SetLuaFunctions_Hook();
    Log("[DLL] Install_SetLuaFunctions_Hook: %s\n", okLua ? "OK" : "FAIL");

    const bool okGameOver = Install_GameOver_Location40_Hook();
    Log("[DLL] Install_GameOver_Location40_Hook: %s\n", okGameOver ? "OK" : "FAIL");

    const bool okLoadingScreen = Install_LoadingScreen_Location40_Hook();
    Log("[DLL] Install_GameOver_Location40_Hook: %s\n", okLoadingScreen ? "OK" : "FAIL");

    const bool okSetEquipBackgroundTexture = Install_SetEquipBackgroundTexture_Location_Hooks();
    Log("[DLL] Install_GameOver_Location40_Hook: %s\n", okSetEquipBackgroundTexture ? "OK" : "FAIL");

    //const bool okHeliCallVoice = Install_HeliCallVoice_Hook();
    //Log("[DLL] Install_HeliCallVoice_Hook: %s\n", okHeliCallVoice ? "OK" : "FAIL");

    const bool okChangeLocationMenu = Install_ChangeLocationMenu_Hook();
    Log("[DLL] Install_ChangeLocationMenu_Hook: %s\n", okChangeLocationMenu ? "OK" : "FAIL");

    Log("[DLL] InitThread done.\n");
    return 0;
}

// Removes all hooks when the DLL unloads normally.
static void UninstallAll(bool processTerminating)
{
    if (processTerminating)
        return;

    Uninstall_SetLuaFunctions_Hook();
    Uninstall_GameOver_Location40_Hook();
    Uninstall_LoadingScreen_Location40_Hook();
    Uninstall_SetEquipBackgroundTexture_Location_Hooks();
    //Uninstall_HeliCallVoice_Hook();
    Uninstall_ChangeLocationMenu_Hook();

    MH_Uninitialize();
    Log("[DLL] UninstallAll done.\n");

    fflush(stdout);
    fflush(stderr);
}

// Standard Windows DLL entry point.
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
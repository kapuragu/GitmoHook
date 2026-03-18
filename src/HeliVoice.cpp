#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <unordered_set>

#include "HookUtils.h"
#include "log.h"
#include "FoxHashes.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

// ----------------------------------------------------
// Function types
// ----------------------------------------------------

using HeliCallVoice_t = void(__fastcall*)(void *SoundControllerImpl,int param_1,int param_2,int voiceType,int param_4);

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

static constexpr uintptr_t ABS_HeliCallVoice = 0x140E23510ull;

// ----------------------------------------------------
// Originals / engine pointers
// ----------------------------------------------------

static HeliCallVoice_t g_OrigHeliCallVoice = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

bool g_isEnableGzHeliVoice = true;

// ----------------------------------------------------
// Hook
// ----------------------------------------------------

static void __fastcall hkHeliCallVoice(void *SoundControllerImpl,int param_1,int param_2,int voiceType,int param_4)
{
    if (g_isEnableGzHeliVoice)
    {
        Log("[hkHeliCallVoice] param_1=0x%llX param_2=0x%llX voiceType=0x%llX param_4=0x%llX\n",
            static_cast<unsigned long>(param_1),
            static_cast<unsigned long>(param_2),
            static_cast<unsigned long>(voiceType),
            static_cast<unsigned long>(param_4));
    }
    g_OrigHeliCallVoice(SoundControllerImpl, param_1, param_2, voiceType, param_4);
}

// ----------------------------------------------------
// Install
// ----------------------------------------------------

bool Install_HeliCallVoice_Hook()
{
    const uintptr_t base = GetExeBase();
    if (!base)
        return false;
    
    void* targetHeliCallVoice =
        reinterpret_cast<void*>(base + ToRva(ABS_HeliCallVoice));
    
    const MH_STATUS initSt = MH_Initialize();
    if (initSt != MH_OK && initSt != MH_ERROR_ALREADY_INITIALIZED)
        return false;
    
    MH_STATUS st = MH_CreateHook(
        targetHeliCallVoice,
        &hkHeliCallVoice,
        reinterpret_cast<void**>(&g_OrigHeliCallVoice));
    if (st != MH_OK && st != MH_ERROR_ALREADY_CREATED)
        return false;
    
    st = MH_EnableHook(targetHeliCallVoice);
    if (st != MH_OK && st != MH_ERROR_ENABLED)
        return false;

    Log("[Hook] HeliCallVoice hook installed\n");
    return true;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_HeliCallVoice_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(ABS_HeliCallVoice));
    g_OrigHeliCallVoice = nullptr;
    return true;
}

void SetEnableGzHeliVoice(bool isEnable)
{
    g_isEnableGzHeliVoice = isEnable;
    Log("[GitmoHook] SetEnableGzHeliVoice set\n");
}
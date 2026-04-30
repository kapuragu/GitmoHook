#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <unordered_set>

#include "HookUtils.h"
#include "log.h"
#include "FoxHashes.h"

#include "HeliVoice.h"

#include <map>

#include "AddressSet.h"
#include "MissionCodeGuard.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using FNVHash32_t = unsigned int(__fastcall*)(const char * strToHash);

// ----------------------------------------------------
// Original pointers
// ----------------------------------------------------
    
static FNVHash32_t g_FNVHash32 = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

static const char* DD_vox_SH_voice = "DD_vox_SH_voice";
static const char* DD_vox_SH_radio = "DD_vox_SH_radio";

unsigned int GetFNVHash32(const char * strToHash)
{
    unsigned int ret = (unsigned int)-1;

    if (!g_FNVHash32)
        g_FNVHash32 = reinterpret_cast<FNVHash32_t>(ResolveGameAddress(gAddr.FNVHash32));
    
    if (g_FNVHash32)
        ret = g_FNVHash32(strToHash);
    
    Log("[HeliVoice] GetFNVHash32(%s)=%d\n",strToHash,ret);
    
    return ret;
}

bool TogglePatch(bool isEnable, uintptr_t pointer, unsigned int originalHash, unsigned int enabledHash)
{
    
    void* target = ResolveGameAddress(pointer);
    if (!target)
    {
        Log("[HeliVoice] TogglePatch(%s): ResolveGameAddress @%lu null\n",
            isEnable ? "true" : "false", pointer);
        return false;
    }

    DWORD oldProtect = 0;
    if (!VirtualProtect(target, sizeof(unsigned int), PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        Log("[HeliVoice] TogglePatch(%s): VirtualProtect failed @%lu (err=%lu)\n",
            isEnable ? "true" : "false", pointer, GetLastError());
        return false;
    }
    
    std::uint8_t* enabledBytes = static_cast<std::uint8_t*>(static_cast<void*>(&enabledHash));
    std::uint8_t* originalBytes = static_cast<std::uint8_t*>(static_cast<void*>(&originalHash));
    
    std::uint8_t* src = isEnable ? enabledBytes : originalBytes;
    std::memcpy(target, src, sizeof(originalHash));

    DWORD restored = 0;
    VirtualProtect(target, sizeof(originalHash), oldProtect, &restored);
    FlushInstructionCache(GetCurrentProcess(), target, sizeof(originalHash));

    Log("[HeliVoice] TogglePatch(%s): wrote at %p\n",
        isEnable ? "true" : "false", target);
}

bool SetEnableHeliVoice(bool isEnable, const char *DD_vox_SH_voice_new, const char *DD_vox_SH_radio_new)
{
    Log("[GitmoHook] SetEnableHeliVoice start\n");
    
    unsigned int original_DD_vox_SH_voice_hash = GetFNVHash32(DD_vox_SH_voice);
    unsigned int new_DD_vox_SH_voice_hash = GetFNVHash32(DD_vox_SH_voice_new);
    
    unsigned int original_DD_vox_SH_radio_hash = GetFNVHash32(DD_vox_SH_radio);
    unsigned int new_DD_vox_SH_radio_hash = GetFNVHash32(DD_vox_SH_radio_new);
    
    bool success0 = TogglePatch(isEnable, gAddr.DD_vox_SH_voice, original_DD_vox_SH_voice_hash, new_DD_vox_SH_voice_hash);
    bool success1 = TogglePatch(isEnable, gAddr.DD_vox_SH_radio, original_DD_vox_SH_radio_hash, new_DD_vox_SH_radio_hash);
    bool success2 = TogglePatch(isEnable, gAddr.DD_vox_SH_radio2, original_DD_vox_SH_radio_hash, new_DD_vox_SH_radio_hash);
    bool success3 = TogglePatch(isEnable, gAddr.DD_vox_SH_radio3, original_DD_vox_SH_radio_hash, new_DD_vox_SH_radio_hash);
    
    Log("[GitmoHook] SetEnableHeliVoice set\n");
    
    return (success0 && success1 && success2 && success3);
}
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

using HeliSoundControllerImplUpdate_t = void(__thiscall*)(void* self);

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

//tpp::gm::heli::impl::SoundControllerImpl::Update 140e242c0
static constexpr uintptr_t ABS_HeliSoundControllerImplUpdate = 0x140e242c0ull;
static constexpr uintptr_t ABS_DD_vox_SH_voice = 0x140e2470full;
static constexpr uintptr_t ABS_DD_vox_SH_radio = 0x140e24707ull;
static constexpr uintptr_t ABS_DD_vox_SH_radio2 = 0x140e246ffull;

// ----------------------------------------------------
// Original pointers
// ----------------------------------------------------

static HeliSoundControllerImplUpdate_t g_OrigHeliSoundControllerImplUpdate = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

bool g_isEnableHeliVoice = false;

static void __thiscall hkHeliSoundControllerImplUpdate(void* self)
{
    g_OrigHeliSoundControllerImplUpdate(self);
    if (!g_isEnableHeliVoice)
        return;
    const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(self);
    const std::uintptr_t lVar15 = (base + 0x58);
    const std::uintptr_t quarkDesc = (base + 0x60);
}

bool Install_HeliVoice_Hook()
{
    void* target = ResolveGameAddress(gAddr.HeliSoundControllerImplUpdate);
    
    const bool okTarget = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkHeliSoundControllerImplUpdate),
        reinterpret_cast<void**>(&g_OrigHeliSoundControllerImplUpdate));

    Log("[Hook] GameOverScreen hook installed? %p\n", okTarget);
    return okTarget;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_HeliVoice_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(gAddr.HeliSoundControllerImplUpdate));
    g_OrigHeliSoundControllerImplUpdate = nullptr;
    return true;
}

void SetEnableHeliVoice(bool isEnable)
{
    g_isEnableHeliVoice = isEnable;
    Log("[GitmoHook] SetEnableHeliVoice set\n");
}
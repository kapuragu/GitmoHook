#include "CpAntiAir.h"

#include "AddressSet.h"
#include "HookUtils.h"
#include "log.h"
#include "LuaBroadcaster.h"
#include "MissionCodeGuard.h"

using HideBinocleHook_t = void(__thiscall*)(long long* self);

// ----------------------------------------------------
// Original pointers
// ----------------------------------------------------

static HideBinocleHook_t g_OrigHideBinocleHook = nullptr;

// ----------------------------------------------------
// Message
// ----------------------------------------------------

void SendOnHideBinocularsMessage()
{
    GitmoHook::EmitMessage("Player", "OnHideBinoculars", 0);
}

// ----------------------------------------------------
// Hook
// ----------------------------------------------------

void __thiscall hkHideBinocle(long long* self)
{
    g_OrigHideBinocleHook(self);
    if (MissionCodeGuard::ShouldBypassHooks())
        return;
    SendOnHideBinocularsMessage();
    Log("[hkHideBinocle] %p\n", self);
}

bool Install_OnHideBinoculars_Hook()
{
    void* target = ResolveGameAddress(gAddr.HideBinocle);

    const bool okTarget = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkHideBinocle),
        reinterpret_cast<void**>(&g_OrigHideBinocleHook));

    Log("[Hook] HideBinocle %p installed at %p\n", okTarget, target);
    
    return okTarget;
}

bool Uninstall_OnHideBinoculars_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(gAddr.HideBinocle));
    g_OrigHideBinocleHook = nullptr;
    return true;
}
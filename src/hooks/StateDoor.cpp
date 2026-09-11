#include "AddressSet.h"
#include "HookUtils.h"
#include "log.h"
#include "LuaBroadcaster.h"
#include "MissionCodeGuard.h"

using StateDoorStartHook_t = void(__thiscall*)(void* self,std::uint32_t playerIndex,std::uint32_t proc, void* param3);
/*using StateDoorLoopHook_t = void(__thiscall*)(long long* self,unsigned long long param_1,long long stateProc,long long *param_3);
using StateDoorEndHook_t = void(__thiscall*)(long long* self,unsigned long long param_1,long long stateProc,long long *param_3);*/

// ----------------------------------------------------
// Original pointers
// ----------------------------------------------------

static StateDoorStartHook_t g_OrigStateDoorStartHook = nullptr;
/*static StateDoorLoopHook_t g_OrigStateDoorLoopHook = nullptr;
static StateDoorEndHook_t g_OrigStateDoorEndHook = nullptr;*/

// ----------------------------------------------------
// Message
// ----------------------------------------------------

void SendStateDoorMessage(unsigned long long playerIndex,unsigned short doorId)
{
    GitmoHook::EmitMessage("Player", "TryPicking", playerIndex,doorId);
}

// ----------------------------------------------------
// Hook
// ----------------------------------------------------

static bool ReadDoor(void* self, std::uint32_t playerIndex,
    bool& started, std::uint16_t& gimmickId, std::uint32_t& doorSide)
{
    started = false; gimmickId = 0; doorSide = 0;
    if (!self) return false;

    __try
    {
        const auto base   = reinterpret_cast<std::uintptr_t>(self);
        const auto info   = *reinterpret_cast<std::uintptr_t*>(base + 0x38);
        const auto slots  = *reinterpret_cast<std::uintptr_t*>(base + 0x78);
        if (!info || !slots) return false;

        const auto origin = *reinterpret_cast<std::uint32_t*>(info + 0x24);
        if (playerIndex < origin) return false;

        const auto work = slots + static_cast<std::uintptr_t>(playerIndex - origin) * 0x480;
        gimmickId = *reinterpret_cast<std::uint16_t*>(work + 0x16);
        doorSide  = (*reinterpret_cast<std::uint8_t*>(work + 0x478) >> 2) & 1u;
        started   = (*reinterpret_cast<std::uint8_t*>(work + 0x46c) & 1u) != 0;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

void __thiscall hkStateDoorStart(void* self,std::uint32_t playerIndex,std::uint32_t proc, void* param3)
{
    bool was = false; std::uint16_t gid; std::uint32_t side;
    const bool ok0 = ReadDoor(self, playerIndex, was, gid, side);

    g_OrigStateDoorStartHook(self,playerIndex,proc,param3);
    
    if (MissionCodeGuard::ShouldBypassHooks())
        return;

    bool now = false;
    const bool ok1 = ReadDoor(self, playerIndex, now, gid, side);
    if (ok0 && ok1 && !was && now)
        SendStateDoorMessage(playerIndex,gid);
    
    //long long lVar16 = (unsigned long long)(param_1 - *(int *)(*(long long *)(self + 0x38) + 0x24)) * 0x480 + *(long long *)(self + 0x78);
    //unsigned short doorId = *(unsigned short *)(lVar16 + 0x16);
    Log("[hkStateDoorStart] %p, playerIndex: %d, stateProc: %d, %p, doorId: %d\n", self, playerIndex, proc, param3, gid);
}

/*void __thiscall hkStateDoorLoop(long long* self,unsigned long long param_1,long long stateProc,long long *param_3)
{
    g_OrigStateDoorLoopHook(self,param_1,stateProc,param_3);
    if (MissionCodeGuard::ShouldBypassHooks())
        return;
    Log("[hkStateDoorLoop] %p, %d, stateProc: %d, %p\n", self, param_1, stateProc, param_3);
}

void __thiscall hkStateDoorEnd(long long* self,unsigned long long param_1,long long stateProc,long long *param_3)
{
    g_OrigStateDoorEndHook(self,param_1,stateProc,param_3);
    if (MissionCodeGuard::ShouldBypassHooks())
        return;
    Log("[hkStateDoorEnd] %p, %d, stateProc: %d, %p\n", self, param_1, stateProc, param_3);
}*/

bool Install_StateDoor_Hook()
{
    void* target = ResolveGameAddress(gAddr.StateDoorStart);

    const bool okTarget = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkStateDoorStart),
        reinterpret_cast<void**>(&g_OrigStateDoorStartHook));

    Log("[Hook] StateDoorStart %p installed at %p\n", okTarget, target);
    
    /*void* target2 = ResolveGameAddress(gAddr.StateDoorLoop);

    const bool okTarget2 = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkStateDoorLoop),
        reinterpret_cast<void**>(&g_OrigStateDoorLoopHook));

    Log("[Hook] StateDoorLoop %p installed at %p\n", okTarget2, target2);
    
    void* target3 = ResolveGameAddress(gAddr.StateDoorEnd);

    const bool okTarget3 = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkStateDoorEnd),
        reinterpret_cast<void**>(&g_OrigStateDoorEndHook));

    Log("[Hook] StateDoorEnd %p installed at %p\n", okTarget3, target3);*/
    
    return okTarget /*&& okTarget2 && okTarget3*/;
}

bool Uninstall_StateDoor_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(gAddr.StateDoorStart));
    g_OrigStateDoorStartHook = nullptr;
    /*DisableAndRemoveHook(ResolveGameAddress(gAddr.StateDoorLoop));
    g_OrigStateDoorLoopHook = nullptr;
    DisableAndRemoveHook(ResolveGameAddress(gAddr.StateDoorEnd));
    g_OrigStateDoorEndHook = nullptr;*/
    return true;
}
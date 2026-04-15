#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <unordered_set>

#include "HookUtils.h"
#include "log.h"
#include "FoxHashes.h"

#include "ChangeLocationMenu.h"

#include <map>

#include "MissionCodeGuard.h"
#include "AddressSet.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using GetChangeLocationMenuParameterByLocationId_t = ChangeLocationMenuParameter* (__thiscall*) (MotherBaseMissionCommonData* This, unsigned short locationCode);
using GetMbFreeChangeLocationMenuParameter_t = ChangeLocationMenuParameter* (__thiscall*) (MotherBaseMissionCommonData* This);

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

static constexpr uintptr_t ABS_GetChangeLocationMenuParameterByLocationId = 0x145F785D0ull;
static constexpr uintptr_t ABS_GetMbFreeChangeLocationMenuParameter = 0x145F78B90ull;

// ----------------------------------------------------
// Original pointers
// ----------------------------------------------------

static GetChangeLocationMenuParameterByLocationId_t g_OrigGetChangeLocationMenuParameterByLocationId = nullptr;
static GetMbFreeChangeLocationMenuParameter_t g_OrigGetMbFreeChangeLocationMenuParameter = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

std::list<unsigned short> changeLocationMenuIds{};

// ----------------------------------------------------
// Hook
// ----------------------------------------------------

ChangeLocationMenuParameter* __thiscall hkGetChangeLocationMenuParameterByLocationId(MotherBaseMissionCommonData* This, unsigned short locationCode)
{
    if (MissionCodeGuard::ShouldBypassHooks())
        return g_OrigGetChangeLocationMenuParameterByLocationId(This,locationCode);
    
    //Joey's structs and iteration code!
    ChangeLocationMenuParameter* params = This->ChangeLocationMenuParams;
    for (int i = 0; i < This->ChangeLocationMenuParamCount; i++)
    {
        //top line is to ensure this locationcode is a valid free roam location
        //if (locationLangIds.find(locationCode) != locationLangIds.end())
        if (std::find(changeLocationMenuIds.begin(), changeLocationMenuIds.end(), locationCode)!=changeLocationMenuIds.end())
            if (params[i].LocationId == locationCode)
                return params + i;
    }
        
    return g_OrigGetChangeLocationMenuParameterByLocationId(This,locationCode);
}

bool Install_ChangeLocationMenu_Hook()
{
    void* target = ResolveGameAddress(gAddr.GetChangeLocationMenuParameterByLocationId);

    g_OrigGetMbFreeChangeLocationMenuParameter = reinterpret_cast<GetMbFreeChangeLocationMenuParameter_t>(
        ResolveGameAddress(gAddr.GetMbFreeChangeLocationMenuParameter));

    const bool okTarget = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkGetChangeLocationMenuParameterByLocationId),
        reinterpret_cast<void**>(&g_OrigGetChangeLocationMenuParameterByLocationId));

    Log("[Hook] ChangeLocationMenu %p installed at %p\n", okTarget, target);
    return okTarget;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_ChangeLocationMenu_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(gAddr.GetChangeLocationMenuParameterByLocationId));
    DisableAndRemoveHook(ResolveGameAddress(gAddr.GetMbFreeChangeLocationMenuParameter));
    g_OrigGetChangeLocationMenuParameterByLocationId = nullptr;
    g_OrigGetMbFreeChangeLocationMenuParameter = nullptr;
    return true;
}

void AddLocationIdToChangeLocationMenu(unsigned short locationId)
{
    if (std::find(changeLocationMenuIds.begin(), changeLocationMenuIds.end(), locationId)==changeLocationMenuIds.end())
    {
        changeLocationMenuIds.push_back(locationId);
        Log("[GitmoHook] AddLocationIdToChangeLocationMenu set\n");
    }
    else
    {
        Log("[GitmoHook] AddLocationIdToChangeLocationMenu already been set\n");
    }
}
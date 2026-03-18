#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <unordered_set>

#include "HookUtils.h"
#include "log.h"
#include "FoxHashes.h"

#include "ChangeLocationMenu.h"

#include <map>

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

static bool g_isEnableLoadingScreen = false;

std::list<unsigned short> changeLocationMenuIds{};

// ----------------------------------------------------
// Hook
// ----------------------------------------------------

ChangeLocationMenuParameter* __thiscall hkGetChangeLocationMenuParameterByLocationId(MotherBaseMissionCommonData* This, unsigned short locationCode)
{
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
    const uintptr_t base = GetExeBase();
    if (!base)
        return false;

    ChangeLocationMenuParameter* target = reinterpret_cast<ChangeLocationMenuParameter*>(
        base + ToRva(ABS_GetChangeLocationMenuParameterByLocationId));

    g_OrigGetMbFreeChangeLocationMenuParameter = reinterpret_cast<GetMbFreeChangeLocationMenuParameter_t>(
        base + ToRva(ABS_GetMbFreeChangeLocationMenuParameter));

    const MH_STATUS initSt = MH_Initialize();
    if (initSt != MH_OK && initSt != MH_ERROR_ALREADY_INITIALIZED)
        return false;

    MH_STATUS st = MH_CreateHook(
        target,
        &hkGetChangeLocationMenuParameterByLocationId,
        reinterpret_cast<void**>(&g_OrigGetChangeLocationMenuParameterByLocationId));

    if (st != MH_OK && st != MH_ERROR_ALREADY_CREATED)
        return false;

    st = MH_EnableHook(target);
    if (st != MH_OK && st != MH_ERROR_ENABLED)
        return false;

    Log("[Hook] ChangeLocationMenu installed at %p\n", target);
    return true;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_ChangeLocationMenu_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(ABS_GetChangeLocationMenuParameterByLocationId));
    DisableAndRemoveHook(ResolveGameAddress(ABS_GetMbFreeChangeLocationMenuParameter));
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
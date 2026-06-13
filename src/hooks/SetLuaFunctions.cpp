#include "CautionStepNormalTimerHook.h"
#include "FoxHashes.h"
#include "GameOverMusic.h"
#include "HeliVoice.h"
#include "LostHostageHook.h"
#include "LuaApi.h"
#include "pch.h"
#include "SoldierObjectRtpc.h"
#include "State_EnterStandHoldup1.h"
#include "StepRadioDiscovery.h"
#include "VIPHoldupHook.h"
#include "VIPRadioHook.h"
#include "VIPSleepFaintHook.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <Windows.h>
#include <cstdint>
#include <unordered_set>
#include <mutex>

#include "HookUtils.h"
#include "log.h"

#include "AddressSet.h"

#include "ChangeLocationMenu.h"
#include "GameOverScreen.h"
#include "GetPhotoAdditionalTextLangId.h"
#include "LoadingScreen.h"
#include "SetEquipBackgroundTexture.h"

void Set_UseCancelLookToPlayerVoice(bool enabled);

namespace
{
    using SetLuaFunctions_t = void(__fastcall*)(lua_State* L);


    static constexpr uintptr_t BOOTSTRAP_EN_SetLuaFunctions = 0x1408D81F0ull;

    static SetLuaFunctions_t       g_OrigSetLuaFunctions = nullptr;

    static std::unordered_set<lua_State*> g_RegisteredLuaStates;
    static std::mutex g_RegisteredLuaStatesMutex;
    static bool g_SetLuaFunctionsHookInstalled = false;
}


static uintptr_t GetLuaBridgeAddress(uintptr_t resolvedAddr, uintptr_t bootstrapAddr)
{
    return resolvedAddr ? resolvedAddr : bootstrapAddr;
}


static void SetLuaTop(lua_State* L, int idx)
{
    if (!ResolveLuaApi() || !g_lua_settop)
        return;

    g_lua_settop(L, idx);
}


static bool IsLuaStateRegistered(lua_State* L)
{
    std::lock_guard<std::mutex> lock(g_RegisteredLuaStatesMutex);
    return g_RegisteredLuaStates.find(L) != g_RegisteredLuaStates.end();
}


static void TrackLuaState(lua_State* L)
{
    std::lock_guard<std::mutex> lock(g_RegisteredLuaStatesMutex);
    g_RegisteredLuaStates.insert(L);
}

lua_State* GitmoHook_AnyLuaState()
{
    std::lock_guard<std::mutex> lock(g_RegisteredLuaStatesMutex);
    if (g_RegisteredLuaStates.empty()) return nullptr;
    return *g_RegisteredLuaStates.begin();
}


static void ClearTrackedLuaStates()
{
    std::lock_guard<std::mutex> lock(g_RegisteredLuaStatesMutex);
    g_RegisteredLuaStates.clear();
}


static bool LuaReadRequiredStringField(lua_State* L, const char* fieldName, std::string& outValue)
{
    outValue.clear();

    LuaGetField(L, -1, fieldName);
    const bool ok = LuaIsString(L, -1);

    if (ok)
    {
        const char* value = GetLuaString(L, -1);
        if (value && value[0] != '\0')
        {
            outValue = value;
        }
        else
        {
            LuaPop(L, 1);
            return false;
        }
    }

    LuaPop(L, 1);
    return ok && !outValue.empty();
}

static double LuaToNumber(lua_State* L, int idx)
{
    if (!ResolveLuaApi() || !g_lua_tonumber)
        return 0.0;

    return static_cast<double>(g_lua_tonumber(L, idx));
}


static std::int32_t LuaReadOptionalIntField(lua_State* L, const char* fieldName, std::int32_t defaultValue)
{
    LuaGetField(L, -1, fieldName);

    std::int32_t value = defaultValue;
    if (LuaIsNumber(L, -1))
    {
        value = static_cast<std::int32_t>(GetLuaInt(L, -1));
    }

    LuaPop(L, 1);
    return value;
}


static std::uint32_t LuaReadOptionalUIntField(lua_State* L, const char* fieldName, std::uint32_t defaultValue)
{
    LuaGetField(L, -1, fieldName);

    std::uint32_t value = defaultValue;
    if (LuaIsNumber(L, -1))
    {
        value = static_cast<std::uint32_t>(GetLuaInt(L, -1));
    }

    LuaPop(L, 1);
    return value;
}

static bool TryReadTableIntField(lua_State* L, int tableIndex, const char* fieldName, int& outValue)
{
    outValue = 0;
    LuaGetField(L, tableIndex, const_cast<char*>(fieldName));

    const bool ok = (LuaType(L, -1) == 3);
    if (ok)
        outValue = GetLuaInt(L, -1);

    SetLuaTop(L, -2);
    return ok;
}

static bool TryReadTableStringField(lua_State* L, int tableIndex, const char* fieldName, const char*& outValue)
{
    outValue = nullptr;
    LuaGetField(L, tableIndex, const_cast<char*>(fieldName));

    const bool ok = (LuaType(L, -1) == 4);
    if (ok)
        outValue = GetLuaString(L, -1);

    SetLuaTop(L, -2);
    return ok;
}

static bool TryReadTableBoolField(lua_State* L, int tableIndex, const char* fieldName, bool defaultValue)
{
    LuaGetField(L, tableIndex, const_cast<char*>(fieldName));

    const int type = LuaType(L, -1);
    bool result = defaultValue;

    if (type != 0)
        result = GetLuaBool(L, -1) != 0;

    SetLuaTop(L, -2);
    return result;
}


static bool TryReadTableSubAssetField(
    lua_State* L, int tableIndex, const char* fieldName,
    const char*& outPath, bool& outVanilla, bool defaultVanilla)
{
    outPath = nullptr;
    outVanilla = defaultVanilla;

    LuaGetField(L, tableIndex, const_cast<char*>(fieldName));
    const int type = LuaType(L, -1);

    if (type == 4)
    {
        outPath = GetLuaString(L, -1);
        outVanilla = false;
    }
    else if (type == 1)
    {
        outVanilla = GetLuaBool(L, -1);
    }


    SetLuaTop(L, -2);
    return true;
}

static void LuaPushString(lua_State* L, const char* value)
{
    if (!ResolveLuaApi() || !g_lua_pushstring || !value)
        return;

    g_lua_pushstring(L, const_cast<char*>(value));
}

static void LuaCreateTable(lua_State* L, int narr, int nrec)
{
    if (!ResolveLuaApi() || !g_lua_createtable)
        return;

    g_lua_createtable(L, narr, nrec);
}

static void LuaGetTable(lua_State* L, int idx)
{
    if (!ResolveLuaApi() || !g_lua_gettable)
        return;

    g_lua_gettable(L, idx);
}

static void LuaRawSet(lua_State* L, int idx)
{
    if (!ResolveLuaApi() || !g_lua_rawset)
        return;

    g_lua_rawset(L, idx);
}

static void LuaSetTable(lua_State* L, int idx)
{
    if (!ResolveLuaApi() || !g_lua_settable)
        return;

    g_lua_settable(L, idx);
}

static void LuaPushNil(lua_State* L)
{
    if (!ResolveLuaApi() || !g_lua_pushnil)
        return;

    g_lua_pushnil(L);
}

static int LuaNext(lua_State* L, int idx)
{
    if (!ResolveLuaApi() || !g_lua_next)
        return 0;

    return g_lua_next(L, idx);
}

static void LuaPushValue(lua_State* L, int idx)
{
    if (!ResolveLuaApi() || !g_lua_pushvalue)
        return;

    g_lua_pushvalue(L, idx);
}

static void PushLuaUInt32(lua_State* L, std::uint32_t v)
{
    if (ResolveLuaApi() && g_lua_pushnumber)
        g_lua_pushnumber(L, static_cast<lua_Number>(static_cast<double>(v)));
}

//----------------
// LUA FUNCTIONS
//----------------

void SetEnableTelopBg(bool is_enable);

static int __cdecl l_SetEnableGzUi(lua_State* L)
{
    const bool isEnable = GetLuaBool(L, 1) or false;
    SetEnableEquipBackgroundTexture(isEnable);
    SetEnableGameOverScreen(isEnable);
    SetEnableLoadingScreen(isEnable);
    SetEnableTelopBg(isEnable);
    return 1;
}

static int __cdecl l_AddToChangeLocationMenu(lua_State* L)
{
    if ( !(LuaType( L, -1)==LUA_TTABLE) ) {
        Log("UpdateChangeLocationMenu expected table\n");
        return 0;
    }
    
    for (g_lua_pushnil(L); g_lua_next(L, -2); LuaPop(L, 1)) {
        if ( LuaType( L, -1)==LUA_TNUMBER ) {
            unsigned short locationCode = GetLuaInt(L, -1);
            Log("{%llX}\n",locationCode);
            AddLocationIdToChangeLocationMenu(locationCode);
        }
    }
    LuaPop( L, 1 );
    
    return 1;
}

static int __cdecl l_AddPhotoAdditionalText(lua_State* L)
{
    if ( !(LuaType( L, -1)==LUA_TTABLE) ) {
        Log("AddPhotoAdditionalText expected table\n");
        return 0;
    }
    
    for (g_lua_pushnil(L); g_lua_next(L, -2); LuaPop(L, 1)) 
    {
        if ( LuaType( L, -1)==LUA_TTABLE ) 
        {
            unsigned short missionCode = 0xFFFF;
            unsigned char photoId = 0xFF;
            unsigned char photoType = 0xFF;
            const char* targetTypeLangIdStr = "";
            
            LuaGetField(L,-1,"missionCode");
            if (LuaType(L,-1)==LUA_TNUMBER)
                missionCode = static_cast<unsigned short>(GetLuaInt(L, -1));
            LuaPop(L, 1);
            Log("AddPhotoAdditionalText missionCode %d\n",missionCode);
            
            LuaGetField(L,-1,"photoId");
            if (LuaType(L,-1)==LUA_TNUMBER)
                photoId = static_cast<unsigned char>(GetLuaInt(L, -1));
            LuaPop(L, 1);
            Log("AddPhotoAdditionalText photoId %d\n",photoId);
            
            LuaGetField(L,-1,"photoType");
            if (LuaType(L,-1)==LUA_TNUMBER)
                photoType = static_cast<unsigned char>(GetLuaInt(L, -1));
            LuaPop(L, 1);
            Log("AddPhotoAdditionalText photoType %d\n",photoType);
            
            LuaGetField(L,-1,"targetTypeLangId");
            if (LuaType(L,-1)==LUA_TSTRING)
                targetTypeLangIdStr = GetLuaString(L, -1);
            LuaPop(L, 1);
            Log("AddPhotoAdditionalText targetTypeLangIdStr %s\n",targetTypeLangIdStr);
            
            if (missionCode==0xFFFF) continue;
            if (photoId==0xFF) continue;
            if (photoType==0xFF) continue;
            AddPhotoAdditionalText(missionCode,photoId,photoType,targetTypeLangIdStr);
        }
    }
    LuaPop( L, 1 );
    
    return 1;
}

static int __cdecl l_SetHeliDialogueEvents(lua_State* L)
{
    Log("[GitmoHook] l_SetHeliDialogueEvents start\n");
    const bool isEnable = GetLuaBool(L, 1);
    Log("[GitmoHook] l_SetHeliDialogueEvents 1\n");
    if (isEnable)
    {
        Log("[GitmoHook] isEnable 1\n");
        const char* dialogueEvent1 = GetLuaString(L, 2);
        Log("[GitmoHook] isEnable 2\n");
        const char* dialogueEvent2 = GetLuaString(L, 3);
        Log("[GitmoHook] isEnable 3\n");
        bool success = SetEnableHeliVoice(isEnable,dialogueEvent1,dialogueEvent2);
        Log("[GitmoHook] isEnable 4\n");
        return success ? 1 : 0;
    }
    Log("[GitmoHook] l_SetHeliDialogueEvents 2\n");
    
    bool success = SetEnableHeliVoice(isEnable,"","");
    Log("[GitmoHook] l_SetHeliDialogueEvents 3\n");
    return success ? 1 : 0;
}


static int l_HoldUpReactionCowardlyReactions(lua_State* L)
{
    const bool enabled = GetLuaBool(L, 1);
    Set_HoldUpReactionCowardlyReactions(enabled);
    return 0;
}

static int l_SetCancelLookToPlayerVoice(lua_State* L)
{
    const bool enabled = GetLuaBool(L, 1);
    Set_UseCancelLookToPlayerVoice(enabled);
    return 0;
}

// Sets the caution timer override.
// Params: seconds
static int l_SetCautionStepNormalDurationSeconds(lua_State* L)
{
    const float seconds = GetLuaNumber(L, 1);
    Set_CautionStepNormalDurationSeconds(seconds);
    return 0;
}

// Gets the caution timer override.
// Params: none
static int l_GetCautionStepNormalDurationSeconds(lua_State* L)
{
    PushLuaNumber(L, Get_CautionStepNormalDurationSeconds());
    return 1;
}

// Clears the caution timer override.
// Params: none
static int l_UnsetCautionStepNormalDurationSeconds(lua_State* L)
{
    UNREFERENCED_PARAMETER(L);
    Unset_CautionStepNormalDurationSeconds();
    return 0;
}

// Gets the remaining caution timer.
// Params: none
static int l_GetCautionStepNormalRemainingSeconds(lua_State* L)
{
    PushLuaNumber(L, Get_CautionStepNormalRemainingSeconds());
    return 1;
}


static int __cdecl l_SetLostHostage(lua_State* L)
{
    const std::uint32_t gameObjectId = static_cast<std::uint32_t>(GetLuaInt64(L, 1));
    const int hostageType = GetLuaInt(L, 2);
    // Optional 3rd arg: voice line for the "prisoner gone" radio. Accepts
    // either a label-name string (auto-hashed via FoxStrHash32) or a
    // pre-hashed numeric StrCode32. 0 / omitted = built-in male/female/
    // child × taken matrix.
    const std::uint32_t customLostLabel = GetLuaStrCode32Arg(L, 3);

    Add_LostHostageTrap(gameObjectId, hostageType, customLostLabel);
    Add_LostHostageDiscovery(gameObjectId, hostageType);
    return 0;
}


static int __cdecl l_RemoveLostHostage(lua_State* L)
{
    const std::uint32_t gameObjectId = static_cast<std::uint32_t>(GetLuaInt64(L, 1));

    Remove_LostHostageTrap(gameObjectId);
    Remove_LostHostageDiscovery(gameObjectId);
    return 0;
}


static int __cdecl l_ClearLostHostages(lua_State* L)
{
    UNREFERENCED_PARAMETER(L);
    Clear_LostHostagesTrap();
    Clear_LostHostageDiscovery();
    return 0;
}

static int __cdecl l_SetLostHostageFromPlayer(lua_State* L)
{
    const std::uint32_t gameObjectId = static_cast<std::uint32_t>(GetLuaInt64(L, 1));
    const bool playerTookHostage = GetLuaBool(L, 2);
    PlayerTookHostage(gameObjectId, playerTookHostage);
    return 0;
}

static int __cdecl l_SetVIPImportant(lua_State* L)
{
    const std::uint32_t gameObjectId = static_cast<std::uint32_t>(GetLuaInt64(L, 1));
    const bool isOfficer = GetLuaBool(L, 2);
    const std::uint32_t customDeadBodyLabel = GetLuaStrCode32Arg(L, 3);

    Add_VIPSleepFaintImportantGameObjectId(gameObjectId, isOfficer);
    Add_VIPHoldupImportantGameObjectId(gameObjectId, isOfficer);
    Add_VIPRadioImportantGameObjectId(gameObjectId, isOfficer, customDeadBodyLabel);
    return 0;
}

// Removes one VIP-important soldier.
// Params: gameObjectId
static int __cdecl l_RemoveVIPImportant(lua_State* L)
{
    const std::uint32_t gameObjectId = static_cast<std::uint32_t>(GetLuaInt64(L, 1));

    Remove_VIPSleepFaintImportantGameObjectId(gameObjectId);
    Remove_VIPHoldupImportantGameObjectId(gameObjectId);
    Remove_VIPRadioImportantGameObjectId(gameObjectId);
    return 0;
}

// Clears all VIP-important soldiers.
// Params: none
static int __cdecl l_ClearVIPImportant(lua_State* L)
{
    UNREFERENCED_PARAMETER(L);

    Clear_VIPSleepFaintImportantGameObjectIds();
    Clear_VIPHoldupImportantGameObjectIds();
    Clear_VIPRadioImportantGameObjectIds();
    return 0;
}

// Per-soldier RTPC by name (DLL hashes via fox::sd::ConvertParameterID).
static int __cdecl l_SetSoldierObjectRtpcByName(lua_State* L)
{
    const std::uint32_t goId     = static_cast<std::uint32_t>(GetLuaInt64(L, 1));
    const char*         rtpcName = GetLuaString(L, 2);
    const float         value    = GetLuaNumber(L, 3);
    const long          timeMs   = static_cast<long>(GetLuaInt(L, 4));
    const bool ok = ::Set_SoldierObjectRtpcByName(goId, rtpcName, value, timeMs);
    PushLuaBool(L, ok);
    return 1;
}

static int __cdecl l_SetGameOverMusic(lua_State* L)
{
    const bool isEnable = GetLuaBool(L, 1);
    const GAME_OVER_TYPE gameOverType = static_cast<GAME_OVER_TYPE>(GetLuaInt(L, 2));
    if (isEnable)
    {
        const char* playEventString = GetLuaString(L, 3);
        const char* stopEventString = GetLuaString(L, 4);
        bool success = SetGameOverMusic(isEnable,gameOverType,playEventString,stopEventString);
        return success ? 1 : 0;
    }
    
    bool success = SetGameOverMusic(isEnable,gameOverType,"","");
    return success ? 1 : 0;
}

static luaL_Reg g_GitmoHook[] =
{   //SetDefaultEquipBgTexturePath is the one that is going to be used in lua.
    { "SetEnableGzUi", l_SetEnableGzUi },
    { "AddToChangeLocationMenu", l_AddToChangeLocationMenu },
    { "AddPhotoAdditionalText", l_AddPhotoAdditionalText },
    { "SetHeliDialogueEvents", l_SetHeliDialogueEvents },
    { "SetCancelLookToPlayerVoice",         l_SetCancelLookToPlayerVoice },
        
    { "SetCautionStepNormalDurationSeconds",    l_SetCautionStepNormalDurationSeconds },
    { "GetCautionStepNormalDurationSeconds",    l_GetCautionStepNormalDurationSeconds },
    { "UnsetCautionStepNormalDurationSeconds",  l_UnsetCautionStepNormalDurationSeconds },
    { "GetCautionStepNormalRemainingSeconds",   l_GetCautionStepNormalRemainingSeconds },
    
    { "SetGameOverMusic", l_SetGameOverMusic },
    //e20010
    { "SetLostHostage", l_SetLostHostage },
    { "RemoveLostHostage", l_RemoveLostHostage },
    { "ClearLostHostages", l_ClearLostHostages },
    { "SetLostHostageFromPlayer", l_SetLostHostageFromPlayer },
    //e20020
    { "SetVIPImportant", l_SetVIPImportant },
    { "RemoveVIPImportant", l_RemoveVIPImportant },
    { "ClearVIPImportant", l_ClearVIPImportant },
    
    { "SetSoldierRtpc",             l_SetSoldierObjectRtpcByName },
    { nullptr, nullptr }
};

//-----------------------
// Register Lua libraries
//-----------------------

// Registers V_FrameWork into a UI Lua state only once.
// Params: L (lua_State*)
static void RegisterAllUiLuaLibraries(lua_State* L)
{
    if (!L)
        return;

    if (IsLuaStateRegistered(L))
        return;

    if (RegisterLuaLibrary(L, "GitmoHook", g_GitmoHook))
    {
        TrackLuaState(L);
    }
}

// Hooked SetLuaFunctions.
// Params: L
static void __fastcall hkSetLuaFunctions(lua_State* L)
{
    Log("[Hook] SetLuaFunctions invoked: L=%p\n", L);

    if (g_OrigSetLuaFunctions)
    {
        g_OrigSetLuaFunctions(L);
    }

    RegisterAllUiLuaLibraries(L);
}

// Exported Lua loader for require("GitmoHook").
extern "C" __declspec(dllexport) int __cdecl luaopen_GitmoHook(lua_State* L)
{
    if (!L)
        return 0;

    if (IsLuaStateRegistered(L))
        return 0;

    if (!RegisterLuaLibrary(L, "GitmoHook", g_GitmoHook))
        return 0;

    TrackLuaState(L);
    return 1;
}

// Installs the SetLuaFunctions hook.
// Params: none
bool Install_SetLuaFunctions_Hook()
{
    if (g_SetLuaFunctionsHookInstalled)
    {
        Log("[Hook] SetLuaFunctions: already installed\n");
        return true;
    }

    ResolveLuaApi();

    
    const uintptr_t setLuaFunctionsAddr = GetLuaBridgeAddress(gAddr.SetLuaFunctions, BOOTSTRAP_EN_SetLuaFunctions);
    void* target = ResolveGameAddress(setLuaFunctionsAddr);
    if (!target)
        return false;

    const bool ok = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkSetLuaFunctions),
        reinterpret_cast<void**>(&g_OrigSetLuaFunctions));

    if (ok)
    {
        g_SetLuaFunctionsHookInstalled = true;
    }

    Log("[Hook] SetLuaFunctions: %s target=%p orig=%p\n",
        ok ? "OK" : "FAIL",
        target,
        g_OrigSetLuaFunctions);
    return ok;
}

// Removes the SetLuaFunctions hook.
// Params: none
bool Uninstall_SetLuaFunctions_Hook()
{
    const uintptr_t setLuaFunctionsAddr = GetLuaBridgeAddress(gAddr.SetLuaFunctions, BOOTSTRAP_EN_SetLuaFunctions);
    DisableAndRemoveHook(ResolveGameAddress(setLuaFunctionsAddr));
    g_OrigSetLuaFunctions = nullptr;
    ClearTrackedLuaStates();
    return true;
}
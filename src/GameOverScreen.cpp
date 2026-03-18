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

using SetTextureName_t = void(__fastcall*)(void* modelNodeMesh, uint64_t textureHash, uint64_t slotHash, int unk);
using GameOverSetVisible_t = void(__fastcall*)(uint64_t* param_1, char param_2);

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

static constexpr uintptr_t ABS_SetTextureName = 0x141DC78F0ull;
static constexpr uintptr_t ABS_GameOverSetVisible = 0x145CB8890ull;

// ----------------------------------------------------
// Original pointers
// ----------------------------------------------------

static SetTextureName_t g_SetTextureName = nullptr;
static GameOverSetVisible_t g_OrigGameOverSetVisible = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

bool g_isEnableGameOverScreen = false;

// ----------------------------------------------------
// Texture hashes
// ----------------------------------------------------

static constexpr uint64_t TEX_MAIN_GZ = 0x15693e01563c09c3ull; //   \Assets\tpp\common_source\ui\common_texture\cm_mblogo_clp_1.ftex
static constexpr uint64_t TEX_BLUR_GZ = 0x156a20d598cc4802ull; //   \Assets\tpp\common_source\ui\common_texture\cm_mblogo_blr_clp_1.ftex


static void __fastcall hkGameOverSetVisible(uint64_t* param_1, char param_2)
{
    g_OrigGameOverSetVisible(param_1, param_2);

    if (param_2 == 0)
        return;

    if (!g_isEnableGameOverScreen)
        return;

    Log("[GameOverSetVisible] Applying Cyprus textures\n");


    void* node8 = reinterpret_cast<void*>(param_1[8]);
    void* node9 = reinterpret_cast<void*>(param_1[9]);
    void* node10 = reinterpret_cast<void*>(param_1[10]);
    void* node11 = reinterpret_cast<void*>(param_1[11]);

    // Main logo
    if (node8) g_SetTextureName(node8, TEX_MAIN_GZ, 0x3bbf9889ull, 2);
    if (node9) g_SetTextureName(node9, TEX_MAIN_GZ, 0x3bbf9889ull, 2);

    // Blur layer on same nodes
    if (node8) g_SetTextureName(node8, TEX_BLUR_GZ, 0x8d982b8eull, 2);
    if (node9) g_SetTextureName(node9, TEX_BLUR_GZ, 0x8d982b8eull, 2);

    // Blur-only nodes
    if (node10) g_SetTextureName(node10, TEX_BLUR_GZ, 0x3bbf9889ull, 2);
    if (node11) g_SetTextureName(node11, TEX_BLUR_GZ, 0x3bbf9889ull, 2);
}

bool Install_GameOver_Location40_Hook()
{
    const uintptr_t base = GetExeBase();
    if (!base)
        return false;

    g_SetTextureName = reinterpret_cast<SetTextureName_t>(
        base + ToRva(ABS_SetTextureName));

    void* target = reinterpret_cast<void*>(
        base + ToRva(ABS_GameOverSetVisible));

    const MH_STATUS initSt = MH_Initialize();
    if (initSt != MH_OK && initSt != MH_ERROR_ALREADY_INITIALIZED)
        return false;

    MH_STATUS st = MH_CreateHook(
        target,
        &hkGameOverSetVisible,
        reinterpret_cast<void**>(&g_OrigGameOverSetVisible));

    if (st != MH_OK && st != MH_ERROR_ALREADY_CREATED)
        return false;

    st = MH_EnableHook(target);
    if (st != MH_OK && st != MH_ERROR_ENABLED)
        return false;

    Log("[Hook] GameOver location-40 hook installed\n");
    return true;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_GameOver_Location40_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(ABS_SetTextureName));
    DisableAndRemoveHook(ResolveGameAddress(ABS_GameOverSetVisible));
    g_SetTextureName = nullptr;
    g_OrigGameOverSetVisible = nullptr;
    return true;
}

void SetEnableGameOverScreen(bool isEnable)
{
    g_isEnableGameOverScreen = isEnable;
    Log("[GitmoHook] SetEnableGameOverScreen set\n");
}
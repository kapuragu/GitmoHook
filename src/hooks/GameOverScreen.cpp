#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <unordered_set>

#include "HookUtils.h"
#include "log.h"
#include "FoxHashes.h"
#include "MissionCodeGuard.h"

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

//fox::ui::ModelNodeMesh::SetTextureName
static constexpr uintptr_t ABS_SetTextureName = 0x141DC78F0ull;
//tpp::ui::menu::GameOverEvCall::MainLayout::SetVisible
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
    MISSION_GUARD_RETURN_VOID();

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

bool Install_GameOverScreen_Hook()
{
    g_SetTextureName = reinterpret_cast<SetTextureName_t>(
        ResolveGameAddress(ABS_SetTextureName));

    void* target = ResolveGameAddress(ABS_GameOverSetVisible);
    
    const bool okTarget = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkGameOverSetVisible),
        reinterpret_cast<void**>(&g_OrigGameOverSetVisible));

    Log("[Hook] GameOverScreen hook installed? %p\n", okTarget);
    return okTarget;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_GameOverScreen_Hook()
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
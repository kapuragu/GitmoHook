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

using LoadingScreenOrGameOverSplash2_t = void(__fastcall*)(void* param_1);
using SetTextureName_t = void(__fastcall*)(void* modelNodeMesh, uint64_t textureHash, uint64_t slotHash, int unk);

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

static constexpr uintptr_t ABS_LoadingScreenOrGameOverSplash2 = 0x145CD0630ull;
static constexpr uintptr_t ABS_SetTextureName = 0x141DC78F0ull;


static LoadingScreenOrGameOverSplash2_t g_OrigLoadingScreenOrGameOverSplash2 = nullptr;
static SetTextureName_t g_SetTextureName = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

static bool g_isEnableLoadingScreen = false;

// Cyprus textures
static constexpr uint64_t TEX_LOADING_MAIN_CYPRUS   = 0x15693e01563c09c3ull; //   \Assets\tpp\common_source\ui\common_texture\cm_mblogo_clp_1.ftex
static constexpr uint64_t TEX_LOADING_BLUR_GZ       = 0x156a20d598cc4802ull; //   \Assets\tpp\common_source\ui\common_texture\cm_mblogo_blr_clp_1.ftex

// ----------------------------------------------------
// Hook
// ----------------------------------------------------

static void __fastcall hkLoadingScreenOrGameOverSplash2(void* param_1)
{
    g_OrigLoadingScreenOrGameOverSplash2(param_1);
    
    if (MissionCodeGuard::ShouldBypassHooks())
        return;

    if (!g_isEnableLoadingScreen)
        return;

    Log("[LoadingScreenOrGameOverSplash2] Applying Cyprus textures\n");

    const uintptr_t self = reinterpret_cast<uintptr_t>(param_1);

    void* mainNode = *reinterpret_cast<void**>(self + 0x9d8);
    void* blurNode = *reinterpret_cast<void**>(self + 0x9e0);

    Log("[LoadingScreenOrGameOverSplash2] mainNode=%p blurNode=%p\n", mainNode, blurNode);

    if (mainNode)
    {
        g_SetTextureName(mainNode, TEX_LOADING_MAIN_CYPRUS, 0x3bbf9889ull, 2);
        Log("[LoadingScreenOrGameOverSplash2] main texture set to 0x%llX\n",
            static_cast<unsigned long long>(TEX_LOADING_MAIN_CYPRUS));
    }

    if (blurNode)
    {
        g_SetTextureName(blurNode, TEX_LOADING_BLUR_GZ, 0x3bbf9889ull, 2);
        Log("[LoadingScreenOrGameOverSplash2] blur texture set to 0x%llX\n",
            static_cast<unsigned long long>(TEX_LOADING_BLUR_GZ));
    }
}

bool Install_LoadingScreen_Hook()
{
    g_SetTextureName = reinterpret_cast<SetTextureName_t>(
        ResolveGameAddress(ABS_SetTextureName));

    void* target = ResolveGameAddress(ABS_LoadingScreenOrGameOverSplash2);
    
    const bool okTarget = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkLoadingScreenOrGameOverSplash2),
        reinterpret_cast<void**>(&g_OrigLoadingScreenOrGameOverSplash2));

    Log("[Hook] LoadingScreenOrGameOverSplash2 installed %p at %p\n", okTarget, target);
    return okTarget;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_LoadingScreen_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(ABS_LoadingScreenOrGameOverSplash2));
    DisableAndRemoveHook(ResolveGameAddress(ABS_SetTextureName));
    g_OrigLoadingScreenOrGameOverSplash2 = nullptr;
    g_SetTextureName = nullptr;
    return true;
}

void SetEnableLoadingScreen(const bool isEnable)
{
    g_isEnableLoadingScreen = isEnable;
    Log("[GitmoHook] SetEnableLoadingScreen set\n");
}
#include "pch.h"

#include <Windows.h>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include "FoxHashes.h"
#include "HookUtils.h"
#include "log.h"
#include "AddressSet.h"
#include "MissionCodeGuard.h"

namespace
{
    using SetWeaponPanelLogo_t = uint8_t(__fastcall*)(int equipId, void* node);
    using SetTextureName_t = void(__fastcall*)(void* modelNodeMesh, uint64_t textureHash, uint64_t slotHash, int unk);
    using GetUixUtility_t = void** (__fastcall*)();
    using GetQuarkSystemTable_t = void* (__fastcall*)();

    using TexStatusCreate_t = char(__fastcall*)(void*, void*, unsigned);

    TexStatusCreate_t     g_OrigTexStatusCreate = nullptr;

    constexpr uintptr_t   kAddr_TexStatusCreate_En154 = 0x141DBC2D0;
    
    bool g_isEnableEquipBg = false;

    bool DescriptorReadableSEH(const void* src)
    {
        const uintptr_t v = reinterpret_cast<uintptr_t>(src);
        if (v < 0x10000ull || v >= 0x7FFFFFFFFFFFull)
            return false;
        __try
        {
            volatile unsigned probe =
                *reinterpret_cast<const unsigned*>(
                    static_cast<const char*>(src) + 0x18);
            (void)probe;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    char __fastcall hkTexStatusCreate(void* out, void* src, unsigned flags)
    {
        if (src && !DescriptorReadableSEH(src))
        {
            static bool s_Warned = false;
            if (!s_Warned)
            {
                s_Warned = true;
                Log("[UiTextureGuard] a UI material texture slot holds the "
                    "corrupt streamer descriptor %p - the bind is skipped so "
                    "fox::gr::TextureStreamerStatus does not fault on it; "
                    "that slot draws untextured instead of crashing the "
                    "render worker\n", src);
            }
            return 0;
        }
        return g_OrigTexStatusCreate(out, src, flags);
    }

    SetWeaponPanelLogo_t  g_OrigSetWeaponPanelLogo = nullptr;
    SetTextureName_t      g_SetTextureName = nullptr;
    GetUixUtility_t       g_GetUixUtility = nullptr;
    GetQuarkSystemTable_t g_GetQuarkSystemTable = nullptr;
    uint64_t              g_MaskSlot = 0;
    
    constexpr uint64_t VANILLA_BG = 0x15695ED8A56AE919ull;
    
    constexpr uint64_t NEW_TEXTURE = 0x156810775f8c8515ull; //default, which been changed to\Assets\tpp\ui\texture\equip_bg\

    bool Resolve()
    {
        if (!g_SetTextureName)
            g_SetTextureName = reinterpret_cast<SetTextureName_t>(ResolveGameAddress(gAddr.SetTextureName));
        if (!g_GetQuarkSystemTable && gAddr.GetQuarkSystemtable != 0)
            g_GetQuarkSystemTable = reinterpret_cast<GetQuarkSystemTable_t>(ResolveGameAddress(gAddr.GetQuarkSystemtable));
        if (g_MaskSlot == 0)
            g_MaskSlot = static_cast<uint64_t>(FoxHashes::StrCode32("Mask_Texture"));
        return g_SetTextureName != nullptr && g_MaskSlot != 0;
    }


    void Prefetch(uint64_t textureHash)
    {
        if (textureHash == 0 || gAddr.GetUixUtilityToFeedQuarkEnvironment == 0)
            return;
        if (!g_GetUixUtility)
            g_GetUixUtility = reinterpret_cast<GetUixUtility_t>(ResolveGameAddress(gAddr.GetUixUtilityToFeedQuarkEnvironment));
        if (!g_GetUixUtility)
            return;
        __try
        {
            void** util = g_GetUixUtility();
            if (!util) return;
            void** vtbl = *reinterpret_cast<void***>(util);
            if (!vtbl) return;
            auto fn = reinterpret_cast<void(__fastcall*)(void*, uint64_t, int)>(vtbl[0x548 / sizeof(void*)]);
            if (fn) fn(util, textureHash, 2);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    bool IsSortieEquip(int equipId)
    {
        if (!g_GetQuarkSystemTable)
            return true;
        __try
        {
            char* quark = reinterpret_cast<char*>(g_GetQuarkSystemTable());
            if (!quark) return true;
            const uintptr_t mgr = *reinterpret_cast<uintptr_t*>(quark + 0x98);
            if (!mgr) return true;
            const uintptr_t lm = *reinterpret_cast<uintptr_t*>(mgr + 0x130);
            if (!lm) return true;
            const uint8_t idx = *reinterpret_cast<uint8_t*>(lm + 0x3b4);
            char* info = reinterpret_cast<char*>(lm + 0x10 + static_cast<uintptr_t>(idx) * 0xe8);

            if (*reinterpret_cast<int*>(info + 0x18) == equipId) return true;
            if (*reinterpret_cast<int*>(info + 0x2c) == equipId) return true;
            if (*reinterpret_cast<int*>(info + 0x40) == equipId) return true;
            for (int i = 0; i < 8; ++i)
                if (*reinterpret_cast<int*>(info + 0x54 + i * 4) == equipId) return true;
            for (int i = 0; i < 8; ++i)
                if (*reinterpret_cast<int*>(info + 0x74 + i * 4) == equipId) return true;
            return false;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) { return true; }
    }


    void Apply(void* node, uint64_t hash)
    {
        Prefetch(hash);
        g_SetTextureName(node, hash, g_MaskSlot, 2);
    }


    uint8_t EquipBgApply(int equipId, void* node, SetWeaponPanelLogo_t orig)
    {
        if (node && Resolve())
        {
            const bool sortie = IsSortieEquip(equipId);

            if (sortie)
            {
                Apply(node, NEW_TEXTURE);
                return 1;
            }
        }
        return orig(equipId, node);
    }


    uint8_t __fastcall hkSetWeaponPanelLogo(int equipId, void* node)
    {
        MISSION_GUARD_ORIGINAL_RET(g_OrigSetWeaponPanelLogo, equipId, node);
        return EquipBgApply(equipId, node, g_OrigSetWeaponPanelLogo);
    }
}

bool Install_SetEquipBackgroundTexture_Hook()
{
    void* target = ResolveGameAddress(gAddr.SetEquipBackgroundTexture);
    if (!target)
        return false;

    const bool ok = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkSetWeaponPanelLogo),
        reinterpret_cast<void**>(&g_OrigSetWeaponPanelLogo));

    Resolve();

    if (gGameBuild == AddressSetRuntime::GameBuild::Tpp_steam_mst_en_day3800)
    {
        void* guard = ResolveGameAddress(kAddr_TexStatusCreate_En154);
        if (guard && !CreateAndEnableHook(
                guard,
                reinterpret_cast<void*>(&hkTexStatusCreate),
                reinterpret_cast<void**>(&g_OrigTexStatusCreate)))
            Log("[UiTextureGuard] install FAILED - a corrupt UI texture "
                "descriptor will fault the render worker inside "
                "fox::gr::TextureStreamerStatus instead of being skipped\n");
    }

#ifdef _DEBUG
    Log("[Hook] EquipBgTexture: %s\n", ok ? "OK" : "FAIL");
#else
    if (!ok)
        Log("[Hook] EquipBgTexture: %s\n", ok ? "OK" : "FAIL");
#endif
    return ok;
}


bool Uninstall_SetEquipBackgroundTexture_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(gAddr.SetEquipBackgroundTexture));

    if (g_OrigTexStatusCreate)
    {
        DisableAndRemoveHook(ResolveGameAddress(kAddr_TexStatusCreate_En154));
        g_OrigTexStatusCreate = nullptr;
    }

    g_OrigSetWeaponPanelLogo = nullptr;
    return true;
}


void SetEnableEquipBackgroundTexture(bool isEnable)
{
    g_isEnableEquipBg = isEnable;
    Log("[GitmoHook] SetEnableEquipBackgroundTexture set\n");
}
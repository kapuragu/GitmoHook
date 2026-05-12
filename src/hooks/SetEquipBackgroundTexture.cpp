#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <unordered_set>

#include "AddressSet.h"
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
// Engine function types
// ----------------------------------------------------

using SetEquipBackgroundTexture_t = uint8_t(__fastcall*)(int equipId, void* isSortieWeapon);
using SetTextureName_t = void(__fastcall*)(void* modelNodeMesh, uint64_t textureHash, uint64_t slotHash, int unk);

// ----------------------------------------------------
// Originals / engine pointers
// ----------------------------------------------------

static SetEquipBackgroundTexture_t g_OrigSetEquipBackgroundTexture = nullptr;
static SetTextureName_t            g_OrigSetTextureName = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

static thread_local bool g_InSetEquipBackgroundTexture = false;
static thread_local int  g_CurrentEquipId = -1;
bool g_isEnableEquipBg = false;

// ----------------------------------------------------
// Hook 1: capture equipId
// ----------------------------------------------------

static uint8_t __fastcall hkSetEquipBackgroundTexture(int equipId, void* isSortieWeapon)
{
    if (MissionCodeGuard::ShouldBypassHooks())
        return g_OrigSetEquipBackgroundTexture(equipId, isSortieWeapon);
    
    g_InSetEquipBackgroundTexture = true;
    g_CurrentEquipId = equipId;

    const uint8_t result = g_OrigSetEquipBackgroundTexture(equipId, isSortieWeapon);

    g_CurrentEquipId = -1;
    g_InSetEquipBackgroundTexture = false;

    return result;
}

static constexpr uint64_t TEX_DEFAULT_ORIG = 0x15695ed8a56ae919ull;

static void __fastcall hkSetTextureName(void* modelNodeMesh, uint64_t textureHash, uint64_t slotHash, int unk)
{
    if (MissionCodeGuard::ShouldBypassHooks())
        return g_OrigSetTextureName(modelNodeMesh, textureHash, slotHash, unk);
    
    if (g_InSetEquipBackgroundTexture)
    {
        if (g_isEnableEquipBg)
        {
            uint64_t newTexture = 0x156810775f8c8515ull; //default, which been changed to\Assets\tpp\ui\texture\equip_bg\

            switch (g_CurrentEquipId)
            {
            case 0x203:
                /*  Unique arm BG textures: Stun Arm BG
                    TppEquip.EQP_HAND_STUNARM = 515 */
                newTexture = 0x15682b4e5f2626d2ull;
                break;
            case 0x204:
                /*  Hand of Jehuty BG
                    TppEquip.EQP_HAND_JEHUTY = 516 */
                newTexture = 0x156b6be3346d38acull;
                break;
            case 0x205:
                /*  Hand of Jehuty BG
                    TppEquip..EQP_HAND_STUN_ROCKET = 517 */
                newTexture = 0x15684206a365ca64;
                break;

            case 0x206:
                /*  Hand of Jehuty BG
                    TppEquip..EQP_HAND_STUN_ROCKET = 518 */
                newTexture = 0x1568b462f43ed09full;
                break;

				//Example for adding more overrides, adjust as needed
            //case 1070: // Tornado-6
            //    newTexture = 0x1569327dd1edbb0full; \Assets\tpp\ui\texture\Emblem\front\ui_emb_front_8012_h_alp.ftex
            //    break;

            default:
                break;
            }

            if (newTexture != 0)
            {
                //gets called every frame its onscreen
                /*Log("[SetTextureName] location=40 equipId=%d: 0x%llX -> 0x%llX\n",
                    g_CurrentEquipId,
                    static_cast<unsigned long long>(textureHash),
                    static_cast<unsigned long long>(newTexture));*/

                textureHash = newTexture;
            }
        }
    }

    g_OrigSetTextureName(modelNodeMesh, textureHash, slotHash, unk);
}

// ----------------------------------------------------
// Install
// ----------------------------------------------------

bool Install_SetEquipBackgroundTexture_Hook()
{
    void* targetSetEquipBackgroundTexture =
        ResolveGameAddress(gAddr.SetEquipBackgroundTexture);

    void* targetSetTextureName = ResolveGameAddress(gAddr.SetTextureName);
    
    const bool okSetEquipBackgroundTexture = CreateAndEnableHook(
        targetSetEquipBackgroundTexture,
        reinterpret_cast<void*>(&hkSetEquipBackgroundTexture),
        reinterpret_cast<void**>(&g_OrigSetEquipBackgroundTexture));
    
    const bool okSetTextureName = CreateAndEnableHook(
        targetSetTextureName,
        reinterpret_cast<void*>(&hkSetTextureName),
        reinterpret_cast<void**>(&g_OrigSetTextureName));

    Log("[Hook] SetEquipBackgroundTexture hooks installed %p and %p\n",okSetEquipBackgroundTexture,okSetTextureName);
    return true;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_SetEquipBackgroundTexture_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(gAddr.SetEquipBackgroundTexture));
    DisableAndRemoveHook(ResolveGameAddress(gAddr.SetTextureName));
    g_OrigSetEquipBackgroundTexture = nullptr;
    g_OrigSetTextureName = nullptr;
    return true;
}

void SetEnableEquipBackgroundTexture(bool isEnable)
{
    g_isEnableEquipBg = isEnable;
    Log("[GitmoHook] SetEnableEquipBackgroundTexture set\n");
}
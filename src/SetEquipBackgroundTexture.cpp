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
// Engine function types
// ----------------------------------------------------

using SetEquipBackgroundTexture_t = uint8_t(__fastcall*)(int equipId, void* isSortieWeapon);
using SetTextureName_t = void(__fastcall*)(void* modelNodeMesh, uint64_t textureHash, uint64_t slotHash, int unk);

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

static constexpr uintptr_t ABS_SetEquipBackgroundTexture = 0x145F236F0ull;
static constexpr uintptr_t ABS_SetTextureName = 0x141DC78F0ull;

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
thread_local bool  g_isEnableEquipBg = false;

// ----------------------------------------------------
// Hook 1: capture equipId
// ----------------------------------------------------

static uint8_t __fastcall hkSetEquipBackgroundTexture(int equipId, void* isSortieWeapon)
{
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
                Log("[SetTextureName] location=40 equipId=%d: 0x%llX -> 0x%llX\n",
                    g_CurrentEquipId,
                    static_cast<unsigned long long>(textureHash),
                    static_cast<unsigned long long>(newTexture));

                textureHash = newTexture;
            }
        }
    }

    g_OrigSetTextureName(modelNodeMesh, textureHash, slotHash, unk);
}

// ----------------------------------------------------
// Install
// ----------------------------------------------------

bool Install_SetEquipBackgroundTexture_Location_Hooks()
{
    const uintptr_t base = GetExeBase();
    if (!base)
        return false;

    void* targetSetEquipBackgroundTexture =
        reinterpret_cast<void*>(base + ToRva(ABS_SetEquipBackgroundTexture));

    void* targetSetTextureName =
        reinterpret_cast<void*>(base + ToRva(ABS_SetTextureName));

    const MH_STATUS initSt = MH_Initialize();
    if (initSt != MH_OK && initSt != MH_ERROR_ALREADY_INITIALIZED)
        return false;

    MH_STATUS st = MH_CreateHook(
        targetSetEquipBackgroundTexture,
        &hkSetEquipBackgroundTexture,
        reinterpret_cast<void**>(&g_OrigSetEquipBackgroundTexture));
    if (st != MH_OK && st != MH_ERROR_ALREADY_CREATED)
        return false;

    st = MH_CreateHook(
        targetSetTextureName,
        &hkSetTextureName,
        reinterpret_cast<void**>(&g_OrigSetTextureName));
    if (st != MH_OK && st != MH_ERROR_ALREADY_CREATED)
        return false;

    st = MH_EnableHook(targetSetEquipBackgroundTexture);
    if (st != MH_OK && st != MH_ERROR_ENABLED)
        return false;

    st = MH_EnableHook(targetSetTextureName);
    if (st != MH_OK && st != MH_ERROR_ENABLED)
        return false;

    Log("[Hook] SetEquipBackgroundTexture location-40 hooks installed\n");
    return true;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_SetEquipBackgroundTexture_Location_Hooks()
{
    DisableAndRemoveHook(ResolveGameAddress(ABS_SetEquipBackgroundTexture));
    DisableAndRemoveHook(ResolveGameAddress(ABS_SetTextureName));
    g_OrigSetEquipBackgroundTexture = nullptr;
    g_OrigSetTextureName = nullptr;
    return true;
}

void SetEnableEquipBackgroundTexture(bool isEnable)
{
    g_isEnableEquipBg = isEnable;
    Log("[GitmoHook] SetEnableEquipBackgroundTexture set\n");
}
#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include "log.h"
#include "HeliVoice.h"
#include "AddressSet.h"
#include "FNVHash32.h"
#include "patch.h"

extern "C" {
#include "lua.h"
}

static const char* DD_vox_SH_voice = "DD_vox_SH_voice";
static const char* DD_vox_SH_radio = "DD_vox_SH_radio";

bool SetEnableHeliVoice(bool isEnable, const char *DD_vox_SH_voice_new, const char *DD_vox_SH_radio_new)
{
    Log("[GitmoHook] SetEnableHeliVoice start\n");
    
    unsigned int original_DD_vox_SH_voice_hash = GetFNVHash32(DD_vox_SH_voice);
    unsigned int new_DD_vox_SH_voice_hash = GetFNVHash32(DD_vox_SH_voice_new);
    
    unsigned int original_DD_vox_SH_radio_hash = GetFNVHash32(DD_vox_SH_radio);
    unsigned int new_DD_vox_SH_radio_hash = GetFNVHash32(DD_vox_SH_radio_new);
    
    std::uint8_t* original_DD_vox_SH_voice_Bytes = static_cast<std::uint8_t*>(static_cast<void*>(&original_DD_vox_SH_voice_hash));
    std::uint8_t* new_DD_vox_SH_voice_Bytes = static_cast<std::uint8_t*>(static_cast<void*>(&new_DD_vox_SH_voice_hash));
    
    std::uint8_t* original_DD_vox_SH_radio_Bytes = static_cast<std::uint8_t*>(static_cast<void*>(&original_DD_vox_SH_radio_hash));
    std::uint8_t* new_DD_vox_SH_radio_Bytes = static_cast<std::uint8_t*>(static_cast<void*>(&new_DD_vox_SH_radio_hash));
    
    SIZE_T dwSize = sizeof(original_DD_vox_SH_voice_hash);
    
    bool success0 = TogglePatch(isEnable, gAddr.DD_vox_SH_voice, dwSize, original_DD_vox_SH_voice_Bytes, new_DD_vox_SH_voice_Bytes);
    bool success1 = TogglePatch(isEnable, gAddr.DD_vox_SH_radio, dwSize, original_DD_vox_SH_radio_Bytes, new_DD_vox_SH_radio_Bytes);
    bool success2 = TogglePatch(isEnable, gAddr.DD_vox_SH_radio2, dwSize, original_DD_vox_SH_radio_Bytes, new_DD_vox_SH_radio_Bytes);
    bool success3 = TogglePatch(isEnable, gAddr.DD_vox_SH_radio3, dwSize, original_DD_vox_SH_radio_Bytes, new_DD_vox_SH_radio_Bytes);
    
    Log("[GitmoHook] SetEnableHeliVoice set\n");
    
    return success0 && success1 && success2 && success3;
}
#include "TelopStartTitleSetBgTexture.h"

#include <cstdint>

#include "AddressSet.h"
#include "HookUtils.h"
#include "log.h"
#include "patch.h"

//tpp::ui::hud::TelopStartTitleEvCall::SetBgTexture

// Textures
static uint64_t TEX_TELOP_BG_ORIGINAL       = 0x156846156e516e5eull; //   /Assets/tpp/common_source/ui/common_texture/cm_diamonddogs_clp.ftex
static uint64_t TEX_TELOP_BG_ORIGINAL_BLUR  = 0x156848f067a209acull; //   /Assets/tpp/common_source/ui/common_texture/cm_diamonddogs_blr_clp.ftex
static uint64_t TEX_TELOP_BG_GZ             = 0x15693e01563c09c3ull; //   /Assets/tpp/common_source/ui/common_texture/cm_mblogo_clp_1.ftex
static uint64_t TEX_TELOP_BG_GZ_BLUR        = 0x156a20d598cc4802ull; //   /Assets/tpp/common_source/ui/common_texture/cm_mblogo_blr_clp_1.ftex

void SetEnableTelopBg(const bool isEnable)
{
    Log("[GitmoHook] SetEnableTelopBg set\n");
    
    std::uint8_t* originalBytes = static_cast<std::uint8_t*>(static_cast<void*>(&TEX_TELOP_BG_ORIGINAL));
    std::uint8_t* enabeldBytes = static_cast<std::uint8_t*>(static_cast<void*>(&TEX_TELOP_BG_GZ));
    
    //The function is called, but the texture swap doesn't apply?
    //bool success = TogglePatch(isEnable,gAddr.TelopStartTitleEvCall_BgTexture,sizeof(TEX_TELOP_BG_ORIGINAL),originalBytes,enabeldBytes);
}
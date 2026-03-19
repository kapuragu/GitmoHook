#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <unordered_set>

#include "HookUtils.h"
#include "log.h"
#include "FoxHashes.h"

#include "HeliVoice.h"

#include <map>

#include "MissionCodeGuard.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

//tpp::gm::heli::impl::SoundControllerImpl::Update
static constexpr uintptr_t ABS_DD_vox_SH_voice = 0x140d5d242ull;
static constexpr uintptr_t ABS_DD_vox_SH_radio = 0x140d5d240ull;
static constexpr uintptr_t ABS_DD_vox_SH_radio2 = 0x140d5d232ull;
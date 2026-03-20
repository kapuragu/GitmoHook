#include "GetPhotoAdditionalTextLangId.h"
#include "pch.h"
#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <unordered_set>

#include "HookUtils.h"
#include "log.h"
#include "FoxHashes.h"

#include "ChangeLocationMenu.h"

#include <map>

#include "MissionCodeGuard.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using GetPhotoAdditionalTextLangIdHook_t = unsigned long long(__thiscall*)(MotherBaseMissionCommonData* self, unsigned long long* __return_storage_ptr__, unsigned short missionCode, unsigned char photoId, unsigned char photoType);

// ----------------------------------------------------
// Addresses
// ----------------------------------------------------

//tpp::ui::menu::MotherBaseMissionCommonData::GetPhotoAdditionalTextLangId
static constexpr uintptr_t ABS_GetPhotoAdditionalTextLangId = 0x140925ef0ull;

// ----------------------------------------------------
// Original pointers
// ----------------------------------------------------

static GetPhotoAdditionalTextLangIdHook_t g_OrigGetPhotoAdditionalTextLangIdHook = nullptr;

// ----------------------------------------------------
// Context
// ----------------------------------------------------

std::list<PhotoInfo> addPhotoInfos{};

// ----------------------------------------------------
// Hook
// ----------------------------------------------------

unsigned long long __thiscall hkGetPhotoAdditionalTextLangId(MotherBaseMissionCommonData* self, unsigned long long* ret, unsigned short missionCode, unsigned char photoId, unsigned char photoType)
{
    if (MissionCodeGuard::ShouldBypassHooks())
        return g_OrigGetPhotoAdditionalTextLangIdHook(self,ret,missionCode,photoId,photoType);
    
    for (auto const& i : addPhotoInfos) {
        if (i.MissionCode == missionCode)
        {
            if (i.PhotoId == photoId)
            {
                if (i.PhotoType == photoType)
                {
                    Log("GetPhotoAdditionalTextLangIdHook return {:x}\n", *ret);
                    *ret = i.TargetTypeLangId;
                    return *ret;
                }
            }
        }
    }
    return g_OrigGetPhotoAdditionalTextLangIdHook(self,ret,missionCode,photoId,photoType);
}

bool Install_PhotoAdditionalText_Hook()
{
    void* target = ResolveGameAddress(ABS_GetPhotoAdditionalTextLangId);

    const bool okTarget = CreateAndEnableHook(
        target,
        reinterpret_cast<void*>(&hkGetPhotoAdditionalTextLangId),
        reinterpret_cast<void**>(&g_OrigGetPhotoAdditionalTextLangIdHook));

    Log("[Hook] PhotoAdditionalText %p installed at %p\n", okTarget, target);
    return okTarget;
}

// Removes the SetLuaFunctions hook.
bool Uninstall_PhotoAdditionalText_Hook()
{
    DisableAndRemoveHook(ResolveGameAddress(ABS_GetPhotoAdditionalTextLangId));
    g_OrigGetPhotoAdditionalTextLangIdHook = nullptr;
    return true;
}

void AddPhotoAdditionalText(unsigned short missionCode, unsigned char photoId, unsigned char photoType, const char* targetTypeLangIdStr)
{
    unsigned long long hash = FoxHashes::StrCode64(targetTypeLangIdStr);
    for (std::list<PhotoInfo>::iterator it = addPhotoInfos.begin(); it != addPhotoInfos.end(); ++it){
        if (it->MissionCode == missionCode)
        {
            if (it->PhotoId == photoId)
            {
                if (it->PhotoType == photoType)
                {
                    Log("[GitmoHook] AddPhotoAdditionalText replaced %d %d %d with %s\n",missionCode,photoId,photoType,targetTypeLangIdStr);
                    it->TargetTypeLangId = hash;
                    return;
                }
            }
        }
    }
    PhotoInfo photoInfo = {
        missionCode,
        photoId,
        static_cast<PHOTO_TYPE>(photoType),
        hash,
    };
    addPhotoInfos.push_back(photoInfo);
    Log("[GitmoHook] AddPhotoAdditionalText added %d %d %d with %s\n",missionCode,photoId,photoType,targetTypeLangIdStr);
}
#include "FNVHash32.h"

#include "AddressSet.h"
#include "HookUtils.h"

using FNVHash32_t = unsigned int(__fastcall*)(const char * strToHash);
    
static FNVHash32_t g_FNVHash32 = nullptr;

unsigned int GetFNVHash32(const char * strToHash)
{
    unsigned int ret = (unsigned int)-1;

    if (!g_FNVHash32)
        g_FNVHash32 = reinterpret_cast<FNVHash32_t>(ResolveGameAddress(gAddr.FNVHash32));
    
    if (g_FNVHash32)
        ret = g_FNVHash32(strToHash);
    
    Log("[HeliVoice] GetFNVHash32(%s)=%d\n",strToHash,ret);
    
    return ret;
}
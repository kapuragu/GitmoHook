#include "patch.h"

#include <cstring>

#include "HookUtils.h"
#include "log.h"

bool TogglePatch(bool isEnable, uintptr_t pointer, SIZE_T dwSize, std::uint8_t* originalBytes, std::uint8_t* enabledBytes)
{
    
    void* target = ResolveGameAddress(pointer);
    if (!target)
    {
        Log("[Patch] TogglePatch(%s): ResolveGameAddress @%lu null\n",
            isEnable ? "true" : "false", pointer);
        return false;
    }

    DWORD oldProtect = 0;
    if (!VirtualProtect(target, dwSize, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        Log("[Patch] TogglePatch(%s): VirtualProtect failed @%lu (err=%lu)\n",
            isEnable ? "true" : "false", pointer, GetLastError());
        return false;
    }
    
    std::uint8_t* src = isEnable ? enabledBytes : originalBytes;
    std::memcpy(target, src, dwSize);

    DWORD restored = 0;
    VirtualProtect(target, dwSize, oldProtect, &restored);
    FlushInstructionCache(GetCurrentProcess(), target, dwSize);

    Log("[Patch] TogglePatch(%s): wrote at %p\n",
        isEnable ? "true" : "false", target);
}

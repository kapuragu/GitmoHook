#pragma once
#include <cstdint>

#include "hooks/AddressSet.h"

class patch
{
public:
    
};

bool TogglePatch(bool isEnable, uintptr_t pointer, SIZE_T dwSize, std::uint8_t* originalBytes, std::uint8_t* enabledBytes);
//taken from unknown321's dynamite
//https://github.com/unknown321/dynamite
#ifndef HOOK_PATCH_H
#define HOOK_PATCH_H

#include <vector>
#include <string>

struct Patch {
    uintptr_t address;
    std::vector<signed short> expected;
    std::vector<signed short> patch;
    std::string description;

    bool Apply() const;
};

#endif // HOOK_PATCH_H
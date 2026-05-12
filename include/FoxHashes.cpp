#include "pch.h"
#include "FoxHashes.h"

#include <Windows.h>
#include <algorithm>
#include <cstdint>
#include <string>

#include "HookUtils.h"
#include "hooks/AddressSet.h"

namespace
{
    using FoxStrHash32_t = uint32_t(__fastcall*)(char* str);
    using FoxStrHash64_t = uint64_t(__fastcall*)(char* str);
    using PathHashCode_t = uint64_t(__fastcall*)(char* str);

    using FNVHash32_t = uint32_t(__fastcall*)(char* str);

    static FoxStrHash32_t g_FoxStrHash32 = nullptr;
    static FoxStrHash64_t g_FoxStrHash64 = nullptr;
    static PathHashCode_t g_PathHashCode = nullptr;
    
    static FNVHash32_t g_FNVHash32 = nullptr;
}

namespace FoxHashes
{
    bool Resolve()
    {
        if (g_FoxStrHash32 && g_FoxStrHash64 && g_PathHashCode && g_FNVHash32)
            return true;

        if (!g_FoxStrHash32)
            g_FoxStrHash32 = reinterpret_cast<FoxStrHash32_t>(ResolveGameAddress(gAddr.FoxStrHash32));

        if (!g_FoxStrHash64)
            g_FoxStrHash64 = reinterpret_cast<FoxStrHash64_t>(ResolveGameAddress(gAddr.FoxStrHash64));

        if (!g_PathHashCode)
            g_PathHashCode = reinterpret_cast<PathHashCode_t>(ResolveGameAddress(gAddr.PathHashCode));
        
        if (!g_FNVHash32)
            g_FNVHash32 = reinterpret_cast<FNVHash32_t>(ResolveGameAddress(gAddr.FNVHash32));

        return g_FoxStrHash32 && g_FoxStrHash64 && g_PathHashCode && g_FNVHash32;
    }

    std::string NormalizeAssetPath(const std::string& path)
    {
        std::string out = path;
        std::replace(out.begin(), out.end(), '\\', '/');

        if (out.empty())
            return out;

        if (out.rfind("Assets/", 0) == 0)
            out = "/" + out;

        if (!out.empty() && out.front() != '/')
            out = "/" + out;

        return out;
    }

    uint32_t StrCode32(const char* text)
    {
        if (!Resolve() || !text || !*text)
            return 0;

        std::string temp(text);
        return g_FoxStrHash32(&temp[0]);
    }

    uint32_t StrCode32(const std::string& text)
    {
        if (!Resolve())
            return 0;

        std::string temp(text);
        return g_FoxStrHash32(&temp[0]);
    }

    uint64_t StrCode64(const char* text)
    {
        if (!Resolve() || !text || !*text)
            return 0;

        std::string temp(text);
        return g_FoxStrHash64(&temp[0]);
    }

    uint64_t StrCode64(const std::string& text)
    {
        if (!Resolve())
            return 0;

        std::string temp(text);
        return g_FoxStrHash64(&temp[0]);
    }

    uint64_t PathCode64Ext(const char* path)
    {
        if (!Resolve() || !path || !*path)
            return 0;

        std::string normalized = NormalizeAssetPath(path);
        return g_PathHashCode(&normalized[0]);
    }

    uint64_t PathCode64Ext(const std::string& path)
    {
        if (!Resolve())
            return 0;

        std::string normalized = NormalizeAssetPath(path);
        return g_PathHashCode(&normalized[0]);
    }

    uint32_t FNVHash32(const char* text)
    {
        if (!Resolve() || !text || !*text)
            return 0;
        
        std::string temp(text);
        auto str = &temp[0];
        Log("[FoxHashes] FNVHash32 3 %s\n",str);
        auto ret = g_FNVHash32(str);
        Log("[FoxHashes] FNVHash32 4 %ull\n",ret);
        return ret;
    }

    uint32_t FNVHash32(const std::string& text)
    {
        if (!Resolve())
            return 0;

        std::string temp(text);
        return g_FNVHash32(&temp[0]);
    }
}
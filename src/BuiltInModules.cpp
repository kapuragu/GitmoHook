#include "pch.h"

#include <Windows.h>
#include <mutex>

#include "BuiltInModules.h"
#include "FeatureModule.h"

// Installs the Lua registration hook.
bool Install_SetLuaFunctions_Hook();
bool Install_GameOverScreen_Hook();
bool Install_LoadingScreen_Hook();
bool Install_SetEquipBackgroundTexture_Hook();
bool Install_ChangeLocationMenu_Hook();
bool Install_PhotoAdditionalText_Hook();

// Removes the Lua registration hook.
bool Uninstall_SetLuaFunctions_Hook();
bool Uninstall_GameOverScreen_Hook();
bool Uninstall_LoadingScreen_Hook();
bool Uninstall_SetEquipBackgroundTexture_Hook();
bool Uninstall_ChangeLocationMenu_Hook();
bool Uninstall_PhotoAdditionalText_Hook();

namespace
{
    class LuaBridgeModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "LuaBridge";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_SetLuaFunctions_Hook();
        }

        void Uninstall() override
        {
            Uninstall_SetLuaFunctions_Hook();
        }
    };

    class GameOverScreenModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "GameOverScreen";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_GameOverScreen_Hook();
        }

        void Uninstall() override
        {
            Uninstall_GameOverScreen_Hook();
        }
    };

    class LoadingScreenModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "LoadingScreen";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_LoadingScreen_Hook();
        }

        void Uninstall() override
        {
            Uninstall_LoadingScreen_Hook();
        }
    };

    class SetEquipBackgroundTextureModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "SetEquipBackgroundTexture";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_SetEquipBackgroundTexture_Hook();
        }

        void Uninstall() override
        {
            Uninstall_SetEquipBackgroundTexture_Hook();
        }
    };

    class ChangeLocationMenuModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "ChangeLocationMenu";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_ChangeLocationMenu_Hook();
        }

        void Uninstall() override
        {
            Uninstall_ChangeLocationMenu_Hook();
        }
    };

    class PhotoAdditionalTextModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "PhotoAdditionalText";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_PhotoAdditionalText_Hook();
        }

        void Uninstall() override
        {
            Uninstall_PhotoAdditionalText_Hook();
        }
    };
}

void RegisterBuiltInFeatureModules()
{
    static LuaBridgeModule s_LuaBridgeModule;
    static GameOverScreenModule s_GameOverScreenModule;
    static LoadingScreenModule s_LoadingScreenModule;
    static SetEquipBackgroundTextureModule s_SetEquipBackgroundTextureModule;
    static ChangeLocationMenuModule s_ChangeLocationMenuModule;
    static PhotoAdditionalTextModule s_PhotoAdditionalTextModule;

    static std::once_flag s_Once;
    std::call_once(s_Once, []()
        {
            FeatureModuleRegistry::Instance().Register(&s_LuaBridgeModule);
            FeatureModuleRegistry::Instance().Register(&s_GameOverScreenModule);
            FeatureModuleRegistry::Instance().Register(&s_LoadingScreenModule);
            FeatureModuleRegistry::Instance().Register(&s_SetEquipBackgroundTextureModule);
            FeatureModuleRegistry::Instance().Register(&s_ChangeLocationMenuModule);
            FeatureModuleRegistry::Instance().Register(&s_PhotoAdditionalTextModule);
        });
}
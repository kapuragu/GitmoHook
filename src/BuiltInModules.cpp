#include "pch.h"

#include <Windows.h>
#include <mutex>

#include "BuiltInModules.h"
#include "FeatureModule.h"
#include "hooks/State_EnterStandHoldup1.h"

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

bool Install_CautionStepNormalTimerHook();
bool Uninstall_CautionStepNormalTimerHook();

bool Install_VIPSleepFaint_Hook();
bool Uninstall_VIPSleepFaint_Hook();

bool Install_VIPHoldup_Hook();
bool Uninstall_VIPHoldup_Hook();

bool Install_VIPRadio_Hook();
bool Uninstall_VIPRadio_Hook();

bool Install_LostHostage_Hooks();
bool Uninstall_LostHostage_Hooks();

bool Install_LostHostageDiscovery_Hooks();
bool Uninstall_LostHostageDiscovery_Hooks();

bool Install_UpdateOptCamo_Hook();
bool Uninstall_UpdateOptCamo_Hook();

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

    class CautionTimerModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "CautionTimer";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_CautionStepNormalTimerHook();
        }

        void Uninstall() override
        {
            Uninstall_CautionStepNormalTimerHook();
        }
    };

    class VIPSleepFaintModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "VIPSleepFaint";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_VIPSleepFaint_Hook();
        }

        void Uninstall() override
        {
            Uninstall_VIPSleepFaint_Hook();
        }
    };

    class VIPHoldupModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "VIPHoldup";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_VIPHoldup_Hook();
        }

        void Uninstall() override
        {
            Uninstall_VIPHoldup_Hook();
        }
    };

    class VIPRadioModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "VIPRadio";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_VIPRadio_Hook();
        }

        void Uninstall() override
        {
            Uninstall_VIPRadio_Hook();
        }
    };

    class HoldUpReactionCowardlyReactionsModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "HoldUpReactionCowardlyReactions";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_HoldUpReactionCowardlyReactions_Hook();
        }

        void Uninstall() override
        {
            Uninstall_HoldUpReactionCowardlyReactions_Hook();
        }
    };

    class LostHostageModule final : public IFeatureModule
    {
    public:
        const char* GetName() const override
        {
            return "LostHostage";
        }

        bool Install(HMODULE hGame) override
        {
            UNREFERENCED_PARAMETER(hGame);
            return Install_LostHostage_Hooks() && Install_LostHostageDiscovery_Hooks();
        }

        void Uninstall() override
        {
            Uninstall_LostHostage_Hooks();
            Uninstall_LostHostageDiscovery_Hooks();
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
    static CautionTimerModule s_CautionTimerModule;
    static HoldUpReactionCowardlyReactionsModule s_HoldUpReactionCowardlyReactionsModule;
    
    static LostHostageModule s_LostHostageModule;

    static VIPSleepFaintModule s_VIPSleepFaintModule;
    static VIPHoldupModule s_VIPHoldupModule;
    static VIPRadioModule s_VIPRadioModule;
    
    static std::once_flag s_Once;
    std::call_once(s_Once, []()
        {
            FeatureModuleRegistry::Instance().Register(&s_LuaBridgeModule);
            FeatureModuleRegistry::Instance().Register(&s_GameOverScreenModule);
            FeatureModuleRegistry::Instance().Register(&s_LoadingScreenModule);
            FeatureModuleRegistry::Instance().Register(&s_SetEquipBackgroundTextureModule);
            FeatureModuleRegistry::Instance().Register(&s_ChangeLocationMenuModule);
            FeatureModuleRegistry::Instance().Register(&s_PhotoAdditionalTextModule);
            FeatureModuleRegistry::Instance().Register(&s_CautionTimerModule);
            FeatureModuleRegistry::Instance().Register(&s_VIPSleepFaintModule);
            FeatureModuleRegistry::Instance().Register(&s_VIPHoldupModule);
            FeatureModuleRegistry::Instance().Register(&s_VIPRadioModule);
            FeatureModuleRegistry::Instance().Register(&s_HoldUpReactionCowardlyReactionsModule);
            FeatureModuleRegistry::Instance().Register(&s_LostHostageModule);
        });
}
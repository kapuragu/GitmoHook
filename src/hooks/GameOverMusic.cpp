#include "GameOverMusic.h"

#include "AddressSet.h"
#include "FoxHashes.h"
#include "patch.h"

static unsigned int Play_bgm_gameover_FNV132 = 2016311311;
static unsigned int Stop_bgm_gameover_FNV132 = 1577147537;

static unsigned int Play_bgm_gameover_paradox_FNV132 = 2933771421;
static unsigned int Stop_bgm_gameover_paradox_FNV132 = 300567547;

static unsigned int Play_bgm_gameover_perfectstealth_FNV132 = 0x9ae8c2c2;
static unsigned int Stop_bgm_gameover_perfectstealth_FNV132 = 0xfa2c3474;

static unsigned int Play_bgm_s10010_gameover_FNV132 = 3354865787;
static unsigned int Stop_bgm_s10010_gameover_FNV132 = 1018550225;

bool SetGameOverMusic(bool isEnable, GAME_OVER_TYPE type, const char * playEventStr, const char * stopEventStr)
{
    unsigned int playEventHash = FoxHashes::FNVHash32(playEventStr);
    unsigned int stopEventHash = FoxHashes::FNVHash32(stopEventStr);
    
    std::uint8_t* playEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&playEventHash));
    std::uint8_t* stopEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&stopEventHash));
    
    SIZE_T dwSize = sizeof(Play_bgm_gameover_FNV132);
    
    if (type==GAME_OVER_GENERAL)
    {
        std::uint8_t* oldPlayEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Play_bgm_gameover_FNV132));
        std::uint8_t* oldStopEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Stop_bgm_gameover_FNV132));

        const bool success_Play = TogglePatch(isEnable,gAddr.Play_bgm_gameover,dwSize,oldPlayEventBytes,playEventBytes);
        const bool success_Stop = TogglePatch(isEnable,gAddr.Stop_bgm_gameover,dwSize,oldStopEventBytes,stopEventBytes);
        return success_Play && success_Stop;
    }
    else if (type==GAME_OVER_PARADOX)
    {
            std::uint8_t* oldPlayEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Play_bgm_gameover_paradox_FNV132));
            std::uint8_t* oldStopEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Stop_bgm_gameover_paradox_FNV132));

            const bool success_Play = TogglePatch(isEnable,gAddr.Play_bgm_gameover_paradox,dwSize,oldPlayEventBytes,playEventBytes);
            const bool success_Stop = TogglePatch(isEnable,gAddr.Stop_bgm_gameover_paradox,dwSize,oldStopEventBytes,stopEventBytes);
            const bool success_Play_soundId = TogglePatch(isEnable,gAddr.Play_bgm_gameover_paradox_soundId,dwSize,oldPlayEventBytes,playEventBytes);
            const bool success_Stop_soundId = TogglePatch(isEnable,gAddr.Stop_bgm_gameover_paradox_soundId,dwSize,oldStopEventBytes,stopEventBytes);
            return success_Play && success_Stop && success_Play_soundId && success_Stop_soundId;
    }
    else if (type==GAME_OVER_STEALTH)
    {
        std::uint8_t* oldPlayEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Play_bgm_gameover_perfectstealth_FNV132));
        std::uint8_t* oldStopEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Stop_bgm_gameover_perfectstealth_FNV132));

        const bool success_Play = TogglePatch(isEnable,gAddr.Play_bgm_gameover_perfectstealth,dwSize,oldPlayEventBytes,playEventBytes);
        const bool success_Stop = TogglePatch(isEnable,gAddr.Stop_bgm_gameover_perfectstealth,dwSize,oldStopEventBytes,stopEventBytes);
        return success_Play && success_Stop;
    }
    else if (type==GAME_OVER_CYPRUS)
    {
        std::uint8_t* oldPlayEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Play_bgm_s10010_gameover_FNV132));
        std::uint8_t* oldStopEventBytes = static_cast<std::uint8_t*>(static_cast<void*>(&Stop_bgm_s10010_gameover_FNV132));

        const bool success_Play = TogglePatch(isEnable,gAddr.Play_bgm_s10010_gameover,dwSize,oldPlayEventBytes,playEventBytes);
        const bool success_Stop = TogglePatch(isEnable,gAddr.Stop_bgm_s10010_gameover,dwSize,oldStopEventBytes,stopEventBytes);
        return success_Play && success_Stop;
    };
    return false;
}
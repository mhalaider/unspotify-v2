#include "hooks.hpp"

#include "functions/functions.hpp"

#include "minhook/minhook.hpp"
#include "utils/utils.hpp"

#define CREATE_HOOK(address, detour) if(auto status = MH_CreateHook((LPVOID)address, (LPVOID)hooked_functions::detour, (LPVOID*)&hooked_functions::o_##detour); status!= MH_OK) { \
  std::printf("[hook_mgr] failed to create hook at 0x%p for "#detour"\n", (LPVOID)address);\
} else { std::printf("[hook_mgr] created hook at 0x%p for "#detour"\n", (LPVOID)address); }\

void c_hooks::init() const
{
    std::printf("[hook_mgr] starting hooks setup...\n");

    const auto spotify_mod = static_cast<void*>(GetModuleHandleA("Spotify.dll"));
    std::printf("[hook_mgr] spotify.dll -> 0x%p\n", spotify_mod);

    // @note: basic init
    {
	    if(auto status = MH_Initialize(); status != MH_OK)
	    {
            std::printf("[hook_mgr] MH_Initialize failed with status %s\n", MH_StatusToString(status));
            return;
	    }
    }

    // @note: create track
    {
        // @xref: Spotify.dll str:"Creating track player for track (playback_id %s)"
        const auto abs_address = utils::pattern_scan(spotify_mod, "E8 ?? ?? ?? ?? 90 48 8B 45 ?? 4C 89 7D");
        const auto create_track_address = utils::get_abs_call(abs_address);
        std::printf("[hook_mgr] spotify.dll:create_track -> 0x%llx (abs: 0x%llx)\n", create_track_address, abs_address);

        CREATE_HOOK(create_track_address, create_track);
    }

    // @note: enable all hooks
    {
        if(auto status = MH_EnableHook(MH_ALL_HOOKS); status != MH_OK)
        {
            std::printf("[hook_mgr] MH_EnableHook(MH_ALL_HOOKS) failed with status %s\n", MH_StatusToString(status));
            return;
        }
    }

    std::printf("[hook_mgr] hooks setup success!\n");
}

void c_hooks::shutdown() const
{
    MH_DisableHook(MH_ALL_HOOKS);
}

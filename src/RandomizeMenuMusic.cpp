#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <random>
#include "mod_utils.hpp"
#include "mapped-hooks.hpp"
#include <MinHook.h>

void __stdcall fadeInMusicHook(const char* filename) {
    if (filename == std::string("menuLoop.mp3")) {
        return MHook::getOriginal(fadeInMusicHook)(ModUtils::getRandomFileNameFromDir("Resources/MenuSongs", "menuLoop.mp3").data());
    }
    return MHook::getOriginal(fadeInMusicHook)(filename);
}

DWORD WINAPI thread_func(void* hModule) {

    // initialize minhook
    MH_Initialize();

    std::random_device os_seed;
    const unsigned int seed = os_seed();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(250, 1000);
    int sleepMs = distribute(generator);
    Sleep(sleepMs);

    MHook::registerHook(base + 0xC4BD0, fadeInMusicHook);

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

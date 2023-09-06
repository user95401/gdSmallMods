#include "mod_utils.hpp"
#include "hooks.hpp"
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;

inline void(__stdcall* fadeInMusic)(const char* filename);
void __stdcall fadeInMusic_H(const char* filename) {
    if (filename == std::string("menuLoop.mp3"))
        return fadeInMusic(ModUtils::getRandomFileNameFromDir("Resources/MenuSongs", "menuLoop.mp3").data());
    return fadeInMusic(filename);
}

DWORD WINAPI thread_func(void* hModule) {

    // initialize minhook
    MH_SafeInitialize();

    HOOK(base + 0xC4BD0, fadeInMusic);

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

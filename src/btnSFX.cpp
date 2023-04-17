#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <random>
#include <cocos2d.h>
#include <gd.h>
#include "mod_utils.hpp"
#include "mapped-hooks.hpp"
#include <MinHook.h>
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;
void __fastcall CCMenuItemSpriteExtra_selected(CCMenuItemSpriteExtra* item) {
    MHook::getOriginal(CCMenuItemSpriteExtra_selected)(item);
    GameSoundManager::sharedState()->playEffect("btnClick.ogg");
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

    MHook::registerHook(base + 0x19270, CCMenuItemSpriteExtra_selected);
    
    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

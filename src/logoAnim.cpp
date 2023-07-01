#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <random>
#include <cocos2d.h>
#include <gd.h>
#include "mod_utils.hpp"
#include "hooks.hpp"
#include <MinHook.h>
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;
inline bool(__thiscall* MenuLayer_init)(MenuLayer*);
bool __fastcall MenuLayer_init_H(MenuLayer* self) {
    if (!MenuLayer_init(self)) return false;
    auto GJ_logo_001 = (CCSprite*)(self->getChildren()->objectAtIndex(0));
    GJ_logo_001->runAction(CCRepeatForever::create(CCSequence::create(
        CCEaseSineInOut::create(CCScaleTo::create(1.0f, 1.05f)), 
        CCEaseSineInOut::create(CCScaleTo::create(1.0, 1.0f)), nullptr)));
    return true;
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

    HOOK(base + 0x1907b0, MenuLayer_init, false);

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

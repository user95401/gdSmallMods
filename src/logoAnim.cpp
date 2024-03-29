﻿#include "mod_utils.hpp"
#include "hooks.hpp"
#include <cocos2d.h>
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
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
    MH_SafeInitialize();

    HOOK(base + 0x1907b0, MenuLayer_init);

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

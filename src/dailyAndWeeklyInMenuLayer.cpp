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
    MenuLayer_init(self);
    CCMenu* menu = CCMenu::create();
    self->addChild(menu);
    CCMenuItemSpriteExtra* daily = CCMenuItemSpriteExtra::create(ModUtils::createSprite("dailymenu"), self, menu_selector(CreatorLayer::onDailyLevel));
    daily->setPosition({ (CCDirector::sharedDirector()->getScreenRight() / 2) - 39, -26.000 });
    menu->addChild(daily);
    CCMenuItemSpriteExtra* weekly = CCMenuItemSpriteExtra::create(ModUtils::createSprite("weeklymenu"), self, menu_selector(CreatorLayer::onWeeklyLevel));
    weekly->setPosition({ (CCDirector::sharedDirector()->getScreenRight() / 2) - 39, -70.000 });
    menu->addChild(weekly);
    CCMenuItemSpriteExtra* GJ_optionsBtn02_001 = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_optionsBtn02_001.png"), self, menu_selector(MenuLayer::onOptions));
    GJ_optionsBtn02_001->setPosition({ (CCDirector::sharedDirector()->getScreenRight() / 2) - 39, 69.000 });
    menu->addChild(GJ_optionsBtn02_001);
    return true;
}

DWORD WINAPI thread_func(void* hModule) {

    // initialize minhook
    MH_Initialize();

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

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

TextureQuality aviableQuality = kTextureQualityLow;
void updateAviableQuality() {
    if(CCFileUtils::sharedFileUtils()->isFileExist("Resources/CCControlColourPickerSpriteSheet.plist"))
        aviableQuality = kTextureQualityLow;
    if (CCFileUtils::sharedFileUtils()->isFileExist("Resources/CCControlColourPickerSpriteSheet-hd.plist"))
        aviableQuality = kTextureQualityMedium;
    if (CCFileUtils::sharedFileUtils()->isFileExist("Resources/CCControlColourPickerSpriteSheet-uhd.plist"))
        aviableQuality = kTextureQualityHigh;
}

inline LoadingLayer* (__cdecl* LoadingLayer_loadAssets)(LoadingLayer*);
void __fastcall LoadingLayer_loadAssets_H(LoadingLayer* self) {
    LoadingLayer_loadAssets(self);
    updateAviableQuality();
    if (GameManager::sharedState()->m_eQuality != aviableQuality && !self->m_bFromRefresh) {
        GameManager::sharedState()->m_eQuality = aviableQuality;
        GameManager::sharedState()->reloadAll(GameManager::sharedState()->m_bSwitchModes, GameManager::sharedState()->m_bToFullscreen, self->m_bFromRefresh);
        //CC_CONTENT_SCALE_FACTOR
        CCDirector::sharedDirector()->updateContentScale(aviableQuality);
    }
}
    
DWORD WINAPI thread_func(void* hModule) {

    MH_Initialize();
    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets, false);
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

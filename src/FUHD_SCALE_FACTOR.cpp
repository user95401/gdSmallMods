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

class MenuLayerMod {
    void onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
        std::vector<char>* responseData = response->getResponseData();
        std::string responseString(responseData->begin(), responseData->end());
        if (responseString != version) {
        }
    }
};

inline MenuLayer* (__cdecl* MenuLayer_init)(MenuLayer*);
bool __fastcall MenuLayer_init_H(MenuLayer* self) {
    if (!MenuLayer_init(self)) return false;

    //udate if sddso herer
    CCHttpRequest* request = new CCHttpRequest;
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setUrl(MenuLayerMod::upadateInfoUrl);
    request->setResponseCallback(self, httpresponse_selector(MenuLayerMod::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();

    return true;
}


inline void(__thiscall* GameManager_update)(GameManager*, float);
void __fastcall GameManager_update_H(GameManager* self, void*, float dt) {
    GameManager_update(self, dt);
    CCDirector::sharedDirector()->setContentScaleFactor(8.f);
}

DWORD WINAPI thread_func(void* hModule) {
    MH_Initialize();
    HOOK(base + 0xce440, GameManager_update, true);
    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

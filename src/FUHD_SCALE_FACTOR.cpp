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

class HttpRequests {
public:
    void onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
        std::vector<char>* responseData = response->getResponseData();
        std::string responseString(responseData->begin(), responseData->end());
        if (std::string(CCFileUtils::sharedFileUtils()->fullPathForFilename("CCControlColourPickerSpriteSheet-uhd.png", true)).find("FUHD_" + responseString) == std::string::npos) {
            if (
                MessageBoxA(nullptr, 
                    (
                    "Something wrong with resources!\n"
                    "it maybe outdated or was not loaded.\n"
                    ""
                    "The \"FUHD_"+responseString+"\" was not founded in path:\n"+ 
                    CCFileUtils::sharedFileUtils()->fullPathForFilename("CCControlColourPickerSpriteSheet-uhd.png", true) +
                    "\n\nDownload actual resource pack?"
                    ).c_str(), 
                "FUHD_SCALE_FACTOR MOD", MB_ICONERROR | MB_YESNO)
                == IDYES
                ) CCApplication::sharedApplication()->openURL("http://user95401.webq2e.ru/FUHD_SCALE_FACTOR_LAST_TP_VER.download");
        }
    }
};

const char* (__thiscall* LoadingLayer_getString)(LoadingLayer* self);
const char* __fastcall LoadingLayer_getString_H(LoadingLayer* self, void*) {
    //CCDirector::sharedDirector()->setContentScaleFactor(8.f); fucks "GJ_GameSheet.plist"
    if(CC_CONTENT_SCALE_FACTOR() > 4.f) return LoadingLayer_getString(self);
    else return std::string(
        "\n"
        "GD FUHD\n\nBy user666").c_str();
}

inline LoadingLayer* (__cdecl* loadAssets)(LoadingLayer*);
void __fastcall loadAssets_H(LoadingLayer* self, void*) {
    loadAssets(self);
    auto parent = self->getParent();
    if (self->m_nLoadIndex == 1 and parent->getTag() != 21356) self->addChild(self->create(self->m_bFromRefresh), 100, 21356);
    CCDirector::sharedDirector()->setContentScaleFactor(8.f);

    CCLabelBMFont* warn;

    if (self->m_nLoadIndex <= 1) {//one time creating nodes
        warn = CCLabelBMFont::create("One more time reloading contains bugs!", "bigFont.fnt");
        warn->setAnchorPoint({ -0.005 , 0.000 });
        warn->setScale(0.450);
        warn->setColor(ccRED);
    }

    if (self->m_bFromRefresh) {
        if(!self->getChildByTag(5957)) self->addChild(warn, 5, 5957);
    }
}

inline LoadingLayer* (__cdecl* loadingFinished)(LoadingLayer*);
void __fastcall loadingFinished_H(LoadingLayer* self) {
    loadingFinished(self);

    //udate if sddso herer
    CCHttpRequest* request = new CCHttpRequest;
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setUrl("http://user95401.webq2e.ru/FUHD_SCALE_FACTOR_LAST_TP_VER.inf");
    request->setResponseCallback(self, httpresponse_selector(HttpRequests::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();
}

DWORD WINAPI thread_func(void* hModule) {
    MH_Initialize();
    HOOK(base + 0x18cf40, LoadingLayer_getString, true);
    HOOK(base + 0x18C8E0, loadAssets, true);
    HOOK(base + 0x18c790, loadingFinished, false);
    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

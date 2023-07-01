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

bool FullscreenBtnClicked = false;

int toNextLevel;

CCLabelTTF* countLbl;
CCLabelTTF* multiplierLbl;

char* intToStr(int data) {
    std::string strData = std::to_string(data);

    char* temp = new char[strData.length() + 1];
    strcpy(temp, strData.c_str());

    return temp;
}

class clicker : MenuLayer {
public:
    static int getCountGV() {
        return GameManager::sharedState()->getIntGameVariable("clicker-count");
    }
    static void setCountGV(int val) {
        GameManager::sharedState()->setIntGameVariable("clicker-count", val);
    }
    static int getMultiplierGV() {
        int result = GameManager::sharedState()->getIntGameVariable("multiplier-count");
        if (result > 0) return result;
        else setMultiplierGV(1);
        return 1;
    }
    static void setMultiplierGV(int val) {
        GameManager::sharedState()->setIntGameVariable("multiplier-count", val);
    }
    void onClickBtn(CCObject* sneeder) {
        //multiplier
        if (toNextLevel <= 100) ++toNextLevel;
        if (toNextLevel == 100) {
            setMultiplierGV(getMultiplierGV() + 1);
            multiplierLbl->runAction(CCSequence::create(
                CCScaleTo::create(0.01, 1.1),
                CCEaseBounceOut::create(CCScaleTo::create(0.1, 1.0)),
                nullptr
            ));
            toNextLevel = 0;
        }
        multiplierLbl->setString(std::string(std::string(intToStr(getMultiplierGV())) + "x").data());
        //count
        setCountGV(getCountGV() + (1 * getMultiplierGV()));
        countLbl->setString(intToStr(getCountGV()));

        GameManager::sharedState()->save();
    }
    void onResetBtn(CCObject* sneeder) {
        toNextLevel = 0;
        //countLbl
        setCountGV(0);
        countLbl->setString(intToStr(getCountGV()));
        countLbl->runAction(CCSequence::create(CCTintTo::create(0.0, 210, 50, 50), CCTintTo::create(1.0, 0, 0, 0), nullptr));
        //multiplierLbl
        setMultiplierGV(1);
        multiplierLbl->setString(std::string(std::string(intToStr(getMultiplierGV())) + "x").data());
        multiplierLbl->runAction(CCSequence::create(CCTintTo::create(0.0, 210, 50, 50), CCTintTo::create(1.0, 0, 0, 0), nullptr));
    }
    void onFullscreenBtn(CCObject* sneeder) {
        if (FullscreenBtnClicked) {
            GameManager::sharedState()->reloadAll(true, true, false);
            FullscreenBtnClicked = false;
        }
        else {
            FullscreenBtnClicked = true;
            GameManager::sharedState()->reloadAll(true, false, false);
        }
    }
};

inline bool(__thiscall* MenuLayer_init)(MenuLayer*);
bool __fastcall MenuLayer_init_H(MenuLayer* self) {
    return true;
}

inline LoadingLayer* (__cdecl* LoadingLayer_loadAssets)(LoadingLayer*);
void __fastcall LoadingLayer_loadAssets_H(LoadingLayer* self) {
    /*if (!MenuLayer_init(self)) return false;*/
    self->removeAllChildren();
    GameManager::sharedState()->fadeInMusic("1212312_RNMNX---3-A-K-A-T.mp3");
    //ingi_bg.png
    auto backgroundSprite = ModUtils::createSprite("ingi_bg.png");
    backgroundSprite->setScaleX(CCDirector::sharedDirector()->getWinSize().width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(CCDirector::sharedDirector()->getWinSize().height / backgroundSprite->getContentSize().height);
    backgroundSprite->setAnchorPoint({ 0, 0 });
    backgroundSprite->setPosition({ 0,0 });
    self->addChild(backgroundSprite, -1);
    backgroundSprite->runAction(CCFadeIn::create(1.0));
    //btn
    self->addChild(CCMenu::createWithItem(CCMenuItemSpriteExtra::create(ModUtils::createSprite("ingi_logo.png"), self, menu_selector(clicker::onClickBtn))));
    //count lbl
    countLbl = CCLabelTTF::create(intToStr(clicker::getCountGV()), "Comic Sans MS", 20.0);
    countLbl->setHorizontalAlignment(kCCTextAlignmentLeft);
    countLbl->setColor({ 0,0,0 });
    countLbl->setAnchorPoint({ 0.0,0.5 });
    countLbl->setPosition({ 18.000, CCDirector::sharedDirector()->getWinSize().height - 25 });
    self->addChild(countLbl);
    //multiplierLbl
    multiplierLbl = CCLabelTTF::create(std::string(std::string(intToStr(clicker::getMultiplierGV())) + "x").data(), "Comic Sans MS", 15.0);
    multiplierLbl->setHorizontalAlignment(kCCTextAlignmentLeft);
    multiplierLbl->setColor({ 0,0,0 });
    multiplierLbl->setAnchorPoint({ 0.0,0.5 });
    multiplierLbl->setPosition({ 20.000, CCDirector::sharedDirector()->getWinSize().height - 8 });
    self->addChild(multiplierLbl);

    CCMenu* Menu = CCMenu::create();

    //Quit
    CCMenuItemSpriteExtra* Quit = CCMenuItemSpriteExtra::create(CCLabelTTF::create("r", "Webdings", 35.0), self, menu_selector(MenuLayer::onQuit));
    Quit->setPosition({ 0, 0 });
    Menu->addChild(Quit);
    //resetBtn
    CCMenuItemSpriteExtra* reset = CCMenuItemSpriteExtra::create(CCLabelTTF::create("q", "Webdings", 35.0), self, menu_selector(clicker::onResetBtn));
    reset->setPosition({ 0, -32.000 });
    Menu->addChild(reset);
    //FullscreenBtn
    const char* FullscreenBtnChar = "2";
    if (FullscreenBtnClicked) FullscreenBtnChar = "1";
    CCMenuItemSpriteExtra* FullscreenBtn = CCMenuItemSpriteExtra::create(CCLabelTTF::create(FullscreenBtnChar, "Webdings", 35.0), self, menu_selector(clicker::onFullscreenBtn));
    FullscreenBtn->setPosition({ 0, -58.000 });
    Menu->addChild(FullscreenBtn);

    Menu->setPosition({ CCDirector::sharedDirector()->getWinSize().width - 25, CCDirector::sharedDirector()->getWinSize().height - 25 });
    Menu->setColor({ 0,0,0 });
    self->addChild(Menu);
}

DWORD WINAPI thread_func(void* hModule) {

    LoadLibrary("cocos-explorer.dll");

    // initialize minhook
    MH_Initialize();

    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets, true);
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

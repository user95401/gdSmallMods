#include "mod_utils.hpp"
#include "hooks.hpp"
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;


inline void(__thiscall* customSetup)(GameObject*);
void __fastcall customSetup_H(GameObject* self, int) {
    customSetup(self);
    if (self->m_nObjectID == 3004) {//spider ring
        //main setups
        self->m_nObjectType = kGameObjectTypePinkJumpRing;
        self->m_pBaseColor->defaultColorID = 1011;
        self->m_bIsEffectObject = true;
    }
    if (self->m_nObjectID == 3005) {//spider pad
        //main setups
        self->m_nObjectType = kGameObjectTypePinkJumpPad;//type
        self->m_pBaseColor->defaultColorID = 1011;//defaultColor
        self->m_bIsEffectObject = true;//IsEffectObject (for multiactive feature:smiling_face_with_tear:)

        //box setups
        self->setAnchorPoint(CCPoint(self->getAnchorPoint().x, 1.4));// totally :smiling_face_with_tear:
        auto frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(self->m_sTextureName.c_str());
        self->m_obObjectSize = cocos2d::CCSizeMake(frame->getRect().size.width, frame->getRect().size.height);
        self->m_obBoxOffset = CCPoint(0, -10);
        self->m_obBoxOffset2 = CCPoint(0, -10);
    }
}

inline void(__thiscall* ringJump)(PlayerObject*, GameObject*);
void __fastcall ringJump_H(gd::PlayerObject* self, int, gd::GameObject* ring) {
    ringJump(self, ring);
    if (ring->m_nObjectID == 3004 && ring->m_bHasBeenActivated) {
        self->spiderTestJump(true);
        if (ring->m_bRandomisedAnimStart) ring->m_bHasBeenActivated = false;
        if (ring->m_bRandomisedAnimStart) ring->m_bHasBeenActivatedP2 = false;
    }
}

inline void(__thiscall* bumpPlayer)(GJBaseGameLayer*, PlayerObject*, GameObject*);
void __fastcall bumpPlayer_H(GJBaseGameLayer* self, int, gd::PlayerObject* Player, gd::GameObject* bumper) {
    bumpPlayer(self, Player, bumper);
    if (bumper->m_nObjectID == 3005) {
        Player->spiderTestJump(true);
        if (bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivated = false;
        if (bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivatedP2 = false;
    }
}
   
inline void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab6
    auto tab6 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(6));
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3005, 4), 4);//spider pad
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3004, 4), 13);//spider orb
    tab6->reloadItemsInNormalSize();

    return;
}

GameObject* lastSelectedObj;
inline void(__thiscall* EditorUI_selectObject)(EditorUI*, GameObject* obj, bool filter);//win 0x86250;
void __fastcall EditorUI_selectObject_H(EditorUI* self, void*, GameObject* obj, bool filter) {
    EditorUI_selectObject(self, obj, filter);
    lastSelectedObj = obj;
    //CCMessageBox(std::string("lastSelectedObj: " + std::to_string(lastSelectedObj)).c_str(), __FUNCTION__);
}

inline CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char*, const char*);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    //SetupAnimSettingsPopup
    if (std::string(str) == "Edit Animation Settings") {
        if (lastSelectedObj->m_nObjectID == 3004 || lastSelectedObj->m_nObjectID == 3005) //spider orb anda pad
            str = "Object setup";
    }
    if (std::string(str) == "Speed: ") {
        if (lastSelectedObj->m_nObjectID == 3004 || lastSelectedObj->m_nObjectID == 3005) //spider orb anda pad
            str = "-";
    }
    if (std::string(str) == "Randomize Start") {
        if (lastSelectedObj->m_nObjectID == 3004 || lastSelectedObj->m_nObjectID == 3005) //spider orb anda pad
            str = "Allow multi activate";
        return CCLabelBMFont::create(str, fntFile, 220, kCCTextAlignmentCenter);
    }
    if (std::string(str) == "Animation settings help" && std::string(fntFile) == "chatFont.fnt") {
        CCLabelBMFont* lbl = CCLabelBMFont::create("", "chatFont.fnt", 435, kCCTextAlignmentCenter);
        std::string info = "";
        if (lastSelectedObj->m_nObjectID == 3004 || lastSelectedObj->m_nObjectID == 3005)
            info = "Allows multi activate feature.\nNote: set up first groundHeight(first 2 grounds gamemode) \nto reduce bugs with cube or robot";
        lbl->setString(std::string("                      \n" + info + "\n\n\n ").c_str());
        if (info != "") return lbl;
    }
    return CCLabelBMFont_create(str, fntFile);
}

DWORD WINAPI thread_func(void* hModule) {

    MH_SafeInitialize();
    HOOK(base + 0xd1c10, customSetup);
    HOOK(base + 0x1f4ff0, ringJump);
    HOOK(base + 0x10ed50, bumpPlayer);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu);//huh
    HOOK(base + 0x86250, EditorUI_selectObject);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create);
    MH_EnableHook(MH_ALL_HOOKS);

    ObjectToolbox::sharedState()->addObject(3004, "spiderRing_001.png");
    ObjectToolbox::sharedState()->addObject(3005, "spiderBump_001.png");

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

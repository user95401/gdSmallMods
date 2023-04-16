#include "mod_utils.hpp"
DWORD WINAPI thread_func(void* hModule) {
    std::string info = "You can configure what hack will work. Everything is enabled by default! To turn off a certain hack, you must replace + to - before that hack's name using a HEX editor. Example: +VerifyHack => -VerifyHack";
    char plus = '+';

    std::string SliderLimitBypass = "+SliderLimitBypass";
    if (SliderLimitBypass.find(plus) != SliderLimitBypass.npos){
        ModUtils::write_bytes(base + 0x2E5CA, { 0xEB, });
        ModUtils::write_bytes(base + 0x2E5F8, { 0xEB, });
    }

    std::string CopyHack = "+CopyHack";
    if (CopyHack.find(plus) != CopyHack.npos) {
        ModUtils::write_bytes(base + 0x179B8E, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x176FE5, { 0xB0 , 0x01 , 0x90 });
    }

    std::string LevelEdit = "+LevelEdit";
    if (LevelEdit.find(plus) != LevelEdit.npos) {
        ModUtils::write_bytes(base + 0x179B8E, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x176FE5, { 0xB0 , 0x01 , 0x90 });
    }

    std::string CustomObjectBypass = "+CustomObjectBypass";
    if (CustomObjectBypass.find(plus) != CustomObjectBypass.npos) {
        ModUtils::write_bytes(base + 0x179B8E, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x176FE5, { 0xB0 , 0x01 , 0x90 });
    }

    std::string VerifyHack = "+VerifyHack";
    if (VerifyHack.find(plus) != VerifyHack.npos) {
        ModUtils::write_bytes(base + 0x71D48, { 0xEB, });
    }

    std::string ObjectBypass = "+ObjectBypass";
    if (ObjectBypass.find(plus) != ObjectBypass.npos) {
        ModUtils::write_bytes(base + 0x73169, { 0xFF, 0xFF, 0xFF, 0x7F });
        ModUtils::write_bytes(base + 0x856A4, { 0xFF, 0xFF, 0xFF, 0x7F });
        ModUtils::write_bytes(base + 0x87B17, { 0xFF, 0xFF, 0xFF, 0x7F });
        ModUtils::write_bytes(base + 0x87BC7, { 0xFF, 0xFF, 0xFF, 0x7F });
        ModUtils::write_bytes(base + 0x87D95, { 0xFF, 0xFF, 0xFF, 0x7F });
        ModUtils::write_bytes(base + 0x880F4, { 0xFF, 0xFF, 0xFF, 0x7F });
        ModUtils::write_bytes(base + 0x160B06, { 0xFF, 0xFF, 0xFF, 0x7F });
    }

    std::string DefaultSongBypass = "+DefaultSongBypass";
    if (DefaultSongBypass.find(plus) != DefaultSongBypass.npos) {
        ModUtils::write_bytes(base + 0x174407, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174411, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174456, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174460, { 0x90, 0x90, 0x90 });
    }

    std::string ZoomBypass = "+ZoomBypass";
    if (ZoomBypass.find(plus) != ZoomBypass.npos) {
        ModUtils::write_bytes(base + 0x87801, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x87806, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x87871, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x87876, { 0x90, 0x90, 0x90 });
    }

    std::string ToolboxButtonBypass = "+ToolboxButtonBypass";
    if (ToolboxButtonBypass.find(plus) != ToolboxButtonBypass.npos) {
        ModUtils::write_bytes(base + 0x13A548, { 0x83, 0xF9, 0x01 });
        ModUtils::write_bytes(base + 0x13A559, { 0xB8, 0x01, 0x00, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x13A54D, { 0x83, 0xF9, 0x7F });
        ModUtils::write_bytes(base + 0x13A552, { 0xB9, 0x7F, 0x00, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x13A5D8, { 0x83, 0xF9, 0x01 });
        ModUtils::write_bytes(base + 0x13A5E9, { 0xB8, 0x01, 0x00, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x13A5dd, { 0x83, 0xF9, 0x7F });
        ModUtils::write_bytes(base + 0x13A5E2, { 0xB9, 0x7F, 0x00, 0x00, 0x00 });
    }

    std::string EditorExtension = "+EditorExtension";
    if (EditorExtension.find(plus) != EditorExtension.npos) {
        ModUtils::write_bytes(base + 0x2E67A4, { 0x00, 0x60, 0xEA, 0x4B });
        ModUtils::write_bytes(base + 0x8FA4D, { 0x0F, 0x60, 0xEA, 0x4B});
    }

    std::string PlaceOver = "+PlaceOver";
    if (PlaceOver.find(plus) != PlaceOver.npos) {
        ModUtils::write_bytes(base + 0x160EE1, { 0x8B, 0xC1, 0x90 });
        ModUtils::write_bytes(base + 0x160EF2, { 0xE9, 0x23, 0x02, 0x00, 0x00, 0x90 });
    }

    std::string RotationHack = "+RotationHack";
    if (RotationHack.find(plus) != RotationHack.npos) {
        ModUtils::write_bytes(base + 0x85CBC, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x8BDDD, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x8BE16, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xECA3D, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xEE5A9, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x20181E, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    }

    std::string FreeScroll = "+FreeScroll";
    if (FreeScroll.find(plus) != FreeScroll.npos) {
        ModUtils::write_bytes(base + 0x8FAAC, { 0xEB });
        ModUtils::write_bytes(base + 0x8FA95, { 0xEB });
        ModUtils::write_bytes(base + 0x8FAC5, { 0xEB });
        ModUtils::write_bytes(base + 0x8FADC, { 0xEB });
    }

    std::string ZOrderBypass = "+ZOrderBypass";
    if (ZOrderBypass.find(plus) != ZOrderBypass.npos) {
        ModUtils::write_bytes(base + 0x22DEDE, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x22DEE8, { 0x90, 0x90, 0x90 });
    }

    std::string GroupIDBypass = "+GroupIDBypass";
    if (GroupIDBypass.find(plus) != GroupIDBypass.npos) {
        //thanks gos uslugi
        ModUtils::write_bytes(base + 0x1628F7, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x22D66E, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x22D66E, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x132A60, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x131E31, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x230FA0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x23CE90, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x23B790, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x247AA0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x149820, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x14918E, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x124C10, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x1244C1, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x124CB0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x12451E, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x232B60, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x135FE0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x1358B1, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x2357E0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x236EE0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x2385E0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x23E500, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x41940 , { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x235860, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x135FE0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
        ModUtils::write_bytes(base + 0x2358E0, { 0x81, 0xFE, 0x4D, 0x04, 0x00, 0x00 });
    }

    std::string ColourIDBypass = "+ColourIDBypass";
    if (ColourIDBypass.find(plus) != ColourIDBypass.npos) {
        ModUtils::write_bytes(base + 0x472FA, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x473EB, { 0xEB });
        ModUtils::write_bytes(base + 0x4754B, { 0x8B, 0xD0, 0x90 });
        ModUtils::write_bytes(base + 0x4759B, { 0xEB });
        ModUtils::write_bytes(base + 0x470DB, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x470A0, { 0xEB });
        ModUtils::write_bytes(base + 0x1628FD, { 0xEB });
    }

    std::string PlaytestZoomBypass = "+PlaytestZoomBypass";
    if (PlaytestZoomBypass.find(plus) != PlaytestZoomBypass.npos) {
        ModUtils::write_bytes(base + 0x1697A9, { 0x90, 0x90 });
    }

    std::string SmoothEditorTrail = "+SmoothEditorTrail";
    if (SmoothEditorTrail.find(plus) != SmoothEditorTrail.npos) {
        ModUtils::write_bytes(base + 0x16AB0D, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    }

    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

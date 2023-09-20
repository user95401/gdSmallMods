#include "mod_utils.hpp"
#include "hooks.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
using namespace std;

#include "private_code/iconsPatch.hpp"

inline void(__thiscall* update)(GameManager* self, float);//0xce440
void __fastcall update_H(GameManager* self, void*, float dt) {
    update(self, dt);
    updateIconsCount();
}

DWORD WINAPI iconsPatch(void* hModule) {
    ini.LoadFile("config/iconsPatch.ini");
    if (!ini.GetValue("iconsPatch", "cube")) {
        filesystem::create_directories("config");
        std::ofstream ("config/iconsPatch.ini");
        ini.SetValue("DISCOVERED BY RUHAX | GUSCHIN", "", "");
        ini.DeleteValue("DISCOVERED BY RUHAX | GUSCHIN", "", "", false);
        ini.SetValue("iconsPatch", "cube", "142", "; org count of cubes 142");
        ini.SetValue("iconsPatch", "ship", "51", "; org count of ships 51");
        ini.SetValue("iconsPatch", "ball", "42", "; org count of BALLS 42");
        ini.SetValue("iconsPatch", "ufo", "35", "; org count of ufos 35");
        ini.SetValue("iconsPatch", "wave", "35", "; org count of waves 35");
        ini.SetValue("iconsPatch", "robot", "26", "; org count of robots 26");
        ini.SetValue("iconsPatch", "spider", "17", "; org count of robots 17");
        ini.SaveFile("config/iconsPatch.ini");
    }
    MH_SafeInitialize();
    HOOK(base + 0xce440, update);
    MH_EnableHook(MH_ALL_HOOKS);
    updateIconsCount();
    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, iconsPatch, hModule, 0, 0);
    return TRUE;
}

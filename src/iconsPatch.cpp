#include "mod_utils.hpp"
#include "hooks.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
using namespace std;

#include "private_code/iconsPatch.hpp"

#include "SimpleIni.h"

inline void(__thiscall* update)(GameManager* self, float);//0xce440
void __fastcall update_H(GameManager* self, void*, float dt) {
    update(self, dt);
    updateIconsCount();
}

DWORD WINAPI iconsPatch(void* hModule) {
    CSimpleIni ini;
    filesystem::create_directories("config");
    ini.LoadFile("config/iconsPatch.ini");
    if (!(ini.KeyExists("iconsPatch", "cube")))
        ini.SetValue("iconsPatch", "cube", "142", ";------------------------\n; DISCOVERED BY GUSCHIN\n;------------------------\n; org count of cubes 142");
    if (!(ini.KeyExists("iconsPatch", "ship")))
        ini.SetValue("iconsPatch", "ship", "51", "; org count of ships 51");
    if (!(ini.KeyExists("iconsPatch", "ball")))
        ini.SetValue("iconsPatch", "ball", "42", "; org count of BALLS 42");
    if (!(ini.KeyExists("iconsPatch", "ufo")))
        ini.SetValue("iconsPatch", "ufo", "35", "; org count of ufos 35");
    if (!(ini.KeyExists("iconsPatch", "wave")))
        ini.SetValue("iconsPatch", "wave", "35", "; org count of waves 35");
    if (!(ini.KeyExists("iconsPatch", "robot")))
        ini.SetValue("iconsPatch", "robot", "26", "; org count of robots 26");
    if (!(ini.KeyExists("iconsPatch", "spider")))
        ini.SetValue("iconsPatch", "spider", "17", "; org count of robots 17");
    ini.SaveFile("config/iconsPatch.ini");
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

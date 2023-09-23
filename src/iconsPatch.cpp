#include "mod_utils.hpp"
#include "hooks.hpp"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;
using namespace std;

#include "SimpleIni.h"

void updateIconsCount() {
    CSimpleIni ini;
    ini.LoadFile("config/iconsPatch.ini");
    uint8_t cube = stoi(ini.GetValue("iconsPatch", "cube"));
    uint8_t ship = stoi(ini.GetValue("iconsPatch", "ship"));
    uint8_t ball = stoi(ini.GetValue("iconsPatch", "ball"));
    uint8_t ufo = stoi(ini.GetValue("iconsPatch", "ufo"));
    uint8_t wave = stoi(ini.GetValue("iconsPatch", "wave"));
    uint8_t robot = stoi(ini.GetValue("iconsPatch", "robot"));
    uint8_t spider = stoi(ini.GetValue("iconsPatch", "spider"));
    /// BY RUHAX | GUSCHIN
    //icon cube (исправлено!) (150)
    ModUtils::write_bytes(base + 0x1F7E48, { 0xB9, cube }),
    ModUtils::write_bytes(base + 0x12B095, { 0xC7, 0x44, 0x24, 0x1C, cube }),
    ModUtils::write_bytes(base + 0x12C766, { 0xC7, 0x44, 0x24, 0x14, cube }),
    ModUtils::write_bytes(base + 0x12807A, { 0xB8, cube }),
    ModUtils::write_bytes(base + 0x12BE64, { 0xB9, cube }),
    ModUtils::write_bytes(base + 0x1E6DD9, { 0xBA, cube }),
    ModUtils::write_bytes(base + 0x12C26C, { 0xBA, cube });
    //icon ship (исправлено!) (169)
    ModUtils::write_bytes(base + 0x1E6DEF, { 0xB8, ship });
    ModUtils::write_bytes(base + 0x1F7FF6, { 0xBA, ship });
    ModUtils::write_bytes(base + 0x12C6D1, { 0xC7, 0x44, 0x24, 0x14, ship });
    ModUtils::write_bytes(base + 0x12B0CA, { 0xC7, 0x44, 0x24, 0x1C, ship });
    //icon ball (исправлено!) (114)
    ModUtils::write_bytes(base + 0x12C6EC, { 0xC7, 0x44, 0x24, 0x14, ball });
    ModUtils::write_bytes(base + 0x12B0FF, { 0xC7, 0x44, 0x24, 0x1C, ball });
    ModUtils::write_bytes(base + 0x1F83A6, { 0xBA, ball });
    //icon ufo (исправлено!) (148)
    ModUtils::write_bytes(base + 0x22DA45, { 0xB9, ufo });
    ModUtils::write_bytes(base + 0x24A18F, { 0xB8, ufo });
    ModUtils::write_bytes(base + 0x24B210, { 0xB9, ufo });
    ModUtils::write_bytes(base + 0x1F81A6, { 0xBA, ufo });
    ModUtils::write_bytes(base + 0x12B134, { 0xC7, 0x44, 0x24, 0x1C, ufo });
    ModUtils::write_bytes(base + 0x12C704, { 0xC7, 0x44, 0x24, 0x14, ufo });
    ModUtils::write_bytes(base + 0x25612A, { 0xC7, 0x84, 0x24, 0x28, 0x0A, 0x00, 0x00, ufo });
    //icon wave (исправлено!) (96)
    ModUtils::write_bytes(base + 0x128568, { 0xB8, wave });
    ModUtils::write_bytes(base + 0x142762, { 0xBB, wave });
    ModUtils::write_bytes(base + 0x1F8586, { 0xBA, wave });
    ModUtils::write_bytes(base + 0x12B169, { 0xC7, 0x44, 0x24, 0x1C, wave });
    ModUtils::write_bytes(base + 0x12C71C, { 0xC7, 0x44, 0x24, 0x14, wave });
    //icon robot (исправлено!) (68)
    ModUtils::write_bytes(base + 0x12B19E, { 0xC7, 0x44, 0x24, 0x1C, robot, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x12C734, { 0xC7, 0x44, 0x24, 0x14, robot, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x255ADC, { 0xC7, 0x84, 0x24, 0x28, 0x0A, 0x00, 0x00, robot, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x199436, { 0xC7, 0x84, 0x24, 0x08, 0x2E, 0x44, 0x00, robot, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x1F855A, { 0xBA, 0x44, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x20CCD5, { 0xB9, 0x44, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x14673D, { 0xB8, robot, 0x00, 0x00, 0x00 }); //ВИДИМОСТЬ
    ModUtils::write_bytes(base + 0x1F6ACD, { 0xB8, robot, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x20900F, { 0xB9, robot, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x20CCC3, { 0x6A, robot });
    //GeometryDash.exe+125F61  - ВИДИМОСТЬ В ГАРАЖЕ 1
    ModUtils::write_bytes(base + 0x125F61, { 0xB9, robot, 0x00, 0x00, 0x00 });
    //B9 45 00 00 00
    //GeometryDash.exe+12880E   - ВИДИМОСТЬ В ГАРАЖЕ 2
    ModUtils::write_bytes(base + 0x12880E, { 0xB9, robot, 0x00, 0x00, 0x00 });
    //GeometryDash.exe+1800A5 - ???
    //icon Spider
    ModUtils::write_bytes(base + 0x12B1D3, { 0xC7, 0x44, 0x24, 0x1C, spider, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x12C74C, { 0xC7, 0x44, 0x24, 0x14, spider, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x146745, { 0xBA, spider, 0x00, 0x00, 0x00 });
    ModUtils::write_bytes(base + 0x1553A2, { 0xC7, 0x84, 0x24, 0xC0, spider, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 });
    //GeometryDash.exe+1289CE  - видимость спайдера 1
    ModUtils::write_bytes(base + 0x1289CE, { 0xB9, spider, 0x00, 0x00, 0x00 });
    //GeometryDash.exe+126021  - видимость спайдера 2
    //B9 44 00 00 00
    ModUtils::write_bytes(base + 0x126021, { 0xB9, spider });
}

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
        ini.SetValue("iconsPatch", "cube", "142", ";------------------------\n; DISCOVERED BY GUSCHIN\n; https://github.com/zGuschin/IconPatch\n;------------------------\n\n; org count of cubes 142");
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

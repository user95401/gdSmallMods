#include "mod_utils.hpp"
using namespace gd;
DWORD WINAPI thread_func(void* hModule) {
    std::string info = "You can disable unlocking of icons or colors: You must replace '+' to '-' Example: +Icons => -Icons";
    char plus = '+';
    std::string Icons = "+Icons";
    if (Icons.find(plus) != Icons.npos) {
        ModUtils::write_bytes(base + 0xC50A8, { 0xB0, 0x01, 0x90, 0x90, 0x90 });
    }
    std::string Colors = "+Colors";
    if (Colors.find(plus) != Colors.npos) {
        ModUtils::write_bytes(base + 0xC54BA, { 0xB0, 0x01, 0x90, 0x90, 0x90 });
    }
    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

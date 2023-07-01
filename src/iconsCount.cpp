#include "mod_utils.hpp"
DWORD WINAPI thread_func(void* hModule) {
    ModUtils::write_bytes(base + 0x1E7F14, { 0x07, 0x7d, 0x1d, 0xe8, 0x34, 0xcb, 0xed, 0xff }); //icons?
    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

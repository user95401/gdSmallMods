#include "mod_utils.hpp"
#include "hooks.hpp"
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;

namespace fs = std::filesystem;

bool isDebugMode(bool wantedToSelect = false) {

    if (!CCFileUtils::sharedFileUtils()->isFileExist("config/setUrlHook/debugging.cfg") || wantedToSelect) {
        std::ofstream outfile("config/setUrlHook/debugging.cfg");
        if (MessageBoxExA(nullptr, "Enable debugging?", "setUrlHook mod", MB_ICONQUESTION | MB_YESNO, LANG_ENGLISH) == IDYES) {
            outfile << "isDebugMode=true\nNOTE: write false instead true to disable debugging" << std::endl;
            outfile.close();
        }
        else {
            outfile << "isDebugMode=false\nwrite true instead false to enable debugging" << std::endl;
            outfile.close();
        }
    }

    std::string debugging;
    std::ifstream indebugging("config/setUrlHook/debugging.cfg");
    getline(indebugging, debugging);
    indebugging.close();

    if (debugging.find("isDebugMode=true") != debugging.npos)
        return true;

    return false;
}

inline void(__thiscall* CCHttpRequest_setUrl)(CCHttpRequest*, const char*);
void __fastcall CCHttpRequest_setUrl_H(CCHttpRequest* self, void*, const char* url) {

    std::string the_url = url;

    std::string target;
    std::ifstream intarget("config/setUrlHook/target.cfg");
    getline(intarget, target);
    intarget.close();

    std::string replaceto;
    std::ifstream inreplaceto("config/setUrlHook/replaceto.cfg");
    getline(inreplaceto, replaceto);
    inreplaceto.close();

    the_url.replace(the_url.find(target), target.length(), replaceto);

    if(isDebugMode()) 
        if (MessageBoxExA(nullptr, std::string(the_url + "\n" + target + "=>" + replaceto).c_str(), __FUNCTION__, MB_ICONINFORMATION | MB_OKCANCEL | MB_DEFBUTTON1, LANG_ENGLISH) == IDCANCEL)
            isDebugMode(true);

    CCHttpRequest_setUrl(self, the_url.c_str());
}

DWORD WINAPI thread_func(void* hModule) {
    // initialize minhook
    MH_SafeInitialize();
    fs::create_directories("config/setUrlHook");
    if (!CCFileUtils::sharedFileUtils()->isFileExist("config/setUrlHook/target.cfg")) {
        MessageBoxExA(nullptr, "The «target.cfg» file is not exist in «config/setUrlHook» folder!\nI created it with «http://www.boomlings.com/database».", "setUrlHook mod", MB_ICONERROR | MB_OK, LANG_ENGLISH);
        std::ofstream outfile("config/setUrlHook/target.cfg");
        outfile << "http://www.boomlings.com/database" << std::endl;
        outfile.close();
    }
    if (!CCFileUtils::sharedFileUtils()->isFileExist("config/setUrlHook/replaceto.cfg")) {
        MessageBoxExA(nullptr, "The «replaceto.cfg» file is not exist in «config/setUrlHook» folder!\nI created it with «http://ykisl.ru/srve/database».", "setUrlHook mod", MB_ICONERROR | MB_OK, LANG_ENGLISH);
        std::ofstream outfile("config/setUrlHook/replaceto.cfg");
        outfile << "http://ykisl.ru/srve/database" << std::endl;
        outfile.close();
    }
    //(int)GetProcAddress(GetModuleHandle("libExtensions.dll"), "?setUrl@CCHttpRequest@extension@cocos2d@@QAEXPBD@Z")
    CCEXT_HOOK("?setUrl@CCHttpRequest@extension@cocos2d@@QAEXPBD@Z", CCHttpRequest_setUrl);
    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}

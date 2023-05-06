#include "pch.h"
#include "PauseHook.h"
#include <fstream>

gd::TextArea* createHH(void* font, void* e, float scale, float width, float height,
    void* disableColor, void* caption, void* a) {


    std::cout << width << " " << scale << std::endl;

    auto pRet = matdash::orig<&createHH, matdash::Optcall>(font, e, scale, width, height, disableColor, caption, a);


    return pRet;
}


DWORD WINAPI threadFunc(void* hModule) {

    matdash::create_console();

    matdash::add_hook<&PauseLayerHook::createHook, matdash::Thiscall>(gd::base + 0x1E4570);
    matdash::add_hook<&PauseLayerHook::customSetupHook, matdash::Thiscall>(gd::base + 0x1E4620);
    matdash::add_hook<&PauseLayerHook::musicSliderChangedHook, matdash::Thiscall>(gd::base + 0x1E5CE0);
    matdash::add_hook<&PauseLayerHook::sfxSliderChangedHook, matdash::Thiscall>(gd::base + 0x1DDFA0);
    //matdash::add_hook<&createHH, matdash::Optcall>(gd::base + 0x33270);

    //matdash::add_hook<&Hooks::NoNodeI_registerWithTouchDispatcher, matdash::Thiscall>(gd::base + 0x16990);

    //cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("BE_GameSheet01.plist", "BE_GameSheet01.png");//no working :b
    //cocos2d::CCTextureCache::sharedTextureCache()->addImage("BE_GameSheet01.png", 0);


    return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if(CreateThread(0, 0x100, threadFunc, hModule, 0, 0))
        break;
    }
    return TRUE;
}


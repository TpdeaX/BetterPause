#include "pch.h"
#include "PauseHook.h"
#include <fstream>

gd::TextArea* createHH(void* font, void* e, float scale, float width, float height,
    void* disableColor, void* caption, void* a) {


    std::cout << width << " " << scale << std::endl;

    auto pRet = matdash::orig<&createHH, matdash::Optcall>(font, e, scale, width, height, disableColor, caption, a);


    return pRet;
}

LONG_PTR oWindowProc;
bool isClosing = false;
bool newWindowProcSet = false;
bool onPopupEnd = false;

void MenuLayer_FLAlert_ClickedH(gd::MenuLayer* self, gd::FLAlertLayer* param_1, bool param_2) {
    matdash::orig<&MenuLayer_FLAlert_ClickedH, matdash::Thiscall>(self, param_1, param_2);
}

class ButtonsClass : public gd::FLAlertLayer, public cocos2d::CCTextFieldDelegate, public gd::FLAlertLayerProtocol
{
public:
    static void onConfirmExitLevel(cocos2d::CCObject* pSender) {
        auto alert = gd::FLAlertLayer::create(
            new ButtonsClass(), "Quit Game", "Cancel", "Yes", 300.0f,
            "Are you sure you want to <cr>Quit</c>?"
        );
        alert->setTag(0);
        alert->show();
    }

    void FLAlert_Clicked(gd::FLAlertLayer* self, bool btn2) {
        onPopupEnd = false;
        if (!btn2)return;

        switch (self->getTag())
        {
        case 0: {
            matdash::orig<&MenuLayer_FLAlert_ClickedH, matdash::Thiscall>(nullptr, self, btn2);
            break;
        }
        default:
            break;
        }

    }
};


LRESULT CALLBACK nWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_DESTROY:
    case WM_QUIT:
    case WM_CLOSE:

        if (!onPopupEnd) {
            onPopupEnd = true;
            ButtonsClass::onConfirmExitLevel(nullptr);
        }

        return 0;
    }

    return CallWindowProc((WNDPROC)oWindowProc, hwnd, msg, wparam, lparam);
}


bool MenuLayer_init_H(gd::MenuLayer* self) {

    if (!matdash::orig<&MenuLayer_init_H, matdash::Thiscall>(self)) return false;

    if (!newWindowProcSet) oWindowProc = SetWindowLongPtrA(FindWindowA(NULL, "Geometry Dash"), GWL_WNDPROC, (LONG_PTR)nWindowProc);
    newWindowProcSet = true;

    return true;
}

// Funci n que cambia el cursor a uno personalizado cuando est  dentro de la ventana
void SetCustomCursorInsideWindow(HWND hwnd) {
    // Reemplaza "ruta_al_archivo.ico" con la ruta completa de tu archivo de imagen
    // HCURSOR hCustomCursor = LoadCursorFromFileA("C:\\Users\\Joseph\\Downloads\\image-removebg-preview.ico");

   //  if (hCustomCursor == NULL) {
    //     // Maneja el error si la carga del cursor falla
        // Puedes mostrar un mensaje de error o usar un cursor predeterminado
   //      std::cout << "pipipi" << std::endl;
   //      hCustomCursor = LoadCursor(NULL, IDC_ARROW); // Cursor predeterminado
   //  }

    

  //   SetCursor(hCustomCursor);
}

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
{
    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);

    HWND* mainWindowHWND = (HWND*)lParam;
    DWORD targetProcessId = GetCurrentProcessId();

    if (processId == targetProcessId)
    {
        *mainWindowHWND = hwnd;
        return FALSE;  // Detener la enumeraci n
    }

    return TRUE;  // Continuar enumerando
}

HWND GetMainWindowHWND()
{
    HWND mainWindowHWND = NULL;

    EnumWindows(EnumWindowsCallback, (LPARAM)&mainWindowHWND);

    return mainWindowHWND;
}


DWORD WINAPI threadFunc(void* hModule) {


    sharedStateBP().LoadSettings();
    //matdash::create_console();
    //SetCustomCursorInsideWindow(GetMainWindowHWND());

    //// Load the custom cursor image
    //auto cursorImage = LoadCursorFromFileA("C:\\Users\\Joseph\\Downloads\\image-removebg-preview.ico");

    //SetClassLongPtrA(GetMainWindowHWND(), GCLP_HCURSOR, (LONG_PTR)cursorImage);


    //SetCursor(cursorImage);

    matdash::add_hook<&PauseLayerHook::createHook, matdash::Thiscall>(gd::base + 0x1E4570);
    matdash::add_hook<&PauseLayerHook::customSetupHook, matdash::Thiscall>(gd::base + 0x1E4620);
    matdash::add_hook<&PauseLayerHook::musicSliderChangedHook, matdash::Thiscall>(gd::base + 0x1E5CE0);
    matdash::add_hook<&PauseLayerHook::sfxSliderChangedHook, matdash::Thiscall>(gd::base + 0x1DDFA0);
    matdash::add_hook<&PauseLayerHook::createToggleButtonHook, matdash::Thiscall>(gd::base + 0x1E5570);

    matdash::add_hook<&CurrencyRewardLayer_init, matdash::Thiscall>(gd::base + 0x50130);
    matdash::add_hook<&MoreOptionsLayer_addToggle, matdash::Thiscall>(gd::base + 0x1DF6B0);
    matdash::add_hook<&MoreOptionsLayer_init, matdash::Thiscall>(gd::base + 0x1DE8F0);

    matdash::add_hook<&CustomSongWidgetHook::updateSongInfoHook, matdash::Thiscall>(gd::base + 0x69BF0);

    //matdash::add_hook<&ChallengeNodeHook::onClaimRewardA, matdash::Thiscall>(gd::base + 0x40380);
    matdash::add_hook<&AppDelegateHook::trySaveGameH, matdash::Thiscall>(gd::base + 0x3D5E0);

    //matdash::add_hook<&MenuLayer_init_H, matdash::Thiscall>(gd::base + 0x1907B0);
    //matdash::add_hook<&MenuLayer_FLAlert_ClickedH, matdash::Thiscall>(gd::base + 0x192150);


    //matdash::add_hook<&getDownloadProgress, matdash::Thiscall>(gd::base + 0x82d0);
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


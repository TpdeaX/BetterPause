#ifndef __TEXTALERTPOPUP_H__
#define __TEXTALERTPOPUP_H__

#include <gd.h>

namespace gd {
    class TextAlertPopup : public cocos2d::CCNode {
    public:
        static TextAlertPopup* create(std::string str, float idk, float idk2) {
            auto ret = reinterpret_cast<TextAlertPopup * (__vectorcall*)(float, float, std::string)>(base + 0x1450b0)(idk, idk2, str);
            __asm add esp, 24;
            return ret;
        }
    };

}

#endif

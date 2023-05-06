#ifndef __MOREOPTIONSLAYER_H__
#define __MOREOPTIONSLAYER_H__

#include <gd.h>

namespace gd {
    class GDH_DLL MoreOptionsLayer : public FLAlertLayer {
        public:
            static MoreOptionsLayer* create() {
                return reinterpret_cast<MoreOptionsLayer*(__fastcall*)()>(
                    base + 0x1de850
                )();
            }

            bool init() {
                return reinterpret_cast<bool*(__fastcall*)()>(
                    base + 0x1DE8F0
                    )();
            }

            void addToggle(const char* name, const char* key, const char* info) {
                reinterpret_cast<void*(__thiscall*)(MoreOptionsLayer*, const char*, const char*, const char*)>(base + 0x1DF6B0)(this, name, key, info);
            }

            void onKeybindings(cocos2d::CCObject* sender) {
                reinterpret_cast<void*(__thiscall*)(MoreOptionsLayer*, cocos2d::CCObject*)>(base + 0x749d0)(this, sender);
            }

            cocos2d::CCNode* m_unknode;
            cocos2d::CCNode* m_unknode1;
            int pag;//pag actual
            int m_unkInt1;//siempre 41
            int m_unkInt2;//siempre 5
            cocos2d::CCDictionary* m_unkDict6;
            cocos2d::CCDictionary* m_unkDict7;
            gd::CCMenuItemSpriteExtra* m_leftArrowA;
            gd::CCMenuItemSpriteExtra* m_rightArrowA;
            gd::CCTextInputNode* m_inputOffset;
    };
}

#endif
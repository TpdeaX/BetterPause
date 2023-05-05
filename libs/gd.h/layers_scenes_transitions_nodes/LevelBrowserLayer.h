#ifndef __LEVELBROWSERLAYER_H__
#define __LEVELBROWSERLAYER_H__

#include <gd.h>

namespace gd {

    class GJSearchObject;

    class LevelBrowserLayer : public cocos2d::CCLayer {
    public:
        int unk0;
        TextArea* noInternet;
        GJListLayer* listLayer;
        CCMenuItemSpriteExtra* nextBtn;
        CCMenuItemSpriteExtra* prevBtn;
        CCMenuItemSpriteExtra* lastBtn;
        CCMenuItemSpriteExtra* cancelSearchBtn;
        void* unk4;
        cocos2d::CCArray* arrayA;
        GJSearchObject* searchObject;
        cocos2d::CCLabelBMFont* countText;
        cocos2d::CCLabelBMFont* pageText;
        CCMenuItemSpriteExtra* pageBtn;
        cocos2d::CCLabelBMFont* folderText;
        CCMenuItemSpriteExtra* folderBtn;
        int total;
        int from;
        int to;


        static cocos2d::CCScene* scene(gd::GJSearchObject* searchObject) {
            return reinterpret_cast<cocos2d::CCScene * (__fastcall*)(gd::GJSearchObject*)>(
                gd::base + 0x159F60
                )(searchObject);
        }

        void loadPage(gd::GJSearchObject* searchObj) {
            reinterpret_cast<void(__thiscall*)(LevelBrowserLayer*, gd::GJSearchObject*)>(base + 0x15B160)(this, searchObj);
        }

        void setupLevelBrowser(cocos2d::CCArray* levels) {
            reinterpret_cast<void(__thiscall*)(LevelBrowserLayer*, cocos2d::CCArray*)>(base + 0x15bb40)(this, levels);
        }

        static LevelBrowserLayer* create(GJSearchObject* search) {
            return reinterpret_cast<LevelBrowserLayer*(__fastcall*)(gd::GJSearchObject*)>(
                gd::base + 0x159fa0
                )(search);
        }


        static cocos2d::CCScene* sceneWithLayer(gd::LevelBrowserLayer* layer) {
            auto scene = cocos2d::CCScene::create();
            scene->addChild(layer);
            return scene;
        }

    };

    class LevelSearchLayer : public cocos2d::CCLayer, public TextInputDelegate, public FLAlertLayerProtocol, public gd::DemonFilterDelegate {
    public:
        int a;
        CCTextInputNode* m_searchInput;
        cocos2d::CCSprite* m_sprite;
        CCTextInputNode* unk0; //what
        cocos2d::CCSprite* m_starSprite;
        cocos2d::CCDictionary* unk1;
        cocos2d::CCSprite* m_sprite1;
        CCMenuItemSpriteExtra* m_itemExtra1;
    };

    class SearchButton : public cocos2d::CCSprite {
    public:
        cocos2d::CCLabelBMFont* m_pLabel;
        cocos2d::CCSprite* m_pSprite;
        float node;
        static SearchButton* create(char const* background, char const* text, float width, char const* icon) {
            __asm movss xmm2, width

            auto ret = reinterpret_cast<SearchButton * (__fastcall*)(char const*, char const*, char const*)>(
                gd::base + 0x182120
                )(background, text, icon);

            __asm add esp, 0x4
            return ret;
        }
    };

    class MoreSearchLayer : public FLAlertLayer {
    public:
        static MoreSearchLayer* create() {
            return reinterpret_cast<MoreSearchLayer * (__fastcall*)()>(
                gd::base + 0x182520
                )();
        }
    };

}

#endif

#ifndef __ENDLEVELLAYER_H__
#define __ENDLEVELLAYER_H__

#include <gd.h>

namespace gd {
    class FLAlertLayer;
    class FLAlertLayerProtocol;
    class TextInputDelegate;
    class GJDropDownLayerDelegate;
    class LevelSettingsObject;
    class CCTextInputNode;
    class LevelSettingsLayer;
    class TextArea;

    class GDH_DLL EndLevelLayer : public FLAlertLayer, FLAlertLayerProtocol, TextInputDelegate, GJDropDownLayerDelegate {
    public:
        cocos2d::CCSprite* unk2;
        cocos2d::CCSprite* unk3;
        cocos2d::CCSprite* unk4;
        cocos2d::CCLabelBMFont* m_attemptLabel;
        cocos2d::CCLabelBMFont* m_jumpLabel;
        cocos2d::CCLabelBMFont* m_timeLabel;
    };
}

#endif
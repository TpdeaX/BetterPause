#ifndef __GJEFFECTMANAGER_H__
#define __GJEFFECTMANAGER_H__

#include <gd.h>

namespace gd {

    class GJBaseGameLayer;
    class ColorAction;
    class TriggerEffectDelegate;
    class ColorActionSprite;
  
    class GDH_DLL GJEffectManager : public cocos2d::CCNode {
    public:

        TriggerEffectDelegate* m_effectDelegate;
        cocos2d::CCDictionary* m_colorActions;
        cocos2d::CCDictionary* m_colorSprites;
        cocos2d::CCDictionary* m_pulseActionsForGroup;
        cocos2d::CCDictionary* m_colorCache;
        cocos2d::CCDictionary* m_opacityActionsForGroup;
        cocos2d::CCDictionary* m_f0150;
        cocos2d::CCArray* m_opacityActions;
        cocos2d::CCArray* m_touchActions;
        cocos2d::CCDictionary* m_countActions;
        cocos2d::CCArray* m_onDeathActions;
        cocos2d::CCArray* m_collisionActions;
        cocos2d::CCDictionary* m_f0180;
        cocos2d::CCDictionary* m_f0188;
        std::vector<void*> m_inheritanceNodesForColor;
        cocos2d::CCDictionary* m_f01a8;
        cocos2d::CCDictionary* m_collisionActionsForGroup1;
        cocos2d::CCDictionary* m_collisionActionsForGroup2;
        std::vector<ColorAction*> m_colorActionsForColor;
        std::vector<ColorActionSprite*> m_colorSpritesForColor;
        PAD(1100);
        bool m_f063c;
        PAD(2200);
        int m_unusued;
        int* m_unused2;
        cocos2d::CCArray* m_f1bc8;
        cocos2d::CCArray* m_inheritanceChain;
        cocos2d::CCDictionary* m_f1bd8;
        std::vector<bool> m_groupToggled;
        cocos2d::CCDictionary* m_triggeredIDs;
        cocos2d::CCDictionary* m_followActions;
        cocos2d::CCArray* m_spawnActions;
        cocos2d::CCArray* m_moveActions;
        cocos2d::CCArray* m_f1c28;
        cocos2d::CCNode* m_f1c30;
        cocos2d::CCDictionary* m_f1c38;
        cocos2d::CCDictionary* m_f1c40;
        cocos2d::CCDictionary* m_f1c48;
        cocos2d::CCDictionary* m_f1c50;
        float m_time;
        float m_velocity;
        float m_acceleration;
        bool m_moveOptimizationEnabled;
    };
}

#endif
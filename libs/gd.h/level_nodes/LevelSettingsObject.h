#ifndef __LEVELSETTINGSOBJECT_H__
#define __LEVELSETTINGSOBJECT_H__

#include <gd.h>

namespace gd {
    class GJEffectManager;
    class GJGameLevel;
    class GameObject;

    enum Gamemode {
        kGamemodeCube = 0,
        kGamemodeShip = 1,
        kGamemodeBall = 2,
        kGamemodeUfo = 3,
        kGamemodeWave = 4,
        kGamemodeRobot = 5,
        kGamemodeSpider = 6,
    };

    enum Speed {
        kSpeedNormal = 0,
        kSpeedSlow = 1,
        kSpeedFast = 2,
        kSpeedFaster = 3,
        kSpeedFastest = 4,
    };

    class GDH_DLL LevelSettingsObject : public cocos2d::CCNode {
        public:
            GJEffectManager* m_effectManager;
            Gamemode m_startGamemode; // 0xF0
            Speed m_startSpeed; // 0xF4
            bool m_startMini; // 0xF8
            bool m_startDual; // 0xF9
            bool m_twoPlayerMode; // 0xFA
            float m_songStartOffset; // 0xFC
            bool m_fadeIn; // 0x100
            bool m_fadeOut; // 0x101
            int m_selectedBackground; // 0x104 i need a bette rname for these
            int m_selectedGround;
            int m_selectedFont;
            bool m_startsWithStartPos;
            bool m_startInvert;
            PAD(2);
            GJGameLevel* m_level; // 0x114
            std::string m_guidelineString;
            int m_unknown;
            int m_colorPage;
            int m_groundLineIndex;

            std::string getSaveString() {
                std::string res;

                reinterpret_cast<void(__thiscall*)(LevelSettingsObject*, std::string*)>(
                    base + 0x16ebf0
                )(this, &res);

                return res;
            }

            virtual ~LevelSettingsObject(){
                reinterpret_cast<LevelSettingsObject*(__thiscall*)()>(
                    base + 0x16e940
                    )();
            }
            virtual bool init() {
               return reinterpret_cast<bool(__thiscall*)(LevelSettingsObject*)>(
                    base + 0x16e940
                    )(this);

            }
            static LevelSettingsObject* create(){
                return reinterpret_cast<LevelSettingsObject* (__thiscall*)()>(
                    base + 0x16e8a0
                    )();
            }
            static LevelSettingsObject* objectFromDict(cocos2d::CCDictionary* dic) {
                return reinterpret_cast<LevelSettingsObject*(__thiscall*)(cocos2d::CCDictionary*)>(
                    base + 0x16f4d0
                    )(dic);
            }
            static LevelSettingsObject* objectFromString(std::string str) {
                return reinterpret_cast<LevelSettingsObject*(__thiscall*)(std::string)>(
                    base + 0x16f440
                    )(str);
            }
            void setupColorsFromLegacyMode(cocos2d::CCDictionary* dic) {
                reinterpret_cast<void(__thiscall*)(cocos2d::CCDictionary*)>(
                    base + 0x170050
                    )(dic);
            }
    };
}

#endif

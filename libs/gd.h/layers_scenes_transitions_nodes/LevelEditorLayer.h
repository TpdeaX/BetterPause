#ifndef __LEVELEDITORLAYER_H__
#define __LEVELEDITORLAYER_H__

#include <gd.h>

namespace gd {

    class GJBaseGameLayer;
    class EditorUI;
    class GameObject;
    class GJGroundLayer;
    class DrawGridLayer;
    class StartPosObject;


    enum PlaybackMode {
        kPlaybackModeNot        = 0,
        kPlaybackModePlaying    = 1,
        kPlaybackModePaused     = 2,
    };

    class GDH_DLL LevelEditorLayer : public GJBaseGameLayer {
    public:
        bool m_ignoreDamage;
        bool m_followPlayer;
        bool m_drawTriggerBoxes;
        bool m_debugDraw;
        bool m_gridEnabled;
        bool m_hideGridOnPlay;
        bool m_effectLines;
        bool m_showGround;
        bool m_durationLines;
        bool m_moreUndo;
        bool m_hideBackground;
        bool m_smoothFixInEditor; // not entirely sure. used in onPlaytest
        bool m_highDetail;
        cocos2d::CCArray* m_touchTriggeredGroups;
        cocos2d::CCArray* m_triggeredGroups;
        cocos2d::CCDictionary* m_stickyGroups;
        int m_stickyGroupID;
        cocos2d::CCArray* m_unkObjectArr;
        cocos2d::CCArray* m_pulseTriggers;
        cocos2d::CCArray* m_colourObjects;
        cocos2d::CCArray* m_alphaTriggers;
        cocos2d::CCArray* m_spawnTriggers;
        cocos2d::CCArray* m_moveTriggers;
        cocos2d::CCDictionary* m_unkDict5;
        cocos2d::CCArray* m_enabledGroups;
        GameObject* m_copyStateObject;
        cocos2d::CCDictionary* m_unkDict6;
        cocos2d::CCArray* m_unkArray12;
        bool field_14;
        bool field_31D;
        int m_coinCountRand1;
        int m_coinCountRand2;
        int m_coinCount;
        bool m_moveTrigger;
        bool m_colorTrigger;
        bool m_pulseTrigger;
        bool m_alphaTrigger;
        bool m_spawnTrigger;
        cocos2d::CCArray* m_toggleTriggersMaybe;
        bool m_unkArr2Obj;
        cocos2d::CCArray* m_delayedSpawnArray2;
        bool m_delaySpawnNode;
        cocos2d::CCDictionary* m_unkDict3;
        cocos2d::CCDictionary* m_unkDict4;
        bool m_editorInitialising;
        bool field_34D;
        float m_timeMod;
        int m_currentLayer;
        StartPosObject* m_currentStartPos;
        float m_prevObjLayerScale;
        OBB2D* m_OBB2D;
        cocos2d::CCSprite* m_crossSprite;
        cocos2d::CCPoint m_unkPoint2;
        float m_unkFloat1;
        bool m_isDualMode;
        bool m_unkRectBool;
        GameObject* m_currentPortal;
        GameObject* m_portal;
        EditorUI* m_editorUI;
        cocos2d::CCSprite* m_backgroundLayer;
        cocos2d::CCArray* m_undoObjects;
        cocos2d::CCArray* m_redoObjects;
        cocos2d::CCPoint m_unkPoint1;
        int m_objectCountRand1;
        int m_objectCountRand2;
        int m_objectCount;
        DrawGridLayer* m_drawGridLayer;
        GJGameLevel* m_level;
        int m_playbackMode;
        cocos2d::CCPoint m_groundTopMaybe;
        float m_time;
        cocos2d::CCDictionary* m_enabledGroupsDict;
        bool m_3d;
        bool m_previewMode;
        GJGroundLayer* m_groundLayer;
        std::string m_rawLevelString;
        void* m_triggerHitbox;
        std::vector<GameObject*> m_objectVector;
        std::vector<GameObject*> m_groupVector;
        std::vector<cocos2d::CCArray*> m_nestedObjects;
        cocos2d::CCDictionary* m_triggerGroupsDict;
        std::vector<cocos2d::CCArray*> m_triggerGroupsVector;
        bool m_toggleGroupsMaybe;
        std::vector<bool> m_unkVector3; // everything set to false in playback mode
        std::vector<bool> m_disabledGroupVector;
        std::vector<bool> m_blendObjectsVector;
        std::vector<bool> m_blendColorVector;
        std::vector<uint8_t> m_toggledGroupsVector;
        std::vector<float> m_previewGroupsVector;
        double m_unkDouble1;
        cocos2d::CCArray* m_delayedSpawnArray1;
        bool m_removingObjects;

    public:
        static LevelEditorLayer* get() { return gd::GameManager::sharedState()->getEditorLayer(); }
        EditorUI* getEditorUI() { return this->m_editorUI; }

        static LevelEditorLayer* create(GJGameLevel* level) {
            return reinterpret_cast<LevelEditorLayer*(__fastcall*)(GJGameLevel*)>(
                base + 0x15ed60
            )(level);
        }

        static cocos2d::CCScene* scene(GJGameLevel* level) {
            auto scene = cocos2d::CCScene::create();

            scene->addChild(LevelEditorLayer::create(level));
            scene->setObjType(cocos2d::kCCObjectTypeLevelEditorLayer);

            cocos2d::CCDirector::sharedDirector()->replaceScene(
                cocos2d::CCTransitionFade::create(0.5f, scene)
            );
            return scene;
        }

        GameObject* createObject(int id, cocos2d::CCPoint const& position, bool undo) {
            return reinterpret_cast<GameObject*(__thiscall*)(
                LevelEditorLayer*, int, cocos2d::CCPoint, bool
            )>(
                base + 0x160d70
            )(
                this, id, position, undo
            );
            
        }

        void removeObject(GameObject * obj, bool idk) {
            reinterpret_cast<void(__thiscall*)(
                LevelEditorLayer *,GameObject *,bool
            )>(
                base + 0x161cb0
            )(
                this, obj, idk
            );
        }

        int getNextFreeGroupID(cocos2d::CCArray* objs) {
            return reinterpret_cast<int(__thiscall*)(
                LevelEditorLayer*, cocos2d::CCArray*
            )>(
                base + 0x164ae0
            )(
                this, objs
            );
        }

        GameObject* addObjectFromString(std::string const& str) {
            return reinterpret_cast<GameObject*(__thiscall*)(LevelEditorLayer*, std::string)>(base + 0x160c80)(this, str);
        }

        GameObject* objectAtPosition(cocos2d::CCPoint const& pos) {
            return reinterpret_cast<GameObject*(__thiscall*)(
                LevelEditorLayer*, cocos2d::CCPoint
            )>(base + 0x161300)(this, pos);
        }

        cocos2d::CCRect getObjectRect(GameObject* obj, bool unk) {
            cocos2d::CCRect res;
            reinterpret_cast<cocos2d::CCRect*(__thiscall*)(
                LevelEditorLayer*, cocos2d::CCRect*, GameObject*, bool
            )>(base + 0x1616b0)(this, &res, obj, unk);
            return res;
        }

        // yes it's misspelled in GD aswell
        void pasteAtributeState(GameObject* obj, cocos2d::CCArray* objs) {
            reinterpret_cast<void(__thiscall*)(LevelEditorLayer*, GameObject*, cocos2d::CCArray*)>(
                base + 0x16b740
            )(this, obj, objs);
        }
        
        int getCurrentLayer() { return m_currentLayer; }
        void setCurrentLayer(int n) { m_currentLayer = n; }

        float getLastObjectX() {
            reinterpret_cast<void(__fastcall*)(LevelEditorLayer*)>(
                base + 0x167290
            )(this);

            float retVal;
            __asm { movss retVal, xmm0 }

            return retVal;
        }
    
        void updateOptions() {
            reinterpret_cast<void(__thiscall*)(LevelEditorLayer*)>(
                base + 0x15fcc0
            )(this);
        }

        void updateEditorMode() {
            reinterpret_cast<void(__thiscall*)(LevelEditorLayer*)>(
                base + 0x1652b0
            )(this);
        }
    
        void addSpecial(GameObject* obj) {
            reinterpret_cast<void(__thiscall*)(LevelEditorLayer*, GameObject*)>(
                base + 0x162650
            )(this, obj);
        }

        float timeForXPos(float f) {
            return reinterpret_cast<float(__thiscall*)(LevelEditorLayer*, float)>(
                base + 0x167210
                )(this, f);
        }


        bool checkCollisions(PlayerObject* player) {
            return reinterpret_cast<bool(__thiscall*)(LevelEditorLayer*, PlayerObject*)>(
                base + 0x167F10
                )(this, player);
        }

    };

}

#endif

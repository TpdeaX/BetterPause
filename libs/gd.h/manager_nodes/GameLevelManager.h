#ifndef __GAMELEVELMANAGER_H__
#define __GAMELEVELMANAGER_H__

#include <gd.h>

namespace gd {

    class GJGameLevel;
    class GJSearchObject;

    class GameLevelManager : public cocos2d::CCNode {
    public:
        // thanks to wylie for most of these!

        cocos2d::CCDictionary* m_mainLevels; // the values are GJGameLevel
        cocos2d::CCDictionary* m_searchFilters; // the level search filters
        cocos2d::CCDictionary* m_onlineLevels;
        PAD(4);
        cocos2d::CCDictionary* m_followedCreators; // key is the account id
        cocos2d::CCDictionary* m_downloadedLevels;
        // dear robtop, have you heard of a set
        // all of these just have the value of CCString("1")
        cocos2d::CCDictionary* m_likedLevels; // https://github.com/Wyliemaster/gddocs/blob/client/docs/resources/client/gamesave/GLM.md#glm_12
        cocos2d::CCDictionary* m_ratedLevels; // 32
        cocos2d::CCDictionary* m_pRatedDemons;
        cocos2d::CCDictionary* m_reportedLevels;
        // the names of the folders
        cocos2d::CCDictionary* m_onlineFolders;
        cocos2d::CCDictionary* m_localLevelsFolders;
        cocos2d::CCDictionary* m_dailyLevels;
        int m_dailyTimeLeft; // i cant figure out the unit
        int m_dailyID;
        int m_dailyID_; // 64
        PAD(4);
        int m_weeklyTimeLeft;
        int m_weeklyID;
        int m_weeklyID_; // ? (this was 2 lower than the other weekly id)
        cocos2d::CCDictionary* m_gauntletLevels;
        cocos2d::CCDictionary* unkDict13;
        PAD(4);
        cocos2d::CCDictionary* m_pTimerDict; // 108 / 344
        cocos2d::CCDictionary* m_knownUsers; // 348
        cocos2d::CCDictionary* m_accountIDtoUserIDDict; // 352
        cocos2d::CCDictionary* m_userIDtoAccountIDDict; // 356
        cocos2d::CCDictionary* storedLevels; // cached lvls?? (values are arrays) / 360
        cocos2d::CCDictionary* unkDict19; // more cache stuff (values are strings) / 364
        cocos2d::CCDictionary* unkDict20; // 368
        cocos2d::CCDictionary* unkDict21; // 372
        cocos2d::CCDictionary* unkDict22; // 376
        cocos2d::CCDictionary* unkDict23; // 380
        cocos2d::CCDictionary* unkDict24; // 384
        cocos2d::CCDictionary* storedUserInfo; // 388
        cocos2d::CCDictionary* unkDict26;
        cocos2d::CCDictionary* unkDict27;
        cocos2d::CCDictionary* unkDict28;
        std::string unkStr1;
        std::string unkStr2; // im not sure if this is actually is a std::string, although it looks like one
        int leaderboardState;
        bool m_bUnkEditLevelLayerOnBack;

        OnlineListDelegate* m_pOnlineListDelegate;
        LevelDownloadDelegate* m_pLevelDownloadDelegate;
        void* m_pLevelCommentDelegate;
        void* m_pCommentUploadDelegate;
        void* m_pLevelUploadDelegate;
        LevelUpdateDelegate* m_pLevelUpdateDelegate;
        void* m_pLeaderboardManagerDelegate;
        LevelDeleteDelegate* m_pLevelDeleteDelegate;
        void* m_pUserInfoDelegate;
        void* m_pLevelManagerDelegate;
        void* m_pUnkDelegate;
        void* m_pFriendRequestDelegate;
        void* m_pMessageListDelegate;
        void* m_pDownloadMessageDelegate;
        void* m_pUploadMessageDelegate;
        void* m_pGJRewardDelegate;
        void* m_pGJChallengeDelegate;
        void* m_pGJDailyLevelDelegate;
        void* m_pMusicDownloadDelegate;
        int m_nUnkDownload;
        int unk;

        std::string unkStr3;
        cocos2d::CCString* unkStr4;

        inline static GameLevelManager* sharedState() {
            return reinterpret_cast<GameLevelManager * (__stdcall*)()>(gd::base + 0x9f860)();
        }

        inline static gd::GJGameLevel* createNewLevel() {
            return reinterpret_cast<gd::GJGameLevel * (__stdcall*)()>(gd::base + 0xa0db0)();
        }

        void storeUserNames(std::string str) {
            reinterpret_cast<void(__thiscall*)(GameLevelManager*, std::string)>(
                gd::base + 0xA1840
                )(this, str);
            //__asm add esp, 0x18
        }

        void storeUserName(int userID, int accountID, std::string str) {
            reinterpret_cast<void(__thiscall*)(GameLevelManager*, int, int, std::string)>(
                gd::base + 0xA1A70
                )(this, userID, accountID, str);
            //__asm add esp, 0x18
        }

        void getGJUserInfo(int something) {
            reinterpret_cast<void(__thiscall*)(GameLevelManager*, int)>(base + 0xB00B0)(this, something);
        }

        void getOnlineLevels(GJSearchObject* searchObj) {
            reinterpret_cast<void(__thiscall*)(GameLevelManager*, GJSearchObject*)>(base + 0xA7BC0)(this, searchObj);
        }

        void getLevelLeaderboard(GJGameLevel* level, int leaderboardType) {
            reinterpret_cast<void(__thiscall*)(GameLevelManager*, GJGameLevel*, int)>(base + 0xAED70)(this, level, leaderboardType);
        }

        void updateUserScore() {
            reinterpret_cast<void(__thiscall*)(GameLevelManager*)>(base + 0xADA60)(this);
        }

        cocos2d::CCArray* getStoredOnlineLevels(const char* a) {
            return reinterpret_cast<cocos2d::CCArray * (__thiscall*)(GameLevelManager*, const char*)>(base + 0xA3A90)(this, a);
        }

        cocos2d::CCArray* createAndGetScores(std::string result, int scoreType) { //scoreType is actually GJScoreType //this doesnt work
            auto pRet = reinterpret_cast<cocos2d::CCArray * (__thiscall*)(GameLevelManager*, std::string, int)>(base + 0xA2780)(this, result, scoreType);
            //__asm add esp, 0x18
            return pRet;
        }

        cocos2d::CCDictionary* responseToDict(std::string result, bool useTilde) { //this doesnt work either
            auto pRet = reinterpret_cast<cocos2d::CCDictionary * (__thiscall*)(GameLevelManager*, std::string, bool)>(base + 0xBBA50)(this, result, useTilde);
            //__asm add esp, 0x18
            return pRet;
        }

        cocos2d::CCDictionary* getSavedLevels(bool favorite, int folderID) { //this doesnt work either
            auto pRet = reinterpret_cast<cocos2d::CCDictionary * (__thiscall*)(GameLevelManager*, bool, int)>(base + 0xA2960)(this, favorite, folderID);
            //__asm add esp, 0x18
            return pRet;
        }

        void resetStoredUserInfo(int id) { //inlined on windows i think
            storedUserInfo->removeObjectForKey(id);
        }

        void resetAccountComments(int id) {
            int i = 0;
            while (true) {
                auto key = this->getAccountCommentKey(id, i++);
                auto levels = getStoredOnlineLevels(key);
                if (levels != nullptr) {
                    storedLevels->removeObjectForKey(key);
                }
                else {
                    break;
                }
            }
        }

        void resetCommentTimersForLevelID(int id, bool commentHistory) {
            reinterpret_cast<void(__thiscall*)(GameLevelManager*, int, bool)>(base + 0xB3F10)(this, id, commentHistory);
        }

        const char* getAccountCommentKey(int a2, int a3) {
            return cocos2d::CCString::createWithFormat("a_%i_%i", a2, a3)->getCString();
        }

        bool hasLikedItemFullCheck(LikeItemType type, int id, int special) {
            auto pRet = reinterpret_cast<cocos2d::CCDictionary * (__thiscall*)(GameLevelManager*, LikeItemType, int, int)>(base + 0xB86B0)(this, type, id, special);
            return pRet;
        }


    };

}

#endif

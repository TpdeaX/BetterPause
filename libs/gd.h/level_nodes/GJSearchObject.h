#ifndef __GJSEARCHOBJECT_H__
#define __GJSEARCHOBJECT_H__

#include <gd.h>

namespace gd {

    enum SearchType {
        kSearchTypeSearch = 0,
        kSearchTypeMostDownloaded = 1,
        kSearchTypeMostLiked = 2,
        kSearchTypeTrending = 3,
        kSearchTypeRecent = 4,
        kSearchTypeUsersLevels = 5,
        kSearchTypeFeatured = 6,
        kSearchTypeMagic = 7,
        kSearchTypeMapPacks = 9,
        kSearchTypeAwarded = 11,
        kSearchTypeFollowed = 12,
        kSearchTypeFriends = 13,
        kSearchTypeFindUsers = 14,
        kGJSearchTypeLikedGDW = 15,
        kSearchTypeHallOfFame = 16,
        kGJSearchTypeFeaturedGDW = 17,
        kSearchTypeSimilar = 18,
        kSearchType19 = 19,
        kSearchTypeMyLevels = 98,
        kSearchTypeSavedLevels = 99,
        kSearchTypeFavorite = 100,
        kSearchTypeDemonList = 1337,
    };

    class GJSearchObject : public cocos2d::CCNode {
    public:
        SearchType m_nScreenID;
        std::string m_sSearchQuery;
        std::string m_sDifficulty;
        std::string m_sLength;
        int m_nPage;
        bool m_bStarFilter;
        bool m_bNoStarFilter;
        int m_nTotal;
        bool m_bUncompletedFilter;
        bool m_bCompletedFilter;
        bool m_bFeaturedFilter;
        bool m_bOriginalFilter;
        bool m_bTwoPlayerFilter;
        bool m_bCoinsFilter;
        bool m_bEpicFilter;
        int m_eDemonFilter;
        int currentFolder; // might be unsigned, but then again its robtop
        int m_nSongID;
        bool m_bCustomSongFilter;
        bool m_bSongFilter;

        static GJSearchObject* create(SearchType nID) {
            return reinterpret_cast<GJSearchObject * (__fastcall*)(SearchType)>(
                gd::base + 0xc2b90
                )(nID);
        }

        static GJSearchObject* create(SearchType nID, std::string str) {
            auto pRet = reinterpret_cast<GJSearchObject * (__fastcall*)(SearchType, std::string)>(
                gd::base + 0xC2C80
                )(nID, str);
            __asm add esp, 0x18
            return pRet;
        }

        //this isnt a robtop function
        void setSongInfo(bool customSong, int songID) {
            m_bCustomSongFilter = customSong;
            m_nSongID = songID;
            m_bSongFilter = true;
        }

        /*static GJSearchObject* create(SearchType nID, std::string str, std::string diff,std::string len, int page, bool star, bool uncompleted, bool featured, int songID, bool original, bool twoPlayer, bool customSong, bool songFilter, bool noStar, bool coins, bool epic, bool completed, int demonDiff, int folderNum) {
            auto pRet = reinterpret_cast<GJSearchObject*(__fastcall*)(SearchType, std::string, std::string,std::string,int,bool,bool,bool,int,bool,bool,bool,bool,bool,bool,bool,bool,int,int)>(
                gd::base + 0xC2D80
            )(nID, str, diff, len, page, star, uncompleted, featured, songID, original, twoPlayer, customSong, songFilter, noStar, coins, epic, completed, demonDiff, folderNum);
            __asm add esp, 0x48
            return pRet;
        }*/

        SearchType getType() {
            return this->m_nScreenID;
        }
    };

}

#endif

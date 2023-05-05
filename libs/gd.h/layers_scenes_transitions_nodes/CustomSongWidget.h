#ifndef __CUSTOMSONGWIDGET_H__
#define __CUSTOMSONGWIDGET_H__

#include <gd.h>

namespace gd {
    class FLAlertLayer;
    class FLAlertLayerProtocol;
    class SongInfoObject;

    class GDH_DLL CustomSongWidget : public cocos2d::CCNode, MusicDownloadDelegate, public FLAlertLayerProtocol {
    public:
        SongInfoObject* m_songInfo;//0xf4
        cocos2d::CCMenu* m_pMenuButtons;
        cocos2d::CCLabelBMFont* m_pSongNameLabel;
        cocos2d::CCLabelBMFont* m_pArtistNameLabel;
        cocos2d::CCLabelBMFont* m_pInfoLabel;
        cocos2d::CCLabelBMFont* m_pMessageLabel;
        CCMenuItemSpriteExtra* m_pDownloadBtn;
        CCMenuItemSpriteExtra* m_pCancelDownloadBtn;
        CCMenuItemSpriteExtra* m_pUseMusicBtn;
        CCMenuItemSpriteExtra* m_pRefreshMusicBtn;
        CCMenuItemSpriteExtra* m_pPlayMusicBtn;
        CCMenuItemSpriteExtra* m_pMoreInfoSongBtn;
        cocos2d::CCSprite* m_pSliderGrooveDownload;
        cocos2d::CCSprite* m_pSliderBarDownload;
        LevelSettingsObject* m_pLevelSettingsObject;
        bool m_pIDK;//DERREPENTE PARA DECIR QUE ESTA EN OTRO LABEL
        int m_pIsLocalSong;
        PAD(0x17);

        void updateSongObject(SongInfoObject* song) {
            reinterpret_cast<void(__thiscall*)(CustomSongWidget*, SongInfoObject*)>(base + 0x69280)(this, song);
        }

        virtual void FLAlert_Clicked(FLAlertLayer*, bool) {}
        // too lazy to type out all of them
        virtual void loadSongInfoFinished(SongInfoObject*) {}

        inline virtual ~CustomSongWidget() {
            std::cout << "epico" << std::endl;
        }

        void onStartDownload(cocos2d::CCObject* pSender) {
            reinterpret_cast<void(__thiscall*)(CustomSongWidget*, cocos2d::CCObject*)>(base + 0x69540)(this, pSender);
        }
    };
}

#endif


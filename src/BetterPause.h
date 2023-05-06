#pragma once

#include "pch.h"
#include "Utils.h"
#include "gdstring.h"

class BarBetterShow : public cocos2d::CCNode {
public:

	cocos2d::CCSprite* m_pBarBase = nullptr;
	cocos2d::CCSprite* m_pBarMain = nullptr;
	float m_pBarMainW = 0.f;
	cocos2d::CCSprite* m_pBarBG = nullptr;
	cocos2d::CCLabelBMFont* m_pPercentageCurrent = nullptr;
	cocos2d::CCLabelBMFont* m_pPercentageBest = nullptr;
	cocos2d::CCLabelBMFont* m_pPercentageMax = nullptr;

	static BarBetterShow* create(cocos2d::ccColor3B color, bool enabledSecondBar, bool showCurrentPer, float perCurrent, float bestCurrent);
	bool init(cocos2d::ccColor3B color, bool enabledSecondBar, bool showCurrentPer, float perCurrent, float bestCurrent);
	void updateBar(cocos2d::CCSprite* m_pBar, float per);
};

class BetterPause : public cocos2d::CCLayer {
public:
	static bool isNotRegister;
	cocos2d::CCMenu* m_pMenuButtons = nullptr;
	cocos2d::CCMenu* m_pMenuButtons2 = nullptr;
	gd::PauseLayer* pauseLayer = nullptr;
	gd::CCMenuItemSpriteExtra* m_pVisibleButton = nullptr;
	bool m_pIsHide = false;
	gd::Slider* m_pSliderMusic = nullptr;
	gd::Slider* m_pSliderSFX = nullptr;
	gd::ChallengesPage* m_pQuestMenu = nullptr;
	cocos2d::CCLabelBMFont* m_pLabelMusicVPercentage = nullptr;
	cocos2d::CCLabelBMFont* m_pLabelSFXVPercentage = nullptr;
	cocos2d::CCLabelBMFont* m_pNameLevelLabel = nullptr;
	cocos2d::CCLabelBMFont* m_pTypeLevelLabel = nullptr;
	cocos2d::CCLabelBMFont* m_pStatusLevelLabel = nullptr;
	gd::TextArea* m_pAttemptCurrentLevelLabel = nullptr;
	gd::TextArea* m_pTimeCurrentLevelLabel = nullptr;
	BarBetterShow* m_pNormalBarPerB = nullptr;
	BarBetterShow* m_pPracticeBarPerB = nullptr;
	cocos2d::CCMenu* m_pMenuButtonsConfig = nullptr;
	cocos2d::CCLabelBMFont* m_pQuickSettingsLabel = nullptr;
	cocos2d::CCLabelBMFont* m_pVolumenSettingsLabel = nullptr;
	cocos2d::CCLabelBMFont* m_pVolumenMusicSettingsLabel = nullptr;
	cocos2d::CCLabelBMFont* m_pVolumenSFXSettingsLabel = nullptr;
	cocos2d::CCLabelBMFont* m_pQuestsLabel = nullptr;
	//cocos2d::CCMenu* m_MenuSliders = nullptr;//why?????!!!
	cocos2d::CCMenu* m_pMenuButtonsVolSet = nullptr;

	static BetterPause* create(gd::PauseLayer* pauseLayer, bool isEditor);
	bool init(gd::PauseLayer* pauseLayer, bool isEditor);
	void createToggleButton(cocos2d::SEL_MenuHandler callback, bool on,
		cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos);
	void onOptionsLayer(cocos2d::CCObject* pSender);
	void onHide(cocos2d::CCObject* pSender);
	void musicSliderChanged(cocos2d::CCObject* pSender);
	void sfxSliderChanged(cocos2d::CCObject* pSender);
	void onAutoRetryA(cocos2d::CCObject* pSender);
	void onAutoCheckpointsA(cocos2d::CCObject* pSender);
	void onProgressBarA(cocos2d::CCObject* pSender);
	void onProgressBarPercentageA(cocos2d::CCObject* pSender);
	void onDisableShakeEffects(cocos2d::CCObject* pSender);
	void onShowCursorInGame(cocos2d::CCObject* pSender);
	void updatePercentageObjects();
	void onSetValueMusic(cocos2d::CCObject* pSender);
	void onSetValueSFX(cocos2d::CCObject* pSender);
};


class SetVolumenPopup : public gd::FLAlertLayer, public cocos2d::CCTextFieldDelegate, public gd::FLAlertLayerProtocol, public gd::TextInputDelegate
{
public:

	cocos2d::CCMenu* m_pButtonsMenu = nullptr;
	gd::CCMenuItemSpriteExtra* m_pSetValueBtn = nullptr;
	cocos2d::extension::CCScale9Sprite* m_pBGInputTextValue = nullptr;
	gd::CCTextInputNode* m_pInputTextValue = nullptr;
	gd::Slider* m_pSliderRef = nullptr;
	BetterPause* m_pBetterPauseRef = nullptr;

	static SetVolumenPopup* create(gd::Slider* ref);
	virtual void keyBackClicked();
	virtual bool init(gd::Slider* ref);
	void keyDown(cocos2d::enumKeyCodes key);
	void onSet(cocos2d::CCObject* pSender);
};


static void NoNodeI_registerWithTouchDispatcher(cocos2d::CCNode* self) {
	matdash::add_hook<&NoNodeI_registerWithTouchDispatcher>(self);
}
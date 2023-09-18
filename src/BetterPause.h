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
	static cocos2d::CCMenu* pauseLayer_MenuToggles;
	static cocos2d::CCPoint pauseLayer_lastPoint;
	static std::vector<std::string> quickSettings_Name;
	static std::vector<std::string> quickSettings_Desc;
	static std::vector<std::string> quickSettings_Key;
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
	gd::CCMenuItemSpriteExtra* m_pBtnMusicVPercentage = nullptr;
	gd::CCMenuItemSpriteExtra* m_pBtnSFXVPercentage = nullptr;
	gd::TextArea* m_pDownloadMusicLabel = nullptr;
	bool m_pIsTextureEye = true;
	gd::CustomSongWidget* m_pCustomSongWidget = nullptr;
	gd::CCMenuItemSpriteExtra* m_pButtonQuestAlt = nullptr;

	static BetterPause* create(gd::PauseLayer* pauseLayer, bool isEditor, bool notBetter);
	bool init(gd::PauseLayer* pauseLayer, bool isEditor, bool notBetter);
	void createToggleButton(cocos2d::SEL_MenuHandler callback, bool on,
		cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos, float size,
		bool twoColumns);
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
	void onOpenChallenges(cocos2d::CCObject* pSender);
	void onInfoLevelOpen(cocos2d::CCObject* pSender);
	void createToggleButtonWithGameVariable(const char* key, cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos, float size, bool twoColumns);
	void onToggleWithGameVariable(cocos2d::CCObject* pSender);
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

class MoreOptionsPauseLayer : public gd::FLAlertLayer, public cocos2d::CCTextFieldDelegate, public gd::FLAlertLayerProtocol
{
public:
	static MoreOptionsPauseLayer* create();
	virtual void keyBackClicked();
	virtual bool init();
	void onClose(CCObject* pSender);
	void onOptionsGame(CCObject* pSender);
	void onOptionsPause(CCObject* pSender);
	void keyDown(cocos2d::enumKeyCodes key);

	cocos2d::extension::CCScale9Sprite* m_pBG = nullptr;
	cocos2d::extension::CCScale9Sprite* m_pBGOptions = nullptr;
	cocos2d::CCSprite* m_pUnderLine = nullptr;
	cocos2d::CCLabelBMFont* m_pTitleLayer = nullptr;
	cocos2d::CCMenu* m_menuButtons = nullptr;

};

struct ListData {
	const char* m_sTitle;
	std::vector<std::string> m_vEntries;
	unsigned int m_uMaxLength;
	unsigned int m_uLength;
	unsigned int m_uOffset;
	unsigned int m_uIndex;

	ListData(const char* title, unsigned int length);
	ListData() { /*doesn't matter since only used in default ctor of LoaderManager*/ };
};


class PauseSettingsLayer : public gd::GJDropDownLayer
{
public:
	friend class HorizontalList;

	HorizontalList* m_pSwitchPause = nullptr;
	HorizontalList* m_pSwitchQuest = nullptr;
	HorizontalList* m_pSwitchButtonsPos = nullptr;
	cocos2d::CCMenu* m_menuButtons = nullptr;

	static PauseSettingsLayer* create();
	virtual void customSetup();
	virtual void exitLayer(cocos2d::CCObject*);
	void onSelectQuickSettings(cocos2d::CCObject*);
};

enum {
	kListUpBtn,
	kListDownBtn,
	kVerticalListSwapUpBtn,
	kVerticalListSwapDownBtn,
	kVerticalListMoveBtn,
	kVerticalListBackground
};

class HorizontalList : public cocos2d::CCNode {
protected:
	ListData& m_pData;
	cocos2d::CCLabelBMFont** m_pLabels = nullptr;
	cocos2d::CCMenu* m_pMenu = nullptr;

protected:
	HorizontalList(ListData& data) : m_pData{ data } {}
	virtual ~HorizontalList() { delete[] m_pLabels; }

	virtual bool init();

	inline void getLength() {
		m_pData.m_uLength = m_pData.m_vEntries.size() -
			m_pData.m_uOffset < m_pData.m_uMaxLength ?
			(m_pData.m_vEntries.size() - m_pData.m_uOffset)
			: m_pData.m_uMaxLength;
	}
	virtual void navigate(cocos2d::CCObject* btn);

public:
	static HorizontalList* create(ListData& data);

	virtual void updateList();
	virtual void setPosition(float x, float y);
};

class SelectQuickSettings : public gd::FLAlertLayer, public cocos2d::CCTextFieldDelegate, public gd::FLAlertLayerProtocol
{
public:
	static SelectQuickSettings* create();
	virtual void keyBackClicked();
	virtual bool init();
	void onClose(CCObject* pSender);
	void keyDown(cocos2d::enumKeyCodes key);
	void onToggleWithGameVariable(CCObject* pSender);

	cocos2d::extension::CCScale9Sprite* m_pBG = nullptr;
	cocos2d::CCSprite* m_pUnderLine = nullptr;
	cocos2d::CCLabelBMFont* m_pTitleLayer = nullptr;
	std::vector<gd::CCMenuItemToggler*> m_toggles;

};


class GenericListCell : public gd::TableViewCell {
protected:
	GenericListCell(const char* name, cocos2d::CCSize size);
	void draw() override;

public:
	static GenericListCell* create(const char* key, cocos2d::CCSize size);
	void updateBGColor(int index);
};

class ListView : public gd::CustomListView {
protected:
	void setupList() override;
	gd::TableViewCell* getListCell(const char* key) override;
	void loadCell(gd::TableViewCell* cell, unsigned int index) override;
	static cocos2d::CCRect calculateNodeCoverage(cocos2d::CCArray* nodes);

public:
	static ListView* create(
		cocos2d::CCArray* items,
		float itemHeight = 30.f,
		float width = 340.f,
		float height = 200.f
	);
};


static void NoNodeI_registerWithTouchDispatcher(cocos2d::CCNode* self) {
	matdash::add_hook<&NoNodeI_registerWithTouchDispatcher>(self);
}
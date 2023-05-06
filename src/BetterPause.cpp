#include "pch.h"
#include "BetterPause.h"

bool BetterPause::isNotRegister = false;

BetterPause* BetterPause::create(gd::PauseLayer* pauseLayer, bool isEditor) {
	auto ret = new BetterPause();

	if (ret && ret->init(pauseLayer, isEditor)) {
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool BetterPause::init(gd::PauseLayer* pauseLayer, bool isEditor) {

	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	this->pauseLayer = pauseLayer;

	m_pQuestMenu = gd::ChallengesPage::create();
	this->addChild(m_pQuestMenu);
	m_pQuestMenu->setScale(0.7f);
	m_pQuestMenu->setOpacity(0);
	m_pQuestMenu->setPosition({ (Utils::winSize().width / 2) - 150.f, -50.f });//140.f, -40.f
	m_pQuestMenu->setKeyboardEnabled(false);
	m_pQuestMenu->setKeypadEnabled(false);

	for (size_t i = 0; i < m_pQuestMenu->m_pLayer->getChildrenCount(); i++)
	{
		auto node = reinterpret_cast<cocos2d::CCNode*>(m_pQuestMenu->m_pLayer->getChildren()->objectAtIndex(i));
		if (std::string(Utils::getNameObj(node)) != "ChallengeNode" && !dynamic_cast<cocos2d::CCLabelBMFont*>(node) &&
			std::string(Utils::getNameObj(node)) != "LoadingCircle") {//jajaj
			node->setVisible(false);
		}
	}

	m_pMenuButtons = cocos2d::CCMenu::create();
	m_pMenuButtons->setPosition({ 40.f, Utils::winSize().height - 42.f });
	this->addChild(m_pMenuButtons);

	auto resumeButtonImage = cocos2d::CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
	resumeButtonImage->setScale(0.5f);
	auto resumeButton = gd::CCMenuItemSpriteExtra::create(resumeButtonImage, pauseLayer, (cocos2d::SEL_MenuHandler)&gd::PauseLayer::onResume);
	m_pMenuButtons->addChild(resumeButton);

	auto replayButtonImage = cocos2d::CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
	replayButtonImage->setScale(0.5f);
	auto replayButton = gd::CCMenuItemSpriteExtra::create(replayButtonImage, pauseLayer, (cocos2d::SEL_MenuHandler)&gd::PauseLayer::onRestart);
	m_pMenuButtons->addChild(replayButton);

	auto practiceButtonImage = cocos2d::CCSprite::createWithSpriteFrameName(Utils::getplayLayerA()->m_isPracticeMode ? "GJ_normalBtn_001.png" : "GJ_practiceBtn_001.png");
	practiceButtonImage->setScale(0.5f);
	auto practiceButton = gd::CCMenuItemSpriteExtra::create(practiceButtonImage, pauseLayer, (Utils::getplayLayerA()->m_isPracticeMode ?
		(cocos2d::SEL_MenuHandler)&gd::PauseLayer::onPracticeModeDisabled : (cocos2d::SEL_MenuHandler)&gd::PauseLayer::onPracticeModeEnabled));
	m_pMenuButtons->addChild(practiceButton);

	auto quitButtonImage = cocos2d::CCSprite::createWithSpriteFrameName("GJ_menuBtn_001.png");
	quitButtonImage->setScale(0.5f);
	auto quitButton = gd::CCMenuItemSpriteExtra::create(quitButtonImage, pauseLayer, (cocos2d::SEL_MenuHandler)&gd::PauseLayer::onQuit);
	m_pMenuButtons->addChild(quitButton);

	m_pMenuButtons->alignItemsVerticallyWithPadding(5.f);

	auto rest1 = resumeButton->getPositionY() - replayButton->getPositionY();
	auto rest2 = replayButton->getPositionY() - quitButton->getPositionY();
	auto rest3 = quitButton->getPositionY() - practiceButton->getPositionY();
	//auto rest1 = practiceButton->getPositionY() - replayButtonImage->getPositionY();

	resumeButton->setPositionY(0.f);
	replayButton->setPositionY(0.f - rest1);
	quitButton->setPositionY(replayButton->getPositionY() - rest2);
	practiceButton->setPositionY(quitButton->getPositionY() - rest3);

	if (Utils::getplayLayerA()->m_level->levelType == gd::kGJLevelTypeEditor ||
		amemory::read_bytes(gd::base + 0x1E4A32, 1)[0] == 0x90) {
		auto editButtonImage = cocos2d::CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
		editButtonImage->setScale(0.38f);
		auto editButton = gd::CCMenuItemSpriteExtra::create(editButtonImage, pauseLayer, (cocos2d::SEL_MenuHandler)&gd::PauseLayer::onEdit);
		m_pMenuButtons->addChild(editButton);

		m_pMenuButtons->alignItemsVerticallyWithPadding(5.f);

		auto rest1 = resumeButton->getPositionY() - replayButton->getPositionY();
		auto rest2 = replayButton->getPositionY() - quitButton->getPositionY();
		auto rest3 = quitButton->getPositionY() - practiceButton->getPositionY();
		auto rest4 = practiceButton->getPositionY() - editButton->getPositionY();

		resumeButton->setPositionY(0.f);
		replayButton->setPositionY(0.f - rest1);
		quitButton->setPositionY(replayButton->getPositionY() - rest2);
		practiceButton->setPositionY(quitButton->getPositionY() - rest3);
		editButton->setPositionY(practiceButton->getPositionY() - rest4);

	}

	m_pMenuButtons2 = cocos2d::CCMenu::create();
	m_pMenuButtons2->setPosition({ 40.f, 42.f });
	this->addChild(m_pMenuButtons2);

	auto visibleButtonImage = cocos2d::CCSprite::create("BE_eye-on-btn.png");
	visibleButtonImage->setScale(0.6f);
	this->m_pVisibleButton = gd::CCMenuItemSpriteExtra::create(visibleButtonImage, this, (cocos2d::SEL_MenuHandler)&BetterPause::onHide);
	m_pMenuButtons2->addChild(this->m_pVisibleButton, -5);

	auto settingsButtonImage = cocos2d::CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
	settingsButtonImage->setScale(0.6f);
	auto settingsButton = gd::CCMenuItemSpriteExtra::create(settingsButtonImage, this, (cocos2d::SEL_MenuHandler)&BetterPause::onOptionsLayer);
	m_pMenuButtons2->addChild(settingsButton);

	auto firstButtonRect = m_pVisibleButton->boundingBox();
	settingsButton->setPositionY(firstButtonRect.getMaxY() + 22.f);

	m_pSliderMusic = gd::Slider::create(this, (cocos2d::SEL_MenuHandler)&BetterPause::musicSliderChanged, 1.f);
	m_pSliderMusic->setValue(Utils::shareFMOD()->getMusicVolume());
	m_pSliderMusic->updateBar();
	m_pSliderMusic->setScale(0.8f);
	m_pSliderMusic->setAnchorPoint({ 0.f, 0.5f });
	m_pSliderMusic->setPosition({ Utils::winSize().width - 155.f, Utils::winSize().height - 90.f });
	this->addChild(m_pSliderMusic);

	m_pSliderSFX = gd::Slider::create(this, (cocos2d::SEL_MenuHandler)&BetterPause::sfxSliderChanged, 1.f);
	m_pSliderSFX->setValue(Utils::shareFMOD()->getSFXVolume());
	m_pSliderSFX->updateBar();
	m_pSliderSFX->setScale(0.8f);
	m_pSliderSFX->setAnchorPoint({ 0.f, 0.5f });
	m_pSliderSFX->setPosition({ Utils::winSize().width - 155.f, Utils::winSize().height - 120.f });
	this->addChild(m_pSliderSFX);

	m_pLabelMusicVPercentage = cocos2d::CCLabelBMFont::create("0%", "goldFont.fnt");
	this->m_pLabelMusicVPercentage->setString(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(this->m_pSliderMusic->getValue() * 100))->getCString()
	);
	m_pLabelMusicVPercentage->setPosition({ this->m_pSliderMusic->getPositionX() + 95.f, this->m_pSliderMusic->getPositionY() + 33.f });
	m_pLabelMusicVPercentage->setScale(0.6f);
	m_pLabelMusicVPercentage->setAnchorPoint({ 0.f, 0.5f });
	this->addChild(m_pLabelMusicVPercentage);

	m_pLabelSFXVPercentage = cocos2d::CCLabelBMFont::create("0%", "goldFont.fnt");
	this->m_pLabelSFXVPercentage->setString(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(this->m_pSliderSFX->getValue() * 100))->getCString()
	);
	m_pLabelSFXVPercentage->setPosition({ this->m_pSliderSFX->getPositionX() + 95.f, this->m_pSliderSFX->getPositionY() + 33.f });

	m_pLabelSFXVPercentage->setScale(0.6f);
	m_pLabelSFXVPercentage->setAnchorPoint({ 0.f, 0.5f });
	this->addChild(m_pLabelSFXVPercentage);

	m_pNameLevelLabel = cocos2d::CCLabelBMFont::create(Utils::getplayLayerA()->m_level->levelName.c_str(), "goldFont.fnt");
	m_pNameLevelLabel->limitLabelWidth(150.f, 1.f, 0.1f);
	m_pNameLevelLabel->setAnchorPoint({ 0.f, 0.5f });
	m_pNameLevelLabel->setPosition({ 86.f, Utils::winSize().height - 30.f });
	this->addChild(m_pNameLevelLabel);

	auto getNameLevelType = [](gd::GJLevelType type) {
		switch (type)
		{
		case gd::kGJLevelTypeEditor: {
			return "Editor Level";
		}
		case gd::kGJLevelTypeLocal: {
			return "Official Level";
		}
		case gd::kGJLevelTypeSaved: {
			return "Online Level";
		}
		default: {
			return "NA Level";
		}
		}
	};

	cocos2d::ccColor3B green_Color = { 0, 255, 0 };
	cocos2d::ccColor3B bluesky_Color = { 0, 255, 255 };



	m_pNormalBarPerB = BarBetterShow::create(green_Color, !Utils::getplayLayerA()->m_isPracticeMode, !Utils::getplayLayerA()->m_isPracticeMode, Utils::getPercentageNowFix(), Utils::getplayLayerA()->m_level->normalPercent);
	m_pNormalBarPerB->setPosition({ 86.f, Utils::winSize().height - 90.f });
	m_pNormalBarPerB->setScale(0.5f);
	m_pNormalBarPerB->m_pBarBase->setVisible(true);
	m_pNormalBarPerB->m_pBarBase->setOpacity(Utils::convertOpacitySimplf(0.2f));
	this->addChild(m_pNormalBarPerB);

	m_pPracticeBarPerB = BarBetterShow::create(bluesky_Color, Utils::getplayLayerA()->m_isPracticeMode, Utils::getplayLayerA()->m_isPracticeMode, Utils::getPercentageNowFix(), Utils::getplayLayerA()->m_level->practicePercent);
	m_pPracticeBarPerB->setPosition({ 86.f, Utils::winSize().height - 125.f });
	m_pPracticeBarPerB->setScale(0.5f);
	m_pPracticeBarPerB->m_pBarBase->setVisible(true);
	m_pPracticeBarPerB->m_pBarBase->setOpacity(Utils::convertOpacitySimplf(0.2f));
	this->addChild(m_pPracticeBarPerB);

	m_pMenuButtonsConfig = cocos2d::CCMenu::create();
	this->addChild(m_pMenuButtonsConfig);

	m_pTypeLevelLabel = cocos2d::CCLabelBMFont::create(getNameLevelType(Utils::getplayLayerA()->m_level->levelType), "bigFont.fnt");
	m_pTypeLevelLabel->setScale(0.3f);
	m_pTypeLevelLabel->setPosition({ 86.f, Utils::winSize().height - 45.f });
	m_pTypeLevelLabel->setAnchorPoint({ 0.f, 1.f });
	this->addChild(m_pTypeLevelLabel);

	m_pStatusLevelLabel = cocos2d::CCLabelBMFont::create(Utils::getplayLayerA()->m_isPracticeMode ? "Practice Mode" : "Normal Mode", "bigFont.fnt");
	m_pStatusLevelLabel->setScale(0.3f);
	m_pStatusLevelLabel->setColor(Utils::getplayLayerA()->m_isPracticeMode ? bluesky_Color : green_Color);
	m_pStatusLevelLabel->setPosition({ 86.f + m_pNormalBarPerB->m_pBarBase->getScaledContentSize().width / 2, Utils::winSize().height - 45.f });
	m_pStatusLevelLabel->setAnchorPoint({ 1.f, 1.f });
	this->addChild(m_pStatusLevelLabel);

	auto attemptColorD = Utils::getplayLayerA()->m_isPracticeMode ? "Attempt: <cj>%i</c>" : "Attempt: <cg>%i</c>";
	auto timeColorD = Utils::getplayLayerA()->m_isPracticeMode ? "Time: <cj>%02d:%02d</c>" : "Time: <cg>%02d:%02d</c>";

	m_pAttemptCurrentLevelLabel = gd::TextArea::create("bigFont.fnt", false,
		std::string(cocos2d::CCString::createWithFormat(attemptColorD, Utils::getplayLayerA()->m_currentAttempt)->getCString()),
		0.3f, 100.f, 100.f, { 0.f, 1.f });
	m_pAttemptCurrentLevelLabel->setPosition({ 86.f, Utils::winSize().height - 60.f });
	m_pAttemptCurrentLevelLabel->setAnchorPoint({ 0.f, 1.f });
	this->addChild(m_pAttemptCurrentLevelLabel);

	int totalSeconds = std::floor(Utils::getplayLayerA()->m_totalTime);

	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;


	m_pTimeCurrentLevelLabel = gd::TextArea::create("bigFont.fnt", false,
		std::string(cocos2d::CCString::createWithFormat(timeColorD, minutes, seconds)->getCString()),
		0.3f, 100.f, 100.f, { 1.f, 1.f });
	m_pTimeCurrentLevelLabel->setPosition({ 86.f + m_pNormalBarPerB->m_pBarBase->getScaledContentSize().width / 2,
		Utils::winSize().height - 60.f });

	m_pTimeCurrentLevelLabel->setAnchorPoint({ 1.f, 1.f });

	this->addChild(m_pTimeCurrentLevelLabel);


	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onShowCursorInGame, Utils::shareManager()->getGameVariable("0024"), m_pMenuButtonsConfig, "Show Cursor In-Game", { 250.f, 30.f });
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onDisableShakeEffects, Utils::shareManager()->getGameVariable("0081"), m_pMenuButtonsConfig, "Disable Shake Effects", { 250.f, 50.f });
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarPercentageA, Utils::shareManager()->getGameVariable("0040"), m_pMenuButtonsConfig, "Progress %", { 250.f, 70.f });
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarA, Utils::shareManager()->m_bShowProgressBar, m_pMenuButtonsConfig, "Progress Bar", { 250.f, 90.f });
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onAutoCheckpointsA, Utils::shareManager()->getGameVariable("0027"), m_pMenuButtonsConfig, "Auto-Checkpoints", { 250.f, 110.f });
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onAutoRetryA, Utils::shareManager()->getGameVariable("0026"), m_pMenuButtonsConfig, "Auto-Retry", { 250.f, 130.f });

	this->m_pQuickSettingsLabel = cocos2d::CCLabelBMFont::create("Quick Settings", "goldFont.fnt");
	this->m_pQuickSettingsLabel->setScale(0.6f);
	this->m_pQuickSettingsLabel->setPosition({ 165.f, 158.f });
	this->addChild(this->m_pQuickSettingsLabel);

	this->m_pVolumenSettingsLabel = cocos2d::CCLabelBMFont::create("Volume Settings:", "bigFont.fnt");
	this->m_pVolumenSettingsLabel->setScale(0.5f);
	this->m_pVolumenSettingsLabel->setPosition({ this->m_pSliderMusic->getPositionX() + 5.f, this->m_pSliderMusic->getPositionY() + 60.f });
	this->addChild(this->m_pVolumenSettingsLabel);

	this->m_pVolumenMusicSettingsLabel = cocos2d::CCLabelBMFont::create("Music", "bigFont.fnt");
	this->m_pVolumenMusicSettingsLabel->setScale(0.4f);
	this->m_pVolumenMusicSettingsLabel->setPosition({ this->m_pSliderMusic->getPositionX() - 115.f, this->m_pSliderMusic->getPositionY() + 33.f });
	this->addChild(this->m_pVolumenMusicSettingsLabel);

	this->m_pVolumenSFXSettingsLabel = cocos2d::CCLabelBMFont::create("SFX", "bigFont.fnt");
	this->m_pVolumenSFXSettingsLabel->setScale(0.4f);
	this->m_pVolumenSFXSettingsLabel->setPosition({ this->m_pSliderSFX->getPositionX() - 110.f, this->m_pSliderSFX->getPositionY() + 33.f });
	this->addChild(this->m_pVolumenSFXSettingsLabel);

	this->m_pQuestsLabel = cocos2d::CCLabelBMFont::create("Quest:", "bigFont.fnt");
	this->m_pQuestsLabel->setScale(0.5f);
	this->m_pQuestsLabel->setPosition({ Utils::winSize().width - 150.f, 210.f });
	this->addChild(this->m_pQuestsLabel);

	//m_pTimeCurrentLevelLabel = cocos2d::CCLabelBMFont::create(
	//	cocos2d::CCString::createWithFormat(timeColorD, minutes, seconds)->getCString(), "bigFont.fnt");
	//m_pTimeCurrentLevelLabel->setScale(0.3f);
	//m_pTimeCurrentLevelLabel->setPosition({ m_pAttemptCurrentLevelLabel->boundingBox().getMaxX() + 30.f, Utils::winSize().height - 60.f });
	//m_pTimeCurrentLevelLabel->setAnchorPoint({ 0.f, 1.f });
	//this->addChild(m_pTimeCurrentLevelLabel);

	//std::cout << (int)pauseLayer->getOpacity() << std::endl;//75

	//MBO(bool, questMenu, 0x1dc) = false;
	//MBO(bool, questMenu, 0xfc) = true;


	//(**(code**)(*param_1 + 0x1dc))(0);
	//(**(code**)(*param_1 + 0xfc))(1);

	isNotRegister = false;


	return true;
}

void BetterPause::onOptionsLayer(cocos2d::CCObject* pSender) {
	gd::OptionsLayer::addToCurrentScene();
}

void BetterPause::onHide(cocos2d::CCObject* pSender) {
	this->m_pIsHide = !this->m_pIsHide;
	pauseLayer->setOpacity(this->m_pIsHide ? 0 : 75);

	for (size_t i = 0; i < this->getChildrenCount(); i++)
	{
		auto node = reinterpret_cast<cocos2d::CCNode*>(this->getChildren()->objectAtIndex(i));
		node->setVisible(!this->m_pIsHide);
	}

	if (this->m_pIsHide) {
		for (size_t i = 0; i < pauseLayer->getChildrenCount(); i++)
		{
			if (!dynamic_cast<BetterPause*>(pauseLayer->getChildren()->objectAtIndex(i))) {
				auto node = reinterpret_cast<cocos2d::CCNode*>(pauseLayer->getChildren()->objectAtIndex(i));
				node->setVisible(false);
			}
		}
	}
	else {
		auto Fnode = reinterpret_cast<cocos2d::CCNode*>(pauseLayer->getChildren()->objectAtIndex(0));
		Fnode->setVisible(true);
		for (size_t i = 1; i < pauseLayer->getChildrenCount(); i++)
		{
			if (!dynamic_cast<BetterPause*>(pauseLayer->getChildren()->objectAtIndex(i))) {
				auto node = reinterpret_cast<cocos2d::CCNode*>(pauseLayer->getChildren()->objectAtIndex(i));
				node->setVisible(false);
			}
		}
	}

	this->setVisible(true);
	this->m_pMenuButtons2->setVisible(true);

	for (size_t i = 0; i < this->m_pMenuButtons2->getChildrenCount(); i++)
	{
		auto node = reinterpret_cast<cocos2d::CCNode*>(this->m_pMenuButtons2->getChildren()->objectAtIndex(i));
		node->setVisible(!this->m_pIsHide);
	}

	reinterpret_cast<cocos2d::CCSprite*>(m_pVisibleButton->getChildren()->objectAtIndex(0))->initWithFile(this->m_pIsHide ? "BE_eye-off-btn.png" : "BE_eye-on-btn.png");
	m_pVisibleButton->setVisible(true);
	m_pVisibleButton->setOpacity(this->m_pIsHide ? 50 : 255);

}

void BetterPause::createToggleButton(cocos2d::SEL_MenuHandler callback, bool on,
	cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos) {

	auto toggleButton = gd::CCMenuItemToggler::createWithStandardSprites(this, callback, 0.5f);
	toggleButton->toggle(on);
	toggleButton->setPosition(menu->convertToNodeSpace(pos));
	if (menu) {
		menu->addChild(toggleButton);
	}

	auto text = cocos2d::CCLabelBMFont::create(caption.c_str(), "bigFont.fnt");
	text->limitLabelWidth(150.f, 0.3f, 0.1f);
	text->setAlignment(cocos2d::kCCTextAlignmentRight);
	text->setPosition(pos);
	text->setPositionX(pos.x - 15.f);
	text->setAnchorPoint({ 1.f, 0.5f });
	this->addChild(text);
}

void BetterPause::musicSliderChanged(cocos2d::CCObject* pSender) {
	this->pauseLayer->musicSliderChanged(pSender);
	auto valueV = this->m_pSliderMusic->getValue();
	Utils::shareFMOD()->m_pGlobalChannel->setVolume(valueV);
	this->m_pLabelMusicVPercentage->setString(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(valueV * 100))->getCString()
	);
}

void BetterPause::sfxSliderChanged(cocos2d::CCObject* pSender) {
	this->pauseLayer->sfxSliderChanged(pSender);
	auto valueV = this->m_pSliderSFX->getValue();
	Utils::shareFMOD()->m_pCurrentSoundChannel->setVolume(valueV);
	this->m_pLabelSFXVPercentage->setString(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(valueV * 100))->getCString()
	);
}

BarBetterShow* BarBetterShow::create(cocos2d::ccColor3B color, bool enabledSecondBar, bool showCurrentPer, float perCurrent, float bestCurrent) {
	auto ret = new BarBetterShow();

	if (ret && ret->init(color, enabledSecondBar, showCurrentPer, perCurrent, bestCurrent)) {
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool BarBetterShow::init(cocos2d::ccColor3B color, bool enabledSecondBar, bool showCurrentPer, float perCurrent, float bestCurrent) {
	if (!cocos2d::CCNode::init()) {
		return false;
	}

	m_pBarBase = cocos2d::CCSprite::create("GJ_progressBar_001.png");
	m_pBarBase->setVisible(false);
	m_pBarBase->setAnchorPoint({ 0.f, 0.5f });
	this->addChild(m_pBarBase);

	m_pBarMain = cocos2d::CCSprite::create("GJ_progressBar_001.png");
	this->updateBar(m_pBarMain, perCurrent);
	m_pBarMain->setColor(color);
	m_pBarMain->setAnchorPoint({ 0.f, 0.5f });
	this->addChild(m_pBarMain);

	m_pBarBG = cocos2d::CCSprite::create("GJ_progressBar_001.png");
	this->updateBar(m_pBarBG, bestCurrent);
	m_pBarBG->setColor(color);
	m_pBarBG->setOpacity(Utils::convertOpacitySimplf(0.4f));
	m_pBarBG->setAnchorPoint({ 0.f, 0.5f });
	this->addChild(m_pBarBG);

	float rightPosXCurrentPer = 1.f + m_pBarBase->getContentSize().width * min(max(perCurrent / 100.f, 0.f), 100.f);
	float rightPosXBestPer = 1.f + m_pBarBase->getContentSize().width * min(max(bestCurrent / 100.f, 0.f), 100.f);

	m_pPercentageCurrent = cocos2d::CCLabelBMFont::create(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(perCurrent))->getCString(), "bigFont.fnt");
	m_pPercentageCurrent->setScale(0.7f);
	m_pPercentageCurrent->setPosition({ rightPosXCurrentPer, -25.f });
	m_pPercentageCurrent->setVisible(showCurrentPer);
	this->addChild(m_pPercentageCurrent);

	m_pPercentageBest = cocos2d::CCLabelBMFont::create(
		cocos2d::CCString::createWithFormat("%i%% Best", static_cast<int>(bestCurrent))->getCString(), "goldFont.fnt");
	m_pPercentageBest->setScale(0.7f);
	m_pPercentageBest->setAnchorPoint({ 1.f, 0.5f });
	m_pPercentageBest->setPosition({ rightPosXBestPer, -25.f });
	this->addChild(m_pPercentageBest);

	m_pPercentageMax = cocos2d::CCLabelBMFont::create(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(100))->getCString(), "bigFont.fnt");
	m_pPercentageMax->setScale(0.7f);
	m_pPercentageMax->setOpacity(Utils::convertOpacitySimplf(0.4f));
	m_pPercentageMax->setPosition({ 340.f, -25.f });
	this->addChild(m_pPercentageMax);

	auto currentBox = m_pPercentageCurrent->boundingBox();
	auto bestBox = m_pPercentageBest->boundingBox();
	auto maxBox = m_pPercentageMax->boundingBox();

	if ((currentBox.getMaxX() >= bestBox.getMinX()) && m_pPercentageBest->isVisible() && m_pPercentageCurrent->isVisible()) {
		m_pPercentageBest->setPositionY(25.f);
	}
	if (currentBox.getMaxX() >= maxBox.getMinX() && m_pPercentageCurrent->isVisible()) {
		m_pPercentageMax->setPositionY(25.f);
	}

	if (bestCurrent >= 100.f && currentBox.getMaxX() >= (maxBox.getMinX() - 80.f)) {
		m_pPercentageMax->setPositionY(25.f);
	}

	if ((bestBox.getMaxX() >= maxBox.getMinX()) && m_pPercentageBest->isVisible()) {
		if (m_pPercentageMax->getPositionY() == 25.f) {
			m_pPercentageBest->setAnchorPoint({ 1.f, 0.5f });
			m_pPercentageBest->setPosition(m_pPercentageMax->getPosition());
			m_pPercentageBest->setPositionX(m_pPercentageMax->getPositionX() - m_pPercentageMax->getContentSize().width);
		}
		else {
			m_pPercentageBest->setPositionY(25.f);
		}
	}

	if (bestCurrent >= 100.f) {
		m_pPercentageMax->setFntFile("goldFont.fnt");
		m_pPercentageMax->setScale(0.7f);
		m_pPercentageMax->setOpacity(Utils::convertOpacitySimplf(1.f));
		m_pPercentageMax->setString("100% Best");
		m_pPercentageMax->setAnchorPoint({ 1.f, 0.5f });
		m_pPercentageBest->setVisible(false);
	}

	if (perCurrent >= bestCurrent) {
		m_pPercentageCurrent->setFntFile("goldFont.fnt");
		m_pPercentageCurrent->setScale(0.7f);
		m_pPercentageBest->setVisible(false);
	}

	if (!enabledSecondBar) {
		m_pBarMain->setVisible(false);
		m_pBarBG->setOpacity(Utils::convertOpacitySimplf(1.f));
		m_pPercentageCurrent->setVisible(false);
		if (m_pPercentageMax->getOpacity() != 255) {
			m_pPercentageBest->setVisible(true);
			m_pPercentageBest->setAnchorPoint({ 0.5f, 0.5f });
		}
	}

	if (bestCurrent <= 30.f) {
		m_pPercentageBest->setAnchorPoint({ 0.f, 0.5f });
	}

	return true;
}

void BarBetterShow::updateBar(cocos2d::CCSprite* m_pBar, float per) {
	auto mProgressBarSize = cocos2d::CCSize(m_pBarBase->getTextureRect().size.width - 4.0f, 8.0f);
	float width = mProgressBarSize.width;
	if (per >= 100.f) {
		return;
	}
	width = width * static_cast<float>(per) / 100.0f;
	m_pBar->setTextureRect(cocos2d::CCRect(0.0f, 0.0f, width, m_pBarBase->getTextureRect().size.height));
}

void BetterPause::onAutoRetryA(cocos2d::CCObject* pSender) {
	this->pauseLayer->onAutoRetry(pSender);
}

void BetterPause::onAutoCheckpointsA(cocos2d::CCObject* pSender) {
	this->pauseLayer->onAutoCheckpoints(pSender);
}

void BetterPause::updatePercentageObjects() {
	Utils::getplayLayerA()->m_percentLabel->setVisible(Utils::shareManager()->getGameVariable("0040"));

	float ypos = Utils::winSize().height - 8.f;

	if (Utils::shareManager()->m_bShowProgressBar) {
		Utils::getplayLayerA()->m_sliderBarSprite->getParent()->setPositionY(ypos);
		float xPer = (Utils::winSize().width / 2.f + (110.f * Utils::getplayLayerA()->m_sliderBarSprite->getParent()->getScale()));
		float yPer = ypos;
		Utils::getplayLayerA()->m_percentLabel->setPosition(xPer, yPer);
		Utils::getplayLayerA()->m_percentLabel->setAnchorPoint({ 0.f, 0.5f });
	}
	else {
		Utils::getplayLayerA()->m_percentLabel->setAnchorPoint({ 0.5f, 0.5f });
		Utils::getplayLayerA()->m_percentLabel->setPosition((Utils::winSize().width / 2.f), ypos);
	}
}

void BetterPause::onProgressBarA(cocos2d::CCObject* pSender) {
	this->pauseLayer->onProgressBar(pSender);
	if (Utils::getplayLayerA() && (Utils::getplayLayerA()->m_percentLabel->isVisible() != Utils::shareManager()->getGameVariable("0040"))) {
		this->updatePercentageObjects();
	}
}

void BetterPause::onProgressBarPercentageA(cocos2d::CCObject* pSender) {
	Utils::shareManager()->setGameVariable("0040", !Utils::shareManager()->getGameVariable("0040"));
	this->updatePercentageObjects();
}

void BetterPause::onDisableShakeEffects(cocos2d::CCObject* pSender) {
	Utils::shareManager()->setGameVariable("0081", !Utils::shareManager()->getGameVariable("0081"));
}

void BetterPause::onShowCursorInGame(cocos2d::CCObject* pSender) {
	Utils::shareManager()->setGameVariable("0024", !Utils::shareManager()->getGameVariable("0024"));
}
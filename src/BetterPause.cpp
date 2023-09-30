#include "pch.h"
#include "BetterPause.h"
#include "BetterPauseManager.h"

bool BetterPause::isNotRegister = false;
cocos2d::CCMenu* BetterPause::pauseLayer_MenuToggles = nullptr;
cocos2d::CCPoint BetterPause::pauseLayer_lastPoint = {};
std::vector<std::string> BetterPause::quickSettings_Name = {};
std::vector<std::string> BetterPause::quickSettings_Desc = {};
std::vector<std::string> BetterPause::quickSettings_Key = {};

BetterPause* BetterPause::create(gd::PauseLayer* pauseLayer, bool isEditor, bool notBetter) {
	auto ret = new BetterPause();

	if (ret && ret->init(pauseLayer, isEditor, notBetter)) {
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool BetterPause::init(gd::PauseLayer* pauseLayer, bool isEditor, bool notBetter) {

	if (!cocos2d::CCLayer::init()) {
		return false;
	}

	this->pauseLayer = pauseLayer;

	if (!notBetter) {
		m_pMenuButtons2 = cocos2d::CCMenu::create();
		m_pMenuButtons2->setPosition({ 40.f, 42.f });
		this->addChild(m_pMenuButtons2);

		auto settingsButtonImage = cocos2d::CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
		settingsButtonImage->setScale(0.6f);
		auto settingsButton = gd::CCMenuItemSpriteExtra::create(settingsButtonImage, this, (cocos2d::SEL_MenuHandler)&BetterPause::onOptionsLayer);
		m_pMenuButtons2->addChild(settingsButton);

		if (BetterPauseManager::sharedState()->m_pSwitchPause.m_uOffset == 1) {
			m_pMenuButtons2->setPositionY(72.f);

			/*if (BetterPause::pauseLayer_MenuToggles) {
				this->pauseLayer->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarA,
					!Utils::shareManager()->getGameVariable("0040"), BetterPause::pauseLayer_MenuToggles, "%",
					cocos2d::CCPoint(BetterPause::pauseLayer_lastPoint.x + 65.f, BetterPause::pauseLayer_lastPoint.y));
			}*/


			auto menu = cocos2d::CCMenu::create();
			menu->setPosition({ 0,0 });
			menu->setZOrder(50);
			this->pauseLayer->addChild(menu);

			auto openLayerButtonSprite = gd::ButtonSprite::createWithSpriteFrameName("GJ_challengeBtn_001.png");
			openLayerButtonSprite->setScale(0.7f);

			this->m_pButtonQuestAlt = gd::CCMenuItemSpriteExtra::create(openLayerButtonSprite, menu, (cocos2d::SEL_MenuHandler)&BetterPause::onOpenChallenges);
			this->m_pButtonQuestAlt->setPosition(Utils::winSize().width - 59.f, Utils::winSize().height - 65.f);
			menu->addChild(this->m_pButtonQuestAlt);

			auto texto_del_nivel = RCAST(cocos2d::CCLabelBMFont*, this->pauseLayer->getChildren()->objectAtIndex(1));
			texto_del_nivel->limitLabelWidth(300.f, 1.f, 0.f);

			auto openinfoLayerbutton_sprite = gd::ButtonSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
			openinfoLayerbutton_sprite->setScale(1.f);
			auto openinfoLayerbutton = gd::CCMenuItemSpriteExtra::create(openinfoLayerbutton_sprite, menu, (cocos2d::SEL_MenuHandler)&BetterPause::onInfoLevelOpen);
			openinfoLayerbutton->setPosition({ 40.f, 35.f });
			menu->addChild(openinfoLayerbutton);

			/*for (size_t i = 0; i < pauseLayer->getChildrenCount(); i++)
			{
				pauseLayer->getChildren()->objectAtIndex(i)->setTag(i);
			}

			auto percentajeLabel = static_cast<cocos2d::CCLabelBMFont*>(pauseLayer->getChildren()->objectAtIndex(11));

			if (percentajeLabel && std::string(percentajeLabel->getString()) == "Progress Bar") {
				percentajeLabel->setString("Bar");
			}*/

		}
		else if (BetterPauseManager::sharedState()->m_pSwitchPause.m_uOffset == 3) {
			for (size_t i = 0; i < pauseLayer->getChildrenCount(); i++)
			{
				if ((i >= 0 && i <= 5) || i == 8) {
					continue;
				}

				if (auto node = static_cast<cocos2d::CCNode*>(pauseLayer->getChildren()->objectAtIndex(i)); node) {
					node->setVisible(false);
				}
			}

			auto bgPause = reinterpret_cast<cocos2d::extension::CCScale9Sprite*>(pauseLayer->getChildren()->objectAtIndex(0));
			auto titleLevel = reinterpret_cast<cocos2d::CCLabelBMFont*>(pauseLayer->getChildren()->objectAtIndex(1));
			auto barNormal = reinterpret_cast<cocos2d::CCSprite*>(pauseLayer->getChildren()->objectAtIndex(2));
			auto barPractice = reinterpret_cast<cocos2d::CCSprite*>(pauseLayer->getChildren()->objectAtIndex(3));
			auto perNormal = reinterpret_cast<cocos2d::CCLabelBMFont*>(pauseLayer->getChildren()->objectAtIndex(4));
			auto perPractice = reinterpret_cast<cocos2d::CCLabelBMFont*>(pauseLayer->getChildren()->objectAtIndex(5));
			auto buttonsMenu = reinterpret_cast<cocos2d::CCMenu*>(pauseLayer->getChildren()->objectAtIndex(8));

			bgPause->setContentSize({ bgPause->getContentSize().width, 70.f });
			bgPause->setPositionY(Utils::winSize().height - 52.f);
			titleLevel->setAnchorPoint({ 0.f,0.5f });
			titleLevel->setPosition({ 68.f, 268.f });
			titleLevel->limitLabelWidth(250.f, 1.f, 0.1f);
			barNormal->setPosition({ 115.5f, Utils::winSize().height - 100.f }); //160.000
			barNormal->setScale(0.6f);
			barPractice->setPosition({ 323.5f, Utils::winSize().height - 100.f });
			barPractice->setScale(0.6f);
			perNormal->setPosition({ 115.5f, Utils::winSize().height - 100.f });
			perPractice->setPosition({ 323.5f, Utils::winSize().height - 100.f });
			m_pMenuButtons2->setPositionY(Utils::winSize().height - 54.f);
			buttonsMenu->setPosition({ Utils::winSize().width - 269.f, Utils::winSize().height - 132.f });
			buttonsMenu->setScale(0.5f);

			auto bordeBarNormal = cocos2d::CCSprite::create("slidergroove2.png");
			auto bordeBarPractice = cocos2d::CCSprite::create("slidergroove2.png");
			bordeBarNormal->setScaleX(0.98f);
			bordeBarNormal->setScaleY(1.2f);
			bordeBarPractice->setScaleX(0.98f);
			bordeBarPractice->setScaleY(1.2f);
			bordeBarNormal->setPosition({ 115.5f, Utils::winSize().height - 100.f });
			bordeBarPractice->setPosition({ 323.5f, Utils::winSize().height - 100.f });
			bordeBarNormal->setZOrder(3);
			bordeBarPractice->setZOrder(3);
			pauseLayer->addChild(bordeBarNormal);
			pauseLayer->addChild(bordeBarPractice);
		}

		return true;
	}

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

	m_pQuestMenu->setVisible(false);


	switch (BetterPauseManager::sharedState()->m_pSwitchQuest.m_uOffset)
	{
	case 0: {
		m_pQuestMenu->setVisible(true);
		break;
	}
	case 1: {
		auto menu = cocos2d::CCMenu::create();
		menu->setPosition({ 0,0 });
		menu->setZOrder(50);
		this->addChild(menu);

		auto openLayerButtonSprite = gd::ButtonSprite::createWithSpriteFrameName("GJ_challengeBtn_001.png");
		openLayerButtonSprite->setScale(0.8f);
		this->m_pButtonQuestAlt = gd::CCMenuItemSpriteExtra::create(openLayerButtonSprite, this, (cocos2d::SEL_MenuHandler)&BetterPause::onOpenChallenges);
		this->m_pButtonQuestAlt->setPosition(Utils::winSize().width - 150.f, 120.f);
		menu->addChild(this->m_pButtonQuestAlt);

		break;
	}
	default:
		break;
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
	if (!visibleButtonImage) {
		visibleButtonImage = cocos2d::CCSprite::createWithSpriteFrameName("GJ_reportBtn_001.png");
		this->m_pIsTextureEye = false;
	}
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

	m_pMenuButtonsVolSet = cocos2d::CCMenu::create();
	m_pMenuButtonsVolSet->setPosition({ 0.f, 0.f });
	this->addChild(m_pMenuButtonsVolSet);

	m_pLabelMusicVPercentage = cocos2d::CCLabelBMFont::create("0%", "goldFont.fnt");
	this->m_pLabelMusicVPercentage->setString(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(this->m_pSliderMusic->getValue() * 100))->getCString()
	);
	//m_pLabelMusicVPercentage->setPosition({ this->m_pSliderMusic->getPositionX() + 95.f, this->m_pSliderMusic->getPositionY() + 33.f });
	//this->addChild(m_pLabelMusicVPercentage);

	m_pBtnMusicVPercentage = gd::CCMenuItemSpriteExtra::create(m_pLabelMusicVPercentage, this, (cocos2d::SEL_MenuHandler)&BetterPause::onSetValueMusic);
	m_pBtnMusicVPercentage->setPosition({ this->m_pSliderMusic->getPositionX() + 95.f, this->m_pSliderMusic->getPositionY() + 33.f });
	m_pLabelMusicVPercentage->setScale(0.6f);
	m_pLabelMusicVPercentage->setAnchorPoint({ 0.f, 0.5f });
	m_pMenuButtonsVolSet->addChild(m_pBtnMusicVPercentage);

	m_pLabelSFXVPercentage = cocos2d::CCLabelBMFont::create("0%", "goldFont.fnt");
	this->m_pLabelSFXVPercentage->setString(
		cocos2d::CCString::createWithFormat("%i%%", static_cast<int>(this->m_pSliderSFX->getValue() * 100))->getCString()
	);
	//m_pLabelSFXVPercentage->setPosition({ this->m_pSliderSFX->getPositionX() + 95.f, this->m_pSliderSFX->getPositionY() + 33.f });
	//m_pLabelSFXVPercentage->setScale(0.6f);
	//m_pLabelSFXVPercentage->setAnchorPoint({ 0.f, 0.5f });
	//this->addChild(m_pLabelSFXVPercentage);

	m_pBtnSFXVPercentage = gd::CCMenuItemSpriteExtra::create(m_pLabelSFXVPercentage, this, (cocos2d::SEL_MenuHandler)&BetterPause::onSetValueSFX);
	m_pBtnSFXVPercentage->setPosition({ this->m_pSliderSFX->getPositionX() + 95.f, this->m_pSliderSFX->getPositionY() + 33.f });
	m_pLabelSFXVPercentage->setScale(0.6f);
	m_pLabelSFXVPercentage->setAnchorPoint({ 0.f, 0.5f });
	m_pMenuButtonsVolSet->addChild(m_pBtnSFXVPercentage);

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

	//m_pDownloadMusicLabel = gd::TextArea::create("bigFont.fnt", false,
	//	std::string(cocos2d::CCString::createWithFormat("Download: ", gd::MusicDownloadManager::sharedState()->getDownloadProgress(Utils::getplayLayerA()->m_level->songID))->getCString()),
	//	0.3f, 100.f, 100.f, { 1.f, 1.f });
	//m_pDownloadMusicLabel->setPosition({ 86.f, Utils::winSize().height - 80.f });
	//m_pDownloadMusicLabel->setAnchorPoint({ 0.f, 1.f });
	//this->addChild(m_pDownloadMusicLabel);

	/*this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onShowCursorInGame, Utils::shareManager()->getGameVariable("0024"), m_pMenuButtonsConfig, "Show Cursor In-Game", { 250.f, 30.f }, 0.3f);
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onDisableShakeEffects, Utils::shareManager()->getGameVariable("0081"), m_pMenuButtonsConfig, "Disable Shake Effects", { 250.f, 50.f }, 0.3f);
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarPercentageA, Utils::shareManager()->getGameVariable("0040"), m_pMenuButtonsConfig, "Progress %", { 250.f, 70.f }, 0.3f);
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarA, Utils::shareManager()->m_bShowProgressBar, m_pMenuButtonsConfig, "Progress Bar", { 250.f, 90.f }, 0.3f);
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onAutoCheckpointsA, Utils::shareManager()->getGameVariable("0027"), m_pMenuButtonsConfig, "Auto-Checkpoints", { 250.f, 110.f }, 0.3f);
	this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onAutoRetryA, Utils::shareManager()->getGameVariable("0026"), m_pMenuButtonsConfig, "Auto-Retry", { 250.f, 130.f }, 0.3f);*/

	auto xPosButtonsToggles = BetterPauseManager::sharedState()->m_pSwitchButtonsPos.m_uOffset == 1 ? 196.f : 250.f;

	auto mlt = gd::MoreOptionsLayer::create();
	mlt->keyBackClicked();
	CC_SAFE_DELETE(mlt);

	float xPosRES[6] = { xPosButtonsToggles, xPosButtonsToggles , xPosButtonsToggles, xPosButtonsToggles - 90.f, xPosButtonsToggles - 90.f, xPosButtonsToggles - 90.f };
	float yPosRES[6] = { 140.f, 120.f , 100.f, 140.f, 120.f , 100.f };

	for (size_t i = 0; i < 6; i++)
	{
		auto posA = sharedStateBP().posQuickA[i];
		if (posA == -2) {
			this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarA, Utils::shareManager()->m_bShowProgressBar, m_pMenuButtonsConfig, "Progress Bar", { xPosRES[i], yPosRES[i] }, 0.25f, true);
		}
		else if (posA == -1) {
			continue;
		}
		else if (BetterPause::quickSettings_Name[posA].c_str() != nullptr) {
			if (BetterPause::quickSettings_Key[posA] == "0040") {
				this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarPercentageA, "0040", m_pMenuButtonsConfig, "Progress %", { xPosRES[i], yPosRES[i] }, 0.25f, true);

			}
			else {
				this->createToggleButtonWithGameVariable(BetterPause::quickSettings_Key[posA].c_str(), m_pMenuButtonsConfig, BetterPause::quickSettings_Name[posA].c_str(), { xPosRES[i], yPosRES[i] }, 0.25f, true);
			}
		}
		else {
			for (size_t j = 0; j < 6; j++)
			{
				bool romp = false;
				for (size_t k = 0; k < 6; k++)
				{
					if (sharedStateBP().posQuickASafe[j] == sharedStateBP().posQuickA[k]) {
						break;
					}
					if (j + 1 == 6 && sharedStateBP().posQuickASafe[j] != sharedStateBP().posQuickA[k]) {
						sharedStateBP().posQuickA[i] = sharedStateBP().posQuickASafe[j];
						romp = true;
						break;
					}
				}

				if (romp) {
					break;
				}
			}

			if (BetterPause::quickSettings_Key[posA] == "0040") {
				this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarPercentageA, "0040", m_pMenuButtonsConfig, "Progress %", { xPosRES[i], yPosRES[i] }, 0.25f, true);

			}
			else {
				this->createToggleButtonWithGameVariable(BetterPause::quickSettings_Key[posA].c_str(), m_pMenuButtonsConfig, BetterPause::quickSettings_Name[posA].c_str(), { xPosRES[i], yPosRES[i] }, 0.25f, true);
			}
		}
	}


	//this->createToggleButtonWithGameVariable("0024", m_pMenuButtonsConfig, "Show Cursor In-Game", { xPosButtonsToggles, 140.f }, 0.25f, true);
	//this->createToggleButtonWithGameVariable("0081", m_pMenuButtonsConfig, "Disable Shake Effects", { xPosButtonsToggles, 120.f }, 0.25f, true);
	//
	//this->createToggleButton((cocos2d::SEL_MenuHandler)&BetterPause::onProgressBarA, Utils::shareManager()->m_bShowProgressBar, m_pMenuButtonsConfig, "Progress Bar", { xPosButtonsToggles - 90.f, 140.f }, 0.25f, true);
	//this->createToggleButtonWithGameVariable("0027", m_pMenuButtonsConfig, "Auto-Checkpoints", { xPosButtonsToggles - 90.f, 120.f }, 0.25f, true);
	//this->createToggleButtonWithGameVariable("0026", m_pMenuButtonsConfig, "Auto-Retry", { xPosButtonsToggles - 90.f, 100.f }, 0.25f, true);

	/*this->m_pQuickSettingsLabel = cocos2d::CCLabelBMFont::create("Quick Settings", "goldFont.fnt");
	this->m_pQuickSettingsLabel->setScale(0.6f);
	this->m_pQuickSettingsLabel->setPosition({ 165.f, 158.f });
	this->addChild(this->m_pQuickSettingsLabel);*/

	this->m_pQuickSettingsLabel = cocos2d::CCLabelBMFont::create("Quick Settings", "goldFont.fnt");
	this->m_pQuickSettingsLabel->setScale(0.5f);
	this->m_pQuickSettingsLabel->setPosition({ 165.f, 164.f });
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
	this->m_pQuestsLabel->setPosition({ Utils::winSize().width - 150.f, this->m_pSliderSFX->getPositionY() + 10.f });
	this->addChild(this->m_pQuestsLabel);


	auto songID_ = Utils::getplayLayerA()->m_level->songID;
	gd::SongInfoObject* songObj = nullptr;

	if (songID_ == 0) {
		songObj = gd::LevelTools::getSongObject(Utils::getplayLayerA()->m_level->audioTrack);
	}
	else {
		songObj = gd::SongInfoObject::create(songID_);
	}


	this->m_pCustomSongWidget = gd::CustomSongWidget::create(songObj, 0,
		0, 0, true, songID_ == 0, 0);
	this->m_pCustomSongWidget->setPosition(172.f, 50.f);
	this->m_pCustomSongWidget->setScale(0.6f);
	this->addChild(this->m_pCustomSongWidget);


	if (BetterPauseManager::sharedState()->m_pSwitchButtonsPos.m_uOffset == 1) {
		m_pMenuButtons->setPositionX(Utils::winSize().width - 40.f);
		m_pMenuButtons2->setPositionX(Utils::winSize().width - 40.f);
		this->m_pCustomSongWidget->setPosition(120.f, 50.f);
		m_pNormalBarPerB->setPosition({ 32.f, Utils::winSize().height - 90.f });
		m_pPracticeBarPerB->setPosition({ 32.f, Utils::winSize().height - 125.f });
		m_pTypeLevelLabel->setPosition({ 32.f, Utils::winSize().height - 45.f });
		m_pStatusLevelLabel->setPosition({ 32.f + m_pNormalBarPerB->m_pBarBase->getScaledContentSize().width / 2, Utils::winSize().height - 45.f });
		m_pAttemptCurrentLevelLabel->setPosition({ 32.f, Utils::winSize().height - 60.f });
		m_pTimeCurrentLevelLabel->setPosition({ 32.f + m_pNormalBarPerB->m_pBarBase->getScaledContentSize().width / 2,
			Utils::winSize().height - 60.f });
		m_pNameLevelLabel->setPosition({ 32.f, Utils::winSize().height - 30.f });
		this->m_pQuickSettingsLabel->setPosition({ 111.f, 164.f });
		m_pSliderMusic->setPosition({ Utils::winSize().width - 215.f, Utils::winSize().height - 90.f });
		m_pSliderSFX->setPosition({ Utils::winSize().width - 215.f, Utils::winSize().height - 120.f });
		this->m_pVolumenSettingsLabel->setPosition({ this->m_pSliderMusic->getPositionX() + 5.f, this->m_pSliderMusic->getPositionY() + 60.f });
		this->m_pVolumenMusicSettingsLabel->setPosition({ this->m_pSliderMusic->getPositionX() - 115.f, this->m_pSliderMusic->getPositionY() + 33.f });
		this->m_pVolumenSFXSettingsLabel->setPosition({ this->m_pSliderSFX->getPositionX() - 110.f, this->m_pSliderSFX->getPositionY() + 33.f });
		this->m_pQuestsLabel->setPosition({ Utils::winSize().width - 210.f, 210.f });
		m_pBtnMusicVPercentage->setPosition({ this->m_pSliderMusic->getPositionX() + 95.f, this->m_pSliderMusic->getPositionY() + 33.f });
		m_pBtnSFXVPercentage->setPosition({ this->m_pSliderSFX->getPositionX() + 95.f, this->m_pSliderSFX->getPositionY() + 33.f });
		if (m_pQuestMenu) {
			m_pQuestMenu->setPosition({ (Utils::winSize().width / 2) - 210.f, -50.f });
		}
		else if(this->m_pButtonQuestAlt) {
			this->m_pButtonQuestAlt->setPosition(Utils::winSize().width - 210.f, 120.f);
		}
	}

	switch (BetterPauseManager::sharedState()->m_pSwitchQuest.m_uOffset)
	{
	case 2: {
		this->m_pVolumenMusicSettingsLabel->setPositionY(Utils::winSize().height / 2.f + 32.f);
		this->m_pVolumenSFXSettingsLabel->setPositionY(Utils::winSize().height / 2.f + 2.f);
		this->m_pSliderMusic->setPositionY(Utils::winSize().height / 2.f);
		this->m_pSliderSFX->setPositionY(Utils::winSize().height / 2.f - 30.f);
		this->m_pBtnMusicVPercentage->setPositionY(Utils::winSize().height / 2.f + 32.f);
		this->m_pBtnSFXVPercentage->setPositionY(Utils::winSize().height / 2.f + 2.f);
		this->m_pQuestsLabel->setVisible(false);
		this->m_pVolumenSettingsLabel->setPosition({ this->m_pSliderMusic->getPositionX() + 5.f, this->m_pSliderMusic->getPositionY() + 60.f });
		break;
	}
	default:
		break;
	}

	auto visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();

	float aspectRatio = visibleSize.width / visibleSize.height;

	float targetAspectRatio = 4.0f / 3.0f;

	//std::cout << fabs(aspectRatio - targetAspectRatio) << std::endl;

	if (fabs(aspectRatio - targetAspectRatio) < 0.39) {

		this->m_pVolumenMusicSettingsLabel->setScale(0.4f);
		m_pVolumenMusicSettingsLabel->setPositionX(m_pVolumenMusicSettingsLabel->getPositionX() + 70.f);
		this->m_pVolumenSFXSettingsLabel->setScale(0.4f);
		m_pVolumenSFXSettingsLabel->setPositionX(m_pVolumenSFXSettingsLabel->getPositionX() + 70.f);
		this->m_pSliderMusic->setScale(0.5f);
		m_pSliderMusic->setPositionX(m_pSliderMusic->getPositionX() + 35.f);
		this->m_pSliderSFX->setScale(0.5f);
		m_pSliderSFX->setPositionX(m_pSliderSFX->getPositionX() + 35.f);
		m_pSliderMusic->setPositionY(m_pSliderMusic->getPositionY() - 58.f);
		m_pSliderSFX->setPositionY(m_pSliderSFX->getPositionY() - 58.f);

		//this->m_pBtnMusicVPercentage->setScale(0.5f);
		//this->m_pBtnSFXVPercentage->setScale(0.5f);
		this->m_pVolumenSettingsLabel->setScale(0.4f);
		this->m_pQuestsLabel->setScale(0.4f);
		if (m_pQuestMenu) {
			m_pQuestMenu->setScale(0.5f);
			m_pQuestMenu->setPositionX(m_pQuestMenu->getPositionX() + 35.f);
		}
		else if (this->m_pButtonQuestAlt) {
			this->m_pButtonQuestAlt->setScale(0.5f);
		}

		/*this->m_pVolumenMusicSettingsLabel->setPositionX(Utils::winSize().height / 2.f + 32.f);
		this->m_pVolumenSFXSettingsLabel->setPositionX(Utils::winSize().height / 2.f + 2.f);
		this->m_pSliderMusic->setPositionX(Utils::winSize().height / 2.f);
		this->m_pSliderSFX->setPositionX(Utils::winSize().height / 2.f - 30.f);
		this->m_pBtnMusicVPercentage->setPositionX(Utils::winSize().height / 2.f + 32.f);
		this->m_pBtnSFXVPercentage->setPositionX(Utils::winSize().height / 2.f + 2.f);
		this->m_pVolumenSettingsLabel->setPosition({ this->m_pSliderMusic->getPositionX() + 5.f, this->m_pSliderMusic->getPositionY() + 60.f });
		this->m_pQuestsLabel->setPosition({ Utils::winSize().width - 210.f, 210.f });
		if (m_pQuestMenu) {
			m_pQuestMenu->setPosition({ (Utils::winSize().width / 2) - 210.f, -50.f });
		}
		else if (this->m_pButtonQuestAlt) {
			this->m_pButtonQuestAlt->setPosition(Utils::winSize().width - 210.f, 120.f);
		}*/
	}


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

void BetterPause::onSetValueMusic(cocos2d::CCObject* pSender) {
	SetVolumenPopup::create(this->m_pSliderMusic)->show();
}

void BetterPause::onSetValueSFX(cocos2d::CCObject* pSender) {
	SetVolumenPopup::create(this->m_pSliderSFX)->show();
}

void BetterPause::onOptionsLayer(cocos2d::CCObject* pSender) {
	this->addChild(MoreOptionsPauseLayer::create(), 415);
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

	if (m_pIsTextureEye) {
		reinterpret_cast<cocos2d::CCSprite*>(m_pVisibleButton->getChildren()->objectAtIndex(0))->initWithFile(this->m_pIsHide ? "BE_eye-off-btn.png" : "BE_eye-on-btn.png");
	}
	m_pVisibleButton->setVisible(true);
	m_pVisibleButton->setOpacity(this->m_pIsHide ? 50 : 255);

}

void BetterPause::onToggleWithGameVariable(cocos2d::CCObject* pSender) {
	auto keyCode = std::string("00") + std::to_string(static_cast<int>(reinterpret_cast<cocos2d::CCNode*>(pSender)->getTag()));
	Utils::shareManager()->setGameVariable(keyCode.c_str(), !Utils::shareManager()->getGameVariable(keyCode.c_str()));
}

void BetterPause::createToggleButtonWithGameVariable(const char* key, cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos, float size, bool twoColumns) {

	auto toggleButton = gd::CCMenuItemToggler::createWithStandardSprites(this, (cocos2d::SEL_MenuHandler)&BetterPause::onToggleWithGameVariable, size + 0.2f);
	toggleButton->toggle(Utils::shareManager()->getGameVariable(key));
	toggleButton->setTag(std::stoi(key));
	toggleButton->setPosition(menu->convertToNodeSpace(pos));
	if (menu) {
		menu->addChild(toggleButton);
	}

	auto text = cocos2d::CCLabelBMFont::create(caption.c_str(), "bigFont.fnt");
	float labelWidth = twoColumns ? (250.f * size) : (500.f * size);
	text->limitLabelWidth(labelWidth, size, 0.1f);
	text->setAlignment(cocos2d::kCCTextAlignmentRight);
	text->setPosition({ pos.x - 15.f, pos.y });
	text->setAnchorPoint({ 1.f, 0.5f });
	this->addChild(text);
}

void BetterPause::createToggleButton(cocos2d::SEL_MenuHandler callback, bool on,
	cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos, float size, bool twoColumns) {

	auto toggleButton = gd::CCMenuItemToggler::createWithStandardSprites(this, callback, size + 0.2f);
	toggleButton->toggle(on);
	toggleButton->setPosition(menu->convertToNodeSpace(pos));
	if (menu) {
		menu->addChild(toggleButton);
	}

	auto text = cocos2d::CCLabelBMFont::create(caption.c_str(), "bigFont.fnt");
	float labelWidth = twoColumns ? (250.f * size) : (500.f * size);
	text->limitLabelWidth(labelWidth, size, 0.1f);
	text->setAlignment(cocos2d::kCCTextAlignmentRight);
	text->setPosition({ pos.x - 15.f, pos.y });
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

void BetterPause::onInfoLevelOpen(cocos2d::CCObject* pSender) {

	std::string creatorname = Utils::getplayLayerA()->m_level->userName.empty() ? "-" : Utils::getplayLayerA()->m_level->userName;
	std::string SongID = Utils::returnZeroBool(Utils::getplayLayerA()->m_level->songID) ? "-" : std::to_string(static_cast<int>(Utils::getplayLayerA()->m_level->songID));
	std::string ObjectCount = Utils::returnZeroBool(Utils::getplayLayerA()->m_level->objectCount) ? "-" : std::to_string(static_cast<int>(Utils::getplayLayerA()->m_level->objectCount));

	std::string contentStream = "<cg>Total Attempts:</c> " + std::to_string(Utils::getplayLayerA()->m_level->attempts) +
		"\n<cj>Total Jumps:</c> " + std::to_string(Utils::getplayLayerA()->m_level->jumps) +
		"\n<cy>Creator:</c> " + creatorname +
		"\n<cl>ID:</c> " + std::to_string(Utils::getplayLayerA()->m_level->levelID) +
		"\n<cr>Song ID:</c> " + SongID +
		"\n<co>Objects Total:</c> " + ObjectCount +
		"\n<cl>Coins:</c> " + std::to_string(Utils::getplayLayerA()->m_level->coins);

	return gd::FLAlertLayer::create(nullptr, "Level Stats", "OK", nullptr, 300, contentStream)->show();

}

void BetterPause::onOpenChallenges(cocos2d::CCObject* pSender) {
	gd::ChallengesPage::create()->show();
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

SetVolumenPopup* SetVolumenPopup::create(gd::Slider* m_pSliderRef) {
	auto node = new SetVolumenPopup();
	if (node && node->init(m_pSliderRef)) {
		node->autorelease();
	}
	else {
		CC_SAFE_DELETE(node);
	}
	return node;
}

void SetVolumenPopup::onSet(cocos2d::CCObject* pSender) {
	int numberAs = 0;
	try {
		numberAs = std::stoi(this->m_pInputTextValue->getString());
	}
	catch (std::exception const& e) {
		numberAs = this->m_pSliderRef->getValue() * 100;
		//gd::FLAlertLayer::create(nullptr, "Error", "OK", nullptr, "There was an error processing the number.")->show();
	}
	numberAs = min(100, max(0, numberAs));
	this->m_pSliderRef->setValue(static_cast<float>(numberAs) / 100.f);
	this->m_pSliderRef->m_pTouchLogic->getThumb()->activate();
	this->m_pSliderRef->updateBar();
	this->keyBackClicked();
}

void SetVolumenPopup::keyBackClicked() {
	gd::FLAlertLayer::keyBackClicked();
}


bool SetVolumenPopup::init(gd::Slider* m_pSliderRef) {
	if (!initWithColor({ 0, 0, 0, 105 })) return false;

	this->m_pSliderRef = m_pSliderRef;

	m_pLayer = cocos2d::CCLayer::create();
	m_pLayer->setPosition({ Utils::winSize().width / 2.f, Utils::winSize().height / 2.f });
	m_pLayer->setAnchorPoint({ 0.f, 0.f });
	this->addChild(m_pLayer);

	auto background = cocos2d::extension::CCScale9Sprite::create("GJ_square02.png");
	background->setContentSize({ 200.f, 100.f });
	m_pLayer->addChild(background);

	m_pButtonMenu = cocos2d::CCMenu::create();
	m_pButtonMenu->setPosition({ -98.f, 50.f });
	auto imageClose = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
	imageClose->setScale(0.7f);
	auto buttonExtraItem = gd::CCMenuItemSpriteExtra::create(imageClose, this, (cocos2d::SEL_MenuHandler)&SetVolumenPopup::onClose);
	m_pButtonMenu->addChild(buttonExtraItem);
	m_pLayer->addChild(m_pButtonMenu);

	auto titleLayer = cocos2d::CCLabelBMFont::create("- Set Value -", "goldFont.fnt");
	titleLayer->setScale(0.7f);
	titleLayer->setPositionY(35.f);
	m_pLayer->addChild(titleLayer);

	auto underline = cocos2d::CCSprite::createWithSpriteFrameName("floorLine_001.png");
	underline->setPosition({ 0.f, 18.f });
	underline->setScaleX(0.4f);
	underline->setScaleY(0.5f);
	underline->setOpacity(100);
	m_pLayer->addChild(underline);

	m_pButtonsMenu = cocos2d::CCMenu::create();
	m_pButtonsMenu->setPosition({ 0.f, 0.f });
	m_pLayer->addChild(m_pButtonsMenu, 1);

	auto buttonSetValue = gd::ButtonSprite::create("Set", 0xFC, false, "goldFont.fnt", "GJ_button_01.png", 30.f, 0.6f);
	m_pSetValueBtn = gd::CCMenuItemSpriteExtra::create(buttonSetValue, this, (cocos2d::SEL_MenuHandler)&SetVolumenPopup::onSet);
	m_pSetValueBtn->setPosition({ 48.f, -15.f });
	m_pButtonsMenu->addChild(m_pSetValueBtn);

	m_pBGInputTextValue = cocos2d::extension::CCScale9Sprite::create("square02_small.png");
	m_pBGInputTextValue->setContentSize({ 70.f, 30.f });
	m_pBGInputTextValue->setScale(1.f);
	m_pBGInputTextValue->setPosition({ -40.f, -14.f });
	m_pBGInputTextValue->setColor({ 255, 255, 255 });
	m_pBGInputTextValue->setOpacity(100);
	m_pLayer->addChild(m_pBGInputTextValue);

	m_pInputTextValue = gd::CCTextInputNode::create("Vol", this, "bigFont.fnt", 50.f, 20.f);
	m_pInputTextValue->setString(std::to_string(static_cast<int>(this->m_pSliderRef->getValue() * 100)));
	m_pInputTextValue->setLabelPlaceholderColor({ 0x75, 0xAA, 0xF0 });
	m_pInputTextValue->setMaxLabelLength(3);
	m_pInputTextValue->setAllowedChars("0123456789");
	m_pInputTextValue->setMaxLabelScale(0.7f);
	m_pInputTextValue->setPosition({ -41.f, -14.f });
	m_pInputTextValue->setDelegate(this);
	m_pLayer->addChild(m_pInputTextValue);

	auto perSymbol = cocos2d::CCLabelBMFont::create("%", "bigFont.fnt");
	perSymbol->setScale(0.6f);
	perSymbol->setPosition({ 9.f, -15.f });
	m_pLayer->addChild(perSymbol);

	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	this->setKeyboardEnabled(true);
	this->setMouseEnabled(true);
	this->registerWithTouchDispatcher();
	Utils::shareDirectorA()->getTouchDispatcher()->setForcePrio(true);
	Utils::shareDirectorA()->getTouchDispatcher()->incrementForcePrio(2);
	this->setTouchPriority(3);



	return true;
}

void SetVolumenPopup::keyDown(cocos2d::enumKeyCodes key) {
	switch (key) {
	case cocos2d::enumKeyCodes::KEY_Space:
		break;
	case cocos2d::enumKeyCodes::CONTROLLER_X:
		this->keyBackClicked();
		break;
	case cocos2d::enumKeyCodes::KEY_Left:
	case cocos2d::enumKeyCodes::CONTROLLER_Left:
		break;
	case cocos2d::enumKeyCodes::KEY_Right:
	case cocos2d::enumKeyCodes::CONTROLLER_Right:
		break;
	default:
		CCLayer::keyDown(key);
	}
}


MoreOptionsPauseLayer* MoreOptionsPauseLayer::create() {
	auto node = new MoreOptionsPauseLayer();
	if (node && node->init()) {
		node->autorelease();
	}
	else {
		CC_SAFE_DELETE(node);
	}
	return node;
}

bool MoreOptionsPauseLayer::init() {
	if (!initWithColor({ 0, 0, 0, 105 })) return false;

	m_pLayer = cocos2d::CCLayer::create();
	m_pLayer->setPosition({ Utils::winSize().width * -1.f, Utils::winSize().height / 2.f });
	this->addChild(m_pLayer);

	this->m_pBG = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png");
	this->m_pBG->setContentSize({ 250.f, 150.f });
	m_pLayer->addChild(this->m_pBG);


	m_pButtonMenu = cocos2d::CCMenu::create();
	m_pButtonMenu->setPosition({ -120.f, 75.f });
	auto imageClose = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
	imageClose->setScale(0.7f);
	auto buttonExtraItem = gd::CCMenuItemSpriteExtra::create(imageClose, this, (cocos2d::SEL_MenuHandler)&MoreOptionsPauseLayer::onClose);
	m_pButtonMenu->addChild(buttonExtraItem);
	m_pLayer->addChild(m_pButtonMenu);

	auto animationEntry = cocos2d::CCEaseElasticOut::create((cocos2d::CCActionInterval*)cocos2d::CCMoveTo::create(0.5f, { Utils::winSize().width / 2.f, Utils::winSize().height / 2.f }), 1.f);
	m_pLayer->runAction(cocos2d::CCSequence::create((cocos2d::CCFiniteTimeAction*)animationEntry, nullptr));

	this->m_pTitleLayer = cocos2d::CCLabelBMFont::create("- Settings -", "goldFont.fnt");
	this->m_pTitleLayer->setScale(0.7f);
	this->m_pTitleLayer->setPositionY(60.f);
	m_pLayer->addChild(this->m_pTitleLayer);

	this->m_pUnderLine = cocos2d::CCSprite::createWithSpriteFrameName("floorLine_001.png");
	this->m_pUnderLine->setPosition({ 0.f, 45.f });
	this->m_pUnderLine->setScaleX(0.5f);
	this->m_pUnderLine->setScaleY(0.8f);
	this->m_pUnderLine->setOpacity(100);
	m_pLayer->addChild(this->m_pUnderLine);

	this->m_pBGOptions = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png");
	this->m_pBGOptions->setContentSize({ 215.f, 100.f });
	this->m_pBGOptions->setPositionY(-11.f);
	this->m_pBGOptions->setColor({ 30, 30, 30 });
	this->m_pBGOptions->setOpacity((GLubyte)70);
	m_pLayer->addChild(this->m_pBGOptions);

	m_menuButtons = cocos2d::CCMenu::create();
	m_menuButtons->setPosition({ 0.f, 0.f });
	m_pLayer->addChild(m_menuButtons);

	auto imageButtonRealPauseSettings = cocos2d::CCSprite::createWithSpriteFrameName("GJ_pauseBtn_001.png");
	imageButtonRealPauseSettings->setPosition({ 175.f, 18.f});
	auto txtRealOptionsPause = cocos2d::CCLabelBMFont::create("Pause Options", "bigFont.fnt");
	txtRealOptionsPause->setScale(0.6f);
	txtRealOptionsPause->setAnchorPoint({ 0.f, 0.5f });
	txtRealOptionsPause->setPosition({ 7.f, 18.f });
	auto m_pBGRealOptionsPause = cocos2d::extension::CCScale9Sprite::create("GJ_button_01.png");
	m_pBGRealOptionsPause->setContentSize({ 180.f, 35.f });
	m_pBGRealOptionsPause->addChild(imageButtonRealPauseSettings);
	m_pBGRealOptionsPause->addChild(txtRealOptionsPause);
	auto m_pRealOptionsPause = gd::CCMenuItemSpriteExtra::create(m_pBGRealOptionsPause, this, (cocos2d::SEL_MenuHandler)&MoreOptionsPauseLayer::onOptionsPause);
	m_pRealOptionsPause->setPosition({ -5.f, 10.f });
	m_menuButtons->addChild(m_pRealOptionsPause);

	auto imageButtonSettings = cocos2d::CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
	imageButtonSettings->setPosition({ 175.f, 18.f });
	auto txtOptionGame = cocos2d::CCLabelBMFont::create("Game Options", "bigFont.fnt");
	txtOptionGame->setScale(0.6f);
	txtOptionGame->setAnchorPoint({ 0.f, 0.5f });
	txtOptionGame->setPosition({ 7.f, 18.f });
	auto m_pBGOptionsGamePause = cocos2d::extension::CCScale9Sprite::create("GJ_button_01.png");
	m_pBGOptionsGamePause->setContentSize({ 180.f, 35.f });
	m_pBGOptionsGamePause->addChild(imageButtonSettings);
	m_pBGOptionsGamePause->addChild(txtOptionGame);
	auto m_pOptionsGamePause = gd::CCMenuItemSpriteExtra::create(m_pBGOptionsGamePause, this, (cocos2d::SEL_MenuHandler)&MoreOptionsPauseLayer::onOptionsGame);
	m_pOptionsGamePause->setPosition({ -5.f, -35.f });
	m_menuButtons->addChild(m_pOptionsGamePause);


	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	this->setKeyboardEnabled(true);
	this->setMouseEnabled(true);
	this->registerWithTouchDispatcher();
	Utils::shareDirectorA()->getTouchDispatcher()->setForcePrio(true);
	Utils::shareDirectorA()->getTouchDispatcher()->incrementForcePrio(2);
	this->setTouchPriority(2);

	return true;
}

void MoreOptionsPauseLayer::keyBackClicked() {
	auto betterPause = static_cast<BetterPause*>(this->getParent());
	betterPause->pauseLayer->removeFromParentAndCleanup(true);
	Utils::shareDirectorA()->getRunningScene()->addChild(gd::PauseLayer::create(Utils::getplayLayerA()->m_level->levelType == gd::kGJLevelTypeEditor));
	gd::FLAlertLayer::keyBackClicked();
}

void MoreOptionsPauseLayer::onClose(cocos2d::CCObject* pSender) {
	keyBackClicked();
}

void MoreOptionsPauseLayer::keyDown(cocos2d::enumKeyCodes key) {
	switch (key) {
	case cocos2d::enumKeyCodes::KEY_Space:
		break;
	case cocos2d::enumKeyCodes::CONTROLLER_X:
		this->keyBackClicked();
		break;
	case cocos2d::enumKeyCodes::KEY_Left:
	case cocos2d::enumKeyCodes::CONTROLLER_Left:
		break;
	case cocos2d::enumKeyCodes::KEY_Right:
	case cocos2d::enumKeyCodes::CONTROLLER_Right:
		break;
	default:
		CCLayer::keyDown(key);
	}
}

void MoreOptionsPauseLayer::onOptionsGame(cocos2d::CCObject* pSender) {
	gd::OptionsLayer::addToCurrentScene();
}

void MoreOptionsPauseLayer::onOptionsPause(cocos2d::CCObject* pSender) {
	auto dropDown = PauseSettingsLayer::create();
	this->addChild(dropDown);
	dropDown->setPosition(0.0f, 0.0f);
	dropDown->showLayer(false);
}

PauseSettingsLayer* PauseSettingsLayer::create() {
	auto node = new PauseSettingsLayer();
	if (node && node->init("Pause Settings", 220.0f)) {
		node->autorelease();
	}
	else {
		CC_SAFE_DELETE(node);
	}
	return node;
}

void PauseSettingsLayer::customSetup() {

	m_pSwitchPause = HorizontalList::create(BetterPauseManager::sharedState()->m_pSwitchPause);
	m_pSwitchPause->setPosition(80.f, 85.f);
	m_pLayer->addChild(m_pSwitchPause);

	m_menuButtons = cocos2d::CCMenu::create();
	m_pLayer->addChild(m_menuButtons);

	auto txtSwitchPause = cocos2d::CCLabelBMFont::create("Pause Mode: ", "goldFont.fnt");
	txtSwitchPause->setAnchorPoint({ 0.f, 0.5f });
	txtSwitchPause->setPosition({ Utils::winSize().width / 2.f - 165.f, Utils::winSize().height / 2.f + 88.f });
	txtSwitchPause->setScale(0.6f);
	m_pLayer->addChild(txtSwitchPause);

	m_pSwitchQuest = HorizontalList::create(BetterPauseManager::sharedState()->m_pSwitchQuest);
	m_pSwitchQuest->setPosition(80.f, 60.f);
	m_pLayer->addChild(m_pSwitchQuest);

	auto txtSwitchQuest = cocos2d::CCLabelBMFont::create("Quest: ", "goldFont.fnt");
	txtSwitchQuest->setAnchorPoint({ 0.f, 0.5f });
	txtSwitchQuest->setPosition({ Utils::winSize().width / 2.f - 165.f, Utils::winSize().height / 2.f + 58.f });
	txtSwitchQuest->setScale(0.6f);
	m_pLayer->addChild(txtSwitchQuest);

	m_pSwitchButtonsPos = HorizontalList::create(BetterPauseManager::sharedState()->m_pSwitchButtonsPos);
	m_pSwitchButtonsPos->setPosition(80.f, 30.f);
	m_pLayer->addChild(m_pSwitchButtonsPos);
	
	auto txtSwitchButtonsPos = cocos2d::CCLabelBMFont::create("Buttons Pos: ", "goldFont.fnt");
	txtSwitchButtonsPos->setAnchorPoint({ 0.f, 0.5f });
	txtSwitchButtonsPos->setPosition({ Utils::winSize().width / 2.f - 165.f, Utils::winSize().height / 2.f + 28.f });
	txtSwitchButtonsPos->setScale(0.6f);
	m_pLayer->addChild(txtSwitchButtonsPos);

	auto txtSelectQuickSettings = cocos2d::CCLabelBMFont::create("Select Quick Settings: ", "goldFont.fnt");
	txtSelectQuickSettings->setAnchorPoint({ 0.f, 0.5f });
	txtSelectQuickSettings->setPosition({ Utils::winSize().width / 2.f - 165.f, Utils::winSize().height / 2.f - 2.f });
	txtSelectQuickSettings->setScale(0.5f);
	m_pLayer->addChild(txtSelectQuickSettings);

	auto txtSelectQuickPause = cocos2d::CCLabelBMFont::create("Select", "goldFont.fnt");
	txtSelectQuickPause->setAnchorPoint({ 0.5f, 0.5f });
	txtSelectQuickPause->setPosition({ 73.f, 17.f });
	auto m_pBGSelectQuickPause = cocos2d::extension::CCScale9Sprite::create("GJ_button_01.png");
	m_pBGSelectQuickPause->setContentSize({ 150.f, 30.f });
	m_pBGSelectQuickPause->addChild(txtSelectQuickPause);
	m_pBGSelectQuickPause->setScale(0.8f);
	auto m_pRealOptionsPause = gd::CCMenuItemSpriteExtra::create(m_pBGSelectQuickPause, this, (cocos2d::SEL_MenuHandler)&PauseSettingsLayer::onSelectQuickSettings);
	m_pRealOptionsPause->setPosition({ 80.f, -2.f });
	m_menuButtons->addChild(m_pRealOptionsPause);
	
}

void PauseSettingsLayer::onSelectQuickSettings(cocos2d::CCObject*) {
	SelectQuickSettings::create()->show();
}

void PauseSettingsLayer::exitLayer(cocos2d::CCObject*) {
	this->setKeypadEnabled(false);
	Utils::shareDirectorA()->getTouchDispatcher()->setForcePrio(false);
	this->disableUI();
	this->hideLayer(false);
}

//ListData
ListData::ListData(const char* title, unsigned int length) {
	m_sTitle = title;
	m_uMaxLength = length;
	m_uLength = 0;
	m_uOffset = 0;
	m_uIndex = 0;
}

//HorizontalList
bool HorizontalList::init() {
	m_pLabels = new cocos2d::CCLabelBMFont*[m_pData.m_uMaxLength];

	m_pMenu = cocos2d::CCMenu::create();
	this->addChild(m_pMenu);

	auto upBtn = gd::CCMenuItemSpriteExtra::create(
		cocos2d::CCSprite::createWithSpriteFrameName("edit_rightBtn_001.png"),
		this,
		(cocos2d::SEL_MenuHandler)(&HorizontalList::navigate)
	);
	upBtn->setTag(kListUpBtn);
	upBtn->setPosition(m_obPosition.x - 70.0f, m_obPosition.y);
	upBtn->setRotation(180.0f);
	m_pMenu->addChild(upBtn);

	auto downBtn = gd::CCMenuItemSpriteExtra::create(
		cocos2d::CCSprite::createWithSpriteFrameName("edit_rightBtn_001.png"),
		this,
		(cocos2d::SEL_MenuHandler)(&HorizontalList::navigate)
	);
	downBtn->setTag(kListDownBtn);
	downBtn->setPosition(m_obPosition.x + 70.0f, m_obPosition.y);
	m_pMenu->addChild(downBtn);

	//verify offset
	if (!m_pData.m_vEntries.empty() && m_pData.m_uOffset > m_pData.m_vEntries.size() - 1)
		m_pData.m_uOffset = m_pData.m_vEntries.size() - 1;
	else if (m_pData.m_uOffset < 0)
		m_pData.m_uOffset = 0;

	this->getLength();

	if (m_pData.m_uLength != 0) {
		m_pLabels[0] = cocos2d::CCLabelBMFont::create(m_pData.m_vEntries[m_pData.m_uOffset].c_str(), "bigFont.fnt");
		m_pLabels[0]->setPosition(m_obPosition.x, m_obPosition.y);
		m_pLabels[0]->limitLabelWidth(90.0f, 0.8f, 0.0f);
		m_pMenu->addChild(m_pLabels[0]);
	}

	return true;
}

void HorizontalList::updateList() {
	this->getLength();

	if (m_pData.m_uLength != 0) {
		m_pLabels[0]->setString(m_pData.m_vEntries[m_pData.m_uOffset].c_str());
		m_pLabels[0]->limitLabelWidth(90.0f, 0.8f, 0.0f);
	}
}

void HorizontalList::navigate(cocos2d::CCObject* btn) {
	if (!m_pData.m_vEntries.empty()) {
		if (btn->getTag() == kListUpBtn) {
			if (m_pData.m_uOffset != 0)
				--m_pData.m_uOffset;
			else
				m_pData.m_uOffset = m_pData.m_vEntries.size() - 1;
		}
		else if (btn->getTag() == kListDownBtn) {
			if (m_pData.m_uOffset < m_pData.m_vEntries.size() - 1)
				++m_pData.m_uOffset;
			else
				m_pData.m_uOffset = 0;
		}

		this->updateList();
	}
}

HorizontalList* HorizontalList::create(ListData& data) {
	HorizontalList* pRet = new HorizontalList(data);
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

void HorizontalList::setPosition(float x, float y) {
	m_obPosition = ccp(x, y);
	//this->updateList();
}

SelectQuickSettings* SelectQuickSettings::create() {
	auto node = new SelectQuickSettings();
	if (node && node->init()) {
		node->autorelease();
	}
	else {
		CC_SAFE_DELETE(node);
	}
	return node;
}

bool SelectQuickSettings::init() {
	if (!initWithColor({ 0, 0, 0, 105 })) return false;

	m_pLayer = cocos2d::CCLayer::create();
	this->addChild(m_pLayer);

	this->m_pBG = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png");
	this->m_pBG->setPosition({ Utils::winSize().width / 2.f, Utils::winSize().height / 2.f });
	this->m_pBG->setContentSize({ 440.f, 290.f });
	m_pLayer->addChild(this->m_pBG);

	m_pButtonMenu = cocos2d::CCMenu::create();
	m_pButtonMenu->setPosition({ Utils::winSize().width / 2.f - 210.f, Utils::winSize().height / 2 + 140.f });
	auto imageClose = cocos2d::CCSprite::createWithSpriteFrameName("GJ_backBtn_001.png");
	auto buttonExtraItem = gd::CCMenuItemSpriteExtra::create(imageClose, this, (cocos2d::SEL_MenuHandler)&MoreOptionsPauseLayer::onClose);
	m_pButtonMenu->addChild(buttonExtraItem);
	m_pLayer->addChild(m_pButtonMenu);

	this->m_pTitleLayer = cocos2d::CCLabelBMFont::create("- Select Quick Settings -", "bigFont.fnt");
	this->m_pTitleLayer->setScale(0.7f);
	this->m_pTitleLayer->setPosition({ Utils::winSize().width / 2.f, Utils::winSize().height / 2.f + 120.f });
	m_pLayer->addChild(this->m_pTitleLayer);

	this->m_pUnderLine = cocos2d::CCSprite::createWithSpriteFrameName("floorLine_001.png");
	this->m_pUnderLine->setPosition({ Utils::winSize().width / 2.f, Utils::winSize().height / 2.f + 100.f });
	this->m_pUnderLine->setScaleX(0.5f);
	this->m_pUnderLine->setScaleY(0.8f);
	this->m_pUnderLine->setOpacity(100);
	m_pLayer->addChild(this->m_pUnderLine);

	auto arrayList = cocos2d::CCArray::create();

	auto mlt = gd::MoreOptionsLayer::create();
	mlt->keyBackClicked();
	CC_SAFE_DELETE(mlt);

	auto menu = cocos2d::CCMenu::create();
	auto nameList = cocos2d::CCLabelBMFont::create("Progress Bar", "bigFont.fnt");
	auto btnSelect = gd::CCMenuItemToggler::createWithStandardSprites(this, (cocos2d::SEL_MenuHandler)&SelectQuickSettings::onToggleWithGameVariable, 0.6f);
	for (int j = 0; j < 6; j++) { // Recorremos el arreglo posQuickA
		if (-2 == sharedStateBP().posQuickA[j]) {
			btnSelect->toggle(true);
		}
	}
	//btnSelect->toggle(Utils::shareManager()->getGameVariable(key));
	btnSelect->setTag(-2);
	btnSelect->setPosition({ 315.f, 15.f });

	nameList->setPosition({ 10.f, 15.f });
	nameList->setAnchorPoint({ 0.f, 0.5f });

	menu->addChild(nameList);
	menu->addChild(btnSelect);
	nameList->limitLabelWidth(200.f, 0.5f, 0.1f);

	arrayList->addObject(menu);

	m_toggles.push_back(btnSelect);


	for (size_t i = 0; i < BetterPause::quickSettings_Name.size(); i++)
	{
		auto menu = cocos2d::CCMenu::create();
		auto nameList = cocos2d::CCLabelBMFont::create(BetterPause::quickSettings_Name[i].c_str(), "bigFont.fnt");
		auto btnSelect = gd::CCMenuItemToggler::createWithStandardSprites(this, (cocos2d::SEL_MenuHandler)&SelectQuickSettings::onToggleWithGameVariable, 0.6f);
		for (int j = 0; j < 6; j++) { // Recorremos el arreglo posQuickA
			if (i == sharedStateBP().posQuickA[j]) {
				btnSelect->toggle(true);
			}
		}
		//
		btnSelect->setTag(i);
		btnSelect->setPosition({ 315.f, 15.f });
		//auto buttonButton = gd::CCMenuItemSpriteExtra::create(gd::ButtonSprite::create("View", (int)(90 * 0.5), true, "bigFont.fnt", "GJ_button_01.png", 44 * 0.6f, 0.5f), menu, nullptr);

		nameList->setPosition({ 10.f, 15.f });
		nameList->setAnchorPoint({ 0.f, 0.5f });
		//buttonButton->setPosition({ 300.f, 26.f });

		menu->addChild(nameList);
		menu->addChild(btnSelect);
		m_toggles.push_back(btnSelect);
		nameList->limitLabelWidth(200.f, 0.5f, 0.1f);

		//menu->addChild(buttonButton);

		arrayList->addObject(menu);
	}

	

	auto CustomVi = ListView::create(arrayList);

	auto gjCommentBase = gd::GJCommentListLayer::create(CustomVi, { 0,0,0 }, 340.f, 200.f, 0);
	gjCommentBase->setPosition({ Utils::winSize().width / 2.f - 165.f, Utils::winSize().height / 2.f - 120.f });
	m_pLayer->addChild(gjCommentBase);



	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	this->setKeyboardEnabled(true);
	this->setMouseEnabled(true);
	this->registerWithTouchDispatcher();
	Utils::shareDirectorA()->getTouchDispatcher()->setForcePrio(true);
	Utils::shareDirectorA()->getTouchDispatcher()->incrementForcePrio(2);
	this->setTouchPriority(2);

	return true;
}

void SelectQuickSettings::onToggleWithGameVariable(CCObject* pSender) {
	int count = 0;

	for (auto buttonToggle : m_toggles) {
		if (buttonToggle->isToggled()) {
			count++;
		}
	}

	if (reinterpret_cast<gd::CCMenuItemToggler*>(pSender)->isToggled()) {
		count--;
	}
	else {
		count++;
	}

	std::cout << count << "\t" << reinterpret_cast<gd::CCMenuItemToggler*>(pSender)->isToggled() << std::endl;

	if (count > 6) {
		gd::FLAlertLayer::create(
			nullptr,
			"Maximum Exceeded",
			"OK",
			nullptr,
			"You've exceeded the maximum number of quick settings."
		)->show();
		reinterpret_cast<gd::CCMenuItemToggler*>(pSender)->toggle(true);
	}

	if (count < 3) {
		gd::FLAlertLayer::create(
			nullptr,
			"Minimum Not Met",
			"OK",
			nullptr,
			"You haven't met the minimum number of quick settings."
		)->show();
		reinterpret_cast<gd::CCMenuItemToggler*>(pSender)->toggle(false);
	}
}


void SelectQuickSettings::keyBackClicked() {
	/*auto betterPause = static_cast<BetterPause*>(this->getParent());
	betterPause->pauseLayer->removeFromParentAndCleanup(true);
	Utils::shareDirectorA()->getRunningScene()->addChild(gd::PauseLayer::create(Utils::getplayLayerA()->m_level->levelType == gd::kGJLevelTypeEditor));*/

	for (int j = 0; j < 6; j++) { // Recorremos el arreglo posQuickA
		sharedStateBP().posQuickA[j] = -1;
	}

	int count = 0;

	for (size_t i = 0; i < m_toggles.size(); i++)
	{
		auto buttonToggle = m_toggles[i];
		if (buttonToggle->isToggled()) {
			sharedStateBP().posQuickA[count] = m_toggles[i]->getTag();
			count++;
		}
	}
	sharedStateBP().SaveSettings();
	gd::FLAlertLayer::keyBackClicked();
}

void SelectQuickSettings::onClose(cocos2d::CCObject* pSender) {
	keyBackClicked();
}

void SelectQuickSettings::keyDown(cocos2d::enumKeyCodes key) {
	switch (key) {
	case cocos2d::enumKeyCodes::KEY_Space:
		break;
	case cocos2d::enumKeyCodes::CONTROLLER_X:
		this->keyBackClicked();
		break;
	case cocos2d::enumKeyCodes::KEY_Left:
	case cocos2d::enumKeyCodes::CONTROLLER_Left:
		break;
	case cocos2d::enumKeyCodes::KEY_Right:
	case cocos2d::enumKeyCodes::CONTROLLER_Right:
		break;
	default:
		CCLayer::keyDown(key);
	}
}


GenericListCell::GenericListCell(const char* name, cocos2d::CCSize size) :
	TableViewCell(name, size.width, size.height) {}

void GenericListCell::draw() {
	reinterpret_cast<gd::StatsCell*> (this)->gd::StatsCell::draw();
}

GenericListCell* GenericListCell::create(const char* key, cocos2d::CCSize size) {
	auto pRet = new GenericListCell(key, size);
	if (pRet) {
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

void GenericListCell::updateBGColor(int index) {
	if (index & 1) m_pBGLayer->setColor(cocos2d::ccc3(0xc2, 0x72, 0x3e));
	else m_pBGLayer->setColor(cocos2d::ccc3(0xa1, 0x58, 0x2c));
	m_pBGLayer->setOpacity(0xff);
}

cocos2d::CCRect ListView::calculateNodeCoverage(cocos2d::CCArray* nodes) {
	cocos2d::CCRect coverage;
	CCObject* childObj;
	CCARRAY_FOREACH(nodes, childObj) {
		CCNode* child = dynamic_cast<CCNode*>(childObj);
		if (child == nullptr) continue;

		auto contentSize = child->getScaledContentSize();
		contentSize.width *= child->getAnchorPoint().x;
		contentSize.height *= child->getAnchorPoint().y;
		auto pos = child->getPosition() - contentSize;

		contentSize = child->getScaledContentSize();
		auto contentPoint = cocos2d::CCPoint{ 1.f, 1.f } - child->getAnchorPoint();
		contentSize.width *= contentPoint.x;
		contentSize.height *= contentPoint.y;

		auto csize = child->getPosition() + contentSize;
		if (pos.x < coverage.origin.x) {
			coverage.origin.x = pos.x;
		}
		if (pos.y < coverage.origin.y) {
			coverage.origin.y = pos.y;
		}
		if (csize.x > coverage.size.width) {
			coverage.size.width = csize.x;
		}
		if (csize.y > coverage.size.height) {
			coverage.size.height = csize.y;
		}
	}
	return coverage;
}

void ListView::setupList() {
	this->m_fItemSeparation = 30.f;

	this->m_pTableView->reloadData();

	auto coverage = calculateNodeCoverage(m_pTableView->m_pContentLayer->getChildren());
	if (this->m_pEntries->count() > 4)
		m_pTableView->m_pContentLayer->setContentSize({ -coverage.origin.x + coverage.size.width, -coverage.origin.y + coverage.size.height });

	this->m_pTableView->moveToTop();

	if (this->m_pEntries->count() == 1)
		this->m_pTableView->moveToTopWithOffset(this->m_fItemSeparation);

}

gd::TableViewCell* ListView::getListCell(const char* key) {
	return GenericListCell::create(key, { this->m_fWidth, 30.f });
}

void ListView::loadCell(gd::TableViewCell* cell, unsigned int index) {
	auto node = dynamic_cast<CCNode*>(m_pEntries->objectAtIndex(index));
	if (node) {
		auto lcell = static_cast<GenericListCell*>(cell);
		node->setContentSize(lcell->getScaledContentSize());
		node->setPosition(0, 0);
		lcell->addChild(node);
		lcell->updateBGColor(index);
	}
}

ListView* ListView::create(cocos2d::CCArray* items, float itemHeight, float width, float height) {
	auto ret = new ListView();
	if (ret) {
		ret->m_fItemSeparation = itemHeight;
		if (ret->init(items, 0x420, width, height)) {
			ret->autorelease();
			return ret;
		}
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

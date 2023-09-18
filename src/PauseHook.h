#include "pch.h"
#include "Utils.h"
#include "gdstring.h"
#include "BetterPause.h"
#include "BetterPauseManager.h"

class PauseLayerHook : public gd::PauseLayer {
public:

	static gd::PauseLayer* createHook(bool isEditor) {
		auto ret = matdash::orig<&PauseLayerHook::createHook, matdash::Thiscall>(isEditor);
		if (BetterPauseManager::sharedState()->m_pSwitchPause.m_uOffset == 0) {
			for (size_t i = 1; i < ret->getChildrenCount(); i++)
			{
				auto node = dynamic_cast<cocos2d::CCNode*>(ret->getChildren()->objectAtIndex(i));
				if (node) {
					node->setVisible(false);
				}
			}	
		}


		auto betterPauseMenu = BetterPause::create(ret, isEditor, BetterPauseManager::sharedState()->m_pSwitchPause.m_uOffset == 0);
		ret->addChild(betterPauseMenu, 100);
		
		return ret;
	}

	void customSetupHook() {
		matdash::orig<&PauseLayerHook::customSetupHook, matdash::Thiscall>(this);
	}

	void musicSliderChangedHook(cocos2d::CCObject* pSender) {
		matdash::orig<&PauseLayerHook::musicSliderChangedHook, matdash::Thiscall>(this, pSender);

	}

	void sfxSliderChangedHook(cocos2d::CCObject* pSender) {
		matdash::orig<&PauseLayerHook::sfxSliderChangedHook, matdash::Thiscall>(this, pSender);

	}

	void createToggleButtonHook(cocos2d::SEL_MenuHandler callback, bool on,
		cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos) {
		BetterPause::pauseLayer_MenuToggles = menu;
		BetterPause::pauseLayer_lastPoint = pos;

		matdash::orig<&PauseLayerHook::createToggleButtonHook, matdash::Thiscall>(this, callback,
			on, menu, caption, pos);
		return;

		auto toggleButton = gd::CCMenuItemToggler::createWithStandardSprites(this, callback, 0.6f);
		toggleButton->toggle(on);
		toggleButton->setSizeMult(0.6f);
		toggleButton->setPosition(menu->convertToNodeSpace(pos));
		if (menu) {
			menu->addChild(toggleButton);
		}

		auto text = cocos2d::CCLabelBMFont::create(caption.c_str(), "bigFont.fnt");
		text->limitLabelWidth(150.f, 0.4f, 0.1f);
		text->setAlignment(cocos2d::kCCTextAlignmentRight);
		text->setPosition(pos);
		text->setPositionX(pos.x - 15.f);
		text->setAnchorPoint({ 1.f, 0.5f });
		this->addChild(text);
	}
};

class ChallengeNodeHook : public gd::ChallengeNode {
public:
	void onClaimRewardA(cocos2d::CCObject* pSender) {
		m_pChallengesPage->setScale(1.f);
		m_pChallengesPage->setPosition({ 0, 0 });
		matdash::orig<&ChallengeNodeHook::onClaimRewardA, matdash::Thiscall>(this, pSender);
		if (Utils::getplayLayerA()) {
			m_pChallengesPage->setScale(0.7f);
			m_pChallengesPage->setPosition({ (Utils::winSize().width / 2) - 150.f, -50.f });//140.f, -40.f
		}
	}
};
class AppDelegateHook : public gd::AppDelegate {
public:

	void trySaveGameH() {
		BetterPauseManager::sharedState()->save();
		matdash::orig<&AppDelegateHook::trySaveGameH, matdash::Thiscall>(this);
	}



};


float getDownloadProgress(cocos2d::CCNode* self, int key) {
	auto ret =  matdash::orig<&getDownloadProgress, matdash::Thiscall>(self, key);
	std::cout << Utils::getNameObj(self) << "	" << ret << "  " << key << std::endl;
	return ret;
}


class CustomSongWidgetHook : public gd::CustomSongWidget {
public:

	void updateSongInfoHook() {
		auto scaleSafe = this->getScale();
		std::cout << scaleSafe << std::endl;
		if (Utils::getplayLayerA() && Utils::getplayLayerA()->m_bIsPaused) {
			this->setScale(1.f);
		}
		matdash::orig<&CustomSongWidgetHook::updateSongInfoHook, matdash::Thiscall>(this);
		if (Utils::getplayLayerA() && Utils::getplayLayerA()->m_bIsPaused) {
			this->setScale(scaleSafe);
		}
	}

};


bool CurrencyRewardLayer_init(gd::CurrencyRewardLayer* self, void* param_1_00, void* param_1, void* param_2, void* param_3, void* param_4, void* param_5,
	void* param_6, void* param_7, void* param_8, void* param_9, void* p10) {



	if(!matdash::orig<&CurrencyRewardLayer_init, matdash::Thiscall>(self, param_1_00, param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9, p10))return false;
	
	for (size_t i = 0; i < self->getChildrenCount(); i++)
	{
		self->getChildren()->objectAtIndex(i)->setTag(i);
	}

	auto node = static_cast<cocos2d::CCNode*>(self->getChildren()->objectAtIndex(2));
	if (node) {
		node->setPositionX(node->getPositionX() - 61.f);
		float desiredY = Utils::winSize().height + 170.f;
		auto localPosition = node->getParent()->convertToNodeSpace(ccp(0, desiredY));
		node->setPositionY(localPosition.y);
	}
	
	
	return true;
}


void MoreOptionsLayer_addToggle(gd::MoreOptionsLayer* self, const char* name, const char* key, const char* info) {
	std::string name_push = name == nullptr ? "" : name;
	std::string key_push = key == nullptr ? "" : key;
	std::string info_push = info == nullptr ? "" : info;

	matdash::orig<&MoreOptionsLayer_addToggle, matdash::Thiscall>(self, name, key, info);

	BetterPause::quickSettings_Name.push_back(name_push);
	BetterPause::quickSettings_Desc.push_back(info_push);
	BetterPause::quickSettings_Key.push_back(key_push);
}


bool MoreOptionsLayer_init(gd::MoreOptionsLayer* self) {

	BetterPause::quickSettings_Name.clear();
	BetterPause::quickSettings_Desc.clear();
	BetterPause::quickSettings_Key.clear();

	if (!matdash::orig<&MoreOptionsLayer_init, matdash::Thiscall>(self)) return false;

	return true;
}
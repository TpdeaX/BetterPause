#include "pch.h"
#include "Utils.h"
#include "gdstring.h"
#include "BetterPause.h"

class PauseLayerHook : public gd::PauseLayer {
public:

	static gd::PauseLayer* createHook(bool isEditor) {
		auto ret = matdash::orig<&PauseLayerHook::createHook, matdash::Thiscall>(isEditor);
		auto betterPauseMenu = BetterPause::create(ret, isEditor);
		ret->addChild(betterPauseMenu);
		return ret;
	}

	void customSetupHook() {
		matdash::orig<&PauseLayerHook::customSetupHook, matdash::Thiscall>(this);
		for (size_t i = 1; i < this->getChildrenCount(); i++)
		{
			auto node = dynamic_cast<cocos2d::CCNode*>(this->getChildren()->objectAtIndex(i));
			if (node) {
				node->setVisible(false);
			}
		}
	}

	void musicSliderChangedHook(cocos2d::CCObject* pSender) {
		matdash::orig<&PauseLayerHook::musicSliderChangedHook, matdash::Thiscall>(this, pSender);

	}

	void sfxSliderChangedHook(cocos2d::CCObject* pSender) {
		matdash::orig<&PauseLayerHook::sfxSliderChangedHook, matdash::Thiscall>(this, pSender);

	}

	void createToggleButtonHook(cocos2d::SEL_MenuHandler callback, bool on,
		cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos) {
		//matdash::orig<&BetterPause::createToggleButtonHook, matdash::Thiscall>(this, callback,
			//on, menu, caption, pos);
		//return;
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
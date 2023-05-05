#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include <gd.h>

namespace gd {

	class CCBlockLayer;

	class GDH_DLL PauseLayer : public CCBlockLayer {
	public:
		bool m_bUnknown;
		bool m_bUnknown2;
		int a;
		int b;
		cocos2d::CCNode* c;

		static PauseLayer* create(bool isEditor) {
			return reinterpret_cast<PauseLayer*(__thiscall*)(bool)>(
				base + 0x1E4570
				)(isEditor);
		}

		virtual void customSetup() {
			reinterpret_cast<void(__thiscall*)(PauseLayer*)>(
				base + 0x1E4620
				)(this);	
		}

		static PauseLayer* addToCurrentScene(bool isEditor) {
			auto layer = PauseLayer::create(isEditor);
			cocos2d::CCDirector::sharedDirector()
				->getRunningScene()
				->addChild(layer);
			layer->customSetup();
			return layer;
		}

		void createToggleButton(cocos2d::SEL_MenuHandler callback, bool on,
			cocos2d::CCMenu* menu, std::string caption, cocos2d::CCPoint pos) {
			return reinterpret_cast<void(__thiscall*)(PauseLayer*, cocos2d::SEL_MenuHandler,
				bool, cocos2d::CCMenu*, std::string, cocos2d::CCPoint)>(
					base + 0x1E5570
					)(this, callback, on, menu, caption, pos);
		}

		void musicSliderChanged(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(PauseLayer*, cocos2d::CCObject*)>(
				base + 0x1e5ce0
			)(this, pSender);
		}

		void sfxSliderChanged(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(PauseLayer*, cocos2d::CCObject*)>(
				base + 0x1ddfa0
			)(this, pSender);
		}

		void onPracticeMode(bool m_isPracticeMode, cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(m_isPracticeMode ? gd::base + 0x1E5F60 : gd::base + 0x1E5F30)(this, sender);
		}

		void onPracticeModeEnabled(cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(gd::base + 0x1E5F30)(this, sender);
		}
		void onPracticeModeDisabled(cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(gd::base + 0x1E5F60)(this, sender);
		}

		static void onPracticeModeWS(gd::PauseLayer* layer, bool m_isPracticeMode, cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(m_isPracticeMode ? gd::base + 0x1E5F60 : gd::base + 0x1E5F30)(layer, sender);
		}

		void onRestart(cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(gd::base + 0x1E6040)(this, sender);
		}

		static void onMenuWS(cocos2d::CCNode* self, cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(cocos2d::CCNode*, cocos2d::CCObject*)>(gd::base + 0x1E63D0)(self, pSender);
		}

		void onResume(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(cocos2d::CCNode*, cocos2d::CCObject*)>(gd::base + 0x1e5fa0)(this, pSender);
		}

		void onQuit(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(cocos2d::CCNode*, cocos2d::CCObject*)>(gd::base + 0x1e63d0)(this, pSender);
		}

		void onEdit(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(cocos2d::CCNode*, cocos2d::CCObject*)>(gd::base + 0x1e60e0)(this, pSender);
		}

		void onAutoRetry(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(gd::base + 0x1E5EA0)(this, pSender);
		}

		void onAutoCheckpoints(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(gd::base + 0x1E5E10)(this, pSender);
		}

		void onProgressBar(cocos2d::CCObject* pSender) {
			reinterpret_cast<void(__thiscall*)(gd::PauseLayer*, cocos2d::CCObject*)>(gd::base + 0x1E64E0)(this, pSender);
		}
	};

	class GDH_DLL CurrencyRewardLayer : public cocos2d::CCLayer {
	public:
		inline CurrencyRewardLayer() {}
		~CurrencyRewardLayer() {
			reinterpret_cast<CurrencyRewardLayer(__thiscall*)(gd::CurrencyRewardLayer*)>(gd::base + 0x4FFB0)(this);
		} 
		virtual void update(float dt) {
			reinterpret_cast<void(__thiscall*)(gd::CurrencyRewardLayer*, float)>(gd::base + 0x52350)(this, dt);
		}
	};

}

#endif
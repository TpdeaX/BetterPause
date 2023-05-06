
#ifndef __FLALERTLAYER_H__
#define __FLALERTLAYER_H__

#include <gd.h>

namespace gd {

	class FLAlertLayerProtocol;
	class ButtonSprite;
	class ScrollingLayer;

#pragma runtime_checks("s", off)
	class FLAlertLayer : public cocos2d::CCLayerColor {
	public:
		cocos2d::CCMenu* m_pButtonMenu;
		int m_nControlConnected; //?
		cocos2d::CCObject* m_pTarget;
		cocos2d::CCObject* m_pParent;
		PAD(4);
		cocos2d::CCLayer* m_pLayer;
		int m_nZOrder2;
		bool m_bNoElasticity;
		cocos2d::ccColor3B m_cColor2; //?
		ButtonSprite* m_pButton1;
		ButtonSprite* m_pButton2;
		ScrollingLayer* m_pScrollingLayer;
		int m_nJoystickConnected;
		bool m_bBorder; //?
		bool m_bNoAction; //?

	public:

		//CCNode vtable
		virtual void onEnter() {
			return reinterpret_cast<void(__thiscall*)(FLAlertLayer*)>(
				base + 0x23750
				)(this);
		}
		virtual void registerWithTouchDispatcher() {
			return reinterpret_cast<void(__thiscall*)(FLAlertLayer*)>(
				base + 0x236F0
				)(this);
		}

		//CCTouchDelegate vtable
		virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
			return reinterpret_cast<bool(__thiscall*)(char*, cocos2d::CCTouch*, cocos2d::CCEvent*)>(
				base + 0x233C0
				)(reinterpret_cast<char*>(this) + 0xEC, pTouch, pEvent);
		}
		virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
			return reinterpret_cast<void(__thiscall*)(char*, cocos2d::CCTouch*, cocos2d::CCEvent*)>(
				base + 0x23510
				)(reinterpret_cast<char*>(this) + 0xEC, pTouch, pEvent);
		}
		virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
			return reinterpret_cast<void(__thiscall*)(char*, cocos2d::CCTouch*, cocos2d::CCEvent*)>(
				base + 0x23450
				)(reinterpret_cast<char*>(this) + 0xEC, pTouch, pEvent);
		}
		virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
			return reinterpret_cast<void(__thiscall*)(char*, cocos2d::CCTouch*, cocos2d::CCEvent*)>(
				base + 0x234C0
				)(reinterpret_cast<char*>(this) + 0xEC, pTouch, pEvent);
		}

		//CCKeyboardDelegate vtable
		virtual void keyDown(cocos2d::enumKeyCodes key) {
			return reinterpret_cast<void(__thiscall*)(FLAlertLayer*, cocos2d::enumKeyCodes)>(
				base + 0x23250
				)(this, key);
		}

		//CCKeypadDelegate vtable
		virtual void keyBackClicked() {
			return reinterpret_cast<void(__thiscall*)(char*)>(
				base + 0x232C0
				)(reinterpret_cast<char*>(this) + 0xF4);
		}

		//vtable
		virtual void show() {
			return reinterpret_cast<void(__thiscall*)(FLAlertLayer*)>(
				base + 0x23560
				)(this);
		}
		FLAlertLayer() {
			reinterpret_cast<void(__thiscall*)(FLAlertLayer*)>(
				base + 0x224B0
				)(this);
		}

		void onBtn1(cocos2d::CCObject* btn) {
			return reinterpret_cast<void(__thiscall*)(FLAlertLayer*, cocos2d::CCObject*)>(
				base + 0x23340
				)(this, btn);
		}
		void onBtn2(cocos2d::CCObject* btn) {
			return reinterpret_cast<void(__thiscall*)(FLAlertLayer*, cocos2d::CCObject*)>(
				base + 0x23380
				)(this, btn);
		}
		void onClose(cocos2d::CCObject* btn) {
			return reinterpret_cast<void(__thiscall*)(FLAlertLayer*, cocos2d::CCObject*)>(
				base + 0x49C60
				)(this, btn);
		}
		/*FLAlertLayer supports colors of text for the caption. wrap desired text in "<cx></c>"
			* where x is the color desired. colors are:
			* r - red
			* l - lime
			* g - green
			* y - yellow
			* o - orange
			* and more that i'm too lazy to find.
			* MAKE SURE YOU FOLLOW THIS FORMAT. ROB'S PARSING CAN AND WILL MESS UP OTHERWISE.
			*/
		static FLAlertLayer* create(FLAlertLayerProtocol* target, const char* title,
			const char* btn1, const char* btn2, std::string caption) {
			auto pRet = reinterpret_cast<FLAlertLayer * (__fastcall*)(FLAlertLayerProtocol*, const char*,
				const char*, const char*, std::string)>(
					base + 0x22680
					)(target, title, btn1, btn2, caption);
			//clean stack.
			__asm add esp, 0x20
			return pRet;
		}
		static FLAlertLayer* create(FLAlertLayerProtocol* target, const char* title,
			const char* btn1, const char* btn2, float width, std::string caption) {
			auto pRet = reinterpret_cast<FLAlertLayer * (__fastcall*)(FLAlertLayerProtocol*, const char*,
				const char*, const char*, float, std::string)>(
					base + 0x22730
					)(target, title, btn1, btn2, width, caption);
			__asm add esp, 0x24
			return pRet;
		}
		static FLAlertLayer* create(FLAlertLayerProtocol* target, const char* title,
			const char* btn1, const char* btn2, float width, bool scroll, float height, std::string caption) {
			auto pRet = reinterpret_cast<FLAlertLayer * (__fastcall*)(FLAlertLayerProtocol*, const char*,
				const char*, const char*, float, bool, float, std::string)>(
					base + 0x227e0
					)(target, title, btn1, btn2, width, scroll, height, caption);
			__asm add esp, 0x2C
			return pRet;
		}
		bool init(FLAlertLayerProtocol* target, const char* title,
			const char* btn1, const char* btn2, float width, bool scroll, float height, std::string caption) {
			auto pRet = reinterpret_cast<FLAlertLayer * (__thiscall*)(FLAlertLayer*, FLAlertLayerProtocol*, const char*,
				const char*, const char*, float, bool, float, std::string)>(
					base + 0x228E0
					)(this, target, title, btn1, btn2, width, scroll, height, caption);
			return pRet;

		}
		void setParentFLAlert(cocos2d::CCObject* target) {
			m_pParent = target;
			//m_pTarget = target;
		}

	};
#pragma runtime_checks("s", restore)
}


#endif